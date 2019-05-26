#include "ShaderPanel.h"

//(*InternalHeaders(ShaderPanel)
#include <wx/intl.h>
#include <wx/string.h>
//*)

//(*IdInit(ShaderPanel)
//*)

BEGIN_EVENT_TABLE(ShaderPanel,wxPanel)
	//(*EventTable(ShaderPanel)
	//*)
END_EVENT_TABLE()

ShaderPanel::ShaderPanel(wxWindow* parent,wxWindowID id,const wxPoint& pos,const wxSize& size)
{
	//(*Initialize(ShaderPanel)
	Create(parent, id, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL, _T("id"));
	//*)
}

ShaderPanel::~ShaderPanel()
{
	//(*Destroy(ShaderPanel)
	//*)
}

