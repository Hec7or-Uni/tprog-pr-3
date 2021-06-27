# pragma once
# include "tipos.h"

using namespace std;

template <typename T>
class Filter : public Almacen<T>, public Carga {
	private:
		string texto;
	public:
		Filter(const double& _capacidad, const string& _texto)
			: Almacen<T>(_capacidad), Carga("contenedor_estandar", _capacidad, 0), texto(_texto)
		{ }

		const double weight() const override {
			double peso = 0;
			for (auto elem : Almacen<T>::elemento) peso += elem->weight();
			return peso;
		}

		const string to_string(string space = "  ") const override {
			ostringstream str;
			str << space << "Contenedor [" << Filter<T>::capacidad << " m3] [" << Filter<T>::weight() << " kg] de "<< texto <<"\n";
			for (const auto& e : Filter<T>::elemento)
				str << e->to_string(space + "  ");
			return str.str();
		}
};

// ----- Tipos Normales ------------------------------

class Producto : public Carga {
	public:
		Producto(const string& _nombre, const double& _volumen, const double& _peso)
			: Carga(_nombre, _volumen, _peso) {}
};

template <typename T>
class Contenedor : public Filter<T> {
	public:
		Contenedor(const double& _capacidad)
			: Filter<T>(_capacidad, "Carga Estandar") {}
};

class Camion : public Almacen<Carga>, public Item {
	public:
		Camion(const double& _capacidad)
			: Almacen<Carga>(_capacidad), Item("Camion", _capacidad, 0)
		{ }

		const double weight() const override {
			double peso = 0;
			for (auto elem : Almacen::elemento) peso += elem->weight();
			return peso;
		}

		const string to_string(string space = "") const override {
			ostringstream str;
			str << name() << " [" << this->capacidad << " m3] [" << weight() << " kg]\n";
			for (const auto& e : Almacen::elemento) str << e->to_string(space + "  ");
			return str.str();
		}

		friend ostream& operator<<(ostream& f, const Camion& c) {
			f << c.to_string();
			return f;
		}
};

// ----- Tipos Especiales ------------------------------

class SerVivo : public Item {
	public:
		SerVivo(const string& _nombre, const double& _volumen, const double& _peso)
			: Item(_nombre, _volumen, _peso) 
		{ }
};

template <>
class Contenedor<SerVivo> : public Filter<SerVivo> {
	public:
		Contenedor(const double& _capacidad)
			: Filter<SerVivo>(_capacidad, "Seres Vivos") 
		{ }
};

class Toxico : public Item {
	public:
		Toxico(const string& _nombre, const double& _volumen, const double& _peso)
			: Item(_nombre, _volumen, _peso)
		{ }
};

template <>
class Contenedor<Toxico> : public Filter<Toxico> {
	public:
		Contenedor(const double& _capacidad)
			: Filter<Toxico>(_capacidad, "Productos Toxicos")
		{ }
};