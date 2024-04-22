// Autor/a: César Carlos Rubio Pastor
// email: cesrubio@ucm.es

// Nombre del problema : 4.4 Link y el vuelo en paravela

// Solución: utilizando una pila, recorremos la lista de izquierda a derecha, metemos en la pila las alturas según sigan siendo más grandes que la actual
//
#include <iostream>
#include <fstream>
#include <list>
#include <stack>

// Introduce más librerías si son necesarias
using namespace std;

void resolver(list<int> datos);
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
#endif
   return 0;
}


//Coste: O(n) donde n es el numero de pilares. Se recorre la lista de pilares una vez, y por cada iteracion puede manipularse la pila,
//pero solo está cada altura una vez, por lo que la suma de iteraciones del bucle interno es n en el peor de los casos. 
// El coste más preciso sería de O(2n), pero asintóticamente es O(n).
void resolver(list<int> landscape) {

    stack<int> heights;

    for (auto it : landscape) {
        //If height de it es >= desapila el top, si no, apuntamos resultado para ese pilar y apilamos el height de it.
        while (!heights.empty() && heights.top() <= it) {
            heights.pop();
        }
        if (heights.empty()) {
            cout << "NO HAY\n";
        }
        else {
            cout << heights.top() << '\n';
        }
        heights.push(it);

    }
    
    std::cout << "---\n";
}

// resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {

    int in;
    list<int> pillars;


    cin >> in;
    if (in == -1) return false;

    while (in != -1) {
        pillars.push_back(in);
        cin >> in;
    }
    resolver(pillars);

    return true;
}
