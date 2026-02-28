#ifndef DIALOGHIJARECETAS_H
#define DIALOGHIJARECETAS_H
#include "wxfb_project.h"
#include "GestorPanaderia.h"
#include "Receta.h"

/// clase que representa la ventana para ver o editar una receta
class DialogHijaRecetas : public DialogBaseRecetas {
	
private:
	GestorPanaderia *m_gestor; 	// gestor único
	Receta *m_rec; 	// puntero a receta en caso de editar
	bool m_modo_editar; // true para editar; false para agregar
	bool m_cambios; // false por defecto; true si el usuario cambia un dato
	
protected:
	
	/// MÉTODOS DE EVENTOS
	void OnCambioNombre( wxCommandEvent& event )  override;
	void OnClose( wxCloseEvent& event )  override;
	void OnTextBusqueda( wxCommandEvent& event )  override;
	void OnCambioValorCelda( wxGridEvent& event )  override;
	void OnDobleClickInsumo( wxCommandEvent& event )  override;
	void OnClickAgregar( wxCommandEvent& event )  override;
	void OnClickEliminar( wxCommandEvent& event )  override;
	void OnClickGuardar( wxCommandEvent& event )  override;
	void OnClickSalir( wxCommandEvent& event )  override;
	
	/// MÉTODOS AUXILIARES
	void RefrescarListaInsumos();
	int BuscarFilaPorId(int id);
	void AgregarInsumoSeleccionado();
	void GuardarCambios();
	void CerrarVentana();
	
public:
	DialogHijaRecetas(wxWindow *parent=NULL, GestorPanaderia *gestor=nullptr, Receta *rec=nullptr);
	~DialogHijaRecetas();
};

#endif

