
// Autor/a: Nombre y apellidos
// email:
// Compilador y S.O. utilizado
// Nombre del problema
// Comentario general sobre la solución
// explicando como se resuelve el problema

#include <iostream>
#include <fstream>
#include <stack>
#include <string>
// Introduce más librerías si son necesarias
using namespace std;


char openToClose(char symbol) {
    switch (symbol) {
    case '(':
        return ')';
    case '[':
        return ']';
    case '{':
        return '}';
    }
}

// función que resuelve el problema
bool resolver(string datos) {
    std::stack<char> pila;
    //Recorremos la cadena entera
    for (int i = 0; i < datos.size(); i++) {
        //Si lee uno de los caracteres de apertura, lo convierte al de cierre y lo pushea a la pila.
        if (datos[i] == '(' || datos[i] == '{' || datos[i] == '[') pila.push(openToClose(datos[i]));

        //Si lee uno de cierre, chequea que el top es igual, si lo es hace pop, si no return false.
        else if (datos[i] == ')' || datos[i] == '}' || datos[i] == ']'){
            if (pila.empty() || datos[i] != pila.top()) return false;
            else pila.pop();
        }
    }

    //Si al terminar de leer la pila no está vacía, entonces no está equilibrado.
    if (pila.empty()) return true;
    else return false;

}

// resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {

    // leer los datos de la entrada

    

    string line;
    std::getline(std::cin, line);
    if (!std::cin)  // fin de la entrada
        return false;

    if (resolver(line)) {
        cout << "SI" << '\n';
    }
    else
        cout << "NO" << '\n';

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


