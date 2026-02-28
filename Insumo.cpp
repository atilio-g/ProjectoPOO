#include "Insumo.h"
#include <string>
#include <cstring>
#include <algorithm>

Insumo::Insumo(std::string nombre, std::string unidad, TipoInsumo tipo, float costo, float stock) :
	m_nombre(nombre), m_unidad(unidad), m_tipo(tipo), m_costo(costo), m_stock(stock)
{
}

/// FUNCIONES VER
std::string Insumo::verNombre() const { return m_nombre; }
std::string Insumo::verUnidad() const { return m_unidad; }
TipoInsumo Insumo::verTipo() const { return m_tipo; }
int Insumo::verId() const { return m_id; }
float Insumo::verCosto() const { return m_costo; }
float Insumo::verStock() const { return m_stock; }

float Insumo::verStockVisual() const
{
	if (m_unidad == "kg" or m_unidad == "L")
		return m_stock / 1000.0f;
	
	return m_stock;
}

/// VALIDAR
std::string Insumo::validarNombre() 
{ 
	if ( m_nombre.size() == 0 ) 
		return "- El nombre no puede estar vacío.\n"; 
	return "";
}

std::string Insumo::validarUnidad()
{
	if ( m_unidad.size() == 0 ) 
		return "- Falta asignar unidad.\n";
	return "";
}

std::string Insumo::validarTipo()
{
	if ( m_tipo == VACIO ) 
		return "- Falta asignar categoría.\n";
	return "";
}

std::string Insumo::validarCosto()
{
	if ( m_costo < 0 ) 
		return "- El costo no puede ser negativo.\n";
	return "";
}

std::string Insumo::validarStock()
{
	if ( m_stock < 0 ) 
		return "- El stock no puede ser negativo.\n";
	return "";
}

std::string Insumo::validarTODO()
{
	std::string errores = validarNombre() + validarUnidad()
		+ validarTipo() + validarCosto() + validarStock();
	return errores;
}

/// FUNCIONES MODIFICAR
void Insumo::establecerId(int id_insumo) { m_id = id_insumo; }
void Insumo::modificarNombre(std::string nombre) { m_nombre = nombre; }
void Insumo::modificarUnidad(std::string unidad) { m_unidad = unidad; }
void Insumo::modificarTipo(TipoInsumo tipo) { m_tipo = tipo; }
void Insumo::modificarCosto(float costo) { m_costo = costo; }
void Insumo::modificarStock(float stock) { m_stock = stock; }

/// REGISTRO PARA GUARDAR EN ARCHIVO
RegistroIns Insumo::crearRegistro()
{
	RegistroIns aux;
	aux.tipo = m_tipo;
	aux.id = m_id;
	aux.costo = m_costo;
	aux.stock = m_stock;
	
	// aseguro el tamaño del c_string
	strncpy(aux.nombre, m_nombre.c_str(), sizeof(aux.nombre) - 1);
	aux.nombre[sizeof(aux.nombre) - 1] = '\0'; // aseguro el fin de cadena
	
	strncpy(aux.unidad, m_unidad.c_str(), sizeof(aux.unidad) - 1);
	aux.unidad[sizeof(aux.unidad) - 1] = '\0'; // aseguro el fin de cadena
	return aux;
}

/// OPERADORES
bool Insumo::operator==(int id_insumo) { return m_id == id_insumo; }

bool Insumo::operator==(std::string nombre_insumo)
{ 
	std::string aux_nombre = m_nombre;
	
	// paso ambos a minúsculas para comparar
	for (char &c : aux_nombre) c = tolower(c);
	for (char &c : nombre_insumo) c = tolower(c);
	
	if ( aux_nombre.find(nombre_insumo, 0) == std::string::npos) return false;
	return true;
}

/// CRITERIOS DE COMPARACIÓN
bool ins_cmp_nombre(const Insumo &ins1, const Insumo &ins2)
{
	std::string n1 = ins1.verNombre(); for (char &c : n1) c = tolower(c);
	std::string n2 = ins2.verNombre(); for (char &c : n2) c = tolower(c);
	return n1 < n2;
}

bool ins_cmp_tipo(const Insumo &ins1, const Insumo &ins2)
{
	return ins1.verTipo() < ins2.verTipo();
}

bool ins_cmp_costo(const Insumo &ins1, const Insumo &ins2)
{
	return ins1.verCosto() < ins2.verCosto();
}

bool ins_cmp_stock(const Insumo &ins1, const Insumo &ins2)
{
	return ins1.verStock() < ins2.verStock();
}
