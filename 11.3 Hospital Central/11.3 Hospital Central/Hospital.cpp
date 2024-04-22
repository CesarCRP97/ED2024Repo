



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

class Hospital {

public:

	void altaMedico(medico m) {
		if (medicos.count(m) != 0) {
			throw domain_error("Medico existente");
		}
		medicos[m] = { list<paciente>() }; //O(1)
	}

	void pedirConsulta(paciente p, medico m) { //O(1)
		if (medicos.count(m) == 0) {
			throw domain_error("Medico inexistente");
		}
		
		MedicoInfo &medico = medicos.at(m); //O(1)

		//Si no existe el paciente
		if (pacientes.count(p) == 0) {
			//Añade al paciente por delante.
			medico.pacientes_en_espera.push_front(p); //O(1)
			//cogemos el iterador para añadirlo al paciente.
			auto it_paciente = medico.pacientes_en_espera.begin();
			
			//Encuentra en el unordered_map al paciente (si no está lo añade) y dentro inserta la posicion en la cola del medico.
			pacientes[p].posicion_en_colas.insert({ m, it_paciente });//O(1)
		}

		//Si existe el paciente chequeamos si ya está en la cola.
		else {
			PacienteInfo paciente = pacientes.at(p); //O(1)

			if (paciente.posicion_en_colas.count(m) != 0) {
				throw domain_error("Paciente ya esperando");
			}
			
			medico.pacientes_en_espera.push_front(p);
			//cogemos el iterador para añadirlo al paciente.
			auto it_paciente = medico.pacientes_en_espera.begin();
			pacientes[p].posicion_en_colas.insert({ m, it_paciente }); //O(1)
		}
	}

	paciente siguientePaciente(medico m) { //O(1)
		if (medicos.count(m) == 0) {
			throw domain_error("Medico inexistente");
		}
		if (medicos.at(m).pacientes_en_espera.size() == 0)
			throw domain_error("Medico sin pacientes ");

		//Si el medico tiene pacientes en espera, devuelve el que está en el back.
		else if (medicos.at(m).pacientes_en_espera.size() > 0) { //O(1)
			return medicos.at(m).pacientes_en_espera.back(); //O(1)
		}
	}

	//La llamada a siguientePaciente es O(1), porque buscar y borrar en los maps es lineal.
	void atenderConsulta(medico m) {
		if (medicos.count(m) == 0) {
			throw domain_error("Medico inexistente");
		}
		//Lanza error "Medico sin pacientes".
		paciente p = siguientePaciente(m);


		//Encuentra al paciente en el map de pacientes y lo borra de la lista de espera de m
		medicos.at(m).pacientes_en_espera.pop_back();
		pacientes[p].posicion_en_colas.erase(m);

		//Después de esto, si la lista de posciones en colas del paciente es 0, se borra al pacient.
		
		if (pacientes.at(p).posicion_en_colas.size() == 0) {
			pacientes.erase(p);
		}
	}

	list<medico> abandonarConsulta(paciente p) { //O(n) para n = medicos.size porque hay que recorrer el mapa del paciente.
		if (pacientes.count(p) == 0) {
			throw domain_error("Paciente inexistente");
		}
		PacienteInfo paciente = pacientes.at(p);
		listaMedicos baja_medicos;
		//Recorre la lista borrando de las listas de espera al paciente y añadiendo los medicos a baja_medicos.
		for (auto par : paciente.posicion_en_colas) { //O(n) donde n es medicos.size
			medico m = par.first;
			medicos.at(m).pacientes_en_espera.erase(par.second);
			baja_medicos.push_back(m);
		}
		//Tras sacrlo de todas las listas, se borra de pacientes
		pacientes.erase(p);

		return baja_medicos;
	}


	

private:

	struct MedicoInfo
	{
		//importa el orden de llegada.
		listaEspera pacientes_en_espera;
	};

	struct PacienteInfo {
		//Guarda en un mapa los médicos y la posición en la que se encuentra cada paciente
		//Es un map porque no importa el orden de los médicos.
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

	Hospital hospital;

	while (op != "FIN") {

		try {

			if (op == "altaMedico") {

				medico m;
				std::cin >> m;

				hospital.altaMedico(m);

			}

			else if (op == "pedirConsulta") {

				paciente p;
				medico m;

				std::cin >> p >> m;

				hospital.pedirConsulta(p, m);

			}

			else if (op == "siguientePaciente") {

				medico m;
				std::cin >> m;
				std::cout << hospital.siguientePaciente(m) << '\n';
			}

			else if (op == "atenderConsulta") {

				medico m;
				std::cin >> m;
				hospital.atenderConsulta(m);

			}
			if (op == "abandonarConsulta") {
				paciente p;
				std::cin >> p;
				listaMedicos lista = hospital.abandonarConsulta(p);
				cout << "Medicos abandonados: ";
				int i = 0;
				for (medico m : lista) {
					cout << m;
					if (i < lista.size() - 1) cout << " ";
					i++;
				}
				cout << '\n';
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


