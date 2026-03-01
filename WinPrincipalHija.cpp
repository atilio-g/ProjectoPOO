#include "wxfb_project.h"
#include "WinPrincipalHija.h"
#include "ConversionDatos.h"
#include "DialogHijaInsumo.h"
#include "DialogHijaRecetas.h"
#include "DialogHijaProducciones.h"
#include "Insumo.h"
#include "Receta.h"
#include "OrdenProduccion.h"
#include <wx/wx.h>
#include <vector>
#include <string>

/// CONSTRUCTOR
WinPrincipalHija::WinPrincipalHija(wxWindow *parent, GestorPanaderia *gestor) :
	WinPrincipalBase(parent), m_gestor(gestor)
{	
	this->SetIcon(wxIcon("pan.ico", wxBITMAP_TYPE_ICO));
	
	/// grilla insumos
	//se seleccionan filas, no celdas aisladas 
	m_insumos_grilla->SetSelectionMode(wxGrid::wxGridSelectRows);
	
	// cargo grilla
	int cantidad_ins = gestor->verCantidadInsumos();
	m_insumos_grilla->AppendRows(cantidad_ins);
	for (int i=0; i<cantidad_ins; ++i)
	{ 
		Insumo ins = ( m_gestor->verVectorInsumos() )[i];
		ins_cargarFila( i, ins );
	}
	
	// configuro columnas stock y precio
	m_insumos_grilla->SetColFormatFloat(3, -1, 2);
	m_insumos_grilla->SetColFormatFloat(5, -1, 2);
	
	// columna unidad centrada
	wxGridCellAttr* attrUnidad = new wxGridCellAttr;
	attrUnidad->SetAlignment(wxALIGN_CENTER, wxALIGN_CENTER);
	m_insumos_grilla->SetColAttr(4, attrUnidad);
	
	/// grilla de recetas
	//se seleccionan filas, no celdas aisladas 
	m_recetas_grilla->SetSelectionMode(wxGrid::wxGridSelectRows);
	
	// cargo grilla
	int cantidad_rec = gestor->verCantidadRecetas();
	m_recetas_grilla->AppendRows(cantidad_rec);
	for (int i=0; i<cantidad_rec; ++i)
	{
		Receta rec = ( m_gestor->verVectorRecetas() )[i];
		rec_cargarFila( i, rec );
	}
	
	// configuro las columnas num insumos y costo total
	m_recetas_grilla->SetColFormatNumber(2);
	m_recetas_grilla->SetColFormatFloat(3, -1, 2);
	
	/// producción
	//se seleccionan filas, no celdas aisladas 
	m_prod_grilla->SetSelectionMode(wxGrid::wxGridSelectRows);
	
	// cargo grilla
	int cantidad_prod = gestor->verCantidadProducciones();
	m_prod_grilla->AppendRows(cantidad_prod);
	for (int i=0; i<cantidad_prod; ++i)
	{
		OrdenProduccion prod = ( m_gestor->verVectorProduccion() )[i];
		prod_cargarFila( i, prod );
	}
	
	// configuro columnas
	m_prod_grilla->SetColFormatNumber(2);
	m_prod_grilla->SetColFormatFloat(3, -1, 2);
	
	// colores a grillas
	wxColour colorHeader(119, 158, 203);
	wxColour colorHeaderTexto(*wxWHITE);
	
	m_insumos_grilla->SetLabelBackgroundColour(colorHeader);
	m_insumos_grilla->SetLabelTextColour(colorHeaderTexto);
	m_insumos_grilla->SetDefaultRowSize(26, true);  // filas un poco más altas
	m_insumos_grilla->SetGridLineColour(wxColour(210, 215, 220)); // líneas más suaves
	
	m_recetas_grilla->SetLabelBackgroundColour(colorHeader);
	m_recetas_grilla->SetLabelTextColour(colorHeaderTexto);
	m_recetas_grilla->SetDefaultRowSize(26, true);
	m_recetas_grilla->SetGridLineColour(wxColour(210, 215, 220));
	
	m_prod_grilla->SetLabelBackgroundColour(colorHeader);
	m_prod_grilla->SetLabelTextColour(colorHeaderTexto);
	m_prod_grilla->SetDefaultRowSize(26, true);
	m_prod_grilla->SetGridLineColour(wxColour(210, 215, 220));
}

WinPrincipalHija::~WinPrincipalHija() {
	
}

//////////////////////// INICIO PARTE DE INSUMOS ////////////////////////

/// PARA ACTUALIZAR GRILLA
// Carga por defecto desde el vector principal
void WinPrincipalHija::ins_cargarFila(int pos)
{
	Insumo ins = ( m_gestor->verVectorInsumos() )[pos];
	
	m_insumos_grilla->SetCellValue( pos, 0, num_to_wx( ins.verId() ) );
	m_insumos_grilla->SetCellValue( pos, 1, tipoins_to_wx( ins.verTipo() ) );
	m_insumos_grilla->SetCellValue( pos, 2, str_to_wx( ins.verNombre() ) );
	m_insumos_grilla->SetCellValue( pos, 3, num_to_wx( ins.verStockVisual() ) );
	m_insumos_grilla->SetCellValue( pos, 4, str_to_wx( ins.verUnidad() ) );
	m_insumos_grilla->SetCellValue( pos, 5, num_to_wx( ins.verCosto() ) );
}

// Carga específica pasando un insumo
void WinPrincipalHija::ins_cargarFila(int fila, Insumo ins)
{
	m_insumos_grilla->SetCellValue( fila, 0, num_to_wx( ins.verId() ) );
	m_insumos_grilla->SetCellValue( fila, 1, tipoins_to_wx( ins.verTipo() ) );
	m_insumos_grilla->SetCellValue( fila, 2, str_to_wx( ins.verNombre() ) );
	m_insumos_grilla->SetCellValue( fila, 3, num_to_wx( ins.verStockVisual() ) );
	m_insumos_grilla->SetCellValue( fila, 4, str_to_wx( ins.verUnidad() ) );
	m_insumos_grilla->SetCellValue( fila, 5, num_to_wx( ins.verCosto() ) );
}

// Filtrar por búsqueda
void WinPrincipalHija::ins_OnTextBusqueda( wxCommandEvent& event ) 
{
	// limpia la grilla
	int num_filas = m_insumos_grilla->GetNumberRows();
	if ( num_filas > 0 ) m_insumos_grilla->DeleteRows(0, num_filas);
	num_filas = 0;
	
	std::string filtro = wx_to_str( m_insumos_busqueda->GetValue() );
	const std::vector<Insumo> &lista_real = m_gestor->verVectorInsumos();
	int cant = lista_real.size();
	
	// muestra en grilla los insumos que coincidan con la búsqueda
	for (int i=0; i<cant; ++i)
	{
		Insumo ins = lista_real[i];
		if ( (filtro != "") and (not (ins == filtro)) ) continue;
		
		m_insumos_grilla->AppendRows(1);
		this->ins_cargarFila(num_filas, ins);
		++num_filas;
	}
}

// Ordenar por filtro de columna
void WinPrincipalHija::ins_OnGrillaLabelClick( wxGridEvent& event )
{
	int col = event.GetCol();
	switch (col) 
	{
		case 1 : m_gestor->ordenarInsumos(ins_cmp_tipo); break;
		case 2 : m_gestor->ordenarInsumos(ins_cmp_nombre); break;
		case 3 : m_gestor->ordenarInsumos(ins_cmp_stock); break;
		case 5 : m_gestor->ordenarInsumos(ins_cmp_costo); break;
		default : return;
	}
	
	// actualiza grilla manteniendo la búsqueda si la hay
	this->ins_OnTextBusqueda(event);
}


/// AGREGAR INSUMO
void WinPrincipalHija::ins_OnClickNuevo( wxCommandEvent& event ) 
{
	// abre la nueva ventana para ingresar los datos
	DialogHijaInsumo nuevo_dialog(this, m_gestor);
	
	if ( nuevo_dialog.ShowModal() == 1 )
	{
		// si los datos son correctos: agrega el insumo a la grilla y guarda en archivo
		m_insumos_grilla->AppendRows(1);
		ins_cargarFila( m_gestor->verCantidadInsumos() - 1 );
	}
}

/// EDITAR INSUMO
/// función para editar
void WinPrincipalHija::ins_editarSeleccion()
{
	int fila = m_insumos_grilla->GetGridCursorRow();
	int id = wxAtoi( m_insumos_grilla->GetCellValue(fila,0) );
	Insumo *ins = m_gestor->verInsumo(id);
	
	// abre la nueva ventana para ingresar los datos
	DialogHijaInsumo nuevo_dialog(this, m_gestor, ins);
	
	if ( nuevo_dialog.ShowModal() == 1 )
	{
		// si los datos son correctos: modifica el insumo en la grilla y guarda en archivo
		ins_cargarFila( fila );
		
		// actualizo grilla de recetas para actualizar costos
		int cant = m_gestor->verCantidadRecetas();
		for (int i=0; i<cant; ++i)
			rec_cargarFila(i);
	}
}

/// por botón editar
void WinPrincipalHija::ins_OnClickEditar( wxCommandEvent& event ) 
{
	// si no hay selección no hace nada
	if ( not m_insumos_grilla->IsSelection() ) return;
	this->ins_editarSeleccion();
}

/// por doble click en la fila
void WinPrincipalHija::ins_OnGrillaDobleClick( wxGridEvent& event )  
{
	this->ins_editarSeleccion();
}

/// ELIMINAR INSUMO
void WinPrincipalHija::ins_OnClickEliminar( wxCommandEvent& event ) 
{
	// si no hay selección no hace nada
	if ( not m_insumos_grilla->IsSelection() ) return;
	
	int fila = m_insumos_grilla->GetGridCursorRow();
	int id = wxAtoi( m_insumos_grilla->GetCellValue(fila, 0) );
	
	// mensaje de confirmación para eliminar el insumo
	wxString msg = wxString() << "¿Desea eliminar el insumo " << m_insumos_grilla->GetCellValue(fila, 2) << "?";
	int res = wxMessageBox( msg, "Confirmar eliminación", wxYES_NO );
	
	if ( res == wxYES )
	{
		// si se confirma la eliminación: elimina, actualiza grilla y archivos
		m_insumos_grilla->DeleteRows(fila);
		m_gestor->eliminarInsumo(id);
		m_gestor->guardarTodo();
	}
}

//////////////////////// FIN PARTE DE INSUMOS ////////////////////////


/////////////////////// INICIO PARTE DE RECETAS ////////////////////////

/// PARA ACTUALIZAR GRILLA

// Carga por defecto desde el vector principal
void WinPrincipalHija::rec_cargarFila( int pos )
{
	Receta r = ( m_gestor->verVectorRecetas() )[pos];
	
	float costo_total = m_gestor->calcularCostoReceta( r );
	
	m_recetas_grilla->SetCellValue( pos, 0, num_to_wx( r.verId() ) );
	m_recetas_grilla->SetCellValue( pos, 1, str_to_wx( r.verNombre() ) );
	m_recetas_grilla->SetCellValue( pos, 2, num_to_wx( r.verCantidadIngredientes() ) );
	m_recetas_grilla->SetCellValue( pos, 3, num_to_wx( costo_total ) );
}

// Carga específica pasando una receta
void WinPrincipalHija::rec_cargarFila( int fila, Receta rec )
{
	float costo_total = m_gestor->calcularCostoReceta( rec );
	
	m_recetas_grilla->SetCellValue( fila, 0, num_to_wx( rec.verId() ) );
	m_recetas_grilla->SetCellValue( fila, 1, str_to_wx( rec.verNombre() ) );
	m_recetas_grilla->SetCellValue( fila, 2, num_to_wx( rec.verCantidadIngredientes() ) );
	m_recetas_grilla->SetCellValue( fila, 3, num_to_wx( costo_total ) );
}

// Filtrar por búsqueda
void WinPrincipalHija::rec_OnTextBusqueda( wxCommandEvent& event )  
{
	// limpia la grilla
	int num_filas = m_recetas_grilla->GetNumberRows();
	if ( num_filas > 0 ) m_recetas_grilla->DeleteRows(0, num_filas);
	num_filas = 0;
	
	std::string filtro = wx_to_str( m_recetas_busqueda->GetValue() );
	const std::vector<Receta> &lista_real = m_gestor->verVectorRecetas();
	int cant = lista_real.size();
	
	// muestra en grilla las recetas que coincidan con la búsqueda
	for (int i=0; i<cant; ++i)
	{
		Receta rec = lista_real[i];
		if ( (filtro != "") and (not (rec == filtro)) ) continue;
		
		m_recetas_grilla->AppendRows(1);
		this->rec_cargarFila(num_filas, rec);
		++num_filas;
	}
}

// Ordenar por filtro de columna
void WinPrincipalHija::rec_OnGrillaLabelClick( wxGridEvent& event )  
{
	int col = event.GetCol();
	switch (col) 
	{
	case 1 : m_gestor->ordenarRecetas(rec_cmp_nombre); break;
	case 2 : m_gestor->ordenarRecetas(rec_cmp_cantidad); break;
	case 3 : m_gestor->ordenarRecetaCosto(); break;
	default : return;
	}
	
	// actualiza grilla manteniendo la búsqueda si la hay
	this->rec_OnTextBusqueda(event);
}


/// AGREGAR RECETA
void WinPrincipalHija::rec_OnClickNuevo( wxCommandEvent& event ) 
{	
	// abre ventana para cargar datos
	DialogHijaRecetas nuevo_dialog(this, m_gestor, nullptr);
	
	if ( nuevo_dialog.ShowModal() == 1 )
	{
		// si los datos son correctos: agrega la receta, actualiza grilla y archivos
		m_recetas_grilla->AppendRows(1);
		rec_cargarFila( m_gestor->verCantidadRecetas() - 1 );
	}
	
}

/// EDITAR RECETA
/// función para editar
void WinPrincipalHija::rec_editarSeleccion()
{
	int fila = m_recetas_grilla->GetGridCursorRow();
	int id = wxAtoi( m_recetas_grilla->GetCellValue(fila,0) );
	Receta *rec = m_gestor->verReceta(id);
	
	// abre ventana para cargar datos
	DialogHijaRecetas nuevo_dialog(this, m_gestor, rec);
	
	// si los datos son correctos: modifica la receta, actualiza grilla y archivos
	if ( nuevo_dialog.ShowModal() == 1 )
		rec_cargarFila(fila);

}


/// por botón editar
void WinPrincipalHija::rec_OnClickEditar( wxCommandEvent& event )  
{
	// si no hay selección, no hace nada
	if ( not m_recetas_grilla->IsSelection() ) return;
	this->rec_editarSeleccion();
}

/// por doble click en fila
void WinPrincipalHija::rec_OnGrillaDobleClick( wxGridEvent& event )  
{
	this->rec_editarSeleccion();
}

/// ELIMINAR RECETA
void WinPrincipalHija::rec_OnClickEliminar( wxCommandEvent& event )  
{
	// si no hay selección, no hace nada
	if ( not m_recetas_grilla->IsSelection() ) return;
	
	int fila = m_recetas_grilla->GetGridCursorRow();
	int id = wxAtoi( m_recetas_grilla->GetCellValue(fila,0) );
	
	// mensaje de confirmación para eliminar la receta
	wxString msg = wxString() << "¿Desea eliminar la receta " << m_recetas_grilla->GetCellValue(fila, 1) << "?";
	int res = wxMessageBox( msg, "Confirmar eliminación", wxYES_NO );
	
	if ( res == wxYES )
	{
		// si se confirma la eliminación: elimina, actualiza grilla y archivos
		m_recetas_grilla->DeleteRows(fila);
		m_gestor->eliminarReceta(id);
		m_gestor->guardarTodo();
	}
}

//////////////////////// FIN PARTE DE RECETAS ////////////////////////

/////////////////////// INICIO PARTE DE PRODUCCION ////////////////////////

void WinPrincipalHija::prod_cargarFila(int pos)
{
	OrdenProduccion prod = ( m_gestor->verVectorProduccion() )[pos];
	
	// formato DD/MM/AAAA 
	int f = prod.verFecha();
	wxString fecha_str = wxString::Format("%02d/%02d/%04d", f%100, (f/100)%100, f/10000);
	
	m_prod_grilla->SetCellValue( pos, 0, num_to_wx( prod.verId() ) );
	m_prod_grilla->SetCellValue( pos, 1, fecha_str );
	m_prod_grilla->SetCellValue( pos, 2, num_to_wx( prod.verCantidadTotalItems() ) );
	m_prod_grilla->SetCellValue( pos, 3, num_to_wx( prod.verCostoTotal() ) );
}

void WinPrincipalHija::prod_cargarFila(int fila, OrdenProduccion prod)
{	
	int f = prod.verFecha();
	wxString fecha_str = wxString::Format("%02d/%02d/%04d", f%100, (f/100)%100, f/10000);
	
	m_prod_grilla->SetCellValue( fila, 0, num_to_wx( prod.verId() ) );
	m_prod_grilla->SetCellValue( fila, 1, fecha_str );
	m_prod_grilla->SetCellValue( fila, 2, num_to_wx( prod.verCantidadTotalItems() ) );
	m_prod_grilla->SetCellValue( fila, 3, num_to_wx( prod.verCostoTotal() ) );
}


void WinPrincipalHija::prod_OnGrillaLabelClick( wxGridEvent& event ) 
{
	int col = event.GetCol();
	switch (col) 
	{
	case 0 : m_gestor->ordenarProducciones(prod_cmp_id); break;
	case 1 : m_gestor->ordenarProducciones(prod_cmp_fecha); break;
	case 2 : m_gestor->ordenarProducciones(prod_cmp_cant); break;
	case 3 : m_gestor->ordenarProducciones(prod_cmp_costo); break;
	default : return;
	}
	
	// actualiza grilla 
	int cant = m_gestor->verCantidadProducciones();
	for (int i=0; i<cant; ++i)
		prod_cargarFila(i);
}

void WinPrincipalHija::prod_verSeleccion()
{
	// si no hay selección no hace nada
	if ( not m_prod_grilla->IsSelection() ) return;
	
	int fila = m_prod_grilla->GetGridCursorRow();
	int id_produccion = wxAtoi( m_prod_grilla->GetCellValue(fila, 0) );
	
	// al pasar un id_produccion el dialog se abre en modo lectura
	DialogHijaProducciones win(this, m_gestor, id_produccion);
	win.ShowModal();
}


void WinPrincipalHija::prod_OnClickVer( wxCommandEvent& event )  
{
	this->prod_verSeleccion();
}

void WinPrincipalHija::prod_OnGrillaDobleClick( wxGridEvent& event )  
{
	this->prod_verSeleccion();
}



void WinPrincipalHija::prod_OnClickNuevo( wxCommandEvent& event )  
{
	// si no paso id se abre en modo agregar
	DialogHijaProducciones win(this, m_gestor);
	if (win.ShowModal() != wxID_OK) return;
	
	// agrego a la grilla de producciones históricas
	int fila = m_gestor->verCantidadProducciones() - 1;
	m_prod_grilla->AppendRows(1);
	prod_cargarFila(fila);
	
	// actualizo insumos
	int cant_ins = m_gestor->verCantidadInsumos();
	for (int i=0; i<cant_ins; ++i) ins_cargarFila(i);
}

void WinPrincipalHija::prod_OnClickVaciar( wxCommandEvent& event )  
{
	int cant_prod = m_gestor->verCantidadProducciones();
	if (cant_prod == 0)
	{
		wxMessageBox( "No historial que vaciar", "Error", wxICON_INFORMATION );
		return;
	}
	
	int res = wxMessageBox( "¿Desea eliminar por completo el historial de ordenes de producción?"
						   , "Confirmar eliminación", wxYES_NO );
	
	if ( res == wxNO) return;
	
	m_gestor->vaciarHistorialProducciones();
	m_prod_grilla->DeleteRows(0, cant_prod);
	m_gestor->guardarTodo();
}


/////////////////////// FIN PARTE DE PRODUCCION ////////////////////////
