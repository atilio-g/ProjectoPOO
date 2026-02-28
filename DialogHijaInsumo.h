#ifndef DIALOGHIJAINSUMOS_H
#define DIALOGHIJAINSUMOS_H
#include "wxfb_project.h"
#include "GestorPanaderia.h"
#include "Insumo.h"

/// clase que representa la ventana para la carga de datos de un nuevo insumo
class DialogHijaInsumo : public DialogBaseInsumo {
private:
	GestorPanaderia *m_gestor;
	Insumo *m_ins; 			 // puntero al insumo original
	bool m_modo_editar;      // true si es para editar; false si es para agregar
	
protected:
	void OnEligeUnidad( wxCommandEvent& event ) override;
	void OnClickGuardar( wxCommandEvent& event ) override;
	void OnClickCancelar( wxCommandEvent& event ) override;
	
public:
	// si recibe un insumo válido, entra en modo editar
	DialogHijaInsumo(wxWindow *parent, GestorPanaderia *gestor, Insumo *ins = nullptr);
	~DialogHijaInsumo();
};
#endif

