#ifndef INSUMO_H
#define INSUMO_H
#include <string>

/// enumeración de los tipos de insumos
enum TipoInsumo { 
	VACIO = -1, 
	HARINA = 0, 
	LIQUIDO = 1, 
	GRASA = 3, 
	FERMENTO = 4, 
	SEMILLA = 5, 
	EXTRAS = 6 
};

/// struct para guardar los datos en archivo binario
struct RegistroIns{
	char nombre[100];
	char unidad[20];
	TipoInsumo tipo;
	int id;
	float costo;
	float stock;
};

/// clase que representa un insumo
/// al stock lo trabajo en las unidades mínimas (g, ml, ud)
class Insumo {
private:
	/// id única que distingue a cada insumo
	int m_id;
	
	/// datos accesibles de un insumo
	std::string m_nombre;
	std::string m_unidad;
	TipoInsumo m_tipo;
	float m_costo;
	float m_stock;
	
public:
	Insumo(std::string nombre, std::string unidad, TipoInsumo tipo, float costo, float stock);
	
	/// ver datos
	int verId() const;
	std::string verNombre() const;
	std::string verUnidad() const;
	TipoInsumo verTipo() const;
	float verCosto() const;
	
	// método para manejar en memoria: devuelve el stock como está guardado
	float verStock() const;
	
	// método para mostrar en pantalla: devuelve el stock en su unidad correspondiente
	float verStockVisual() const;
	
	/// valida que los datos del insumo sean coherentes, devuelve un string con los errores
	std::string validarNombre();
	std::string validarUnidad();
	std::string validarTipo();
	std::string validarStock();
	std::string validarCosto();
	std::string validarTODO();
	
	/// modificar datos
	void establecerId(int id_insumo);
	void modificarNombre(std::string nombre);
	void modificarUnidad(std::string unidad);
	void modificarTipo(TipoInsumo tipo);
	void modificarCosto(float costo);
	void modificarStock(float stock);
	
	/// crea el struct registro con los datos actuales
	RegistroIns crearRegistro();
	
	/// operadores para usar stl
	// devuelve true si el id pasado coincide con el id del insumo
	bool operator==(int id_insumo);
	
	// devuelve true si el nombre pasado coincide con el nombre del insumo
	bool operator==(std::string nombre_insumo);
};

/// criterios para comparar dos insumos; usados para la función sort
bool ins_cmp_nombre(const Insumo &ins1, const Insumo &ins2);
bool ins_cmp_tipo(const Insumo &ins1, const Insumo &ins2);
bool ins_cmp_costo(const Insumo &ins1, const Insumo &ins2);
bool ins_cmp_stock(const Insumo &ins1, const Insumo &ins2);

#endif

