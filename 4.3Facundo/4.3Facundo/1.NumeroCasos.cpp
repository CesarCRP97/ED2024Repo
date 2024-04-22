
// Autor/a: Nombre y apellidos
// email:
// Compilador y S.O. utilizado
// Nombre del problema
// Comentario general sobre la solución
// explicando como se resuelve el problema

#include <iostream>
#include <fstream>
#include <deque>
#include <stack>
#include <string>
#include <sstream>

// Introduce más librerías si son necesarias
using namespace std;


void displayFrase(std::deque<string> frase) {
    while (!frase.empty()) {
        std::cout << frase.front() << " ";
        frase.pop_front();
    }
    std::cout << '\n';
}

// función que resuelve el problema
void resolver(deque<string> input) {
    std::string word;
    std::deque<string> frase; //Texto final que se va escribiendo.
    std::stack<string> pilaReversion; //Pila historial acciones previas.


    while (!input.empty()) {
        // Leo el primer string y hago pop
        word = input.front();
        input.pop_front();

        if (word == "*") { //ctrl+delete
            if (!frase.empty()) {
                std::string deleted = frase.back();
               
                frase.pop_back();
                pilaReversion.push(deleted);
            }
        }
        else if (word == "+") { //ctrl+Z
            if (!pilaReversion.empty()) {
                std::string topPila = pilaReversion.top();
                pilaReversion.pop();
                if (topPila == "*") {
                    if(!frase.empty()) frase.pop_back();
                }
                else {
                    frase.push_back(topPila);
                }
            }
        }
        else { 
            //PALABRA NORMAL
            //Si el siguiente string es una palabra, se añade a la frase y se añade a la pila un identificativo 
            // para que si se hace ctrl+z va a tener que borrarse
            frase.push_back(word);
            pilaReversion.push("*");
        }
    }

    displayFrase(frase);
}

// resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
void resuelveCaso() {

    string in;
    deque<string> input;

    getline(cin, in);

    std::stringstream ss(in);

    while (ss >> in) {
        input.push_back(in);

    }

    if(!input.empty()) resolver(input);




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

   string basura;
   getline(std::cin, basura);
   
   for (int i = 0; i < numCasos; ++i)
      resuelveCaso();
   
   // para dejar todo como estaba al principio
#ifndef DOMJUDGE
   std::cin.rdbuf(cinbuf);
   std::cout.rdbuf(coutbuf);
#endif
   return 0;
}
