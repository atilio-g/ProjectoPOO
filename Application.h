#ifndef APPLICATION_H
#define APPLICATION_H

#include <wx/app.h>
#include "GestorPanaderia.h"
#include <string>

class Application : public wxApp {
private:
	// gestor universal en toda la app
	GestorPanaderia m_gestor;
	
public:
	Application();
	virtual bool OnInit();
};

#endif
