#include "DialogHijaInsumoEditar.h"
#include "ConversionDatos.h"
#include "Insumo.h"
#include <wx/valnum.h>
#include <wx/msgdlg.h>

/// CONSTRUCTOR
DialogHijaInsumoEditar::DialogHijaInsumoEditar(wxWindow *parent, GestorPanaderia *gestor, Insumo *ins) :
	DialogBaseInsumo(parent), m_gestor(gestor), m_ins(ins)
{	
	this->SetTitle("Editar insumo");
	
	// en stock y costo sólo se ingresan números
	wxFloatingPointValidator<float> validadorNum(2);
	m_text_stock->SetValidator(validadorNum);
	m_text_costo->SetValidator(validadorNum);
	
	// precargo cada celda con su valor actual
	m_opcion_tipo->SetSelection( tipoIns_to_int( m_ins->verTipo() ) );
	m_opcion_unidad->SetSelection( unidad_to_int( m_ins->verUnidad() ) ) ;
	m_text_nombre->SetValue( str_to_wx( m_ins->verNombre() ) );
	m_text_stock->SetValue( num_to_wx( m_ins->verStockVisual() ) );
	m_text_costo->SetValue( num_to_wx( m_ins->verCosto() ) );
	
	m_statictext_costo->SetLabel( "Costo / " + m_ins->verUnidad() + ":");
}

DialogHijaInsumoEditar::~DialogHijaInsumoEditar() {
	
}

/// Actualizo texto costo / unidad
void DialogHijaInsumoEditar::OnEligeUnidad( wxCommandEvent& event )  
{
	std::string unidad = int_to_unidad( m_opcion_unidad->GetCurrentSelection() );
	m_statictext_costo->SetLabel( "Costo / " + unidad + ":");
}


/// GUARDAR CAMBIOS
void DialogHijaInsumoEditar::OnClickGuardar( wxCommandEvent& event )  
{	
	// obtengo los datos y creo un insumo temporal
	std::string nombre = wx_to_str( m_text_nombre->GetValue() );
	std::string unidad = int_to_unidad( m_opcion_unidad->GetCurrentSelection() );
	TipoInsumo tipo = int_to_tipoIns( m_opcion_tipo->GetCurrentSelection() );
	double costo; m_text_costo->GetValue().ToDouble(&costo);
	double stock; m_text_stock->GetValue().ToDouble(&stock);
	
	// manejo el stock en la unidad mínima
	if ( unidad == "kg" or unidad == "L" ) 
		stock *= 1000.0f;
	
	Insumo ins_temp(nombre, unidad, tipo, costo, stock);
	
	// valido errores en los datos
	std::string errores;
	errores += ins_temp.validarNombre();
	if ( errores.size() == 0 )
	{
		if ( not m_gestor->ValidarNombreInsumo(nombre, m_ins->verId()) )
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
	
	// no hay errores: modifico el insumo y guardo
	m_gestor->modificarInsumo(m_ins->verId(), ins_temp);
	m_gestor->guardarTodo();
	this->EndModal(1);
}

/// CANCELAR / CERRAR VENTANA
void DialogHijaInsumoEditar::OnClickCancelar( wxCommandEvent& event )  {
	this->EndModal(0);
}
