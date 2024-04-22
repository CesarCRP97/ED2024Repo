#include <iostream>
#include <string>
#include <map>
#include <unordered_map>
#include <list>
#include <set>

using namespace std;
using medico = string;
using paciente = string;
using listaMedicos = list<medico>;
using listaEspera = list<paciente>;

class Ferrivistan {

public:

	void nueva_linea(const string& nombre) {

	}

	void nueva_estacion(const string& linea, const string& nombre, int posicion) {

	}

	void eliminar_estacion(const string& estacion) {

	}

	vector<string> lineas_de(const string& estacion) const {

	}

	string proxima_estacion(const string& linea, const string& estacion) const {

	}




private:

	struct MedicoInfo
	{
		//importa el orden de llegada.
		listaEspera pacientes_en_espera;
	};

	struct PacienteInfo {
		//Guarda en un mapa los m�dicos y la posici�n en la que se encuentra cada paciente
		//Es un map porque no importa el orden de los m�dicos.
		map <medico, listaEspera::iterator> posicion_en_colas;
	};

	unordered_map<medico, MedicoInfo> medicos;
	unordered_map<paciente, PacienteInfo> pacientes;



};

bool resuelveCaso() {

	std::string op;
	std::cin >> op;
	if (!std::cin)
		return false;

	Ferrivistan ferrivistan;

	while (op != "FIN") {

		try {

			if (op == "altaMedico") {

			}

			else if (op == "pedirConsulta") {

			}

			else if (op == "siguientePaciente") {

			}

			else if (op == "atenderConsulta") {
			}
			if (op == "abandonarConsulta") {
				
			}

		}
		catch (std::domain_error& e) {

			std::cout << "ERROR: " << e.what() << "\n";
		}

		std::cin >> op;

	}

	std::cout << "---\n";

	return true;
}


int main() {

	while (resuelveCaso());
	return 0;
}


