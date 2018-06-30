#include "FractalEffect.h"
#include "FractalPanel.h"

#include "../RenderBuffer.h"

#include "../../include/warp-64.xpm"
#include "../../include/warp-48.xpm"
#include "../../include/warp-32.xpm"
#include "../../include/warp-24.xpm"
#include "../../include/warp-16.xpm"


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

void FractalEffect::Render(Effect *eff, SettingsMap &SettingsMap, RenderBuffer &buffer)
{
   float progress = buffer.GetEffectTimeIntervalPosition(1.f);

   int xPercentage = GetValueCurveInt( "Fractal_X", 0, SettingsMap, progress, 0, 100 );
   int yPercentage = GetValueCurveInt( "Fractal_Y", 0, SettingsMap, progress, 0, 100 );
   double x = 0.01 * xPercentage;
   double y = 0.01 * yPercentage;
}
