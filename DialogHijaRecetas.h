#ifndef DIALOGHIJARECETAS_H
#define DIALOGHIJARECETAS_H
#include "wxfb_project.h"
#include "GestorPanaderia.h"
#include "Receta.h"

/// clase que representa la ventana para ver o editar una receta
class DialogHijaRecetas : public DialogBaseRecetas {
	
private:
	/// gestor único
	GestorPanaderia *m_gestor;
	
	/// puntero a receta en caso de editar
	Receta *m_rec;
	
	/// true si el usuario entra a editar una receta; false si el usuario agregar una receta
	bool m_modo_editar;
	
	/// false por defecto; true si el usuario cambia un dato
	bool m_cambios;
	
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

