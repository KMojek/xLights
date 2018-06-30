#ifndef FRACTALEFFECT_H
#define FRACTALEFFECT_H

#include "RenderableEffect.h"

class FractalEffect : public RenderableEffect
{
    public:
        FractalEffect(int id);
        virtual ~FractalEffect();
        virtual bool CanBeRandom() override {return false;}
        virtual void Render(Effect *effect, SettingsMap &settings, RenderBuffer &buffer) override;
        virtual bool SupportsLinearColorCurves(const SettingsMap &SettingsMap) override { return false; }
        virtual void SetDefaultParameters() override;

    protected:
        virtual void RemoveDefaults(const std::string &version, Effect *effect) override;
        virtual wxPanel *CreatePanel(wxWindow *parent) override;
};

#endif // FRACTALEFFECT_H
