#ifndef DIALOGHIJAPRODUCCIONES_H
#define DIALOGHIJAPRODUCCIONES_H
#include "wxfb_project.h"
#include "GestorPanaderia.h"
#include "OrdenProduccion.h"

/// clase que representa la ventana para agregar o ver una orden de producción
class DialogHijaProducciones : public DialogProducciones {
	
private:
	GestorPanaderia *m_gestor; // gestor único
	bool m_modo_vista; // true si es para ver; false si es para agregar
	std::vector<ItemOrden> m_carrito; // orden temporal para el modo agregar
	
	void ActualizarGrilla();
	void ActualizarCosto();
	void CerrarVentana();
	
protected:
	void OnClose( wxCloseEvent& event )  override;
	void OnClickAgregar( wxCommandEvent& event )  override;
	void OnGrillaCambioCelda( wxGridEvent& event )  override;
	void OnClickQuitarSel( wxCommandEvent& event )  override;
	void OnClickConfirmar( wxCommandEvent& event )  override;
	void OnClickCancelar( wxCommandEvent& event )  override;
	
public:
	// si pasa un id_orden > 0, entra en modo vista
	DialogHijaProducciones(wxWindow *parent=NULL, 
				GestorPanaderia *gestor=nullptr, int id_orden=-1);
	
	~DialogHijaProducciones();
};

#endif

