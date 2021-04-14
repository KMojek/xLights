/***************************************************************
 * This source files comes from the xLights project
 * https://www.xlights.org
 * https://github.com/smeighan/xLights
 * See the github commit history for a record of contributing
 * developers.
 * Copyright claimed based on commit dates recorded in Github
 * License: https://github.com/smeighan/xLights/blob/master/License.txt
 **************************************************************/

#include <wx/checkbox.h>

#include <sstream>

#include "../../include/warp-64.xpm"
#include "../../include/warp-48.xpm"
#include "../../include/warp-32.xpm"
#include "../../include/warp-24.xpm"
#include "../../include/warp-16.xpm"

#include "WarpEffect.h"
#include "WarpPanel.h"
#include "../sequencer/Effect.h"
#include "../RenderBuffer.h"
#include "../UtilClasses.h"
#include "../xLightsMain.h"
#include "../DissolveTransitionPattern.h"
#include "../xLightsApp.h"
#include "../TimingPanel.h"
#include "UtilFunctions.h"

#include <log4cpp/Category.hh>

#include "../Parallel.h"

#include <cstdint>
#include <vector>

namespace
{
   template <class T> T CLAMP( const T& lo, const T&val, const T& hi )
   {
      return std::min( hi, std::max( lo, val ) );
   }

   const float PI = 3.14159265359f;

   struct Vec2D
   {
      Vec2D( double i_x = 0., double i_y = 0. ) : x( i_x ), y( i_y ) {}

      Vec2D    operator+( const Vec2D& p ) const { return Vec2D( x + p.x, y + p.y ); }
      Vec2D    operator-( const Vec2D& p ) const { return Vec2D( x - p.x, y - p.y ); }
      double   operator^( const Vec2D& p ) const { return x * p.y - y * p.x; }
      Vec2D    operator*( const double& k ) const { return Vec2D( x*k, y*k ); }
      Vec2D    operator*( const Vec2D& p ) const { return Vec2D( x * p.x, y * p.y ); }
      Vec2D    operator/( const double& k ) const { return *this * ( 1 / k ); }
      Vec2D    operator+=( const Vec2D& p ) { return *this = *this + p; }
      Vec2D    operator-=( const Vec2D& p ) { return *this = *this - p; }
      Vec2D    operator*=( const double& k ) { return *this = *this * k; }
      Vec2D    operator/=( const double& k ) { return *this = *this / k; }
      Vec2D    operator-() const { return Vec2D( -x, -y ); }
      Vec2D    Min( const Vec2D& p ) const { return Vec2D( std::min( x, p.x ), std::min( y, p.y ) ); }
      Vec2D    Max( const Vec2D& p ) const { return Vec2D( std::max( x, p.x ), std::max( y, p.y ) ); }
      double   Len2() const { return x * x + y * y; }
      double   Len() const { return ::sqrt( Len2() ); }
      double   Dist2( const Vec2D& p ) const { return ( *this - p ).Len2(); }
      double   Dist( const Vec2D& p ) const { return ( *this - p ).Len(); }
      Vec2D    Norm() const { return Len() > 0 ? *this / Len() : Vec2D( 0, 0 ); }
      bool     IsNormal() const { return fabs( Len2() - 1 ) < 1e-6; }
      Vec2D    Rotate( const double& fAngle ) const
      {
         float cs = RenderBuffer::cos( fAngle );
         float sn = RenderBuffer::sin( fAngle );
         return Vec2D( x*cs + y * sn, -x * sn + y * cs );
      }
      static Vec2D lerp( const Vec2D& a, const Vec2D& b, double progress )
      {
         double x = a.x + progress * ( b.x - a.x );
         double y = a.y + progress * ( b.y - a.y );
         return Vec2D( x, y );
      }
      double x, y;
   };
   Vec2D operator +( double a, const Vec2D& b )
   {
      return Vec2D( a + b.x, a + b.y );
   }
   Vec2D operator -( double a, const Vec2D& b )
   {
      return Vec2D( a - b.x, a - b.y );
   }
   Vec2D operator *( double a, const Vec2D& b )
   {
      return Vec2D( a * b.x, a * b.y );
   }

   double dot( const Vec2D& a, const Vec2D& b )
   {
      return a.x * b.x + a.y * b.y;
   }

   struct LinearInterpolater
   {
      double operator()( double t ) const { return t; }
   };

   template <class T> double interpolate( double x, double loIn, double loOut, double hiIn, double hiOut, const T& interpolater )
   {
      return ( loIn != hiIn )
         ? ( loOut + (hiOut - loOut) * interpolater( (x-loIn)/(hiIn-loIn) ) )
         : ( (loOut + hiOut) / 2 );
   }

   double lerp( double a, double b, double progress )
   {
      return a + progress * ( b - a );
   }
   xlColor lerp( const xlColor& a, const xlColor& b, double progress )
   {
      double red   = a.red   + progress * ( b.red   - a.red   );
      double green = a.green + progress * ( b.green - a.green );
      double blue  = a.blue  + progress * ( b.blue  - a.blue  );

      return xlColor( uint8_t( red ), uint8_t( green ), uint8_t( blue ) );
   }

   struct ColorBuffer
   {
      ColorBuffer( const xlColorVector& i_cv, int i_w, int i_h ) : cv( i_cv ), w( i_w ), h( i_h ) {}

      xlColor GetPixel( int x, int y ) const
      {
         return ( x >= 0 && x < w && y >= 0 && y <h ) ? cv[y*w + x] : xlBLACK;
      }

      const xlColorVector & cv;
      const int w;
      const int h;
   };

   xlColor tex2D( const ColorBuffer& cb, double s, double t )
   {
      s = CLAMP( 0., s, 1. );
      t = CLAMP( 0., t, 1. );

      int x = int( s * ( cb.w - 1 ) );
      int y = int( t * ( cb.h - 1 ) );

      return cb.GetPixel( x, y );
   }
   xlColor tex2D( const ColorBuffer& cb, double s, double t, const xlColor& borderColor )
   {
      if ( s < 0. || s > 1. || t < 0. || t > 1. )
         return borderColor;

      int x = int( s * ( cb.w - 1 ) );
      int y = int( t * ( cb.h - 1 ) );

      return cb.GetPixel( x, y );
   }

   xlColor dissolveTex( double s, double t )
   {
      const unsigned char *data = DissolveTransitonPattern;
      s = CLAMP( 0., s, 1. );
      t = CLAMP( 0., t, 1. );

      int x = int( s * (DissolvePatternWidth - 1 ) );
      int y = int( t * (DissolvePatternHeight -1 ) );

      const unsigned char *val = data + y * DissolvePatternWidth + x;
      return xlColor( *val, *val, *val );
   }

   struct WarpEffectParams
   {
      WarpEffectParams( float i_progress, const Vec2D& i_xy, float i_speed, float i_frequency )
         : progress(i_progress), xy(i_xy), speed(i_speed), frequency(i_frequency) {}
      float progress;
      Vec2D xy;
      float speed;
      float frequency;
   };

   float genWave( float len, float speed, float time )
   {
      float wave = RenderBuffer::sin( speed * PI * len + time );
      wave = ( wave + 1.0 ) * 0.5;
      wave -= 0.3f;
      wave *= wave * wave;
      return wave;
   }

   xlColor waterDrops( const ColorBuffer& cb, double s, double t, const WarpEffectParams& params )
   {
#define time (-params.progress * 35.0)
      Vec2D pos2( Vec2D( s, t ) - params.xy );
      Vec2D pos2n( pos2.Norm() );

      double len = pos2.Len();
      float wave = genWave( len, params.speed, time );
#undef time
      Vec2D uv2( -pos2n * wave / ( 1.0 + 5.0 * len ) );

      Vec2D st( s + uv2.x, t + uv2.y );
      return tex2D( cb, st.x, st.y );
   }

   xlColor rippleIn( const ColorBuffer& cb, double s, double t, const WarpEffectParams& params )
   {
      const double amplitude = 0.15;

      Vec2D toUV( s - params.xy.x, t - params.xy.y );
      double distanceFromCenter = toUV.Len();
      Vec2D normToUV = toUV / distanceFromCenter;

      double wave = RenderBuffer::cos( params.frequency * distanceFromCenter - params.speed * params.progress );
      double offset = params.progress * wave * amplitude;

      Vec2D newUV = params.xy + normToUV * ( distanceFromCenter + offset );

      xlColor c1 = tex2D( cb, s, t );
      xlColor c2 = tex2D( cb, newUV.x, newUV.y );

      return lerp( c2, c1, params.progress );
   }
   xlColor rippleOut( const ColorBuffer& cb, double s, double t, const WarpEffectParams& params )
   {
      const double amplitude = 0.15;

      Vec2D toUV( s - params.xy.x, t - params.xy.y );
      double distanceFromCenter = toUV.Len();
      Vec2D normToUV = toUV / distanceFromCenter;

      double wave = RenderBuffer::cos( params.frequency * distanceFromCenter - params.speed * params.progress );
      double offset = params.progress * wave * amplitude;

      Vec2D newUV = params.xy + normToUV * ( distanceFromCenter + offset );

      xlColor c1 = tex2D( cb, s, t );
      xlColor c2 = tex2D( cb, newUV.x, newUV.y );

      return lerp( c1, c2, params.progress );
   }

   xlColor dissolveIn( const ColorBuffer& cb, double s, double t, const WarpEffectParams& params )
   {
      xlColor dissolveColor = dissolveTex( s, t );
      unsigned char byteProgress = (unsigned char)( 255 * params.progress );
      return (dissolveColor.red <= byteProgress) ? tex2D( cb, s, t ) : xlBLACK;
   }
   xlColor dissolveOut( const ColorBuffer& cb, double s, double t, const WarpEffectParams& params )
   {
      xlColor dissolveColor = dissolveTex( s, t );
      unsigned char byteProgress = (unsigned char)( 255 * params.progress );
      return (dissolveColor.red > byteProgress) ? tex2D( cb, s, t ) : xlBLACK;
   }

   xlColor circleRevealIn( const ColorBuffer& cb, double s, double t, const WarpEffectParams& params )
   {
      const float FuzzyAmount = 0.04f;
      const float CircleSize = 0.60f;

      float radius = -FuzzyAmount + params.progress * (CircleSize + 2.0 * FuzzyAmount);
      float fromCenter = ( Vec2D(s,t) - params.xy).Len();
      float distFromCircle = fromCenter - radius;

      xlColor c = tex2D( cb, s, t );
      float p = CLAMP((distFromCircle + FuzzyAmount) / (2.0 * FuzzyAmount), 0., 1. );
      return lerp( c, xlBLACK, p );
   }
   xlColor circleRevealOut( const ColorBuffer& cb, double s, double t, const WarpEffectParams& params )
   {
      const float FuzzyAmount = 0.04f;
      const float CircleSize = 0.60f;

      float radius = -FuzzyAmount + (1-params.progress) * (CircleSize + 2.0 * FuzzyAmount);
      float fromCenter = ( Vec2D(s,t) - params.xy).Len();
      float distFromCircle = fromCenter - radius;

      xlColor c = tex2D( cb, s, t );
      float p = CLAMP((distFromCircle + FuzzyAmount) / (2.0 * FuzzyAmount), 0., 1. );
      return lerp( c, xlBLACK, p );
   }

   xlColor bandedSwirlIn( const ColorBuffer& cb, double s, double t, const WarpEffectParams& params )
   {
      const double TwistAmount = 1.6;

      Vec2D toUV( Vec2D( s, t ) - params.xy );
      double distanceFromCenter = toUV.Len();
      Vec2D normToUV( toUV / distanceFromCenter );
      float angle = ::atan2( normToUV.y, normToUV.x );

      angle += RenderBuffer::sin( distanceFromCenter * params.frequency ) * TwistAmount * (1 - params.progress);
      Vec2D newUV( RenderBuffer::cos( angle ), RenderBuffer::sin( angle ) );
      newUV = newUV * distanceFromCenter + params.xy;

      xlColor c1 = tex2D( cb, s, t );
      xlColor c2 = tex2D( cb, newUV.x, newUV.y );

      return lerp( c1, c2, params.progress );
   }
   xlColor bandedSwirlOut( const ColorBuffer& cb, double s, double t, const WarpEffectParams& params )
   {
      const double TwistAmount = 1.6;

      Vec2D toUV( Vec2D( s, t ) - params.xy );
      double distanceFromCenter = toUV.Len();
      Vec2D normToUV( toUV / distanceFromCenter );
      float angle = ::atan2( normToUV.y, normToUV.x );

      angle += RenderBuffer::sin( distanceFromCenter * params.frequency ) * TwistAmount * params.progress;
      Vec2D newUV( RenderBuffer::cos( angle ), RenderBuffer::sin( angle ) );
      newUV = newUV * distanceFromCenter + params.xy;

      xlColor c1 = tex2D( cb, s, t );
      xlColor c2 = tex2D( cb, newUV.x, newUV.y );

      return lerp( c2, c1, params.progress );
   }

   const float dropletExpandSpeed = 1.5;
   const float dropletHeightFactor = 0.3f;
   const float dropletRipple = /*80.0*/60.0; // possible progress

   float getDropletHeight( const Vec2D& uv, const Vec2D& dropletPosition, float time )
   {
      float decayRate = 0.5; // smaller = faster drops
      float dropletStrength = 1.0; // larger = bigger impact (0.5 min)
      float dropletStrengthBias = 0.6f;
      float dropFraction = time / decayRate;
      float dummy;
      dropFraction = std::modf( dropFraction, &dummy );

      float ringRadius = dropletExpandSpeed * dropFraction * dropletStrength - dropletStrengthBias;
      float distanceToDroplet = Vec2D( uv - dropletPosition ).Len();

      float dropletHeight = distanceToDroplet > ringRadius ? 0.0 : distanceToDroplet;
      dropletHeight = RenderBuffer::cos(PI + (dropletHeight - ringRadius) * dropletRipple * dropletStrength) * 0.5 + 0.5;
      dropletHeight *= 1.0 - dropFraction;
      dropletHeight *= distanceToDroplet > ringRadius ? 0.0 : distanceToDroplet / ringRadius;

      return (1.0 - (RenderBuffer::cos(dropletHeight * PI) + 1.0) * 0.5) * dropletHeightFactor;
   }

   xlColor singleWaterDrop( const ColorBuffer& cb, double s, double t, const WarpEffectParams& params )
   {
      Vec2D uv( s, t );
      Vec2D pos2( uv - params.xy );
      Vec2D pos2n( pos2.Norm() );

      float dh = getDropletHeight( uv - Vec2D( 0.5,0.5 ), params.xy - Vec2D( 0.5, 0.5 ), params.progress );
      Vec2D uv2 = -pos2n * dh / ( 1.0 + 3.0 * pos2.Len() );

      return tex2D( cb, uv.x + uv2.x, uv.y + uv2.y );
   }

   xlColor circularSwirl( const ColorBuffer& cb, double s, double t, const WarpEffectParams& params )
   {
      Vec2D uv( s, t );
      Vec2D dir( uv - params.xy );
      double len = dir.Len();

      double radius = (1. - params.progress) * 0.70710678;
      if ( len < radius )
      {
         Vec2D rotated( dir.Rotate( -params.speed * len * params.progress * PI ) );
         Vec2D scaled( rotated * (1. - params.progress) + params.xy );

         Vec2D newUV( Vec2D::lerp( params.xy, scaled, 1. - params.progress ) );

         return tex2D( cb, newUV.x, newUV.y );
      }

      return xlBLACK;
   }

   xlColor drop( const ColorBuffer& cb, double s, double t, const WarpEffectParams& params )
   {
      const double notSoRandomY = 0.16;
      float noise = dissolveTex( s, notSoRandomY ).red / 255.f;

      return tex2D( cb, s, t + noise * params.progress );
   }

   Vec2D noiseVec( const Vec2D& p )
   {
      xlColor noiseColor = dissolveTex( p.x, p.y );
      double c = noiseColor.red / 255.;

      return Vec2D( c, c );
   }

   double noise( const Vec2D& p )
   {
      Vec2D i, f;
      f.x = std::modf( p.x, &i.x );
      f.y = std::modf( p.y, &i.y );

      Vec2D u( f * f * (3. - (2. * f) ) );

      Vec2D aa( noiseVec( i + Vec2D(0.,0.) ) );
      Vec2D bb( f - Vec2D(0.,0.) );
      Vec2D cc( noiseVec( i + Vec2D(1.,0.) ) );
      Vec2D dd( f - Vec2D(1.,0.) );
      Vec2D ee( noiseVec( i + Vec2D(0.,1.) ) );
      Vec2D ff( f - Vec2D(0.,1.) );
      Vec2D gg( noiseVec( i + Vec2D(1.,1.) ) );
      Vec2D hh( f - Vec2D(1.,1.) );

      double ab = dot( aa, bb );
      double cd = dot( cc, dd );
      double ef = dot( ee, ff );
      double gh = dot( gg, hh );

      double foo = lerp( ab, cd, u.x );
      double bar = lerp( ef, gh, u.x );

      return lerp( foo, bar, u.y );
   }

   xlColor mirror(const ColorBuffer& cb, double s, double t, const WarpEffectParams& params)
   {
       Vec2D uv(s, t);
       Vec2D pos2(uv);
       if (uv.x > params.xy.x)            {
           pos2.x = 2 * params.xy.x - uv.x;
       }
       if (uv.y > params.xy.y) {
           pos2.y = 2 * params.xy.y - uv.y;
       }

       return tex2D(cb, pos2.x, pos2.y, xlBLACK);
   }

   xlColor copy(const ColorBuffer& cb, double s, double t, const WarpEffectParams& params)
   {
       Vec2D uv(s, t);
       Vec2D pos2(uv);

       if (pos2.x > params.xy.x) pos2.x -= params.xy.x;
       if (pos2.y > params.xy.y) pos2.y -= params.xy.y;

       return tex2D(cb, pos2.x, pos2.y, xlBLACK);
   }

   xlColor wavy( const ColorBuffer& cb, double s, double t, const WarpEffectParams& params )
   {
      Vec2D uv( s, t );

      double time = params.speed * params.progress;

      uv.x += 0.4 * noise( time + 0.3 * uv );
      uv.y += 0.5 * noise( time + 0.5 * uv );

      return tex2D( cb, uv.x, uv.y, xlBLACK );
   }

   class FloatColorBuffer
   {
   public:
      FloatColorBuffer( int width, int height )
         : _width( width )
         , _height( height )
      {
         _cb.resize( width * 4 * height );
      }
      FloatColorBuffer( const RenderBuffer& rb )
         : _width( rb.BufferWi )
         , _height( rb.BufferHt )
      {
         int stride = 4 * _width;
         const xlColorVector& cv( rb.pixels );
         int cvIndex = 0, cbIndex = 0;
         const double mult = 1. / 255;

         _cb.resize( stride * _height );
         for ( int y = 0; y < _height; ++y)
         {
            for ( int x = 0; x < _width; ++x )
            {
               xlColor c( cv[cvIndex++] );
               _cb[cbIndex++] = mult * c.red;
               _cb[cbIndex++] = mult * c.green;
               _cb[cbIndex++] = mult * c.blue;
               _cb[cbIndex++] = mult * c.alpha;
            }
         }
      }

      xlColorVector asColorVector() const
      {
         xlColorVector ret( _width * 4 * _height );
         int cbIndex = 0, cvIndex = 0;
         for ( int y = 0; y < _height; ++y )
         {
            for ( int x = 0; x < _width; ++x, ++cvIndex, cbIndex += 4 )
            {
               xlColor c( static_cast<uint8_t>( _cb[cbIndex] * 255 ), static_cast<uint8_t>( _cb[1+cbIndex] * 255 ), static_cast<uint8_t>( _cb[2+cbIndex] * 255 ), static_cast<uint8_t>( _cb[3+cbIndex] * 255 ) );
               ret[cvIndex] = c;
            }
         }
         return ret;
      }

      const float& at( int i ) const
      {
         return _cb[ static_cast<std::vector<float>::size_type>( i ) ];
      }
      float& at( int i )
      {
         return _cb[ static_cast<std::vector<float>::size_type>( i ) ];
      }

      int width() const { return _width; }
      int height() const { return _height; }
      //std::vector<float>& cb() { return _cb; }

      const float* tex( double s, double t ) const
      {
         s = CLAMP( 0., s, 1. );
         t = CLAMP( 0., t, 1. );

         int x = static_cast<int>( std::floor( s * (_width - 1) ) );
         int y = static_cast<int>( std::floor( t * (_height - 1) ) );
         int index = y * 4 * _width + x * 4;
         return _cb.data() + index;
      }

      float* at( double s, double t )
      {
         s = CLAMP( 0., s, 1. );
         t = CLAMP( 0., t, 1. );

         int x = static_cast<int>( s * (_width - 1) );
         int y = static_cast<int>( t * (_height - 1) );
         int index = y * 4 * _width + x * 4;
         return _cb.data() + index;
      }

   protected:
      const int               _width;
      const int               _height;
      std::vector<float> _cb;
   };

   void zoomWarp( FloatColorBuffer& fcb, double s, double t, float progress )
   {
   #if 0
      const float scale = 2.f;

      Vec2D p1( s, t );
      Vec2D p2( (0.5 + (p1.x - 0.5) / scale ), ( 0.5 + (p1.y - 0.5 ) / scale ) );
      double interpol = 1. - ( std::abs( progress - 0.5 ) * 2.0 );
      Vec2D p3( Vec2D::lerp( p1, p2, interpol ) );
      float newColor[4] = {  0.f, 0.f, 0.f, 1.f };
      if ( progress < 0.5 )
         memcpy( newColor, fcb.tex( p3.x, p3.y ), sizeof(float[4]) );

      const float* tv = fcb.tex( p3.x, p3.y );
      double foo = lerp( 0.0, 1.0, interpol );
#endif
      float* bar = fcb.at( s, t );
      bar[0] = /*tv[0] +foo*/0.f;
      bar[1] = /*tv[1] +foo*/1.f;
      bar[2] = /*tv[2] +foo*/0.f;
      bar[3] = /*tv[3] +foo*/1.f;
   }

   void RenderGlowWarp(  RenderBuffer& rb, const WarpEffectParams& params )
   {
      // todo
      // 1) save off original image
      // 2) adjust brightness ( drawLuminance( float ( 1 - _Intensity ), 1. )
      // 3) blur
      // 4) color-adjust
      // 5) "bloom" combines (1) with result of (2..4)

      FloatColorBuffer origImage( rb );
      //FloatColorBuffer imageToAdjust( origImage );

      AudioManager* audioManager = rb.GetMedia();
      if ( audioManager == nullptr )
         return;

      auto highData = audioManager->GetFrameData( rb.curPeriod, FRAMEDATA_HIGH, "" );
      auto lowData = audioManager->GetFrameData( rb.curPeriod, FRAMEDATA_LOW, "" );
      auto spreadData = audioManager->GetFrameData( rb.curPeriod, FRAMEDATA_SPREAD, "" );
      auto fftData = audioManager->GetFrameData( rb.curPeriod, FRAMEDATA_VU, "" );

      std::vector<float> fft128( fftData->cbegin(), fftData->cend() );
      fft128.push_back( 0.f );
      //float minValue = 10e10f, maxValue = -10e10f;
      //for ( auto v : fft128 )
      //{
      //   minValue = std::min( v, minValue );
      //   maxValue = std::max( v, maxValue );
      //}
      //static log4cpp::Category& logger_base = log4cpp::Category::getInstance(std::string("log_base"));
      //logger_base.warn( "FFT values (low, high, spread) : %f (%d)   %f (%d)   %f (%d)",
      //   lowData->front(), int( lowData->size() ), highData->front(), int( highData->size() ), spreadData->front(), int( spreadData->size() ) );
      //int index = 0;

      for ( int y = 0; y < rb.BufferHt; ++y )
      {
         double t = double ( y ) / ( rb.BufferHt - 1);
         for ( int x = 0; x < rb.BufferWi; ++x )
         {
            double s = double( x ) / (rb.BufferWi - 1 );
            zoomWarp( origImage, s, t, params.progress );
            //double sScaled = 128 * s;
            //int fftIndex = (int)std::floor( sScaled );
            //fftIndex = std::min( fftIndex, 127 );

            // hmm... just playing with colors isn't all that interesting...
#if 0
            float r = origImage.at( index );
            float g = origImage.at( index+1 );
            float b = origImage.at( index+2 );

            double luminance = 0.2126 * r + 0.7152 * g + 0.0722 * b;
            double u = -0.09991 * r - 0.33609 * g + 0.436 * b;
            double v = 0.615 * r - 0.55861 * g - 0.05639 * b;

            // FFT seems to be in [0,1] range
            // It's unclear what low/high/spread do exactly
            //double avg = ( lowData->front() + highData->front() ) / 2.0;
            //luminance = avg;
            //luminance = std::max( luminance, static_cast<double>( spreadData->front() ) );
            //luminance = (1/2.5) * luminance * /*fft128[fftIndex]*/highData->front();
            //u += 0.5 * lowData->front();
            //v -= 0.5 * lowData->front();
            //luminance += 0.05 * lowData->front();
            //luminance *= /*lowData*/highData->front();
            //luminance = CLAMP( 0., luminance * fft128[fftIndex], 1.0 );
            //u = v = 0.f;

            origImage.at( index ) = CLAMP( 0.0, luminance + 1.28033 * v, 1.0 );
            origImage.at( index + 1 ) = CLAMP( 0.0, luminance - 0.21482 * u - 0.38059 * v, 1.0 );
            origImage.at( index + 2 ) = CLAMP( 0.0, luminance + 2.12798 * u, 1.0 );

            index += 4;
#endif
            //rb.SetPixel( x, y, xlColor( 0, 0, 128, 255 ) );
         }
      }

      rb.pixels = std::move( origImage.asColorVector() );
   }


   typedef xlColor( *PixelTransform ) ( const ColorBuffer& cb, double s, double t, const WarpEffectParams& params );

   void RenderSampleOn(RenderBuffer& rb, double x, double y)
   {
       int xx = x * (rb.BufferWi - 1);
       int yy = y * (rb.BufferHt - 1);
       xlColor c = rb.GetPixel(xx, yy);

       for (int yyy = 0; yyy < rb.BufferHt; ++yyy)
       {
           for (int xxx = 0; xxx < rb.BufferWi; ++xxx)
           {
               rb.SetPixel(xxx, yyy, c);
           }
       }
   }

   void RenderPixelTransform( PixelTransform transform, RenderBuffer& rb, const WarpEffectParams& params )
   {
      xlColorVector cvOrig( rb.pixels );
      ColorBuffer cb( cvOrig, rb.BufferWi, rb.BufferHt );

      parallel_for(0, rb.BufferHt, [&rb, &cb, &transform, &params](int y) {
         double t = double( y ) / ( rb.BufferHt - 1 );
         for ( int x = 0; x < rb.BufferWi; ++x ) {
            double s = double( x ) / ( rb.BufferWi - 1 );
            rb.SetPixel( x, y, transform( cb, s, t, params ) );
         }
      }, 25);
   }
}

WarpEffect::WarpEffect( int id ) : RenderableEffect( id, "Warp", warp_16_xpm, warp_24_xpm, warp_32_xpm, warp_48_xpm, warp_64_xpm )
{

}

WarpEffect::~WarpEffect()
{

}

xlEffectPanel *WarpEffect::CreatePanel(wxWindow *parent)
{
    return new WarpPanel(parent);
}

bool WarpEffect::needToAdjustSettings(const std::string &version)
{
    return IsVersionOlder("2018.20", version);
}

void WarpEffect::adjustSettings(const std::string &version, Effect *effect, bool removeDefaults)
{
    SettingsMap &settings = effect->GetSettings();

    auto treatment = settings.Get("E_CHOICE_Warp_Treatment", "");
    if (treatment != "")
    {
        settings["E_CHOICE_Warp_Treatment_APPLYLAST"] = treatment;
        settings.erase("E_CHOICE_Warp_Treatment");
    }

    // also give the base class a chance to adjust any settings
    if (RenderableEffect::needToAdjustSettings(version))
    {
        RenderableEffect::adjustSettings(version, effect, removeDefaults);
    }
}

std::list<std::string> WarpEffect::CheckEffectSettings(const SettingsMap& settings, AudioManager* media, Model* model, Effect* eff, bool renderCache)
{
    std::list<std::string> res;

    if (settings.Get("T_CHECKBOX_Canvas", "0") == "0")
    {
        res.push_back(wxString::Format("    WARN: Canvas mode not enabled on a warp effect. Without canvas mode warp won't do anything. Effect: Warp, Model: %s, Start %s", model->GetFullName(), FORMATTIME(eff->GetStartTimeMS())).ToStdString());
    }

    return res;
}

void WarpEffect::SetDefaultParameters()
{
    WarpPanel *p = (WarpPanel *)panel;

    p->BitmapButton_Warp_X->SetActive( false );
    p->BitmapButton_Warp_Y->SetActive( false );

    p->Choice_Warp_Type->SetSelection( 0 );
    p->Choice_Warp_Treatment->SetSelection( 0 );

    SetSliderValue( p->Slider_Warp_X, 50 );

    SetSliderValue( p->Slider_Warp_Y, 50 );

    SetSliderValue( p->Slider_Warp_Cycle_Count, 1 );

    SetSliderValue( p->Slider_Warp_Speed, 20 );

    SetSliderValue( p->Slider_Warp_Frequency, 20 );

    // Turn on canvas mode as this really only makes sense in canvas mode
    xLightsFrame* frame = xLightsApp::GetFrame();
    TimingPanel* layerBlendingPanel = frame->GetLayerBlendingPanel();
    layerBlendingPanel->CheckBox_Canvas->SetValue(true);
}

void WarpEffect::RemoveDefaults(const std::string &version, Effect *effect)
{
    SettingsMap &settingsMap = effect->GetSettings();

    if ( settingsMap.Get( "E_CHOICE_Warp_Type", "" )== "water drops" )
      settingsMap.erase( "E_CHOICE_Warp_Type" );
    if ( settingsMap.Get( "E_CHOICE_Warp_Treatment_APPLYLAST", "" )== "constant" )
      settingsMap.erase( "E_CHOICE_Warp_Treatment_APPLYLAST" );
    if ( settingsMap.Get( "E_TEXTCTRL_Warp_Cycle_Count", "" ) == "1" )
      settingsMap.erase( "E_TEXTCTRL_Warp_Cycle_Count" );
    if ( settingsMap.Get( "E_TEXTCTRL_Warp_Speed", "" )== "20" )
      settingsMap.erase( "E_TEXTCTRL_Warp_Speed" );
    if ( settingsMap.Get( "E_TEXTCTRL_Warp_Frequency", "" )== "20" )
      settingsMap.erase( "E_TEXTCTRL_Warp_Frequency" );

    RenderableEffect::RemoveDefaults(version, effect);
}

void WarpEffect::Render(Effect *eff, SettingsMap &SettingsMap, RenderBuffer &buffer)
{
   float progress = buffer.GetEffectTimeIntervalPosition(1.f);

   std::string warpType = SettingsMap.Get( "CHOICE_Warp_Type", "water drops" );
   std::string warpTreatment = SettingsMap.Get( "CHOICE_Warp_Treatment_APPLYLAST", "constant");
   std::string warpStrCycleCount = SettingsMap.Get( "TEXTCTRL_Warp_Cycle_Count", "1" );
   std::string speedStr = SettingsMap.Get( "TEXTCTRL_Warp_Speed", "20" );
   std::string freqStr = SettingsMap.Get( "TEXTCTRL_Warp_Frequency", "20" );
   int xPercentage = GetValueCurveInt( "Warp_X", 0, SettingsMap, progress, 0, 100, buffer.GetStartTimeMS(), buffer.GetEndTimeMS());
   int yPercentage = GetValueCurveInt( "Warp_Y", 0, SettingsMap, progress, 0, 100, buffer.GetStartTimeMS(), buffer.GetEndTimeMS());
   double x = 0.01 * xPercentage;
   double y = 0.01 * yPercentage;
   float speed = std::stof( speedStr );
   float frequency = std::stof( freqStr );

   WarpEffectParams params( progress, Vec2D( x, y ), speed, frequency );
   if ( warpType == "water drops" )
      RenderPixelTransform( waterDrops, buffer, params );
   else if (warpType == "sample on")
   {
       RenderSampleOn(buffer, x, y);
   }
   else if ( warpType == "wavy" )
   {
      LinearInterpolater interpolater;
      params.speed = interpolate( params.speed, 0.0,0.5, 40.0,5.0, interpolater );

      RenderPixelTransform( wavy, buffer, params );
   }
   else if (warpType == "mirror") {
       RenderPixelTransform(mirror, buffer, params);
   }
   else if (warpType == "copy") {
       RenderPixelTransform(copy, buffer, params);
   }
   else if ( warpType == "single water drop" )
   {
      float cycleCount = std::stof( warpStrCycleCount );
      float intervalLen = 1.f / cycleCount;
      float scaledProgress = progress / intervalLen;
      float intervalProgress, intervalIndex;
      intervalProgress = std::modf( scaledProgress, &intervalIndex );

      LinearInterpolater interpolater;
      float interpolatedProgress = interpolate( intervalProgress, 0.0,0.20, 1.0,0.45, interpolater );

      params.progress = interpolatedProgress;
      RenderPixelTransform( singleWaterDrop, buffer, params );
   }
   else if ( warpType == "glow" )
   {
      //RenderPixelTransform( glow, buffer, params );
      RenderGlowWarp( buffer, params );
   }
   else
   {
      PixelTransform xform = nullptr;
      // the other warps were originally intended as transitions in or out... for constant
      // treatment, we'll just cycle between progress of [0,1] and [1,0]. "constant" wasn't
      // a very good description, maybe back-and-forth or something would be more accurate
      if ( warpTreatment == "constant" )
      {
         float cycleCount = std::stof( warpStrCycleCount );
         float intervalLen = 1.f / (2 * cycleCount );
         float scaledProgress = progress / intervalLen;
         float intervalProgress, intervalIndex;
         intervalProgress = std::modf( scaledProgress, &intervalIndex );
         if ( int(intervalIndex) % 2 )
            intervalProgress = 1.f - intervalProgress;
         params.progress = intervalProgress;
         if ( warpType == "ripple" )
            xform = rippleIn;
         else if ( warpType == "dissolve" )
            xform = dissolveIn;
         else if ( warpType == "banded swirl" )
            xform = bandedSwirlIn;
         else if ( warpType == "circle reveal" )
            xform = circleRevealIn;
         else if ( warpType == "circular swirl" )
         {
            params.progress = 1. - params.progress;
            xform = circularSwirl;
         }
         else if ( warpType == "drop" )
         {
            params.progress = 1. - params.progress;
            xform = drop;
         }
      }
      else
      {
         if ( warpType == "ripple" )
            xform = ( warpTreatment == "in" )? rippleIn : rippleOut;
         else if ( warpType == "dissolve" )
            xform = ( warpTreatment == "in" ) ? dissolveIn : dissolveOut;
         else if ( warpType == "banded swirl" )
            xform = ( warpTreatment == "in" ) ? bandedSwirlIn : bandedSwirlOut;
         else if ( warpType == "circle reveal" )
            xform = ( warpTreatment == "in" ) ? circleRevealIn : circleRevealOut;
         else if ( warpType == "circular swirl" )
            xform = circularSwirl;
         else if ( warpType == "drop" )
         {
            xform = drop;
            if ( warpTreatment == "in" )
               params.progress = 1. - params.progress;
         }
      }

      if ( warpType == "circular swirl" )
      {
         params.speed = interpolate( params.speed, 0.0, 1.0, 40.0, 9.0, LinearInterpolater() );
         if ( warpTreatment == "in" )
            params.progress = 1. - params.progress;
      }

      if ( xform != nullptr )
         RenderPixelTransform( xform, buffer, params );
   }
}
