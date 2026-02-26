#ifndef RECETA_H
#define RECETA_H
#include "Insumo.h"
#include <string>
#include <vector>

/// el struct ingrediente contiene los datos esenciales de un insumo para 
/// una receta: su id (qué insumo es) y una cantidad (cuanto uso)
struct Ingrediente{
	int id;
	float cantidad;
	
	// devuelve true si coinciden los id
	bool operator==(int id_insumo)
	{
		if (this->id == id_insumo) return true;
		else return false;
	}
};

/// struct para guardar los datos en archivo binario
struct RegistroReceta{
	char nombre[50];
	int id;
	int cantidad;
};

/// clase que representa toda una receta
class Receta {
private:
	// id único
	int m_id;
	
	// datos de la receta
	std::string m_nombre;
	std::vector<Ingrediente> m_ingredientes;
public:
	/// crea una receta sólo con un nombre
	Receta(std::string nombre);
	
	/// ver datos
	std::string verNombre() const;
	int verCantidadIngredientes() const;
	int verId() const;
	
	/// valida que los datos de la receta sean coherentes, devuelve un string con los errores
	std::string validarDatos();
	
	/// establece el valor pasado como el id de la receta
	void establecerId(int id_receta);
	
	/// modifica el nombre de la receta
	void modificarNombre(std::string nombre);

	/// modifica o agrega un ingrediente:
	/// 1) si no está el id pasado, lo agrega
	/// 2) si está el id pasado, lo modifica
	void modificarIngrediente(int id_insumo, float cant=-1);
	
	/// sobreescribe toda la receta, funciona como un =
	void sobreescribir(Receta rec);
	
	/// elimina el ingrediente que corresponda con la id
	bool eliminarIngrediente(int id_insumo);
	
	/// crea el struct registro con los datos actuales
	RegistroReceta crearRegistro();
	
	/// devuelve el ingrediente que se encuentra en la posición i del vector
	Ingrediente operator[](size_t i);
	
	/// devuelve true si los id coinciden
	bool operator==(int id_receta);
	
	/// devuelve true si el nombre pasado coincide con el nombre de la receta
	bool operator==(std::string nombre_receta);
};

/// criterios para comparar dos recetas; usados para la función sort
bool rec_cmp_nombre(const Receta &rec1, const Receta &rec2);
bool rec_cmp_cantidad(const Receta &rec1, const Receta &rec2);

#endif

