#include <iostream>
#include <list>

using namespace std;

bool toepliz(const list<list<int>> matrix) {
	auto fila_anterior = matrix.cbegin();
	auto fila_actual = ++matrix.cbegin();

	while (fila_actual != matrix.cend()) {
		auto columna_anterior = (*fila_anterior).cbegin();
		auto columna_actual = ++(*fila_actual).cbegin();
		while (columna_actual != (*fila_actual).cend()) {
			if (*columna_actual != *columna_anterior) return false;
			columna_actual++;
			columna_anterior++;
		}
	}
}