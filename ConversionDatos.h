#ifndef CONVERSIONDATOS_H
#define CONVERSIONDATOS_H
#include "Insumo.h"
#include <string>
#include <wx/string.h>

/// para convertir un c-string, o una constante, a wxString
inline wxString c_to_wx(const char *c_str) { 
	return wxString::From8BitData(c_str); 
}
/// para convertir un std::string a wxString
inline wxString str_to_wx(const std::string &std_str) { 
	return wxString::From8BitData(std_str.c_str()); 
}
/// para convertir wxString a std::string
inline std::string wx_to_str(const wxString &wx_str) { 
	return static_cast<const char*>(wx_str.To8BitData()); 
}
/// para convertir un int o flaot a wxString
inline wxString num_to_wx(const int &num) { 
	std::string s = std::to_string(num);
	return str_to_wx(s); 
}
/* -------el problema de hacerlo así es que me devuelve un float con 6 decimales
inline wxString num_to_wx(const float &num) { 
	std::string s = std::to_string(num);
	return str_to_wx(s); 
} */
inline wxString num_to_wx(const float &num) { 
	// "%.2f": flotante (f) con 2 decimales (.2)
	return wxString::Format("%.2f", num); 
}

/// convertir wxString a TipoInsumo
inline TipoInsumo wx_to_tipoIns(const wxString &wx_str) {
	if ( wx_str == "Harina" ) return HARINA;
	if ( wx_str == "Líquido" ) return LIQUIDO;
	if ( wx_str == "Grasa" ) return GRASA;
	if ( wx_str == "Fermento" ) return FERMENTO;
	if ( wx_str == "Semilla" ) return SEMILLA;
	if ( wx_str == "Extra" ) return EXTRAS;
}

/// convertir int a TipoInsumo
inline TipoInsumo int_to_tipoIns(const int &num) {
	switch (num) {
	case 0: return HARINA;
	case 1: return LIQUIDO;
	case 2: return GRASA;
	case 3: return FERMENTO;
	case 4: return SEMILLA;
	case 5: return EXTRAS;
	default: return VACIO;
	}
}

/// convertir TipoInsumo a int
inline int tipoIns_to_int(const TipoInsumo &tipo) {
	switch (tipo) {
	case HARINA: return 0;
	case LIQUIDO: return 1;
	case GRASA: return 2;
	case FERMENTO: return 3;
	case SEMILLA: return 4;
	case EXTRAS: return 5;
	default: return -1;
	}
}

/// convertir tipo insumo a wxstring
inline wxString tipoins_to_wx(const TipoInsumo &t) {
	switch (t) {
	case HARINA: return "Harina";
	case LIQUIDO: return "Líquido";
	case GRASA: return "Grasa";
	case FERMENTO: return "Fermento";
	case SEMILLA: return "Semilla";
	case EXTRAS: return "Extra";
	default: return "Vacío";
	}
}

/// convertir int a unidad
inline std::string int_to_unidad(const int &num) {
	switch (num) {
	case 0: return "ud";
	case 1: return "g";
	case 2: return "kg";
	case 3: return "ml";
	case 4: return "L";
	default: return "";
	}
}

/// convertir unidad a int
inline int unidad_to_int(const std::string &uni) {
	if ( uni == "ud" ) return 0;
	if ( uni == "g" ) return 1;
	if ( uni == "kg" ) return 2;
	if ( uni == "ml" ) return 3;
	if ( uni == "L" ) return 4;
	return -1;
}

#endif
