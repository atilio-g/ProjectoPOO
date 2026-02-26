#include "GestorPanaderia.h"
#include "ConversionDatos.h"
#include "Insumo.h"
#include "Receta.h"
#include <string>
#include <vector>
#include <fstream>
#include <algorithm>
#include <map>

/// CONSTRUCTOR
GestorPanaderia::GestorPanaderia(std::string archi_insumos, std::string archi_recetas, std::string archi_ids) :
	m_arch_insumos(archi_insumos),
	m_arch_recetas(archi_recetas),
	m_arch_ids(archi_ids),
	m_ultimoIdInsumo(0),
	m_ultimoIdReceta(0)
{
	cargarInsumos();
	cargarRecetas();
	cargarIds();
}

/////////////////////////////////////////////////////////////////////////////
/// MÉTODOS DE GESTIÓN DE ARCHIVOS Y DATOS
/////////////////////////////////////////////////////////////////////////////

/// métodos guardar
/// los insumos se guardan con el struct RegistroIns, uno tras otro
void GestorPanaderia::guardarInsumos()
{
	std::ofstream archi(m_arch_insumos, std::ios::binary);
	
	size_t i, cant = v_insumos.size();
	for (i=0; i<cant; ++i)
	{
		RegistroIns aux = v_insumos[i].crearRegistro();
		archi.write(reinterpret_cast<char*>(&aux), sizeof(aux));
	}
}

/// cada receta se guarda como: (1) struct RegistroReceta (2) seguido de los n Ingredientes
void GestorPanaderia::guardarRecetas()
{
	std::ofstream archi(m_arch_recetas, std::ios::binary);
	
	size_t i, cant = v_recetas.size();
	for (i=0; i<cant; ++i)
	{
		// guardo el registro receta que contiene cuantos ingredientes le siguen
		RegistroReceta aux_rec = v_recetas[i].crearRegistro();
		archi.write(reinterpret_cast<char*>(&aux_rec), sizeof(aux_rec));
		
		// luego guardo los n ingredientes
		int j, cant_ing = v_recetas[i].verCantidadIngredientes();
		for (j=0; j<cant_ing; ++j)
		{
			Ingrediente aux_ing = v_recetas[i][j];
			archi.write(reinterpret_cast<char*>(&aux_ing), sizeof(aux_ing));
		}
	}
}

void GestorPanaderia::guardarIds()
{
	std::ofstream archi(m_arch_ids,std::ios::binary);
	
	// primero el id de insumos y después el id de recetas
	archi.write(reinterpret_cast<char*>(&m_ultimoIdInsumo), sizeof(m_ultimoIdInsumo));
	archi.write(reinterpret_cast<char*>(&m_ultimoIdReceta), sizeof(m_ultimoIdReceta));
}

void GestorPanaderia::guardarTodo()
{
	this->guardarInsumos();
	this->guardarRecetas();
	this->guardarIds();
}

/// métodos cargar
bool GestorPanaderia::cargarInsumos()
{
	std::ifstream archi(m_arch_insumos, std::ios::binary|std::ios::in);
	if (not archi.is_open()) return false;
	
	// si el archivo está vacío, que no cargue nada
	/*archi.seekg(0, std::ios::end);
	int tam = archi.tellg();
	if ( tam == 0 ) return true;
	
	auto final_pos = archi.tellg();
	archi.seekg(0);
	while ( archi.tellg() < final_pos ) */
	
	RegistroIns aux;
	while ( archi.read(reinterpret_cast<char*>(&aux), sizeof(aux)) )
	{
		// paso de c_string a string
		std::string nombre = aux.nombre, unidad = aux.unidad;
		Insumo ins(nombre, unidad, aux.tipo, aux.costo, aux.stock);
		ins.establecerId(aux.id);
		
		v_insumos.push_back(ins);
	}
	return true;
}

bool GestorPanaderia::cargarRecetas()
{
	std::ifstream archi(m_arch_recetas, std::ios::binary|std::ios::in);
	if (not archi.is_open()) return false;
	
	// si el archivo está vacío, que no cargue nada
	/* 
	archi.seekg(0, std::ios::end);
	int tam = archi.tellg();
	if ( tam == 0 ) return true;
	
	auto final_pos = archi.tellg();
	archi.seekg(0);
	while ( archi.tellg() < final_pos )
	*/
	
	// primero leo el registro de receta i
	RegistroReceta regi;
	while( archi.read(reinterpret_cast<char*>(&regi), sizeof(regi)) )
	{
		// paso de c_string a string
		std::string nombre = regi.nombre; 
		Receta rec(nombre);
		rec.establecerId(regi.id);
		
		// luego leo los n ingredientes de la receta i
		for (int i=0; i<regi.cantidad; ++i)
		{
			Ingrediente ing;
			archi.read(reinterpret_cast<char*>(&ing), sizeof(ing));
			
			rec.modificarIngrediente(ing.id, ing.cantidad);
		}
		v_recetas.push_back(rec);
	}
	return true;
}

bool GestorPanaderia::cargarIds()
{
	std::ifstream archi(m_arch_ids, std::ios::binary);
	if (not archi.is_open()) return false;
	
	// si el archivo está vacío, que no cargue nada
	/*archi.seekg(0, std::ios::end);
	int tam = archi.tellg();
	if ( tam == 0 ) return true; */

	archi.read(reinterpret_cast<char*>(&m_ultimoIdInsumo), sizeof(m_ultimoIdInsumo));
	archi.read(reinterpret_cast<char*>(&m_ultimoIdReceta), sizeof(m_ultimoIdReceta));
	return true;
}

/// generar ids
int GestorPanaderia::generarIdInsumo() { return ++m_ultimoIdInsumo; }
int GestorPanaderia::generarIdReceta() { return ++m_ultimoIdReceta; }

/////////////////////////////////////////////////////////////////////////////
/// MÉTODOS DE INSUMO
/////////////////////////////////////////////////////////////////////////////

/// validar nombre no repetido
bool GestorPanaderia::ValidarNombreInsumo(std::string nombre, int id_insumo)
{
	// paso a todo a minúsculas y comparo
	for (char &c : nombre) c = tolower(c);
	
	size_t i, cant = v_insumos.size();
	for (i=0; i<cant; ++i)
	{
		std::string aux_nombre = v_insumos[i].verNombre();
		for (char &c : aux_nombre) c = tolower(c);
		int aux_id = v_insumos[i].verId();
		
		// que coincida el nombre pero sea otro id
		if (aux_nombre == nombre and aux_id != id_insumo) return false;
	}
	return true;
}

/// agregar insumo al vector de insumos
int GestorPanaderia::agregarInsumo(Insumo ins)
{	
	// valido
	std::string err = ins.validarTODO();
	if ( err.size() > 0 ) return -1;
	if ( not this->ValidarNombreInsumo( ins.verNombre() ) ) return -1;
	
	int id = this->generarIdInsumo();
	ins.establecerId( id );
	v_insumos.push_back(ins);
	
	return id;
}

/// modificar insumo
bool GestorPanaderia::modificarInsumo(int id_insumo, Insumo ins)
{
	Insumo *real_ins = verInsumo(id_insumo);
	if (real_ins == nullptr) return false;
	
	// valido coherencia del insumo
	std::string errores = ins.validarTODO();
	if (errores.size() > 0) return false;
	
	// valido nombre no repetido
	if (not this->ValidarNombreInsumo(ins.verNombre(), id_insumo)) return false;
	
	real_ins->modificarNombre(ins.verNombre());
	real_ins->modificarUnidad(ins.verUnidad());
	real_ins->modificarTipo(ins.verTipo());
	real_ins->modificarCosto(ins.verCosto());
	real_ins->modificarStock(ins.verStock());

	return true;
}

/// eliminar Insumo del vector
bool GestorPanaderia::eliminarInsumo(int id_insumo)
{
	// iteradores para usar .erase()
	auto it = find(v_insumos.begin(), v_insumos.end(), id_insumo);
	if (it == v_insumos.end()) return false;
	
	// elimino el ingrediente de las recetas que lo usan
	size_t i, cant = v_recetas.size();
	for (i=0; i<cant; ++i)
	{
		// el método ya valida 
		v_recetas[i].eliminarIngrediente(id_insumo);
	}
	
	// elimino el insumo en general
	v_insumos.erase(it);
	return true;
}

/// ver id 
int GestorPanaderia::verIdInsumo(int pos) { return v_insumos[pos].verId(); }

/// obtener puntero a Insumo
Insumo* GestorPanaderia::verInsumo(int id_insumo)
{
	size_t i, cant = v_insumos.size();
	for (i=0; i<cant; ++i)
	{
		if (v_insumos[i].verId() == id_insumo) return &(v_insumos[i]);
	}
	return nullptr;
}

/// ver cantidad de insumos en vector
int GestorPanaderia::verCantidadInsumos() { return v_insumos.size(); }

/// ver vector de insumos
const std::vector<Insumo>& GestorPanaderia::verVectorInsumos() { return v_insumos; }


/////////////////////////////////////////////////////////////////////////////
/// MÉTODOS DE RECETA  
/////////////////////////////////////////////////////////////////////////////

/// validar nombre no repetido
bool GestorPanaderia::ValidarNombreReceta(std::string nombre, int id_receta)
{
	for (char &c : nombre) c = tolower(c);
	
	size_t i, cant = v_recetas.size();
	for (i=0; i<cant; ++i)
	{
		std::string aux_nombre = v_recetas[i].verNombre();
		for (char &c : aux_nombre) c = tolower(c);
		int aux_id = v_recetas[i].verId();
		
		// que coincida el nombre pero sea otro id
		if (aux_nombre == nombre and aux_id != id_receta ) return false;
	}
	return true;
}

/// agregar receta al vector de recetas
int GestorPanaderia::agregarReceta(Receta rec)
{
	// valido nombre no vacío ni repetido
	std::string errores = rec.validarDatos();
	if (errores.size() > 0) return -1;
	if ( not this->ValidarNombreReceta(rec.verNombre()) ) return -1;
	
	int id = this->generarIdReceta();
	rec.establecerId(id);
	v_recetas.push_back(rec);
	
	return id;
}

/// modificar nombre de receta
bool GestorPanaderia::modificarNombreReceta(int id_receta, std::string nombre)
{
	// valido que haya receta
	Receta *rec = verReceta(id_receta);
	if (rec == nullptr) return false;
	
	// valido nombre no vacío ni repetido
	if (nombre.size() == 0) return false;
	if ( not this->ValidarNombreReceta(nombre, id_receta) ) return false;
	
	rec->modificarNombre(nombre);
	return true;
}

/// modificar receta por completo: la sobreescribe
bool GestorPanaderia::modificarReceta(int id_receta, Receta aux_rec)
{
	Receta *rec = this->verReceta(id_receta);
	if (rec == nullptr) return false;
	
	// valido nombre no vacío ni repetido
	std::string errores = aux_rec.validarDatos();
	if (errores.size() > 0) return false;
	if ( not this->ValidarNombreReceta(aux_rec.verNombre(), id_receta) ) return false;
	
	rec->sobreescribir(aux_rec);
	return true;
}

/// agregar o modificar ingrediente
bool GestorPanaderia::modificarIngredienteReceta(int id_receta, int id_ingrediente, float cantidad)
{
	Receta *rec = verReceta(id_receta);
	if (rec == nullptr) return false;
	
	// la función valida el id: agrega o modifica el ingrediente
	rec->modificarIngrediente(id_ingrediente, cantidad);
	return true;
}

/// elimina el ingrediente de la receta
bool GestorPanaderia::eliminarIngredienteReceta(int id_receta, int id_ingrediente)
{
	Receta *rec = verReceta(id_receta);
	if (rec == nullptr) return false;
	
	// la función ya valida el id
	return rec->eliminarIngrediente(id_ingrediente);
}

/// elimina la receta del vector de recetas
bool GestorPanaderia::eliminarReceta(int id_receta)
{
	// iteradores para usar .erase()
	auto it = find(v_recetas.begin(), v_recetas.end(), id_receta);
	if (it == v_recetas.end()) return false;
	
	v_recetas.erase(it);
	return true;
}

/// ver id 
int GestorPanaderia::verIdReceta(int pos) { return v_recetas[pos].verId(); }

/// obtener puntero a la receta
Receta* GestorPanaderia::verReceta(int id_receta)
{
	size_t i, cant = v_recetas.size();
	for (i=0; i<cant; ++i)
	{
		if (v_recetas[i].verId() == id_receta) return &(v_recetas[i]);
	}
	return nullptr;
}

/// ver cantidad de recetas en vector
int GestorPanaderia::verCantidadRecetas() { return v_recetas.size(); }

/// ver vector de recetas
const std::vector<Receta>& GestorPanaderia::verVectorRecetas() { return v_recetas; }

/// calcular costo de producir la receta por id
float GestorPanaderia::calcularCostoReceta(int id_receta)
{
	float costo_total = 0.0f;
	Receta *r = verReceta(id_receta);
	if( r == nullptr ) return -1.0f;
	
	// recorro el vector de ingredientes y agrego cada costo al costo total
	int cant = r->verCantidadIngredientes();
	for (int i=0; i<cant; ++i)
	{
		Ingrediente aux = (*r)[i];
		Insumo *ins = verInsumo( aux.id );
		
		if ( ins == nullptr ) continue;
		
		// ajusto según la unidad
		std::string unidad = ins->verUnidad();
		float costo = ins->verCosto();
		if (unidad == "kg" or unidad == "L")
			costo /= 1000.0f;
		
		costo *= aux.cantidad;
		costo_total += costo;
	}
	return costo_total;
}

/// calcular costo de producir la receta por objeto
float GestorPanaderia::calcularCostoReceta(Receta &r)
{
	float costo_total = 0.0f;
	int cant = r.verCantidadIngredientes();
	
	// recorro el vector de ingredientes y agrego cada costo al costo total
	for (int i=0; i<cant; ++i)
	{
		Ingrediente aux = r[i];
		Insumo *ins = verInsumo( aux.id );
		
		if ( ins == nullptr ) continue;
		
		// ajusto según la unidad
		std::string unidad = ins->verUnidad();
		float costo = ins->verCosto();
		if (unidad == "kg" or unidad == "L")
			costo /= 1000.0f;
		
		costo *= aux.cantidad;
		costo_total += costo;
	}
	return costo_total;
}
	
/// ordenar vector receta por costo
void GestorPanaderia::ordenarRecetaCosto()
{
	auto cmp = [this](Receta &rec1, Receta &rec2)
	{
		float costoA = this->calcularCostoReceta( rec1 );
		float costoB = this->calcularCostoReceta( rec2 );
		return costoA < costoB;
	};
	
	sort(v_recetas.begin(), v_recetas.end(), cmp);
}

/////////////////////////////////////////////////////////////////////////////
/// MÉTODOS DE PRODUCCION
/////////////////////////////////////////////////////////////////////////////

// recibe vector de pares {id_receta, cantidad_a_producir}
std::map<int,float> GestorPanaderia::acumularInsumos(const std::vector< std::pair<int,int> > &pedido)
{
	// utilizo map por facilidad de búsqueda y acumulación ante ids repetidos
	// formato <id_receta, cant_a_producir>
	std::map<int, float> insumos_necesarios;
	
	// acumulo insumos_necesarios
	for (const auto &item : pedido)
	{
		int id_receta = item.first;
		int cant_a_producir = item.second;
		
		Receta *rec = this->verReceta(id_receta);
		if (rec == nullptr ) continue;
		
		// recorro los ingredientes de la receta
		int cantidad_ingredientes = rec->verCantidadIngredientes();
		for (int i=0; i<cantidad_ingredientes; ++i)
		{
			Ingrediente ing = (*rec)[i];
			
			// cantidad que lleva la receta x la cantidad a producir de la receta
			insumos_necesarios[ing.id] += ing.cantidad * cant_a_producir;
		}
	}
	return insumos_necesarios;
}


std::string GestorPanaderia::validarProduccion(const std::vector< std::pair<int,int> > &pedido)
{
	// formato <id_receta, cant_a_producir>
	std::map<int, float> insumos_necesarios = acumularInsumos(pedido);
	
	// chequeo si alcanza el stock de cada insumo, con que uno no alcance ya se cancela
	std::string errores;
	for (const auto &par_ins : insumos_necesarios)
	{
		int id_insumo = par_ins.first;
		float cant_requerida = par_ins.second;
		
		Insumo *ins = this->verInsumo(id_insumo);
		if (ins == nullptr) continue;
		
		// asumo que el stock no se valida si el costo es cero
		if (ins->verCosto() == 0) continue;
		
		if (cant_requerida > ins->verStock())
		{
			std::string unidad = ins->verUnidad();
			if (unidad == "kg" or unidad == "L")
				cant_requerida /= 1000.0f;
			
			errores += "- Falta " + ins->verNombre() + ": se nececitan "
				+ num_to_wx(cant_requerida) + unidad + " pero el stock es de "
				+ num_to_wx(ins->verStockVisual()) + unidad + ".\n";
		}
	}
	return errores;
}

void GestorPanaderia::ejecutarProduccion(const std::vector< std::pair<int,int> > &pedido)
{
	// formato <id_receta, cant_a_producir>
	std::map<int, float> insumos_necesarios = acumularInsumos(pedido);
	
	// resto el stock de cada insumo
	for (const auto &par_ins : insumos_necesarios)
	{
		int id_insumo = par_ins.first;
		float cant_requerida = par_ins.second;
		
		Insumo *ins = this->verInsumo(id_insumo);
		if (ins == nullptr) continue;
		
		if (ins->verCosto() == 0) continue;
		
		ins->modificarStock( ins->verStock() - cant_requerida );
	}
}



