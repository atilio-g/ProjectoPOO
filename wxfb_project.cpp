///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version 4.2.1-0-g80c4cb6)
// http://www.wxformbuilder.org/
//
// PLEASE DO *NOT* EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#include "wxfb_project.h"

///////////////////////////////////////////////////////////////////////////

WinPrincipalBase::WinPrincipalBase( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxFrame( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );

	wxBoxSizer* bSizer;
	bSizer = new wxBoxSizer( wxVERTICAL );

	m_insumos_notebook = new wxNotebook( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, 0 );
	m_insumos_panel = new wxPanel( m_insumos_notebook, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxBoxSizer* bSizer4;
	bSizer4 = new wxBoxSizer( wxVERTICAL );

	wxBoxSizer* bSizer5;
	bSizer5 = new wxBoxSizer( wxHORIZONTAL );

	m_insumos_busqueda = new wxSearchCtrl( m_insumos_panel, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	#ifndef __WXMAC__
	m_insumos_busqueda->ShowSearchButton( true );
	#endif
	m_insumos_busqueda->ShowCancelButton( false );
	bSizer5->Add( m_insumos_busqueda, 1, wxALL, 5 );

	m_insumos_boton_nuevo = new wxButton( m_insumos_panel, wxID_ANY, wxT("Nuevo"), wxDefaultPosition, wxDefaultSize, 0 );
	m_insumos_boton_nuevo->SetBackgroundColour( wxSystemSettings::GetColour( wxSYS_COLOUR_WINDOW ) );

	bSizer5->Add( m_insumos_boton_nuevo, 0, wxALL, 5 );

	m_insumos_boton_editar = new wxButton( m_insumos_panel, wxID_ANY, wxT("Editar"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer5->Add( m_insumos_boton_editar, 0, wxALL, 5 );

	m_insumos_boton_eliminar = new wxButton( m_insumos_panel, wxID_ANY, wxT("Eliminar"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer5->Add( m_insumos_boton_eliminar, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );


	bSizer4->Add( bSizer5, 0, wxALL|wxEXPAND, 10 );

	m_insumos_grilla = new wxGrid( m_insumos_panel, wxID_ANY, wxDefaultPosition, wxDefaultSize, 0 );

	// Grid
	m_insumos_grilla->CreateGrid( 0, 6 );
	m_insumos_grilla->EnableEditing( false );
	m_insumos_grilla->EnableGridLines( true );
	m_insumos_grilla->EnableDragGridSize( false );
	m_insumos_grilla->SetMargins( 0, 0 );

	// Columns
	m_insumos_grilla->SetColSize( 0, 0 );
	m_insumos_grilla->SetColSize( 1, 110 );
	m_insumos_grilla->SetColSize( 2, 250 );
	m_insumos_grilla->SetColSize( 3, 125 );
	m_insumos_grilla->SetColSize( 4, 55 );
	m_insumos_grilla->SetColSize( 5, 150 );
	m_insumos_grilla->EnableDragColMove( true );
	m_insumos_grilla->EnableDragColSize( true );
	m_insumos_grilla->SetColLabelValue( 0, wxT("ID") );
	m_insumos_grilla->SetColLabelValue( 1, wxT("Tipo") );
	m_insumos_grilla->SetColLabelValue( 2, wxT("Nombre") );
	m_insumos_grilla->SetColLabelValue( 3, wxT("Stock") );
	m_insumos_grilla->SetColLabelValue( 4, wxT("Ud.") );
	m_insumos_grilla->SetColLabelValue( 5, wxT("Costo ($/ud)") );
	m_insumos_grilla->SetColLabelValue( 6, wxEmptyString );
	m_insumos_grilla->SetColLabelAlignment( wxALIGN_CENTER, wxALIGN_CENTER );

	// Rows
	m_insumos_grilla->EnableDragRowSize( true );
	m_insumos_grilla->SetRowLabelSize( 1 );
	m_insumos_grilla->SetRowLabelAlignment( wxALIGN_CENTER, wxALIGN_CENTER );

	// Label Appearance

	// Cell Defaults
	m_insumos_grilla->SetDefaultCellAlignment( wxALIGN_LEFT, wxALIGN_CENTER );
	bSizer4->Add( m_insumos_grilla, 1, wxALL|wxEXPAND, 5 );


	m_insumos_panel->SetSizer( bSizer4 );
	m_insumos_panel->Layout();
	bSizer4->Fit( m_insumos_panel );
	m_insumos_notebook->AddPage( m_insumos_panel, wxT("Insumos"), true );
	m_recetas_panel = new wxPanel( m_insumos_notebook, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxBoxSizer* bSizer41;
	bSizer41 = new wxBoxSizer( wxVERTICAL );

	wxBoxSizer* bSizer51;
	bSizer51 = new wxBoxSizer( wxHORIZONTAL );

	m_recetas_busqueda = new wxSearchCtrl( m_recetas_panel, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	#ifndef __WXMAC__
	m_recetas_busqueda->ShowSearchButton( true );
	#endif
	m_recetas_busqueda->ShowCancelButton( false );
	bSizer51->Add( m_recetas_busqueda, 1, wxALL, 5 );

	m_recetas_btn_nuevo = new wxButton( m_recetas_panel, wxID_ANY, wxT("Nuevo"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer51->Add( m_recetas_btn_nuevo, 0, wxALL, 5 );

	m_recetas_btn_editar = new wxButton( m_recetas_panel, wxID_ANY, wxT("Ver / Editar"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer51->Add( m_recetas_btn_editar, 0, wxALL, 5 );

	m_recetas_btn_eliminar = new wxButton( m_recetas_panel, wxID_ANY, wxT("Eliminar"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer51->Add( m_recetas_btn_eliminar, 0, wxALL, 5 );


	bSizer41->Add( bSizer51, 0, wxALL|wxEXPAND, 10 );

	m_recetas_grilla = new wxGrid( m_recetas_panel, wxID_ANY, wxDefaultPosition, wxDefaultSize, 0 );

	// Grid
	m_recetas_grilla->CreateGrid( 0, 4 );
	m_recetas_grilla->EnableEditing( false );
	m_recetas_grilla->EnableGridLines( true );
	m_recetas_grilla->EnableDragGridSize( false );
	m_recetas_grilla->SetMargins( 0, 0 );

	// Columns
	m_recetas_grilla->SetColSize( 0, 0 );
	m_recetas_grilla->SetColSize( 1, 350 );
	m_recetas_grilla->SetColSize( 2, 130 );
	m_recetas_grilla->SetColSize( 3, 210 );
	m_recetas_grilla->EnableDragColMove( true );
	m_recetas_grilla->EnableDragColSize( true );
	m_recetas_grilla->SetColLabelValue( 0, wxT("ID") );
	m_recetas_grilla->SetColLabelValue( 1, wxT("Nombre") );
	m_recetas_grilla->SetColLabelValue( 2, wxT("N. ingredientes") );
	m_recetas_grilla->SetColLabelValue( 3, wxT("Costo total ($)") );
	m_recetas_grilla->SetColLabelAlignment( wxALIGN_CENTER, wxALIGN_CENTER );

	// Rows
	m_recetas_grilla->EnableDragRowSize( true );
	m_recetas_grilla->SetRowLabelSize( 1 );
	m_recetas_grilla->SetRowLabelAlignment( wxALIGN_CENTER, wxALIGN_CENTER );

	// Label Appearance

	// Cell Defaults
	m_recetas_grilla->SetDefaultCellAlignment( wxALIGN_LEFT, wxALIGN_CENTER );
	bSizer41->Add( m_recetas_grilla, 1, wxALL|wxEXPAND, 5 );


	m_recetas_panel->SetSizer( bSizer41 );
	m_recetas_panel->Layout();
	bSizer41->Fit( m_recetas_panel );
	m_insumos_notebook->AddPage( m_recetas_panel, wxT("Recetas"), false );
	m_produccion_panel = new wxPanel( m_insumos_notebook, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxBoxSizer* bSizer411;
	bSizer411 = new wxBoxSizer( wxVERTICAL );

	m_prod_grilla = new wxGrid( m_produccion_panel, wxID_ANY, wxDefaultPosition, wxDefaultSize, 0 );

	// Grid
	m_prod_grilla->CreateGrid( 0, 4 );
	m_prod_grilla->EnableEditing( false );
	m_prod_grilla->EnableGridLines( true );
	m_prod_grilla->EnableDragGridSize( false );
	m_prod_grilla->SetMargins( 0, 0 );

	// Columns
	m_prod_grilla->SetColSize( 0, 0 );
	m_prod_grilla->SetColSize( 1, 225 );
	m_prod_grilla->SetColSize( 2, 180 );
	m_prod_grilla->SetColSize( 3, 275 );
	m_prod_grilla->EnableDragColMove( false );
	m_prod_grilla->EnableDragColSize( true );
	m_prod_grilla->SetColLabelValue( 0, wxT("ID") );
	m_prod_grilla->SetColLabelValue( 1, wxT("Fecha") );
	m_prod_grilla->SetColLabelValue( 2, wxT("N. Productos") );
	m_prod_grilla->SetColLabelValue( 3, wxT("Costo total ($)") );
	m_prod_grilla->SetColLabelAlignment( wxALIGN_CENTER, wxALIGN_CENTER );

	// Rows
	m_prod_grilla->EnableDragRowSize( true );
	m_prod_grilla->SetRowLabelSize( 1 );
	m_prod_grilla->SetRowLabelAlignment( wxALIGN_CENTER, wxALIGN_CENTER );

	// Label Appearance

	// Cell Defaults
	m_prod_grilla->SetDefaultCellAlignment( wxALIGN_LEFT, wxALIGN_CENTER );
	bSizer411->Add( m_prod_grilla, 1, wxALL|wxEXPAND, 10 );

	wxBoxSizer* bSizer55;
	bSizer55 = new wxBoxSizer( wxHORIZONTAL );

	m_prod_btn_nuevo = new wxButton( m_produccion_panel, wxID_ANY, wxT("Nueva orden"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer55->Add( m_prod_btn_nuevo, 0, wxALL, 5 );

	m_prod_btn_ver = new wxButton( m_produccion_panel, wxID_ANY, wxT("Ver orden"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer55->Add( m_prod_btn_ver, 0, wxALL, 5 );

	m_prod_btn_vaciar = new wxButton( m_produccion_panel, wxID_ANY, wxT("Vaciar historial"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer55->Add( m_prod_btn_vaciar, 0, wxALL, 5 );


	bSizer411->Add( bSizer55, 0, wxALIGN_RIGHT|wxALL, 5 );


	m_produccion_panel->SetSizer( bSizer411 );
	m_produccion_panel->Layout();
	bSizer411->Fit( m_produccion_panel );
	m_insumos_notebook->AddPage( m_produccion_panel, wxT("Producción"), false );

	bSizer->Add( m_insumos_notebook, 1, wxALL|wxEXPAND, 5 );


	this->SetSizer( bSizer );
	this->Layout();

	this->Centre( wxBOTH );

	// Connect Events
	m_insumos_busqueda->Connect( wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler( WinPrincipalBase::ins_OnTextBusqueda ), NULL, this );
	m_insumos_boton_nuevo->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( WinPrincipalBase::ins_OnClickNuevo ), NULL, this );
	m_insumos_boton_editar->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( WinPrincipalBase::ins_OnClickEditar ), NULL, this );
	m_insumos_boton_eliminar->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( WinPrincipalBase::ins_OnClickEliminar ), NULL, this );
	m_insumos_grilla->Connect( wxEVT_GRID_CELL_LEFT_DCLICK, wxGridEventHandler( WinPrincipalBase::ins_OnGrillaDobleClick ), NULL, this );
	m_insumos_grilla->Connect( wxEVT_GRID_LABEL_LEFT_CLICK, wxGridEventHandler( WinPrincipalBase::ins_OnGrillaLabelClick ), NULL, this );
	m_recetas_busqueda->Connect( wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler( WinPrincipalBase::rec_OnTextBusqueda ), NULL, this );
	m_recetas_btn_nuevo->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( WinPrincipalBase::rec_OnClickNuevo ), NULL, this );
	m_recetas_btn_editar->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( WinPrincipalBase::rec_OnClickEditar ), NULL, this );
	m_recetas_btn_eliminar->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( WinPrincipalBase::rec_OnClickEliminar ), NULL, this );
	m_recetas_grilla->Connect( wxEVT_GRID_CELL_LEFT_DCLICK, wxGridEventHandler( WinPrincipalBase::rec_OnGrillaDobleClick ), NULL, this );
	m_recetas_grilla->Connect( wxEVT_GRID_LABEL_LEFT_CLICK, wxGridEventHandler( WinPrincipalBase::rec_OnGrillaLabelClick ), NULL, this );
	m_prod_grilla->Connect( wxEVT_GRID_CELL_LEFT_DCLICK, wxGridEventHandler( WinPrincipalBase::prod_OnGrillaDobleClick ), NULL, this );
	m_prod_btn_nuevo->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( WinPrincipalBase::prod_OnClickNuevo ), NULL, this );
	m_prod_btn_ver->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( WinPrincipalBase::prod_OnClickVer ), NULL, this );
	m_prod_btn_vaciar->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( WinPrincipalBase::prod_OnClickVaciar ), NULL, this );
}

WinPrincipalBase::~WinPrincipalBase()
{
	// Disconnect Events
	m_insumos_busqueda->Disconnect( wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler( WinPrincipalBase::ins_OnTextBusqueda ), NULL, this );
	m_insumos_boton_nuevo->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( WinPrincipalBase::ins_OnClickNuevo ), NULL, this );
	m_insumos_boton_editar->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( WinPrincipalBase::ins_OnClickEditar ), NULL, this );
	m_insumos_boton_eliminar->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( WinPrincipalBase::ins_OnClickEliminar ), NULL, this );
	m_insumos_grilla->Disconnect( wxEVT_GRID_CELL_LEFT_DCLICK, wxGridEventHandler( WinPrincipalBase::ins_OnGrillaDobleClick ), NULL, this );
	m_insumos_grilla->Disconnect( wxEVT_GRID_LABEL_LEFT_CLICK, wxGridEventHandler( WinPrincipalBase::ins_OnGrillaLabelClick ), NULL, this );
	m_recetas_busqueda->Disconnect( wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler( WinPrincipalBase::rec_OnTextBusqueda ), NULL, this );
	m_recetas_btn_nuevo->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( WinPrincipalBase::rec_OnClickNuevo ), NULL, this );
	m_recetas_btn_editar->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( WinPrincipalBase::rec_OnClickEditar ), NULL, this );
	m_recetas_btn_eliminar->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( WinPrincipalBase::rec_OnClickEliminar ), NULL, this );
	m_recetas_grilla->Disconnect( wxEVT_GRID_CELL_LEFT_DCLICK, wxGridEventHandler( WinPrincipalBase::rec_OnGrillaDobleClick ), NULL, this );
	m_recetas_grilla->Disconnect( wxEVT_GRID_LABEL_LEFT_CLICK, wxGridEventHandler( WinPrincipalBase::rec_OnGrillaLabelClick ), NULL, this );
	m_prod_grilla->Disconnect( wxEVT_GRID_CELL_LEFT_DCLICK, wxGridEventHandler( WinPrincipalBase::prod_OnGrillaDobleClick ), NULL, this );
	m_prod_btn_nuevo->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( WinPrincipalBase::prod_OnClickNuevo ), NULL, this );
	m_prod_btn_ver->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( WinPrincipalBase::prod_OnClickVer ), NULL, this );
	m_prod_btn_vaciar->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( WinPrincipalBase::prod_OnClickVaciar ), NULL, this );

}

DialogBaseInsumo::DialogBaseInsumo( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxDialog( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );

	wxBoxSizer* bSizer108;
	bSizer108 = new wxBoxSizer( wxVERTICAL );

	wxBoxSizer* bSizer11;
	bSizer11 = new wxBoxSizer( wxHORIZONTAL );

	m_static_text_1 = new wxStaticText( this, wxID_ANY, wxT("Tipo:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_static_text_1->Wrap( -1 );
	bSizer11->Add( m_static_text_1, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );

	wxString m_opcion_tipoChoices[] = { wxT("Harina"), wxT("Líquido"), wxT("Grasa"), wxT("Fermento"), wxT("Semilla"), wxT("Extra") };
	int m_opcion_tipoNChoices = sizeof( m_opcion_tipoChoices ) / sizeof( wxString );
	m_opcion_tipo = new wxChoice( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, m_opcion_tipoNChoices, m_opcion_tipoChoices, 0 );
	m_opcion_tipo->SetSelection( 0 );
	bSizer11->Add( m_opcion_tipo, 1, wxALL|wxALIGN_CENTER_VERTICAL, 5 );

	m_staticline4 = new wxStaticLine( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLI_VERTICAL );
	bSizer11->Add( m_staticline4, 0, wxEXPAND | wxALL, 5 );

	m_staticText9 = new wxStaticText( this, wxID_ANY, wxT("Unidad:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText9->Wrap( -1 );
	bSizer11->Add( m_staticText9, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );

	wxString m_opcion_unidadChoices[] = { wxT("ud"), wxT("g"), wxT("kg"), wxT("ml"), wxT("L") };
	int m_opcion_unidadNChoices = sizeof( m_opcion_unidadChoices ) / sizeof( wxString );
	m_opcion_unidad = new wxChoice( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, m_opcion_unidadNChoices, m_opcion_unidadChoices, 0 );
	m_opcion_unidad->SetSelection( 0 );
	bSizer11->Add( m_opcion_unidad, 1, wxALL|wxALIGN_CENTER_VERTICAL, 5 );


	bSizer108->Add( bSizer11, 0, wxEXPAND, 5 );

	wxBoxSizer* bSizer111;
	bSizer111 = new wxBoxSizer( wxHORIZONTAL );

	m_static_text_2 = new wxStaticText( this, wxID_ANY, wxT("Nombre:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_static_text_2->Wrap( -1 );
	bSizer111->Add( m_static_text_2, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );

	m_text_nombre = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	bSizer111->Add( m_text_nombre, 1, wxALL|wxALIGN_CENTER_VERTICAL, 5 );


	bSizer108->Add( bSizer111, 0, wxEXPAND, 5 );

	wxBoxSizer* bSizer112;
	bSizer112 = new wxBoxSizer( wxHORIZONTAL );

	m_static_text_3 = new wxStaticText( this, wxID_ANY, wxT("Stock:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_static_text_3->Wrap( -1 );
	bSizer112->Add( m_static_text_3, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );

	m_text_stock = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	bSizer112->Add( m_text_stock, 1, wxALL|wxALIGN_CENTER_VERTICAL, 5 );


	bSizer108->Add( bSizer112, 0, wxEXPAND, 5 );

	wxBoxSizer* bSizer113;
	bSizer113 = new wxBoxSizer( wxHORIZONTAL );

	m_statictext_costo = new wxStaticText( this, wxID_ANY, wxT("Costo / ud:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_statictext_costo->Wrap( -1 );
	bSizer113->Add( m_statictext_costo, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );

	m_text_costo = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	bSizer113->Add( m_text_costo, 1, wxALL|wxALIGN_CENTER_VERTICAL, 5 );


	bSizer108->Add( bSizer113, 0, wxEXPAND, 5 );

	wxBoxSizer* bSizer23;
	bSizer23 = new wxBoxSizer( wxHORIZONTAL );

	m_guardar = new wxButton( this, wxID_ANY, wxT("Guardar"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer23->Add( m_guardar, 0, wxALL, 5 );

	m_cancelar = new wxButton( this, wxID_ANY, wxT("Cancelar"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer23->Add( m_cancelar, 0, wxALL, 5 );


	bSizer108->Add( bSizer23, 0, wxALIGN_RIGHT, 5 );


	this->SetSizer( bSizer108 );
	this->Layout();

	this->Centre( wxBOTH );

	// Connect Events
	m_opcion_unidad->Connect( wxEVT_COMMAND_CHOICE_SELECTED, wxCommandEventHandler( DialogBaseInsumo::OnEligeUnidad ), NULL, this );
	m_guardar->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( DialogBaseInsumo::OnClickGuardar ), NULL, this );
	m_cancelar->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( DialogBaseInsumo::OnClickCancelar ), NULL, this );
}

DialogBaseInsumo::~DialogBaseInsumo()
{
	// Disconnect Events
	m_opcion_unidad->Disconnect( wxEVT_COMMAND_CHOICE_SELECTED, wxCommandEventHandler( DialogBaseInsumo::OnEligeUnidad ), NULL, this );
	m_guardar->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( DialogBaseInsumo::OnClickGuardar ), NULL, this );
	m_cancelar->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( DialogBaseInsumo::OnClickCancelar ), NULL, this );

}

DialogBaseRecetas::DialogBaseRecetas( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxDialog( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );

	wxBoxSizer* bSizer12;
	bSizer12 = new wxBoxSizer( wxVERTICAL );

	wxBoxSizer* bSizer14;
	bSizer14 = new wxBoxSizer( wxHORIZONTAL );

	m_staticText5 = new wxStaticText( this, wxID_ANY, wxT("Nombre de la receta:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText5->Wrap( -1 );
	bSizer14->Add( m_staticText5, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );

	m_recetaEditar_text_nombre = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	bSizer14->Add( m_recetaEditar_text_nombre, 1, wxALL, 5 );


	bSizer12->Add( bSizer14, 0, wxEXPAND, 5 );

	m_staticline111 = new wxStaticLine( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLI_VERTICAL );
	bSizer12->Add( m_staticline111, 0, wxEXPAND | wxALL, 5 );

	wxBoxSizer* bSizer15;
	bSizer15 = new wxBoxSizer( wxHORIZONTAL );

	wxBoxSizer* bSizer17;
	bSizer17 = new wxBoxSizer( wxVERTICAL );

	m_text1 = new wxStaticText( this, wxID_ANY, wxT("Seleccione un insumo"), wxDefaultPosition, wxDefaultSize, wxALIGN_CENTER_HORIZONTAL );
	m_text1->Wrap( -1 );
	bSizer17->Add( m_text1, 0, wxALIGN_CENTER_HORIZONTAL|wxBOTTOM|wxLEFT|wxRIGHT, 5 );

	m_recetaEditar_busqueda = new wxSearchCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	#ifndef __WXMAC__
	m_recetaEditar_busqueda->ShowSearchButton( true );
	#endif
	m_recetaEditar_busqueda->ShowCancelButton( false );
	bSizer17->Add( m_recetaEditar_busqueda, 0, wxEXPAND|wxLEFT|wxRIGHT|wxTOP, 5 );

	m_recetaEditar_lista_insumos = new wxListBox( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, 0, NULL, 0 );
	bSizer17->Add( m_recetaEditar_lista_insumos, 1, wxBOTTOM|wxEXPAND|wxLEFT|wxRIGHT, 5 );

	wxBoxSizer* bSizer201;
	bSizer201 = new wxBoxSizer( wxHORIZONTAL );

	m_recetaEditar_btn_agregar = new wxButton( this, wxID_ANY, wxT("Agregar"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer201->Add( m_recetaEditar_btn_agregar, 0, wxALL, 5 );

	m_recetaEditar_btn_eliminar = new wxButton( this, wxID_ANY, wxT("Eliminar"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer201->Add( m_recetaEditar_btn_eliminar, 0, wxALL, 5 );


	bSizer17->Add( bSizer201, 0, 0, 5 );


	bSizer15->Add( bSizer17, 0, wxEXPAND, 5 );

	m_staticline1 = new wxStaticLine( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLI_VERTICAL );
	bSizer15->Add( m_staticline1, 0, wxEXPAND|wxRIGHT|wxLEFT, 5 );

	wxBoxSizer* bSizer19;
	bSizer19 = new wxBoxSizer( wxVERTICAL );

	m_staticText8 = new wxStaticText( this, wxID_ANY, wxT("Lista de ingredientes"), wxDefaultPosition, wxDefaultSize, wxALIGN_CENTER_HORIZONTAL );
	m_staticText8->Wrap( -1 );
	bSizer19->Add( m_staticText8, 0, wxALIGN_CENTER_HORIZONTAL|wxBOTTOM|wxRIGHT|wxLEFT, 5 );

	m_recetaEditar_grilla = new wxGrid( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, 0 );

	// Grid
	m_recetaEditar_grilla->CreateGrid( 0, 4 );
	m_recetaEditar_grilla->EnableEditing( true );
	m_recetaEditar_grilla->EnableGridLines( true );
	m_recetaEditar_grilla->EnableDragGridSize( false );
	m_recetaEditar_grilla->SetMargins( 0, 0 );

	// Columns
	m_recetaEditar_grilla->SetColSize( 0, 0 );
	m_recetaEditar_grilla->SetColSize( 1, 181 );
	m_recetaEditar_grilla->SetColSize( 2, 108 );
	m_recetaEditar_grilla->SetColSize( 3, 45 );
	m_recetaEditar_grilla->EnableDragColMove( false );
	m_recetaEditar_grilla->EnableDragColSize( true );
	m_recetaEditar_grilla->SetColLabelValue( 0, wxT("Id") );
	m_recetaEditar_grilla->SetColLabelValue( 1, wxT("Insumo") );
	m_recetaEditar_grilla->SetColLabelValue( 2, wxT("Cantidad") );
	m_recetaEditar_grilla->SetColLabelValue( 3, wxT("Ud.") );
	m_recetaEditar_grilla->SetColLabelAlignment( wxALIGN_CENTER, wxALIGN_CENTER );

	// Rows
	m_recetaEditar_grilla->EnableDragRowSize( true );
	m_recetaEditar_grilla->SetRowLabelSize( 25 );
	m_recetaEditar_grilla->SetRowLabelAlignment( wxALIGN_CENTER, wxALIGN_CENTER );

	// Label Appearance

	// Cell Defaults
	m_recetaEditar_grilla->SetDefaultCellAlignment( wxALIGN_LEFT, wxALIGN_CENTER );
	bSizer19->Add( m_recetaEditar_grilla, 1, wxALL|wxEXPAND, 5 );


	bSizer15->Add( bSizer19, 1, wxEXPAND, 5 );


	bSizer12->Add( bSizer15, 1, wxEXPAND, 5 );

	m_staticline1111 = new wxStaticLine( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLI_HORIZONTAL|wxLI_VERTICAL );
	bSizer12->Add( m_staticline1111, 0, wxEXPAND|wxTOP|wxRIGHT|wxLEFT, 5 );

	wxBoxSizer* bSizer20;
	bSizer20 = new wxBoxSizer( wxHORIZONTAL );

	m_recetaEditar_btn_guardar = new wxButton( this, wxID_ANY, wxT("Guardar"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer20->Add( m_recetaEditar_btn_guardar, 0, wxALL, 5 );

	m_recetaEditar_btn_salir = new wxButton( this, wxID_ANY, wxT("Cancelar"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer20->Add( m_recetaEditar_btn_salir, 0, wxALL, 5 );


	bSizer12->Add( bSizer20, 0, wxALIGN_RIGHT, 5 );


	this->SetSizer( bSizer12 );
	this->Layout();

	this->Centre( wxBOTH );

	// Connect Events
	this->Connect( wxEVT_CLOSE_WINDOW, wxCloseEventHandler( DialogBaseRecetas::OnClose ) );
	m_recetaEditar_text_nombre->Connect( wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler( DialogBaseRecetas::OnCambioNombre ), NULL, this );
	m_recetaEditar_busqueda->Connect( wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler( DialogBaseRecetas::OnTextBusqueda ), NULL, this );
	m_recetaEditar_lista_insumos->Connect( wxEVT_COMMAND_LISTBOX_DOUBLECLICKED, wxCommandEventHandler( DialogBaseRecetas::OnDobleClickInsumo ), NULL, this );
	m_recetaEditar_btn_agregar->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( DialogBaseRecetas::OnClickAgregar ), NULL, this );
	m_recetaEditar_btn_eliminar->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( DialogBaseRecetas::OnClickEliminar ), NULL, this );
	m_recetaEditar_grilla->Connect( wxEVT_GRID_CELL_CHANGED, wxGridEventHandler( DialogBaseRecetas::OnCambioValorCelda ), NULL, this );
	m_recetaEditar_btn_guardar->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( DialogBaseRecetas::OnClickGuardar ), NULL, this );
	m_recetaEditar_btn_salir->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( DialogBaseRecetas::OnClickSalir ), NULL, this );
}

DialogBaseRecetas::~DialogBaseRecetas()
{
	// Disconnect Events
	this->Disconnect( wxEVT_CLOSE_WINDOW, wxCloseEventHandler( DialogBaseRecetas::OnClose ) );
	m_recetaEditar_text_nombre->Disconnect( wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler( DialogBaseRecetas::OnCambioNombre ), NULL, this );
	m_recetaEditar_busqueda->Disconnect( wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler( DialogBaseRecetas::OnTextBusqueda ), NULL, this );
	m_recetaEditar_lista_insumos->Disconnect( wxEVT_COMMAND_LISTBOX_DOUBLECLICKED, wxCommandEventHandler( DialogBaseRecetas::OnDobleClickInsumo ), NULL, this );
	m_recetaEditar_btn_agregar->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( DialogBaseRecetas::OnClickAgregar ), NULL, this );
	m_recetaEditar_btn_eliminar->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( DialogBaseRecetas::OnClickEliminar ), NULL, this );
	m_recetaEditar_grilla->Disconnect( wxEVT_GRID_CELL_CHANGED, wxGridEventHandler( DialogBaseRecetas::OnCambioValorCelda ), NULL, this );
	m_recetaEditar_btn_guardar->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( DialogBaseRecetas::OnClickGuardar ), NULL, this );
	m_recetaEditar_btn_salir->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( DialogBaseRecetas::OnClickSalir ), NULL, this );

}

DialogProducciones::DialogProducciones( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxDialog( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );

	wxBoxSizer* bSizer19;
	bSizer19 = new wxBoxSizer( wxVERTICAL );

	wxBoxSizer* bSizer201;
	bSizer201 = new wxBoxSizer( wxHORIZONTAL );

	m_statictext_prod = new wxStaticText( this, wxID_ANY, wxT("Producto:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_statictext_prod->Wrap( -1 );
	bSizer201->Add( m_statictext_prod, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );

	wxArrayString m_lista_recetasChoices;
	m_lista_recetas = new wxChoice( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, m_lista_recetasChoices, 0 );
	m_lista_recetas->SetSelection( 0 );
	bSizer201->Add( m_lista_recetas, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );


	bSizer201->Add( 1, 0, 1, wxEXPAND, 5 );

	m_statictext_uni = new wxStaticText( this, wxID_ANY, wxT("Unidades:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_statictext_uni->Wrap( -1 );
	bSizer201->Add( m_statictext_uni, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );

	m_spin_cantidad = new wxSpinCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxSP_ARROW_KEYS, 1, 999, 1 );
	bSizer201->Add( m_spin_cantidad, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );


	bSizer201->Add( 1, 0, 1, wxEXPAND, 5 );

	m_btn_agregar = new wxButton( this, wxID_ANY, wxT("Agregar"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer201->Add( m_btn_agregar, 0, wxALL, 5 );


	bSizer19->Add( bSizer201, 0, wxEXPAND, 5 );

	m_staticline5 = new wxStaticLine( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLI_HORIZONTAL );
	bSizer19->Add( m_staticline5, 0, wxEXPAND | wxALL, 5 );

	m_prod_grilla = new wxGrid( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, 0 );

	// Grid
	m_prod_grilla->CreateGrid( 0, 3 );
	m_prod_grilla->EnableEditing( false );
	m_prod_grilla->EnableGridLines( true );
	m_prod_grilla->EnableDragGridSize( false );
	m_prod_grilla->SetMargins( 0, 0 );

	// Columns
	m_prod_grilla->SetColSize( 0, 0 );
	m_prod_grilla->SetColSize( 1, 240 );
	m_prod_grilla->SetColSize( 2, 264 );
	m_prod_grilla->EnableDragColMove( false );
	m_prod_grilla->EnableDragColSize( true );
	m_prod_grilla->SetColLabelValue( 0, wxT("ID") );
	m_prod_grilla->SetColLabelValue( 1, wxT("Producto") );
	m_prod_grilla->SetColLabelValue( 2, wxT("Cantidad") );
	m_prod_grilla->SetColLabelAlignment( wxALIGN_CENTER, wxALIGN_CENTER );

	// Rows
	m_prod_grilla->EnableDragRowSize( true );
	m_prod_grilla->SetRowLabelSize( 30 );
	m_prod_grilla->SetRowLabelAlignment( wxALIGN_CENTER, wxALIGN_CENTER );

	// Label Appearance

	// Cell Defaults
	m_prod_grilla->SetDefaultCellAlignment( wxALIGN_LEFT, wxALIGN_TOP );
	bSizer19->Add( m_prod_grilla, 1, wxALL|wxEXPAND, 5 );

	m_btn_quitar = new wxButton( this, wxID_ANY, wxT("Quitar seleccionado"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer19->Add( m_btn_quitar, 0, wxALL|wxALIGN_CENTER_HORIZONTAL, 5 );

	m_staticline7 = new wxStaticLine( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLI_HORIZONTAL );
	bSizer19->Add( m_staticline7, 0, wxEXPAND | wxALL, 5 );

	wxBoxSizer* bSizer23;
	bSizer23 = new wxBoxSizer( wxHORIZONTAL );

	m_staticText151 = new wxStaticText( this, wxID_ANY, wxT("Fecha:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText151->Wrap( -1 );
	bSizer23->Add( m_staticText151, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );

	m_date_fecha = new wxDatePickerCtrl( this, wxID_ANY, wxDefaultDateTime, wxDefaultPosition, wxDefaultSize, wxDP_DROPDOWN );
	bSizer23->Add( m_date_fecha, 0, wxALL, 5 );


	bSizer23->Add( 0, 0, 1, wxEXPAND, 5 );

	m_staticText15 = new wxStaticText( this, wxID_ANY, wxT("Costo:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText15->Wrap( -1 );
	bSizer23->Add( m_staticText15, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );

	m_text_costo = new wxStaticText( this, wxID_ANY, wxT("$ 0.00"), wxDefaultPosition, wxDefaultSize, 0 );
	m_text_costo->Wrap( -1 );
	bSizer23->Add( m_text_costo, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );


	bSizer23->Add( 0, 0, 1, wxEXPAND, 5 );

	m_btn_confirmar = new wxButton( this, wxID_ANY, wxT("Confirmar"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer23->Add( m_btn_confirmar, 0, wxALL, 5 );

	m_btn_cancelar = new wxButton( this, wxID_ANY, wxT("Cancelar"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer23->Add( m_btn_cancelar, 0, wxALL, 5 );


	bSizer19->Add( bSizer23, 0, wxEXPAND, 5 );


	this->SetSizer( bSizer19 );
	this->Layout();

	this->Centre( wxBOTH );

	// Connect Events
	this->Connect( wxEVT_CLOSE_WINDOW, wxCloseEventHandler( DialogProducciones::OnClose ) );
	m_btn_agregar->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( DialogProducciones::OnClickAgregar ), NULL, this );
	m_prod_grilla->Connect( wxEVT_GRID_CELL_CHANGED, wxGridEventHandler( DialogProducciones::OnGrillaCambioCelda ), NULL, this );
	m_btn_quitar->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( DialogProducciones::OnClickQuitarSel ), NULL, this );
	m_btn_confirmar->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( DialogProducciones::OnClickConfirmar ), NULL, this );
	m_btn_cancelar->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( DialogProducciones::OnClickCancelar ), NULL, this );
}

DialogProducciones::~DialogProducciones()
{
	// Disconnect Events
	this->Disconnect( wxEVT_CLOSE_WINDOW, wxCloseEventHandler( DialogProducciones::OnClose ) );
	m_btn_agregar->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( DialogProducciones::OnClickAgregar ), NULL, this );
	m_prod_grilla->Disconnect( wxEVT_GRID_CELL_CHANGED, wxGridEventHandler( DialogProducciones::OnGrillaCambioCelda ), NULL, this );
	m_btn_quitar->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( DialogProducciones::OnClickQuitarSel ), NULL, this );
	m_btn_confirmar->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( DialogProducciones::OnClickConfirmar ), NULL, this );
	m_btn_cancelar->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( DialogProducciones::OnClickCancelar ), NULL, this );

}
