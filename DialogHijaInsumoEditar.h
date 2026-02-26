#ifndef DIALOGHIJAINSUMOEDITAR_H
#define DIALOGHIJAINSUMOEDITAR_H
#include "wxfb_project.h"
#include "GestorPanaderia.h"

class DialogHijaInsumoEditar : public DialogBaseInsumo {
	
private:
	GestorPanaderia *m_gestor;
	Insumo *m_ins;
	
protected:
	void OnEligeUnidad( wxCommandEvent& event )  override;
	void OnClickGuardar( wxCommandEvent& event )  override;
	void OnClickCancelar( wxCommandEvent& event )  override;
	
public:
	DialogHijaInsumoEditar(wxWindow *parent=NULL, GestorPanaderia *gestor=nullptr, Insumo *ins=nullptr);
	~DialogHijaInsumoEditar();
};

#endif

