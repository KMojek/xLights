#pragma once

/***************************************************************
 * This source files comes from the xLights project
 * https://www.xlights.org
 * https://github.com/smeighan/xLights
 * See the github commit history for a record of contributing
 * developers.
 * Copyright claimed based on commit dates recorded in Github
 * License: https://github.com/smeighan/xLights/blob/master/License.txt
 **************************************************************/

#include "RenderableEffect.h"

class WarpEffect : public RenderableEffect
{
    public:
        WarpEffect(int id);
        virtual ~WarpEffect();

        // RenderableEffect impl
        bool CanBeRandom() override {return false;}
        void Render(Effect *effect, SettingsMap &settings, RenderBuffer &buffer) override;
        bool SupportsLinearColorCurves(const SettingsMap &SettingsMap) const override { return false; }
        void SetDefaultParameters() override;
        bool needToAdjustSettings(const std::string &version) override;
        void adjustSettings(const std::string &version, Effect *effect, bool removeDefaults = true) override;
        std::list<std::string> CheckEffectSettings(const SettingsMap& settings, AudioManager* media, Model* model, Effect* eff, bool renderCache) override;

    protected:
        void RemoveDefaults(const std::string &version, Effect *effect) override;
        xlEffectPanel *CreatePanel(wxWindow *parent) override;
};
