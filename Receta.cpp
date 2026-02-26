#include "Receta.h"
#include "Insumo.h"
#include <string>
#include <vector>
#include <algorithm>
#include <cstring>

/// CONSTRUCTOR
Receta::Receta(std::string nombre) :
	m_nombre(nombre) {}

/// FUNCIONES VER
std::string Receta::verNombre() const { return m_nombre; }
int Receta::verCantidadIngredientes() const { return m_ingredientes.size(); }
int Receta::verId() const { return m_id; }

/// FUNCION VALIDAR DATOS
std::string Receta::validarDatos()
{
	std::string errores;
	
	// valido nombre vacío
	if ( m_nombre.size() == 0 ) errores += "- El nombre no puede estar vacío.\n";
	
	// valido que haya ingredientes
	size_t cant = m_ingredientes.size();
	if ( cant == 0 )
	{
		errores += "- La receta no puede tener 0 ingredientes.\n";
	}
	
	// valido que las cantidades sean positivas
	for (size_t i=0; i<cant; ++i)
	{
		if ( m_ingredientes[i].cantidad <= 0 )
		{
			errores += "- Ingrediente " + std::to_string(i+1) + ": la cantidad debe ser mayor a cero.\n";
		}
	}
	return errores;
}

/// FUNCIONES QUE MODIFICAN DATOS
/// estable id
void Receta::establecerId(int id_receta) { m_id = id_receta; }

/// modifica el nombre
void Receta::modificarNombre(std::string nombre) { m_nombre = nombre; }

/// modifica ingrediente específico
void Receta::modificarIngrediente(int id_insumo, float cant)
{
	auto it = find(m_ingredientes.begin(), m_ingredientes.end(), id_insumo);
	
	// no está en el vector: lo agrego
	if ( it == m_ingredientes.end() )
	{
		Ingrediente aux = {id_insumo, cant};
		m_ingredientes.push_back(aux);
	}
	// está en el vector: lo modifico
	else 
	{
		it->cantidad = cant;
	}
}

/// elimina ingrediente específico
bool Receta::eliminarIngrediente(int id_insumo)
{
	auto it = find(m_ingredientes.begin(), m_ingredientes.end(), id_insumo);
	
	// no está en el vector: devuelvo falso
	if ( it==m_ingredientes.end() ) return false;
	
	// está en el vector: elimino y devuelvo true
	m_ingredientes.erase(it);
	return true;
}

/// modifica la receta completa, funciona como un =
void Receta::sobreescribir(Receta rec)
{
	m_nombre = rec.verNombre();
	
	m_ingredientes.clear();
	int cant = rec.verCantidadIngredientes();
	
	for (int i=0; i<cant; ++i)
	{
		Ingrediente aux = rec[i];
		// sirve para agregar
		this->modificarIngrediente(aux.id, aux.cantidad);
	}
}

/// REGISTRO PARA GUARDAR EN ARCHIVO
RegistroReceta Receta::crearRegistro()
{
	RegistroReceta aux;
	aux.id = m_id;
	aux.cantidad = m_ingredientes.size();
	
	// aseguro el tamaño del c_string
	strncpy(aux.nombre, m_nombre.c_str(), sizeof(aux.nombre) - 1);
	aux.nombre[sizeof(aux.nombre) - 1] = '\0';
	
	return aux;
}

/// OPERADORES
Ingrediente Receta::operator[] (size_t i) 
{
	if ( i >= m_ingredientes.size() )
	{
		Ingrediente vacio = {-1, 0}; // ID = -1, indicando error/vacío
		return vacio;
	}
	
	return m_ingredientes[i];
}

bool Receta::operator==(int id_receta) { return m_id == id_receta; }

bool Receta::operator==(std::string nombre_receta)
{
	std::string aux_nombre = m_nombre;
	
	// paso ambos a minúsculas para comparar
	for (char &c : aux_nombre) c = tolower(c);
	for (char &c : nombre_receta) c = tolower(c);
	
	if ( aux_nombre.find(nombre_receta, 0) == std::string::npos) return false;
	return true;
}

/// CRITERIOS DE COMPARACIÓN
bool rec_cmp_nombre(const Receta &rec1, const Receta &rec2)
{
	std::string n1 = rec1.verNombre(); for (char &c : n1) c = tolower(c);
	std::string n2 = rec2.verNombre(); for (char &c : n2) c = tolower(c);
	return n1 < n2;
}

bool rec_cmp_cantidad(const Receta &rec1, const Receta &rec2)
{
	return rec1.verCantidadIngredientes() < rec2.verCantidadIngredientes();
}

