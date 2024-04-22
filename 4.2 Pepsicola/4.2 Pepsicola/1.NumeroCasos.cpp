
// Autor/a: César C. Rubio Pastor
// email: cesrubio@ucm.es
// Compilador y S.O. utilizado
// Nombre del problema
// Comentario general sobre la solución
// explicando como se resuelve el problema

#include <iostream>
#include <fstream>
#include "queue_linkedlist.h"
// Introduce más librerías si son necesarias
using namespace std;

// función que resuelve el problema
void resolver(QueueLinkedList<int> &cola, QueueLinkedList<int> &colegas, int pringao) {
    cola.pepsicola(colegas, pringao);
}

// resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
void resuelveCaso() {
    QueueLinkedList<int> cola;
    QueueLinkedList<int> colegas;
    int input, pringao;
    
    cin >> input;
    while (input != -1) {
        cola.push(input);
        std::cout << input << " "; //Escribe la cola original
        cin >> input;
    }
    std::cout << '\n';
    cin >> pringao;
    //Leer colegas
    cin >> input;
    while (input != -1) {
        colegas.push(input);
        cin >> input;
    }

    resolver(cola, colegas, pringao);

    while (!cola.empty()) {
        cout << cola.front() << " ";
        cola.pop();
    }
    std::cout << '\n';

}

int main() {
   // ajustes para que cin extraiga directamente de un fichero
#ifndef DOMJUDGE
   std::ifstream in("1.in");
   auto cinbuf = std::cin.rdbuf(in.rdbuf());
   std::ofstream out("datos.out");
   auto coutbuf = std::cout.rdbuf(out.rdbuf());
#endif
   
   int numCasos;
   std::cin >> numCasos;
   for (int i = 0; i < numCasos; ++i)
      resuelveCaso();
   
   // para dejar todo como estaba al principio
#ifndef DOMJUDGE
   std::cin.rdbuf(cinbuf);
   std::cout.rdbuf(coutbuf);
   system("PAUSE");
#endif
   return 0;
}


