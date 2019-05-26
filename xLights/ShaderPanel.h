#ifndef SHADERPANEL_H
#define SHADERPANEL_H

//(*Headers(ShaderPanel)
#include <wx/panel.h>
//*)

class ShaderPanel: public wxPanel
{
	public:

		ShaderPanel(wxWindow* parent,wxWindowID id=wxID_ANY,const wxPoint& pos=wxDefaultPosition,const wxSize& size=wxDefaultSize);
		virtual ~ShaderPanel();

		//(*Declarations(ShaderPanel)
		//*)

	protected:

		//(*Identifiers(ShaderPanel)
		//*)

	private:

		//(*Handlers(ShaderPanel)
		//*)

		DECLARE_EVENT_TABLE()
};

#endif
