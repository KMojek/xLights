#include "FractalPanel.h"
#include "EffectPanelUtils.h"

//(*InternalHeaders(FractalPanel)
#include <wx/intl.h>
#include <wx/string.h>
//*)

//(*IdInit(FractalPanel)
const long FractalPanel::ID_STATICTEXT2 = wxNewId();
const long FractalPanel::ID_SLIDER_Fractal_X = wxNewId();
const long FractalPanel::ID_VALUECURVE_Fractal_X = wxNewId();
const long FractalPanel::ID_TEXTCTRL_Fractal_X = wxNewId();
const long FractalPanel::ID_STATICTEXT1 = wxNewId();
const long FractalPanel::ID_SLIDER_Fractal_Y = wxNewId();
const long FractalPanel::ID_VALUECURVE_Fractal_Y = wxNewId();
const long FractalPanel::ID_TEXTCTRL_Fractal_Y = wxNewId();
const long FractalPanel::ID_STATICTEXT3 = wxNewId();
const long FractalPanel::ID_SLIDER_Fractal_Iterations = wxNewId();
const long FractalPanel::ID_VALUECURVE_Fractal_Iterations = wxNewId();
const long FractalPanel::ID_TEXTCTRL_Fractal_Iterations = wxNewId();
//*)

BEGIN_EVENT_TABLE(FractalPanel,wxPanel)
	//(*EventTable(FractalPanel)
	//*)
END_EVENT_TABLE()

FractalPanel::FractalPanel(wxWindow* parent,wxWindowID id,const wxPoint& pos,const wxSize& size)
{
	//(*Initialize(FractalPanel)
	wxFlexGridSizer* FlexGridSizer1;
	wxFlexGridSizer* FlexGridSizer2;
	wxFlexGridSizer* FlexGridSizer3;
	wxFlexGridSizer* FlexGridSizer4;

	Create(parent, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL, _T("wxID_ANY"));
	FlexGridSizer1 = new wxFlexGridSizer(0, 2, 0, 0);
	FlexGridSizer1->AddGrowableCol(1);
	StaticText2 = new wxStaticText(this, ID_STATICTEXT2, _("X"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT2"));
	FlexGridSizer1->Add(StaticText2, 1, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 2);
	FlexGridSizer2 = new wxFlexGridSizer(0, 3, 0, 0);
	FlexGridSizer2->AddGrowableCol(0);
	Slider_Fractal_X = new BulkEditSlider(this, ID_SLIDER_Fractal_X, 50, 0, 100, wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_SLIDER_Fractal_X"));
	FlexGridSizer2->Add(Slider_Fractal_X, 1, wxALL|wxEXPAND, 5);
	BitmapButton_Fractal_X = new BulkEditValueCurveButton(this, ID_VALUECURVE_Fractal_X, wxNullBitmap, wxDefaultPosition, wxDefaultSize, wxBU_AUTODRAW|wxNO_BORDER, wxDefaultValidator, _T("ID_VALUECURVE_Fractal_X"));
	FlexGridSizer2->Add(BitmapButton_Fractal_X, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	TextCtrl_Fractal_X = new BulkEditTextCtrl(this, ID_TEXTCTRL_Fractal_X, _("50"), wxDefaultPosition, wxDLG_UNIT(this,wxSize(20,-1)), 0, wxDefaultValidator, _T("ID_TEXTCTRL_Fractal_X"));
	FlexGridSizer2->Add(TextCtrl_Fractal_X, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	FlexGridSizer1->Add(FlexGridSizer2, 1, wxALL|wxEXPAND, 2);
	StaticText1 = new wxStaticText(this, ID_STATICTEXT1, _("Y"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT1"));
	FlexGridSizer1->Add(StaticText1, 1, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 2);
	FlexGridSizer3 = new wxFlexGridSizer(0, 3, 0, 0);
	FlexGridSizer3->AddGrowableCol(0);
	Slider_Fractal_Y = new BulkEditSlider(this, ID_SLIDER_Fractal_Y, 50, 0, 100, wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_SLIDER_Fractal_Y"));
	FlexGridSizer3->Add(Slider_Fractal_Y, 1, wxALL|wxEXPAND, 5);
	BitmapButton_Fractal_Y = new BulkEditValueCurveButton(this, ID_VALUECURVE_Fractal_Y, wxNullBitmap, wxDefaultPosition, wxDefaultSize, wxBU_AUTODRAW|wxNO_BORDER, wxDefaultValidator, _T("ID_VALUECURVE_Fractal_Y"));
	FlexGridSizer3->Add(BitmapButton_Fractal_Y, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	TextCtrl_Fractal_Y = new BulkEditTextCtrl(this, ID_TEXTCTRL_Fractal_Y, _("50"), wxDefaultPosition, wxDLG_UNIT(this,wxSize(20,-1)), 0, wxDefaultValidator, _T("ID_TEXTCTRL_Fractal_Y"));
	FlexGridSizer3->Add(TextCtrl_Fractal_Y, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	FlexGridSizer1->Add(FlexGridSizer3, 1, wxALL|wxEXPAND, 2);
	StaticText3 = new wxStaticText(this, ID_STATICTEXT3, _("Iterations"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT3"));
	FlexGridSizer1->Add(StaticText3, 1, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	FlexGridSizer4 = new wxFlexGridSizer(0, 3, 0, 0);
	FlexGridSizer4->AddGrowableCol(0);
	Slider_Fractal_Iterations = new BulkEditSlider(this, ID_SLIDER_Fractal_Iterations, 3, 0, 10, wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_SLIDER_Fractal_Iterations"));
	FlexGridSizer4->Add(Slider_Fractal_Iterations, 1, wxALL|wxEXPAND, 5);
	BitmapButton_Fractal_Iterations = new BulkEditValueCurveButton(this, ID_VALUECURVE_Fractal_Iterations, wxNullBitmap, wxDefaultPosition, wxDefaultSize, wxBU_AUTODRAW|wxNO_BORDER, wxDefaultValidator, _T("ID_VALUECURVE_Fractal_Iterations"));
	FlexGridSizer4->Add(BitmapButton_Fractal_Iterations, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	TextCtrl_Fractal_Iterations = new BulkEditTextCtrl(this, ID_TEXTCTRL_Fractal_Iterations, _("3"), wxDefaultPosition, wxDLG_UNIT(this,wxSize(20,-1)), 0, wxDefaultValidator, _T("ID_TEXTCTRL_Fractal_Iterations"));
	FlexGridSizer4->Add(TextCtrl_Fractal_Iterations, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	FlexGridSizer1->Add(FlexGridSizer4, 1, wxALL|wxEXPAND, 2);
	SetSizer(FlexGridSizer1);
	FlexGridSizer1->Fit(this);
	FlexGridSizer1->SetSizeHints(this);
	//*)
}

FractalPanel::~FractalPanel()
{
	//(*Destroy(FractalPanel)
	//*)
}

