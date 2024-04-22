
// Autor/a: César Carlos Rubio Pastor
// email: cesrubio@ucm.es
// Nombre del problema
// Comentario general sobre la solución
// explicando como se resuelve el problema

#include <iostream>
#include <fstream>
#include <list>
#include <cmath>
// Introduce más librerías si son necesarias
using namespace std;

void suavizar(list<int>& lista);
bool resuelveCaso();

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

/*
* Llevando dos iteradores consecutivos, mientras la diferencia absoluta sea 1, avanzamos ambos. 
*    Si la diferencia es superior a 1, inserto itAnt +/-1 delante 
* 
*/
void suavizar(list<int>& lista) {
    if (lista.empty()) return;
    auto itAnterior = lista.begin();
    auto itActual= ++lista.begin();
    //Caso solo hay un elemento
    if (itActual == lista.end()) return;
    
    while (itActual != lista.end()) {
        int dif = *itActual - *itAnterior;
        if (dif == 0) {
            //Si la diferencia es 0, significa que ambos elementos son iguales-> borramos al que apunta itAct y avanzamos ambos.
            itActual = lista.erase(itActual);
        }
        else if (dif < -1) {
            //Si la diferencia es negativa -> hay que rellenar con elementos en orden descendente.
            itAnterior = lista.insert(itActual, *itAnterior - 1);
        }
        else if (dif > 1) {
            //Si es positiva -> rellenar con elementos en orden ascendente
            itAnterior = lista.insert(itActual, *itAnterior + 1);
        }
        else {
            itAnterior++;
            itActual++;
        }
    }
}

// resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {


    // leer los datos de la entrada
    int numCasos;
    int in;
    list<int> l;
    cin >> numCasos;
    if (!cin) return false;
    for (int i = 0; i < numCasos; i++) {
        cin >> in;
        l.push_back(in);
    }
    
    suavizar(l);

    if (!l.empty()) {
        auto it = l.cbegin();
        while (it != l.cend()) {
            cout << *it << " ";
            it++;
        }
        cout << '\n';
    }
    
    return true;
}

