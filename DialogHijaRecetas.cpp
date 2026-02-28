#include "ConversionDatos.h"
#include "DialogHijaRecetas.h"
#include "GestorPanaderia.h"
#include "Insumo.h"
#include "Receta.h"
#include <vector>
#include <string>
#include <wx/msgdlg.h>


/// CONSTRUCTOR
DialogHijaRecetas::DialogHijaRecetas(wxWindow *parent, GestorPanaderia *gestor, Receta *rec) : 
	DialogBaseRecetas(parent), m_gestor(gestor), m_rec(rec), m_cambios(false)
{
	m_modo_editar = (m_rec != nullptr);
	
	// precargo datos si el usuario entra en modo editar
	if (m_modo_editar)
	{
		wxString rec_nombre = str_to_wx( m_rec->verNombre() );
		m_recetaEditar_text_nombre->SetValue( rec_nombre );
		
		int cant = m_rec->verCantidadIngredientes();
		m_recetaEditar_grilla->AppendRows( cant );
		
		for (int i=0; i<cant; ++i)
		{
			Ingrediente ing = (*m_rec)[i];
			wxString ing_nombre = ( m_gestor->verInsumo(ing.id) )->verNombre();
			wxString ing_unidad = ( m_gestor->verInsumo(ing.id) )->verUnidad();
			
			// unidad mínima para cargar ingredientes de la receta
			if (ing_unidad == "kg") ing_unidad = "g";
			else if (ing_unidad == "L") ing_unidad = "ml";
			
			m_recetaEditar_grilla->SetCellValue(i, 0, num_to_wx(ing.id) );
			m_recetaEditar_grilla->SetCellValue(i, 1, ing_nombre);
			m_recetaEditar_grilla->SetCellValue(i, 2, num_to_wx(ing.cantidad) );
			m_recetaEditar_grilla->SetCellValue(i, 3, ing_unidad);
		}
	} 

	// selecciona filas enteras; igualmente puede editar cantidad
	m_recetaEditar_grilla->SetSelectionMode(wxGrid::wxGridSelectRows);
	
	// la columna nombre es de sólo lectura
	wxGridCellAttr* attrNombre = new wxGridCellAttr;
	attrNombre->SetReadOnly();
	m_recetaEditar_grilla->SetColAttr(1, attrNombre);
	
	// características para la columna cantidad
	wxGridCellAttr* attrCantidad = new wxGridCellAttr;
	attrCantidad->SetEditor( new wxGridCellFloatEditor(10, 2) );
	attrCantidad->SetRenderer(new wxGridCellFloatRenderer(10, 2));
	attrCantidad->SetAlignment(wxALIGN_RIGHT, wxALIGN_CENTER);
	m_recetaEditar_grilla->SetColAttr(2, attrCantidad);
	
	// columna unidad centrada y sólo lectura
	wxGridCellAttr* attrUnidad = new wxGridCellAttr;
	attrUnidad->SetReadOnly();
	attrUnidad->SetAlignment(wxALIGN_CENTER, wxALIGN_CENTER);
	m_recetaEditar_grilla->SetColAttr(3, attrUnidad);
	
	// colores a grilla
	m_recetaEditar_grilla->SetLabelBackgroundColour(wxColour(119, 158, 203));
	m_recetaEditar_grilla->SetLabelTextColour(*wxWHITE);
	m_recetaEditar_grilla->SetDefaultRowSize(26, true);
	m_recetaEditar_grilla->SetGridLineColour(wxColour(210, 215, 220));
	
	this->RefrescarListaInsumos();
}

DialogHijaRecetas::~DialogHijaRecetas() {
	
}

/// RFRESCAR LISTA DE INSUMOS POR BÚSQUEDA
void DialogHijaRecetas::RefrescarListaInsumos()
{
	// limpio la lista
	m_recetaEditar_lista_insumos->Clear();
	const std::vector<Insumo> &lista_real = m_gestor->verVectorInsumos();
	std::string filtro = wx_to_str( m_recetaEditar_busqueda->GetValue() );
	
	int cant = lista_real.size();
	for (int i=0; i<cant; ++i)
	{
		// muestro aquellos que coincidan con la búsqeuda
		Insumo ins = lista_real[i];
		if ( (filtro != "") and (not (ins == filtro)) ) continue;
		
		// cada dato de la listbox se guarda como un par: 
		// value [visible] = nombre 
		// clientdata [oculto] = puntero void a insumo
		m_recetaEditar_lista_insumos->Append( ins.verNombre(), (void*)(&lista_real[i]) );
	}
}

/// BUSCADOR
void DialogHijaRecetas::OnTextBusqueda( wxCommandEvent& event )  
{ 
	this->RefrescarListaInsumos(); 
}

/// busca en que fila de la grilla se encuentra el id pasado; devuelve -1 si no está
int DialogHijaRecetas::BuscarFilaPorId(int id)
{
	int cant_filas = m_recetaEditar_grilla->GetNumberRows();
	
	for (int i=0; i<cant_filas; ++i)
	{
		int id_actual = wxAtoi( m_recetaEditar_grilla->GetCellValue(i,0) );
		if ( id_actual == id ) return i;
	}
	return -1;
}

/// AGREGAR IGREDIENTE TEMPORAL
void DialogHijaRecetas::AgregarInsumoSeleccionado()
{
	// si no se selecciona ingrediente, no hace nada
	int pos_sel = m_recetaEditar_lista_insumos->GetSelection();
	if ( pos_sel == wxNOT_FOUND ) return;
	
	// obtengo el insumo guardado en clientdata
	void *ins_void = m_recetaEditar_lista_insumos->GetClientData(pos_sel);
	const Insumo *ins = static_cast<Insumo*>(ins_void);
	
	int fila = BuscarFilaPorId( ins->verId() );
	
	// si el ingrediente no estaba, se agrega con cantidad = 0
	if ( fila == -1 )
	{
		m_recetaEditar_grilla->AppendRows(1);
		fila = m_recetaEditar_grilla->GetNumberRows() - 1;
		
		// unidad mínima para cargar ingredientes de la receta
		wxString unidad = str_to_wx( ins->verUnidad() );
		if (unidad == "kg") unidad = "g";
		else if (unidad == "L") unidad = "ml";
		
		m_recetaEditar_grilla->SetCellValue( fila, 0, num_to_wx(ins->verId()) );
		m_recetaEditar_grilla->SetCellValue( fila, 1, str_to_wx(ins->verNombre()) );
		m_recetaEditar_grilla->SetCellValue( fila, 2, "0" );
		m_recetaEditar_grilla->SetCellValue( fila, 3, unidad );
		m_cambios = true;
	}
	
	// llevo el cursor a la celda para editar la cantidad
	m_recetaEditar_grilla->SetFocus();
	m_recetaEditar_grilla->MakeCellVisible(fila, 2);
	m_recetaEditar_grilla->SetGridCursor(fila,2);
	m_recetaEditar_grilla->EnableCellEditControl(true);
}

/// BOTON AGREGAR
void DialogHijaRecetas::OnClickAgregar( wxCommandEvent& event ) 
{
	AgregarInsumoSeleccionado();
}

/// DOBLE CLICK EN INGREDIENTE AGREGA
void DialogHijaRecetas::OnDobleClickInsumo( wxCommandEvent& event ) 
{
	AgregarInsumoSeleccionado();
}

/// ELIMINAR INGREDIENTE TEMPORAL
void DialogHijaRecetas::OnClickEliminar( wxCommandEvent& event )  
{
	// valido si hay fila seleccionada
	if ( not m_recetaEditar_grilla->IsSelection() ) return;
	
	int fila = m_recetaEditar_grilla->GetGridCursorRow();
	m_recetaEditar_grilla->DeleteRows(fila);
	m_cambios = true;
	
	/*
	-----------versión para eliminar desde la ListBox
	int pos_sel = m_recetaEditar_lista_insumos->GetSelection();
	if ( pos_sel == wxNOT_FOUND ) return;
	
	// obtengo el insumo guardado en clientdata
	void *ins_void = m_recetaEditar_lista_insumos->GetClientData(pos_sel);
	ins = static_cast<Insumo*>(ins_void);
	
	// valido
	fila = BuscarFilaPorId( ins->verId() );
	if ( fila == -1 ) return;
	
	m_recetaEditar_grilla->DeleteRows(fila);
	m_cambios = true;                                 
	*/
}

/// GUARDAR CAMBIOS
void DialogHijaRecetas::GuardarCambios()
{
	// si no hay cambios, salir
	if (not m_cambios)
	{
		this->EndModal(0);
		return;
	}
	
	wxString wx_nombre = m_recetaEditar_text_nombre->GetValue(); 
	std::string nombre = wx_to_str(wx_nombre);
	
	// cargo los datos en una receta temporal
	Receta rec_temp(nombre);
	int cant_filas = m_recetaEditar_grilla->GetNumberRows();
	for (int i=0; i<cant_filas; ++i)
	{
		double cant; ( m_recetaEditar_grilla->GetCellValue(i,2) ).ToDouble(&cant);
		int id = wxAtoi( m_recetaEditar_grilla->GetCellValue(i,0) );
		rec_temp.modificarIngrediente(id, cant);
	}
	
	// valido coherencia de la receta individual y nombre repetido
	int actual_id = -1;
	if ( m_modo_editar ) actual_id = m_rec->verId();
	std::string errores;
	if ( not m_gestor->ValidarNombreReceta(nombre, actual_id) ) 
		errores += "- El nombre introducido ya existe para otra receta\n";
	errores += rec_temp.validarDatos();
	
	// si hay errores, los comunico y no guardo
	if (errores.size() > 0)
	{
		wxMessageBox( wxString() << "Datos incorrectos:\n" << errores, "Cambios no guardados", wxICON_ERROR );
		return;
	}
	
	// la receta es coherente, la agrego o modifico
	if (m_modo_editar)
	{
		m_gestor->modificarReceta( m_rec->verId(), rec_temp );
	}
	else{
		m_gestor->agregarReceta(rec_temp);
	}
	m_gestor->guardarTodo();
	this->EndModal(1);
}

void DialogHijaRecetas::OnClickGuardar( wxCommandEvent& event )  
{
	GuardarCambios();
}

/// CERRAR VENTANA
void DialogHijaRecetas::CerrarVentana()
{	
	// mensaje de confirmación si se quiere cerrar la ventana sin guardar los cambios
	if (m_cambios)
	{
		int res = wxMessageBox( "Hay cambios sin guardar. ¿Desea salir de todas formas?", "Confirmación de salir", wxYES_NO|wxICON_EXCLAMATION );
		if ( res == wxNO ) return;
	}

	this->EndModal(0);
	return;
}

void DialogHijaRecetas::OnClickSalir( wxCommandEvent& event )  
{
	CerrarVentana();
}

void DialogHijaRecetas::OnClose( wxCloseEvent& event )  
{
	CerrarVentana();
}

/// ACTUALIZAR M_CAMBIOS 
/// por cambio en celda cantidad de la grilla
void DialogHijaRecetas::OnCambioValorCelda( wxGridEvent& event )  
{
	m_cambios = true;
}
/// por cambio de nombre
void DialogHijaRecetas::OnCambioNombre( wxCommandEvent& event )  
{
	// si ya se hicieron cambios, no se hace nada
	if (m_cambios) return;
	
	// se actualiza m_cambios
	m_cambios = true;
	
	// se da vuelta en caso de que el nombre vuelva a como estaba
	if (m_modo_editar)
	{
		if ( wxString(m_rec->verNombre()) == m_recetaEditar_text_nombre->GetValue() )
			m_cambios = false;
	}
	else
	{
		if ( m_recetaEditar_text_nombre->IsEmpty() ) m_cambios = false;
	}
}

