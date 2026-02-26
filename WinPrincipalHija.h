#ifndef WINPRINCIPALHIJA_H
#define WINPRINCIPALHIJA_H
#include "wxfb_project.h"
#include "GestorPanaderia.h"


/// clase que representa la ventana principal; contiene 3 paneles
/// panel de insumos, panel de recetas y panel de producción
class WinPrincipalHija : public WinPrincipalBase {
	
private:
	/// puntero al gestor único
	GestorPanaderia *m_gestor;
	
protected:
	/// métodos de insumos
	void ins_cargarFila( int pos );
	void ins_cargarFila(int fila, Insumo ins);
	void ins_editarSeleccion();
	
	void ins_OnGrillaLabelClick( wxGridEvent& event )  override;
	void ins_OnTextBusqueda( wxCommandEvent& event )  override;
	void ins_OnClickNuevo( wxCommandEvent& event )  override;
	void ins_OnClickEditar( wxCommandEvent& event )  override;
	void ins_OnGrillaDobleClick( wxGridEvent& event )  override;
	void ins_OnClickEliminar( wxCommandEvent& event )  override;

	/// métodos de recetas
	void rec_cargarFila( int pos );
	void rec_cargarFila( int fila, Receta rec );
	void rec_editarSeleccion();
	
	void rec_OnGrillaLabelClick( wxGridEvent& event )  override;
	void rec_OnTextBusqueda( wxCommandEvent& event )  override;
	void rec_OnClickNuevo( wxCommandEvent& event )  override;
	void rec_OnClickEditar( wxCommandEvent& event )  override;
	void rec_OnGrillaDobleClick( wxGridEvent& event )  override;
	void rec_OnClickEliminar( wxCommandEvent& event )  override;
	
	/// métodos de producción
	void prod_cargarListaProductos();
	void prod_actualizarCostoTotal();
	
	void prod_OnClickAgregar( wxCommandEvent& event )  override;
	void prod_OnClickQuitarSel( wxCommandEvent& event )  override;
	void prod_OnClickConfirmar( wxCommandEvent& event )  override;
	void prod_OnClickCancelar( wxCommandEvent& event )  override;
	void prod_OnGrillaCambioCelda( wxGridEvent& event )  override;
	
public:
	WinPrincipalHija(wxWindow *parent=NULL, GestorPanaderia *gestor=nullptr);
	~WinPrincipalHija();
};

#endif

