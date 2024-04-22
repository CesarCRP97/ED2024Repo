
// Autor/a: César Carlos Rubio Pastor
// email: cesrubio@ucm.es
// Nombre del problema
// Comentario general sobre la solución
// explicando como se resuelve el problema

#include <iostream>
#include <fstream>
#include "list_linked_double.h"
// Introduce más librerías si son necesarias
using namespace std;


// resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {

    int N, i, m, datos;
    ListLinkedDouble<int> lista;



    cin >> N;
    cin >> i;
    cin >> m;
    
    if (N == 0 && i == 0 && m == 0) return false;

    for (int j = 0; j < N; j++) {
        cin >> datos;
        lista.push_back(datos);
    }
    lista.add_to(i, m);

    lista.display();
    cout << '\n';

    return true;
}

int main() {
    // ajustes para que cin extraiga directamente de un fichero
#ifndef DOMJUDGE
    std::ifstream in("1.in");
    auto cinbuf = std::cin.rdbuf(in.rdbuf());
    std::ofstream out("datos.out");
    auto coutbuf = std::cout.rdbuf(out.rdbuf());
#endif

    while (resuelveCaso());

    // para dejar todo como estaba al principio
#ifndef DOMJUDGE
    std::cin.rdbuf(cinbuf);
    std::cout.rdbuf(coutbuf);
    system("PAUSE");
#endif
    return 0;
}


