# pragma once
# include <sstream>
# include <vector>

using namespace std;

class Item {
	protected:
		string nombre;
		double volumen;
		double peso;

	public:
		Item(const string& _nombre, const double& _volumen, const double& _peso)
			: nombre(_nombre), volumen(_volumen), peso(_peso)
		{ }

		const string& name() const { return this->nombre; }
		const double volume() const { return this->volumen; }
		virtual const double weight() const { return this->peso; }
		virtual const string to_string(string space = "") const {
			ostringstream str;
			str << space << name() << " [" << volume() << " m3] [" << weight() << " kg]\n";
			return str.str();
		}
};

// -----------------------------------------------------------

class Carga : public Item {
	public:
		Carga(const string& _nombre, const double& _volumen, const double& _peso)
			: Item(_nombre, _volumen, _peso)
		{ }
};

template <typename T>
class Almacen {
	protected:
		double cache;	// Guarda los volumenes
		double capacidad;
		vector<T*> elemento;
	public:
		Almacen(const double& _capacidad)
			: cache(0), capacidad(_capacidad) 
		{ }

		bool guardar(T& _elem) {
			if (_elem.volume() <= (capacidad - cache)) {
				cache += _elem.volume();
				this->elemento.push_back(&_elem);
				return true;
			}
			return false;
		}
};