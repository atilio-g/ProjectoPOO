#include "DialogHijaInsumo.h"
#include "ConversionDatos.h"
#include <wx/valnum.h>
#include <wx/msgdlg.h>

/// CONSTRUCTOR
DialogHijaInsumo::DialogHijaInsumo(wxWindow *parent, GestorPanaderia *gestor, Insumo *ins)
	: DialogBaseInsumo(parent), m_gestor(gestor), m_ins(ins)
{
	// si el puntero no es nulo, estamos en modo edición
	m_modo_editar = (ins != nullptr);
	
	if (m_modo_editar)
	{
		this->SetTitle("Editar Insumo");
		
		// precargo cada celda con su valor actual
		m_opcion_tipo->SetSelection( tipoIns_to_int( m_ins->verTipo() ) );
		m_opcion_unidad->SetSelection( unidad_to_int( m_ins->verUnidad() ) ) ;
		m_text_nombre->SetValue( str_to_wx( m_ins->verNombre() ) );
		m_text_stock->SetValue( num_to_wx( m_ins->verStockVisual() ) );
		m_text_costo->SetValue( num_to_wx( m_ins->verCosto() ) );
		m_statictext_costo->SetLabel( "Costo / " + m_ins->verUnidad() + ":");
	}
	else
	{
		this->SetTitle("Agregar Nuevo Insumo");
	}
	
	// en stock y costo sólo se ingresan números
	wxFloatingPointValidator<float> validadorNum(2);
	m_text_stock->SetValidator(validadorNum);
	m_text_costo->SetValidator(validadorNum);

}


/// Actualizo texto costo / unidad
void DialogHijaInsumo::OnEligeUnidad( wxCommandEvent& event )
{
	std::string unidad = int_to_unidad( m_opcion_unidad->GetCurrentSelection() );
	m_statictext_costo->SetLabel( "Costo / " + unidad + ":" );
}

void DialogHijaInsumo::OnClickGuardar( wxCommandEvent& event )
{
	// obtengo los datos 
	std::string nombre = wx_to_str( m_text_nombre->GetValue() );
	std::string unidad = int_to_unidad( m_opcion_unidad->GetCurrentSelection() );
	TipoInsumo tipo = int_to_tipoIns( m_opcion_tipo->GetCurrentSelection() );
	double costo; m_text_costo->GetValue().ToDouble(&costo);
	double stock; m_text_stock->GetValue().ToDouble(&stock);
	
	// manejo el stock en la unidad mínima
	if ( unidad == "kg" or unidad == "L" ) 
		stock *= 1000.0f;
	
	// creo un insumo temporal
	Insumo ins_temp(nombre, unidad, tipo, costo, stock);
	
	// si estamos en modo editar, guardo el id para validar
	int id_aux;
	m_modo_editar ? id_aux = m_ins->verId() : id_aux = -1;
	
	// valido errores en los datos
	std::string errores;
	errores += ins_temp.validarNombre();
	if ( errores.size() == 0 )
	{
		if ( not m_gestor->ValidarNombreInsumo(nombre, id_aux) )
			errores += "- El nombre introducido ya existe para otro insumo\n";
	}
	
	if ( m_text_stock->IsEmpty() ) errores += "- Debe introducir una cifra de stock.\n";
	else errores += ins_temp.validarStock();
	
	if ( m_text_costo->IsEmpty() ) errores += "- Debe introducir una cifra de costo.\n";
	else errores += ins_temp.validarCosto();
	
	errores += ins_temp.validarUnidad();
	errores += ins_temp.validarTipo();
	
	// si hay errores: los comunico y no guardo
	if ( errores.size() > 0 )
	{
		wxMessageBox( wxString() << "Datos incorrectos:\n" << errores, "Cambios no guardados", wxICON_ERROR );
		return;
	}
	
	// no hay errores: agrego o modifico y guardo
	if (m_modo_editar)
		m_gestor->modificarInsumo(m_ins->verId(), ins_temp);
	else
		m_gestor->agregarInsumo(ins_temp);
	
	m_gestor->guardarTodo();
	this->EndModal(1);
}

/// CANCELAR / CERRAR VENTANA
void DialogHijaInsumo::OnClickCancelar( wxCommandEvent& event )
{
	EndModal(0);
}

DialogHijaInsumo::~DialogHijaInsumo() { }
