
#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <unordered_map>
#include <list>
#include <set>
#include <iostream>
#include "Academia.h"


using namespace std;

bool tratar_caso() {
    Academia ac;
    string comando;
    cin >> comando;
    if (cin.eof()) return false;

    while (comando != "FIN") {
        try {
            if (comando == "nuevo_estudiante") {
                string dni;
                int grupo;
                cin >> dni >> grupo;
                ac.nuevo_estudiante(dni, grupo);
            }
            else if (comando == "grupo_estudiante") {
                string dni;
                cin >> dni;
                int grupo = ac.grupo_estudiante(dni);
                cout << dni << " esta en el grupo " << grupo << "\n";
            }
            else if (comando == "promocionar") {
                string dni;
                cin >> dni;
                ac.promocionar(dni);
            }
            else if (comando == "graduados") {
                list<string> graduados = ac.graduados();
                cout << "Lista de graduados:";
                for (const string& s : graduados) {
                    cout << " " << s;
                }
                cout << "\n";
            }
            else if (comando == "novato") {
                int grupo;
                cin >> grupo;
                string novato = ac.novato(grupo);
                cout << "Novato de " << grupo << ": " << novato << "\n";
            }
        }
        catch (std::domain_error& e) {
            cout << "ERROR: " << e.what() << "\n";
        }

        cin >> comando;
    }
    cout << "---\n";

    return true;
} // tratar_caso

int main() {
#ifndef DOMJUDGE
    std::ifstream input("sample.in");
    auto cinbuf = std::cin.rdbuf(input.rdbuf());
#endif

    while (tratar_caso()) {}

#ifndef DOMJUDGE
    std::cin.rdbuf(cinbuf);
    // Descomentar si se trabaja en Windows
    // system("PAUSE");
#endif
    return 0;
}
