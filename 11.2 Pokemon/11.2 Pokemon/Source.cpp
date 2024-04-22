
#include <iostream>
#include <string>
#include "pokemon.h"


using namespace std;

// Resuelve un caso de prueba, leyendo de la entrada la
// configuraci�n, y escribiendo la respuesta
bool resuelveCaso() {
	// leer los datos de la entrada

	std::string op;
	std::cin >> op;
	if (!std::cin)
		return false;

	CentroPokemon centro;

	while (op != "FIN") {
		try {

			if (op == "capturar_pokemon") {

				entrenador e; pokemon p; nivel n;
				std::cin >> e >> p >> n;

				centro.capturar_pokemon(e, p, n);

			}

			else if (op == "vencer_pokemon") {

				entrenador e; int n;
				std::cin >> e >> n;

				std::pair<pokemon, nivel> p = centro.vencer_pokemon(e, n);
				std::cout << e << " utiliza el pokemon " << p.first << " con nivel " <<
					p.second << " para vencer a un nivel " << n << '\n';
			}

			else if (op == "dia_de_liberacion") {
				pokemon p;
				std::cin >> p;
				int n = centro.dia_de_liberacion(p);
				std::cout << "Liberados " << n << " pokemon " << p << '\n';
			}

			if (op == "gimnasio") {
				entrenador e;
				std::cin >> e;
				pokemon p = centro.gimnasio(e);
				std::cout << e << " deja el pokemon " << p << " en un gimnasio\n";
			}
		}
		catch (std::invalid_argument& e) {
			std::cout << "ERROR: " << e.what() << "\n";
		}
		std::cin >> op;
	}
	std::cout << "---\n";
	return true;

}

int main() {

	while (resuelveCaso());//Resolvemos todos los casos


}