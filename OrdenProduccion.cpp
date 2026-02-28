#include "OrdenProduccion.h"
#include <cstring>

/// CONSTRUCTOR
OrdenProduccion::OrdenProduccion(std::string fecha) : 
	m_id(0), m_fecha(fecha), m_costo_total(0.0f) 
{
}

/// FUNCIONES VER
int OrdenProduccion::verId() const { return m_id; }
std::string OrdenProduccion::verFecha() const { return m_fecha; }
float OrdenProduccion::verCostoTotal() const { return m_costo_total; }
ItemOrden OrdenProduccion::operator[](size_t i) const { return m_items[i]; }

int OrdenProduccion::verCantidadPorTipoItems() const { return m_items.size(); }

int OrdenProduccion::verCantidadTotalItems() const
{ 
	int total_items = 0;
	int cant_ordenes = m_items.size(); 
	
	for (int i=0; i<cant_ordenes; ++i)
		total_items += m_items[i].cantidad;
	
	return total_items;
}

/// FUNCIONES QUE MODIFICAN DATOS
void OrdenProduccion::establecerId(int id) { m_id = id; }
void OrdenProduccion::establecerCostoTotal(float costo_historico) { m_costo_total = costo_historico; }
void OrdenProduccion::establecerFecha(std::string fecha) { m_fecha = fecha; }

void OrdenProduccion::agregarItem(int id_receta, std::string nombre_receta, int cantidad, float costo_unitario) 
{
	ItemOrden nuevo_item;
	nuevo_item.id_receta = id_receta;
	nuevo_item.cantidad = cantidad;
	
	// aseguro el tamaño del c_string
	strncpy(nuevo_item.nombre_receta, nombre_receta.c_str(), sizeof(nuevo_item.nombre_receta) - 1);
	nuevo_item.nombre_receta[sizeof(nuevo_item.nombre_receta) - 1] = '\0'; // aseguro el fin de cadena
	
	m_items.push_back(nuevo_item);
	
	// actualizo el costo total
	m_costo_total += (costo_unitario * cantidad);
}

RegistroProduccion OrdenProduccion::crearRegistro() const 
{
	RegistroProduccion aux;
	aux.id = m_id;
	aux.cant_items = m_items.size();
	aux.costo_total = m_costo_total;
	
	// aseguro el tamaño del c_string
	strncpy(aux.fecha, m_fecha.c_str(), sizeof(aux.fecha) - 1);
	aux.fecha[sizeof(aux.fecha) - 1] = '\0'; // aseguro el fin de cadena
	
	return aux;
}

