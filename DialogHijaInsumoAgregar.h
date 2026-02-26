#ifndef DIALOGHIJAINSUMOAGREGAR_H
#define DIALOGHIJAINSUMOAGREGAR_H
#include "wxfb_project.h"
#include "DialogHijaInsumoAgregar.h"
#include "GestorPanaderia.h"

/// clase que representa la ventana para la carga de datos de un nuevo insumo
class DialogHijaInsumoAgregar : public DialogBaseInsumo {
	
private:
	GestorPanaderia *m_gestor;
	
protected:
	void OnEligeUnidad( wxCommandEvent& event )  override;
	void OnClickGuardar( wxCommandEvent& event )  override;
	void OnClickCancelar( wxCommandEvent& event )  override;
	
public:
	DialogHijaInsumoAgregar(wxWindow *parent=NULL, GestorPanaderia *gestor=nullptr);
	~DialogHijaInsumoAgregar();
};

#endif

