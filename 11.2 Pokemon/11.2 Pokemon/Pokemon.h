#pragma once

#include <iostream>
#include <string>
#include <map>
#include <unordered_map>
#include <list>
#include <set>
#include <unordered_set>
#include <queue>

using namespace std;

using pokemon = string;
using entrenador = string;
using nivel = int;

class CentroPokemon {
	private:

	struct PokemonInfo {
		unordered_map<entrenador, std::pair<nivel, list<pokemon>::iterator>> duenyos;
	};

	struct EntrenadorInfo {
		entrenador nombre;
		map<nivel, PokemonInfo> pokemones_por_niveles;
		list<pokemon> pokemones_en_orden;
	};


	unordered_map<entrenador, EntrenadorInfo> entrenadores;
	unordered_map<pokemon, PokemonInfo> pokemones;


public:

	void capturar_pokemon(entrenador e, pokemon p, nivel n) {

	}

	PokemonInfo vencer_pokemon(entrenador e, nivel n) {

	}

	int dia_de_la_liberacion(pokemon p) {
		
	}

	void gimnasio(entrenador e){

	}

	





};
