#ifndef GESTORPANADERIA_H
#define GESTORPANADERIA_H
#include "Insumo.h"
#include "Receta.h"
#include <string>
#include <vector>
#include <map>

/// clase que representa al sistema de panadería
/// puede gestionar la totalidad de recetas y de insumos
class GestorPanaderia {
private:
	/// nombres de archivos
	std::string m_arch_insumos;
	std::string m_arch_recetas;
	std::string m_arch_ids;
	
	/// vectores de datos
	std::vector<Insumo> v_insumos;
	std::vector<Receta> v_recetas;
	
	/// último id usado para asegurar unicidad
	int m_ultimoIdInsumo;
	int m_ultimoIdReceta;
	
	/// métodos privados para la gestión de ids
	int generarIdInsumo();
	int generarIdReceta();
	void guardarIds();
	
public:
	/// crea el objeto gestor y carga los datos desde los archivos
	GestorPanaderia(std::string archi_insumos, std::string archi_recetas, std::string archi_ids);
	
	/// cargar datos desde archivos
	bool cargarInsumos();
	bool cargarRecetas();
	bool cargarIds();
	
	/// guardar datos en archivos
	void guardarInsumos();
	void guardarRecetas();
	void guardarTodo();
	
	/// ordenar los vectores de insumos y recetas (implementación acá por ser template)
	template<typename Pfnc>
	void ordenarInsumos(Pfnc comparador){ sort(v_insumos.begin(), v_insumos.end(), comparador); }
	
	template<typename Pfnc>
	void ordenarRecetas(Pfnc comparador) { sort(v_recetas.begin(), v_recetas.end(), comparador); }
	
	/////////////////////////////////////////////////////////////////////////////
	/// MÉTODOS DE INSUMO 
	/////////////////////////////////////////////////////////////////////////////
	/// devuelve true si el nombre no está usado
	bool ValidarNombreInsumo(std::string nombre, int id_insumo=-1);
	
	/// agrega un insumo y devuelve su id, devuelve id=-1 como caso de error
	int agregarInsumo(Insumo ins);
	
	/// modifica un insumo sobreescribiendo sus datos, excepto el id
	bool modificarInsumo(int id_insumo, Insumo ins);
	
	/// elimina el insumo 
	bool eliminarInsumo(int id_insumo);
	
	/// devuelve el id del insumo en la posición pos del vector
	int verIdInsumo(int pos);
	
	/// devuelve un puntero al insumo; devuelve nullptr si no se encuentra
	Insumo* verInsumo(int id_insumo);
	
	/// devuelve la cantidad de insumos en el vector
	int verCantidadInsumos();
	
	/// devuelve el vector de insumos
	const std::vector<Insumo>& verVectorInsumos();
	
	/////////////////////////////////////////////////////////////////////////////
	/// MÉTODOS DE RECETA  
	/////////////////////////////////////////////////////////////////////////////
	/// devuelve true si el nombre no está usado
	bool ValidarNombreReceta(std::string nombre, int id_receta=-1);
	
	/// agrega una receta y devuelve su id, devuelve id=-1 como caso de error
	int agregarReceta(Receta rec);
	
	/// modifica el nombre de la receta, devuelve false si algún dato es erróneo
	bool modificarNombreReceta(int id_receta, std::string nombre);
	
	/// sobreescribe la receta usando la función -> Receta::sobreescribir
	bool modificarReceta(int id_receta, Receta aux_rec);
	
	/// modifica o agrega ingrediente usando la función -> Receta::modificarIngrediente
	bool modificarIngredienteReceta(int id_receta, int id_ingrediente, float cantidad);
	
	/// elimina el ingrediente de la receta indicada
	bool eliminarIngredienteReceta(int id_receta, int id_ingrediente);
	
	/// elimina la receta indicada
	bool eliminarReceta(int id_receta);
	
	/// devuelve el id de la receta en la posición pos del vector
	int verIdReceta(int pos);
	
	/// devuelve un puntero a la receta; devuelve nullptr si no se encuentra
	Receta* verReceta(int id_receta);
	
	/// devuelve la cantidad de recetas en el vector
	int verCantidadRecetas();
	
	/// devuelve el vector de recetas
	const std::vector<Receta>& verVectorRecetas();
	
	/// devuelve el costo total de producir la receta; costo=-1 como caso de error
	float calcularCostoReceta(int id_receta);
	float calcularCostoReceta(Receta &rec);
	
	/// función lambda para ordenar el vector receta por costo
	void ordenarRecetaCosto();
	
	/////////////////////////////////////////////////////////////////////////////
	/// MÉTODOS DE PRODUCCIÓN
	/////////////////////////////////////////////////////////////////////////////
	
	/// método auxiliar para usar en los métodos siguientes
	// recibe un vector de pares {id_receta, cantidad_a_producir}
	// devuelve un map de {id_insumo, cantidad_usada}
	std::map<int,float> acumularInsumos(const std::vector< std::pair<int,int> > &pedido);
	
	/// valida si hay stock para todo. Si no hay stock, devuelve un string con los faltantes
	std::string validarProduccion(const std::vector< std::pair<int,int> > &pedido);
	
	/// descuenta definitivamente el stock de los insumos
	void ejecutarProduccion(const std::vector< std::pair<int,int> > &pedido);
	

};



#endif

