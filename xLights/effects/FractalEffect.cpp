#include "FractalEffect.h"
#include "FractalPanel.h"

#include "../RenderBuffer.h"

#include "../../include/warp-64.xpm"
#include "../../include/warp-48.xpm"
#include "../../include/warp-32.xpm"
#include "../../include/warp-24.xpm"
#include "../../include/warp-16.xpm"

namespace
{
   /// TEMP - also in WarpEffect.cpp!!
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
      Vec2D Abs() const { return Vec2D( ::abs(x), ::abs(y) ); }
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
   /// TEMP - also in WarpEffect.cpp!!

   struct FractalEffectParams
   {
      float progress;
      Vec2D xy;
   };

   const int MaxIterations = 2;
   const float CircleSize = 1.0 / ( 3.0 * ::pow(2.0, float(MaxIterations) ) );

   xlColor fractal( double s, double t, const FractalEffectParams& params )
   {
      float invProgress = 1. - params.progress;
      float multProgress = 10. * params.progress;

      Vec2D uv( s -params.xy.x, t - params.xy.y );
      uv = uv.Rotate( -multProgress );
      uv *= RenderBuffer::sin( multProgress ) * 0.5 + 1.5;

      float ss = 0.3f;
      for ( int i = 0; i < MaxIterations; ++i )
      {
         uv = uv.Abs() - Vec2D( ss, ss );
         uv = uv.Rotate( multProgress );
         ss /= 2.1f;
      }

      return ( uv.Len() > CircleSize ) ? xlBLACK : xlWHITE;
   }
}


FractalEffect::FractalEffect(int i) : RenderableEffect(i, "Fractal", warp_16_xpm, warp_24_xpm, warp_32_xpm, warp_48_xpm, warp_64_xpm)
{

}

FractalEffect::~FractalEffect()
{

}

wxPanel *FractalEffect::CreatePanel(wxWindow *parent)
{
    return new FractalPanel( parent );
}

void FractalEffect::SetDefaultParameters()
{
    FractalPanel *p = (FractalPanel *)panel;

    p->BitmapButton_Fractal_X->SetActive( false );
    p->BitmapButton_Fractal_Y->SetActive( false );

    SetSliderValue( p->Slider_Fractal_X, 50 );
    SetSliderValue( p->Slider_Fractal_Y, 50 );
}

void FractalEffect::RemoveDefaults( const std::string &version, Effect *effect )
{
    RenderableEffect::RemoveDefaults(version, effect);
}

void FractalEffect::Render( Effect *eff, SettingsMap &SettingsMap, RenderBuffer &buffer )
{
   float progress = buffer.GetEffectTimeIntervalPosition(1.f);

   int xPercentage = GetValueCurveInt( "Fractal_X", 0, SettingsMap, progress, 0, 100 );
   int yPercentage = GetValueCurveInt( "Fractal_Y", 0, SettingsMap, progress, 0, 100 );
   double x = 0.01 * xPercentage;
   double y = 0.01 * yPercentage;

   FractalEffectParams params;
   params.progress = progress;
   params.xy = Vec2D( 0.5, 0.5 );

   for ( int y = 0; y < buffer.BufferHt; ++y )
   {
      double t = double( y ) / ( buffer.BufferHt - 1 );
      for ( int x = 0; x < buffer.BufferWi; ++x )
      {
         double s = double( x ) / ( buffer.BufferWi - 1 );
         buffer.SetPixel( x, y, fractal( s, t, params ) );
      }
   }
}
