#ifndef ORDENPRODUCCION_H
#define ORDENPRODUCCION_H
#include <string>
#include <vector>

/// struct que guarda cada producto individual que se cocinó
struct ItemOrden {
	int id_receta;
	int cantidad;
	char nombre_receta[50];
};

/**
* struct para guardar en archivo
* - funciona como cabecera de un registro de produccion
* - da la información básica y cuantos struct ItemOrden leer a continuación
**/
struct RegistroProduccion {
	int id;
	int fecha; 
	int cant_items;
	float costo_total;
};

/// clase que representa una orden de producción
class OrdenProduccion {
private:
	// datos
	int m_id; // id único
	int m_fecha;
	float m_costo_total;
	
	// lista de produccion
	std::vector<ItemOrden> m_items;
	
public:
	/// crea una orden sólo con la fecha
	OrdenProduccion(int fecha);
	
	/// ver datos
	int verId() const;
	int verFecha() const;
	float verCostoTotal() const;
	
	/// devuelve la cantidad de diferentes items
	int verCantidadPorTipoItems() const;
	
	/// devuelve la cantidad total de items
	int verCantidadTotalItems() const;
	
	/// devuelve el ItemOrden que se encuentra en la posición i del vector
	ItemOrden operator[](size_t i) const;
	
	/// establece valor para m_id
	void establecerId(int id);
	
	/// establece valor para m_costo_total
	void establecerCostoTotal(float costo_historico);
	
	/// establece valor para m_fecha
	void establecerFecha(int fecha);
	
	/// agrega un producto y va sumando al costo total
	void agregarItem(int id_receta=-1, std::string nombre_receta="", int cantidad=0, float costo_unitario=0);
	
	/// crea el struct RegistroPorduccion para guardar en archivo
	RegistroProduccion crearRegistro() const;
	
};

/// criterios para comparar dos órdenes; usados para la función sort
bool prod_cmp_id(const OrdenProduccion &p1, const OrdenProduccion &p2);
bool prod_cmp_cant(const OrdenProduccion &p1, const OrdenProduccion &p2);
bool prod_cmp_costo(const OrdenProduccion &p1, const OrdenProduccion &p2);
bool prod_cmp_fecha(const OrdenProduccion &p1, const OrdenProduccion &p2);



#endif

