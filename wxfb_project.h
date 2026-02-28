///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version 4.2.1-0-g80c4cb6)
// http://www.wxformbuilder.org/
//
// PLEASE DO *NOT* EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#pragma once

#include <wx/artprov.h>
#include <wx/xrc/xmlres.h>
#include <wx/string.h>
#include <wx/srchctrl.h>
#include <wx/gdicmn.h>
#include <wx/font.h>
#include <wx/colour.h>
#include <wx/settings.h>
#include <wx/button.h>
#include <wx/bitmap.h>
#include <wx/image.h>
#include <wx/icon.h>
#include <wx/sizer.h>
#include <wx/grid.h>
#include <wx/panel.h>
#include <wx/notebook.h>
#include <wx/frame.h>
#include <wx/stattext.h>
#include <wx/choice.h>
#include <wx/statline.h>
#include <wx/textctrl.h>
#include <wx/dialog.h>
#include <wx/listbox.h>
#include <wx/datectrl.h>
#include <wx/dateevt.h>
#include <wx/spinctrl.h>

///////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
/// Class WinPrincipalBase
///////////////////////////////////////////////////////////////////////////////
class WinPrincipalBase : public wxFrame
{
	private:

	protected:
		wxNotebook* m_insumos_notebook;
		wxPanel* m_insumos_panel;
		wxSearchCtrl* m_insumos_busqueda;
		wxButton* m_insumos_boton_nuevo;
		wxButton* m_insumos_boton_editar;
		wxButton* m_insumos_boton_eliminar;
		wxGrid* m_insumos_grilla;
		wxPanel* m_recetas_panel;
		wxSearchCtrl* m_recetas_busqueda;
		wxButton* m_recetas_btn_nuevo;
		wxButton* m_recetas_btn_editar;
		wxButton* m_recetas_btn_eliminar;
		wxGrid* m_recetas_grilla;
		wxPanel* m_produccion_panel;
		wxGrid* m_prod_grilla;
		wxButton* m_prod_btn_nuevo;
		wxButton* m_prod_btn_ver;
		wxButton* m_prod_btn_vaciar;

		// Virtual event handlers, override them in your derived class
		virtual void ins_OnTextBusqueda( wxCommandEvent& event ) { event.Skip(); }
		virtual void ins_OnClickNuevo( wxCommandEvent& event ) { event.Skip(); }
		virtual void ins_OnClickEditar( wxCommandEvent& event ) { event.Skip(); }
		virtual void ins_OnClickEliminar( wxCommandEvent& event ) { event.Skip(); }
		virtual void ins_OnGrillaDobleClick( wxGridEvent& event ) { event.Skip(); }
		virtual void ins_OnGrillaLabelClick( wxGridEvent& event ) { event.Skip(); }
		virtual void rec_OnTextBusqueda( wxCommandEvent& event ) { event.Skip(); }
		virtual void rec_OnClickNuevo( wxCommandEvent& event ) { event.Skip(); }
		virtual void rec_OnClickEditar( wxCommandEvent& event ) { event.Skip(); }
		virtual void rec_OnClickEliminar( wxCommandEvent& event ) { event.Skip(); }
		virtual void rec_OnGrillaDobleClick( wxGridEvent& event ) { event.Skip(); }
		virtual void rec_OnGrillaLabelClick( wxGridEvent& event ) { event.Skip(); }
		virtual void prod_OnGrillaDobleClick( wxGridEvent& event ) { event.Skip(); }
		virtual void prod_OnClickNuevo( wxCommandEvent& event ) { event.Skip(); }
		virtual void prod_OnClickVer( wxCommandEvent& event ) { event.Skip(); }
		virtual void prod_OnClickVaciar( wxCommandEvent& event ) { event.Skip(); }


	public:

		WinPrincipalBase( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = wxT("Aplicación para panadería"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 633,452 ), long style = wxDEFAULT_FRAME_STYLE|wxTAB_TRAVERSAL );

		~WinPrincipalBase();

};

///////////////////////////////////////////////////////////////////////////////
/// Class DialogBaseInsumo
///////////////////////////////////////////////////////////////////////////////
class DialogBaseInsumo : public wxDialog
{
	private:

	protected:
		wxStaticText* m_static_text_1;
		wxChoice* m_opcion_tipo;
		wxStaticLine* m_staticline4;
		wxStaticText* m_staticText9;
		wxChoice* m_opcion_unidad;
		wxStaticText* m_static_text_2;
		wxTextCtrl* m_text_nombre;
		wxStaticText* m_static_text_3;
		wxTextCtrl* m_text_stock;
		wxStaticText* m_statictext_costo;
		wxTextCtrl* m_text_costo;
		wxButton* m_guardar;
		wxButton* m_cancelar;

		// Virtual event handlers, override them in your derived class
		virtual void OnEligeUnidad( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnClickGuardar( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnClickCancelar( wxCommandEvent& event ) { event.Skip(); }


	public:

		DialogBaseInsumo( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = wxEmptyString, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 389,196 ), long style = wxDEFAULT_DIALOG_STYLE );

		~DialogBaseInsumo();

};

///////////////////////////////////////////////////////////////////////////////
/// Class DialogBaseRecetas
///////////////////////////////////////////////////////////////////////////////
class DialogBaseRecetas : public wxDialog
{
	private:

	protected:
		wxStaticText* m_staticText5;
		wxTextCtrl* m_recetaEditar_text_nombre;
		wxStaticLine* m_staticline111;
		wxStaticText* m_text1;
		wxSearchCtrl* m_recetaEditar_busqueda;
		wxListBox* m_recetaEditar_lista_insumos;
		wxButton* m_recetaEditar_btn_agregar;
		wxButton* m_recetaEditar_btn_eliminar;
		wxStaticLine* m_staticline1;
		wxStaticText* m_staticText8;
		wxGrid* m_recetaEditar_grilla;
		wxStaticLine* m_staticline1111;
		wxButton* m_recetaEditar_btn_guardar;
		wxButton* m_recetaEditar_btn_salir;

		// Virtual event handlers, override them in your derived class
		virtual void OnClose( wxCloseEvent& event ) { event.Skip(); }
		virtual void OnCambioNombre( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnTextBusqueda( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnDobleClickInsumo( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnClickAgregar( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnClickEliminar( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnCambioValorCelda( wxGridEvent& event ) { event.Skip(); }
		virtual void OnClickGuardar( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnClickSalir( wxCommandEvent& event ) { event.Skip(); }


	public:

		DialogBaseRecetas( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = wxT("Detalles de receta"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 547,370 ), long style = wxDEFAULT_DIALOG_STYLE );

		~DialogBaseRecetas();

};

///////////////////////////////////////////////////////////////////////////////
/// Class DialogProducciones
///////////////////////////////////////////////////////////////////////////////
class DialogProducciones : public wxDialog
{
	private:

	protected:
		wxStaticText* m_staticText151;
		wxDatePickerCtrl* m_date_fecha;
		wxStaticText* m_statictext_prod;
		wxChoice* m_lista_recetas;
		wxStaticText* m_statictext_uni;
		wxSpinCtrl* m_spin_cantidad;
		wxButton* m_btn_agregar;
		wxStaticLine* m_staticline5;
		wxGrid* m_prod_grilla;
		wxButton* m_btn_quitar;
		wxStaticLine* m_staticline7;
		wxStaticText* m_staticText15;
		wxStaticText* m_text_costo;
		wxButton* m_btn_confirmar;
		wxButton* m_btn_cancelar;

		// Virtual event handlers, override them in your derived class
		virtual void OnClose( wxCloseEvent& event ) { event.Skip(); }
		virtual void OnClickAgregar( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnGrillaCambioCelda( wxGridEvent& event ) { event.Skip(); }
		virtual void OnClickQuitarSel( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnClickConfirmar( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnClickCancelar( wxCommandEvent& event ) { event.Skip(); }


	public:

		DialogProducciones( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = wxT("Registrar nueva producción"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 547,370 ), long style = wxDEFAULT_DIALOG_STYLE );

		~DialogProducciones();

};

