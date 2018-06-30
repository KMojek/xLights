#ifndef FRACTALPANEL_H
#define FRACTALPANEL_H

#include "BulkEditControls.h"

//(*Headers(FractalPanel)
#include <wx/bmpbuttn.h>
#include <wx/panel.h>
#include <wx/sizer.h>
#include <wx/slider.h>
#include <wx/stattext.h>
#include <wx/textctrl.h>
//*)

class FractalPanel: public wxPanel
{
	public:

		FractalPanel(wxWindow* parent,wxWindowID id=wxID_ANY,const wxPoint& pos=wxDefaultPosition,const wxSize& size=wxDefaultSize);
		virtual ~FractalPanel();

		//(*Declarations(FractalPanel)
		BulkEditSlider* Slider_Fractal_Iterations;
		BulkEditSlider* Slider_Fractal_X;
		BulkEditSlider* Slider_Fractal_Y;
		BulkEditTextCtrl* TextCtrl_Fractal_Iterations;
		BulkEditTextCtrl* TextCtrl_Fractal_X;
		BulkEditTextCtrl* TextCtrl_Fractal_Y;
		BulkEditValueCurveButton* BitmapButton_Fractal_Iterations;
		BulkEditValueCurveButton* BitmapButton_Fractal_X;
		BulkEditValueCurveButton* BitmapButton_Fractal_Y;
		wxStaticText* StaticText1;
		wxStaticText* StaticText2;
		wxStaticText* StaticText3;
		//*)

	protected:

		//(*Identifiers(FractalPanel)
		static const long ID_STATICTEXT2;
		static const long ID_SLIDER_Fractal_X;
		static const long ID_VALUECURVE_Fractal_X;
		static const long ID_TEXTCTRL_Fractal_X;
		static const long ID_STATICTEXT1;
		static const long ID_SLIDER_Fractal_Y;
		static const long ID_VALUECURVE_Fractal_Y;
		static const long ID_TEXTCTRL_Fractal_Y;
		static const long ID_STATICTEXT3;
		static const long ID_SLIDER_Fractal_Iterations;
		static const long ID_VALUECURVE_Fractal_Iterations;
		static const long ID_TEXTCTRL_Fractal_Iterations;
		//*)

	private:

		//(*Handlers(FractalPanel)
		//*)

		DECLARE_EVENT_TABLE()
};

#endif
