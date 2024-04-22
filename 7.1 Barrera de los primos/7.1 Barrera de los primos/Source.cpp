/*
 * ---------------------------------------------------
 *                ESTRUCTURAS DE DATOS
 * ---------------------------------------------------
 *              Manuel Montenegro Montes
 *              Facultad de Informática
 *         Universidad Complutense de Madrid
 * ---------------------------------------------------
 */

 /*
  * Aquí se introducen los recorridos parametrizados con respecto
  * al tipo de acción que se desea realizar en cada visita.
  */

#ifndef __BINTREE_H
#define __BINTREE_H

#include <cassert>
#include <iostream>
#include <iterator>
#include <memory>
#include <queue>
#include <stack>

template <class T> class BinTree {

private:
    struct TreeNode;
    using NodePointer = std::shared_ptr<TreeNode>;

public:
    BinTree() : root_node(nullptr) {}

    BinTree(const T& elem)
        : root_node(std::make_shared<TreeNode>(nullptr, elem, nullptr)) {}

    BinTree(const BinTree& left, const T& elem, const BinTree& right)
        : root_node(std::make_shared<TreeNode>(left.root_node, elem,
            right.root_node)) {}

    bool empty() const { return root_node == nullptr; }

    const T& root() const {
        assert(root_node != nullptr);
        return root_node->elem;
    }

    BinTree left() const {
        assert(root_node != nullptr);
        BinTree result;
        result.root_node = root_node->left;
        return result;
    }

    BinTree right() const {
        assert(root_node != nullptr);
        BinTree result;
        result.root_node = root_node->right;
        return result;
    }

    void display(std::ostream& out) const { display_node(root_node, out); }

    template <typename U> void preorder(U func) const {
        preorder(root_node, func);
    }

    template <typename U> void inorder(U func) const {
        inorder(root_node, func);
    }

    template <typename U> void postorder(U func) const {
        postorder(root_node, func);
    }

    template <typename U> void levelorder(U func) const;

private:
    struct TreeNode {
        TreeNode(const NodePointer& left, const T& elem, const NodePointer
            & right)
            : elem(elem), left(left), right(right) {}

        T elem;
        NodePointer left, right;
    };

    NodePointer root_node;

    static void display_node(const NodePointer& root, std::ostream& out) {
        if (root == nullptr) {
            out << ".";
        }
        else {
            out << "(";
            display_node(root->left, out);
            out << " " << root->elem << " ";
            display_node(root->right, out);
            out << ")";
        }
    }

    template <typename U> static void preorder(const NodePointer& node, U
        func);

    template <typename U> static void inorder(const NodePointer& node, U func);

    template <typename U> static void postorder(const NodePointer& node, U
        func);
};

template <typename T>
template <typename U>
void BinTree<T>::preorder(const NodePointer& node, U func) {
    if (node != nullptr) {
        func(node->elem);
        preorder(node->left, func);
        preorder(node->right, func);
    }
}

template <typename T>
template <typename U>
void BinTree<T>::inorder(const NodePointer& node, U func) {
    if (node != nullptr) {
        inorder(node->left, func);
        func(node->elem);
        inorder(node->right, func);
    }
}

template <typename T>
template <typename U>
void BinTree<T>::postorder(const NodePointer& node, U func) {
    if (node != nullptr) {
        postorder(node->left, func);
        postorder(node->right, func);
        func(node->elem);
    }
}

template <typename T>
template <typename U>
void BinTree<T>::levelorder(U func) const {
    std::queue<NodePointer> pending;
    if (root_node != nullptr) {
        pending.push(root_node);
    }
    while (!pending.empty()) {
        NodePointer current = pending.front();
        pending.pop();
        func(current->elem);
        if (current->left != nullptr) {
            pending.push(current->left);
        }
        if (current->right != nullptr) {
            pending.push(current->right);
        }
    }
}

template <typename T>
std::ostream& operator<<(std::ostream& out, const BinTree<T>& tree) {
    tree.display(out);
    return out;
}

template <typename T> BinTree<T> read_tree(std::istream& in) {
    char c;
    in >> c;
    if (c == '.') {
        return BinTree<T>();
    }
    else {
        assert(c == '(');
        BinTree<T> left = read_tree<T>(in);
        T elem;
        in >> elem;
        BinTree<T> right = read_tree<T>(in);
        in >> c;
        assert(c == ')');
        BinTree<T> result(left, elem, right);
        return result;
    }
}

#endif


#include <iostream>
#include <fstream>
// Introduce más librerías si son necesarias
using namespace std;

void resuelveCaso();

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

bool es_primo(int n) {

    for (int i = 2; i < n; i++) {
        if (n % i == 0) return false;
    }
    return true;
}
//Devuelve {profundidad del valor, valor}
pair<int, int> barrera(BinTree<int> arbol) {
    if (arbol.empty()) {
        return { 0,0 };
    }
    else {
        auto [prof_encont_izq, valor_izq] = barrera(arbol.left());
        auto [prof_encont_der, valor_der] = barrera(arbol.right());

        int valor_devuelto = 0;
        int prof_devuelta = 0;

        //Si la raiz es primo devuelve {0,0} 
        if (es_primo(arbol.root())){
            return { 0, 0 };
        }

        //Si la raiz es múltiplo de 7, lo devuelve directamente.
        if (arbol.root() % 7 == 0) return { 1 ,arbol.root() };


        //Si el hijo izq devuelve algo que pueda ser solución
        if (valor_izq != 0) {
            valor_devuelto = valor_izq; 
            prof_devuelta = prof_encont_izq + 1;
        }

        //Si el valor_der puede ser solución
        if (valor_der != 0) {
            //Vemos si hay algo ya en el devuelto
            if (valor_devuelto != 0) {
                //Si viene de mayor profundidad
                if (prof_encont_izq > prof_encont_der) {
                    valor_devuelto = valor_der;
                    prof_devuelta = prof_encont_der + 1;
                }
            }
            //Si por la izquierda ha devuelto {0,0}
            else {
                valor_devuelto = valor_der;
                prof_devuelta = prof_encont_der + 1;
            }
        }
        
        return { prof_devuelta, valor_devuelto };
        
    }

}



// resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
void resuelveCaso() {

    BinTree<int> arbol = read_tree<int>(cin);
    auto [profundidad_devuelta, valor_devuelta] = barrera(arbol);

    if (profundidad_devuelta == 0 && valor_devuelta == 0)
        cout << "NO HAY\n";
    else {
        cout << valor_devuelta << " " << profundidad_devuelta << '\n';
    }
    


    // escribir solución
}