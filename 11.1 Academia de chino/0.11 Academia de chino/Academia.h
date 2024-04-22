
#include <iostream>
#include <string>
#include <map>
#include <unordered_map>
#include <list>
#include <set>

using namespace std;


class Academia {

public:

	void nuevo_estudiante(string dni, int nivel) {
		if (alumnos.find(dni) != alumnos.end()) {
			throw domain_error("Estudiante ya existente");
		}
		if (nivel < 0 || nivel > 6)
			throw domain_error("Grupo incorrecto");

		//alumnos.insert({ dni, {nivel} });
		grupos[nivel].push_back(dni);
		alumnos[dni] = { nivel, grupos[nivel].begin()};
		
	}


	void promocionar(string dni) { //O(log(A))
		auto alumno = alumnos.find(dni); //O(1)
		if (alumno == alumnos.end())
			throw domain_error("Estudiante no existente");
		if (alumno->second.nivel > 6)
			throw domain_error("Estudiante ya graduado");
		if (alumno->second.nivel < 6) {
			grupos[alumno->second.nivel].erase(alumno->second.posCurso);
			alumno->second.nivel++;
			grupos[alumno->second.nivel].push_front(dni);
			alumno->second.posCurso = grupos[alumno->second.nivel].begin();
		}			
		else {
			//Deja el nivel a 7, eliminamos del curso (6 en concreto)
			grupos[alumno->second.nivel].erase(alumno->second.posCurso);
			alumno->second.nivel++;
			alumnos_graduados.insert(dni); //O(log(A))
		}
	}

	int grupo_estudiante(string dni) {
		auto alumno = alumnos.find(dni); //O(1)
		if (alumno == alumnos.end())
			throw domain_error("Estudiante no existente");
		if (alumno->second.nivel > 6)
			throw domain_error("Estudiante ya graduado");
		
		return alumno->second.nivel;

	}

	list<string> graduados() { //O(A)
		list<string> result;
		for (auto grad : alumnos_graduados) {
			result.push_front(grad);
		}
		return result;
	}

	string novato(int grupo) {
		
		if (grupos.find(grupo) == grupos.end())
			throw domain_error("Grupo incorrecto");
		if (grupos[grupo].size() == 0)
			throw domain_error("Grupo vacio");
		
		return grupos[grupo].back();
	}


private:

	struct AlumnoInfo
	{
		int nivel;
		list<string>::iterator posCurso;
		//información del alumno
	};

	unordered_map<string, AlumnoInfo> alumnos;
	set<string> alumnos_graduados;
	unordered_map<int, list<string>> grupos;

	
};


