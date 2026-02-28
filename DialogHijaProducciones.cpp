#include "DialogHijaProducciones.h"
#include "ConversionDatos.h"
#include "GestorPanaderia.h"
#include "OrdenProduccion.h"
#include <wx/msgdlg.h>
#include <wx/datetime.h>

DialogHijaProducciones::DialogHijaProducciones(wxWindow *parent,
	GestorPanaderia *gestor, int id_orden) 
	: DialogProducciones(parent), m_gestor(gestor) 
{
	m_modo_vista = (id_orden != -1);
	
	// se seleccionan filas
	m_prod_grilla->SetSelectionMode(wxGrid::wxGridSelectRows);
	m_prod_grilla->SetColFormatNumber(2);
	
	if (m_modo_vista) 
	{
		// --- MODO LECTURA ---
		this->SetTitle("Detalle de producción histórica");
		m_prod_grilla->DisableCellEditControl();
		
		// oculto los controles
		m_statictext_prod->Hide();
		m_lista_recetas->Hide();
		m_statictext_uni->Hide();
		m_spin_cantidad->Hide();
		m_btn_agregar->Hide();
		m_btn_quitar->Hide();
		m_btn_cancelar->Hide(); 
		m_btn_confirmar->SetLabel("Cerrar"); // reutilizo el confirmar para salir
		m_date_fecha->Disable(); // la fecha no se cambia
		
		// datos históricos
		const OrdenProduccion* orden = m_gestor->verProduccion(id_orden);
		if (orden == nullptr) return;
		
		// seteo la fecha
		wxDateTime fecha_historica;
		fecha_historica.ParseFormat(orden->verFecha(), "%d/%m/%Y");
		m_date_fecha->SetValue(fecha_historica);
		
		// copio los items de la orden a nuestro carrito temporal para dibujarlos
		int cant = orden->verCantidadPorTipoItems();
		for(int i=0; i<cant; ++i) 
			m_carrito.push_back( (*orden)[i] );
		
		// seteo costo
		float costo = orden->verCostoTotal();
		m_text_costo->SetLabel( "$ " + num_to_wx(costo) );
		
		// wxWidgets reacomoda la ventana por todos los ->Hide()
		this->Layout(); 
	} 
	else 
	{	// --- MODO AGREGAR PRODUCCIÓN ---
		this->SetTitle("Registrar nueva producción");
		m_date_fecha->SetValue(wxDateTime::Today());
		
		// cargo el combo box con las recetas disponibles
		const std::vector<Receta> &lista_rec = m_gestor->verVectorRecetas();
		int cant_recetas = m_gestor->verCantidadRecetas();
		
		for (int i=0; i<cant_recetas; ++i) 
		{
			Receta rec_aux = lista_rec[i];
			
			// cada dato de la listbox se guarda como un par: 
			// value [visible] = nombre 
			// clientdata [oculto] = puntero void a receta
			m_lista_recetas->Append( rec_aux.verNombre(), (void*)(&lista_rec[i]) );
		}
	}
	ActualizarGrilla();	
}

void DialogHijaProducciones::ActualizarGrilla()
{
	// vacío la grilla
	if (m_prod_grilla->GetNumberRows() > 0)
		m_prod_grilla->DeleteRows( 0, m_prod_grilla->GetNumberRows() );
	
	// dibujo la grilla con m_carrito
	size_t cant_prod = m_carrito.size();
	m_prod_grilla->AppendRows(cant_prod);
	
	for (size_t i=0; i<cant_prod; ++i) 
	{
		wxString nombre = m_carrito[i].nombre_receta;
		
		m_prod_grilla->SetCellValue( i, 0, num_to_wx(m_carrito[i].id_receta) );
		m_prod_grilla->SetCellValue( i, 1, nombre );
		m_prod_grilla->SetCellValue( i, 2, num_to_wx(m_carrito[i].cantidad) );
	}
}

void DialogHijaProducciones::ActualizarCosto()
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
	m_text_costo->SetLabel(text);
}

void DialogHijaProducciones::OnClickAgregar( wxCommandEvent& event )  
{
	int pos_sel = m_lista_recetas->GetSelection();
	if (pos_sel == wxNOT_FOUND) return;
	
	// obtengo el client data, casteo a puntero a Receta
	void *rec_void = m_lista_recetas->GetClientData(pos_sel);
	const Receta *rec = static_cast<Receta*>(rec_void);
	
	int id_receta = rec->verId();
	int cantidad_a_agregar = m_spin_cantidad->GetValue();
	bool agregar = true;
	
	// si el producto ya está agregado, le sumo el valor y pongo agregar en false
	int cant_prod = m_prod_grilla->GetNumberRows();
	for (int i=0; i<cant_prod; ++i)
	{
		if ( wxAtoi(m_prod_grilla->GetCellValue(i, 0)) == id_receta )
		{
			int valor = wxAtoi(m_prod_grilla->GetCellValue(i, 2)) + cantidad_a_agregar;
			m_prod_grilla->SetCellValue(i, 2, num_to_wx(valor));
			m_carrito[i].cantidad = valor;
			
			agregar = false;
			break;
		}
	}
	
	// si el producto no estaba, lo agrego
	if (agregar)
	{
		ItemOrden aux;
		aux.id_receta = id_receta;
		aux.cantidad = cantidad_a_agregar;
		
		strncpy(aux.nombre_receta, rec->verNombre().c_str(), sizeof(aux.nombre_receta) - 1);
		aux.nombre_receta[sizeof(aux.nombre_receta) - 1] = '\0';
		
		m_carrito.push_back(aux);
		
		int fila = m_prod_grilla->GetNumberRows();
		m_prod_grilla->AppendRows(1);
		m_prod_grilla->SetCellValue( fila, 0, num_to_wx(id_receta) );
		m_prod_grilla->SetCellValue( fila, 1, str_to_wx(rec->verNombre()) );
		m_prod_grilla->SetCellValue( fila, 2, num_to_wx(cantidad_a_agregar) );
	}
	
	this->ActualizarCosto();
}

void DialogHijaProducciones::OnGrillaCambioCelda( wxGridEvent& event )  
{
	int fila = event.GetRow();
	int col = event.GetCol();
	
	// si modificó la columna de cantidad
	if (col == 2) { 
		int nueva_cant = wxAtoi(m_prod_grilla->GetCellValue(fila, 2));
		m_carrito[fila].cantidad = nueva_cant;
	}
	
	this->ActualizarCosto();
}

void DialogHijaProducciones::OnClickQuitarSel( wxCommandEvent& event )  
{
	if (not m_prod_grilla->IsSelection() ) return;
	
	int fila = m_prod_grilla->GetGridCursorRow();
	m_prod_grilla->DeleteRows(fila,1);
	m_carrito.erase(m_carrito.begin() + fila);
	
	this->ActualizarCosto();
}

void DialogHijaProducciones::OnClickConfirmar( wxCommandEvent& event )  
{
	if (m_modo_vista) {
		// en modo vista este botón dice "Cerrar"; que cierre
		EndModal(wxID_OK);
		return;
	}
	
	// valido que haya datos
	if ( m_carrito.empty() ) 
	{
		wxMessageBox("La orden de producción está vacía", "Error", wxICON_ERROR);
		return;
	}
	
	// obtengo la fecha de hoy
	wxDateTime fecha_seleccionada = m_date_fecha->GetValue();
	std::string fecha_str = wx_to_str( fecha_seleccionada.Format("%d/%m/%Y") );
	
	// armo la OrdenProduccion temporal
	OrdenProduccion nueva_orden(fecha_str);
	size_t cant_prod = m_carrito.size();
	for (size_t i=0; i<cant_prod; ++i) 
	{
		int id_rec = m_carrito[i].id_receta;
		std::string nombre_rec = m_carrito[i].nombre_receta;
		float costo_uni = m_gestor->calcularCostoReceta(id_rec);
		
		nueva_orden.agregarItem(id_rec, nombre_rec, m_carrito[i].cantidad, costo_uni);
	}
	
	// validamos el stock
	std::string errores = m_gestor->validarProduccion(nueva_orden);
	if ( errores.size() > 0 ) 
	{
		wxMessageBox(wxString() << "Stock insuficiente:\n" << errores,
					 "Error al validar orden", wxICON_ERROR);
		return;
	}
	
	// confirmacion final del usuario
	int res = wxMessageBox( "¿Desea confirmar la orden de producción?",
						   "Confirmar orden", wxYES_NO|wxICON_QUESTION );
	if ( res == wxNO ) return;
		
	// ejecuto, agrego y guardo
	m_gestor->ejecutarProduccion(nueva_orden);
	m_gestor->agregarProduccion(nueva_orden);
	m_gestor->guardarTodo();
	
	// mensaje al confirmar
	EndModal(wxID_OK);
	wxMessageBox("Producción registrada con éxito :)", "Orden confirmada", wxICON_INFORMATION);
}

void DialogHijaProducciones::CerrarVentana()
{	

	if (not m_modo_vista and m_carrito.size() > 0)
	{
		int res = wxMessageBox( "¿Desea cancelar la orden de producción?", "", wxYES_NO );
		if ( res == wxNO ) return;
	}
	
	EndModal(wxID_CANCEL);
}

void DialogHijaProducciones::OnClickCancelar( wxCommandEvent& event )  
{
	this->CerrarVentana();
}

void DialogHijaProducciones::OnClose( wxCloseEvent& event )  
{
	this->CerrarVentana();
}

DialogHijaProducciones::~DialogHijaProducciones() {
	
}

