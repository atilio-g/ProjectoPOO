#include <wx/image.h>
#include "Application.h"
#include "WinPrincipalHija.h"


IMPLEMENT_APP(Application)

Application::Application() : m_gestor("insumos.dat", "recetas.dat", "config.dat")
{
}
	
bool Application::OnInit() {
	//wxInitAllImageHandlers();
	WinPrincipalHija *frame = new WinPrincipalHija(nullptr, &m_gestor);
	frame->Show();
	return true;
}

