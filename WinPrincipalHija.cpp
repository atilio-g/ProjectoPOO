#include "WinPrincipalHija.h"
#include "ConversionDatos.h"
#include "DialogHijaInsumoAgregar.h"
#include "DialogHijaInsumoEditar.h"
#include "DialogHijaRecetas.h"
#include "Receta.h"
#include "Insumo.h"
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
	// cargo lista de productos
	this->prod_cargarListaProductos();
	
	//se seleccionan filas, no celdas aisladas 
	m_prod_grilla->SetSelectionMode(wxGrid::wxGridSelectRows);
	
	// columna producto de solo lectura
	wxGridCellAttr* attrSoloLeer = new wxGridCellAttr;
	attrSoloLeer->SetReadOnly();
	m_prod_grilla->SetColAttr(1, attrSoloLeer);
	
	// columna cantidad solo números
	m_prod_grilla->SetColFormatNumber(2);
	
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
	DialogHijaInsumoAgregar nuevo_dialog(this, m_gestor);
	
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
	DialogHijaInsumoEditar nuevo_dialog(this, m_gestor, ins);
	
	if ( nuevo_dialog.ShowModal() == 1 )
	{
		// si los datos son correctos: modifica el insumo en la grilla y guarda en archivo
		ins_cargarFila( fila );
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
	this->prod_cargarListaProductos();
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
		this->prod_cargarListaProductos();
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
	
	if ( nuevo_dialog.ShowModal() == 1 )
	{ 
		// si los datos son correctos: modifica la receta, actualiza grilla y archivos
		rec_cargarFila(fila);
		this->prod_cargarListaProductos();
	}
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
		this->prod_cargarListaProductos();
	}
}

//////////////////////// FIN PARTE DE RECETAS ////////////////////////

/////////////////////// INICIO PARTE DE PRODUCCION ////////////////////////

/// CARGAR DATOS
/// Cargar lista para seleccionar producto
void WinPrincipalHija::prod_cargarListaProductos()
{
	m_prod_lista->Clear();
	const std::vector<Receta> &lista_rec = m_gestor->verVectorRecetas();
	int cant_rec = m_gestor->verCantidadRecetas();
	
	for (int i=0; i<cant_rec; ++i)
	{
		Receta rec_aux = lista_rec[i];
		
		// cada dato de la listbox se guarda como un par: 
		// value [visible] = nombre 
		// clientdata [oculto] = puntero void a receta
		m_prod_lista->Append( rec_aux.verNombre(), (void*)(&lista_rec[i]) );
	}
}

/// actualizar el costo total estimado
void WinPrincipalHija::prod_actualizarCostoTotal()
{
	float costo_total = 0.00f;
	int cant_prod = m_prod_grilla->GetNumberRows();
	
	for (int i=0; i<cant_prod; ++i)
	{
		int rec_id = wxAtoi( m_prod_grilla->GetCellValue(i,0) );
		int rec_cantidad = wxAtoi( m_prod_grilla->GetCellValue(i,2) );
		float rec_costo = m_gestor->calcularCostoReceta(rec_id);
		costo_total += rec_costo * rec_cantidad;
	}
	
	wxString text = "$ " + num_to_wx(costo_total);
	m_prod_text_costo->SetLabel( text );
}

// al cambiar la cantidad por celda actualiza el costo
void WinPrincipalHija::prod_OnGrillaCambioCelda( wxGridEvent& event )  
{
	this->prod_actualizarCostoTotal();
}

/// AGREGAR A PRODUCCION
void WinPrincipalHija::prod_OnClickAgregar( wxCommandEvent& event )  
{
	int pos_sel = m_prod_lista->GetSelection();
	if (pos_sel == wxNOT_FOUND) return;
	
	// obtengo el client data, casteo a puntero a Receta
	void *rec_void = m_prod_lista->GetClientData(pos_sel);
	const Receta *rec = static_cast<Receta*>(rec_void);
	
	int id_receta = rec->verId();
	int cantidad_a_agregar = m_prod_spinctrl->GetValue();
	bool agregar = true;
	
	// si el producto ya está agregado, le sumo el valor
	int cant_prod = m_prod_grilla->GetNumberRows();
	for (int i=0; i<cant_prod; ++i)
	{
		if ( wxAtoi(m_prod_grilla->GetCellValue(i, 0)) == id_receta )
		{
			int valor = wxAtoi(m_prod_grilla->GetCellValue(i, 2)) + cantidad_a_agregar;
			m_prod_grilla->SetCellValue(i, 2, num_to_wx(valor));
			agregar = false;
			break;
		}
	}
	
	// si el producto no estaba, lo agrego
	if (agregar)
	{
		int fila = m_prod_grilla->GetNumberRows();
		m_prod_grilla->AppendRows(1);
		m_prod_grilla->SetCellValue( fila, 0, num_to_wx(id_receta) );
		m_prod_grilla->SetCellValue( fila, 1, str_to_wx(rec->verNombre()) );
		m_prod_grilla->SetCellValue( fila, 2, num_to_wx(cantidad_a_agregar) );
	}
	
	this->prod_actualizarCostoTotal();
}

/// ELIMINAR DE PRODUCCION
void WinPrincipalHija::prod_OnClickQuitarSel( wxCommandEvent& event )  
{
	if (not m_prod_grilla->IsSelection() ) return;
	
	int fila = m_prod_grilla->GetGridCursorRow();
	m_prod_grilla->DeleteRows(fila,1);
	
	this->prod_actualizarCostoTotal();
}

/// CONFIRMAR Y PROCESAR PRODUCCIÓN
void WinPrincipalHija::prod_OnClickConfirmar( wxCommandEvent& event )  
{
	int cant_productos = m_prod_grilla->GetNumberRows();
	if ( cant_productos == 0 ) return;
	
	// acumulo la orden de produccion
	std::vector< std::pair<int,int> > orden_prod;
	for (int i=0; i<cant_productos; ++i)
	{
		// par <id_receta, cantidad>
		std::pair<int,int> producto;
		producto.first = wxAtoi( m_prod_grilla->GetCellValue(i,0) );
		producto.second = wxAtoi( m_prod_grilla->GetCellValue(i,2) );
		
		orden_prod.push_back(producto);
	}
	
	// valido si hay stock suficiente 
	std::string errores = m_gestor->validarProduccion(orden_prod);
	if ( errores.size() > 0 )
	{
		wxMessageBox( wxString() << "Datos incorrectos:\n" << errores,
					 "Error al validar orden", wxICON_ERROR );
		return;
	}
	
	// confirmacion final del usuario
	int res = wxMessageBox( "¿Desea confirmar la orden de producción?", "Confirmar orden", wxYES_NO|wxICON_QUESTION );
	if ( res == wxNO ) return;
	
	// mensaje al confirmar
	wxMessageBox( "Stock actualizado! Buena producción :)", "Orden confirmada", wxICON_INFORMATION );
	
	// actualizo datos y guardo archivos
	m_gestor->ejecutarProduccion(orden_prod);
	m_gestor->guardarInsumos();
	m_prod_grilla->DeleteRows(0, cant_productos);
	this->prod_actualizarCostoTotal();
	
	// refresco grilla de insumos
	int cant_ins = m_gestor->verCantidadInsumos();
	for (int i=0; i<cant_ins; ++i) 
		this->ins_cargarFila(i);
}

/// CANCELAR Y LIMPIAR PRODUCCIÓN
void WinPrincipalHija::prod_OnClickCancelar( wxCommandEvent& event )  
{
	int cant_productos = m_prod_grilla->GetNumberRows();
	if ( cant_productos == 0 ) return;
	
	int res = wxMessageBox( "¿Desea cancelar la orden de producción?", "", wxYES_NO );
	if ( res == wxNO ) return;
	
	m_prod_grilla->DeleteRows(0, cant_productos);
	
	this->prod_actualizarCostoTotal();
}

/////////////////////// FIN PARTE DE PRODUCCION ////////////////////////



