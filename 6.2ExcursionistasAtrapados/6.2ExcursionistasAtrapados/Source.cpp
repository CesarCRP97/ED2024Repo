/*
 * ---------------------------------------------------
 *                ESTRUCTURAS DE DATOS
 * ---------------------------------------------------
 *              Manuel Montenegro Montes
 *              Facultad de Inform�tica
 *         Universidad Complutense de Madrid
 * ---------------------------------------------------
 */

 /*
  * Aqu� se introducen los recorridos parametrizados con respecto
  * al tipo de acci�n que se desea realizar en cada visita.
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
// Introduce m�s librer�as si son necesarias
using namespace std;

void resuelveCaso();

int main() {
  
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

 #ifndef DOMJUDGE
    std::cin.rdbuf(cinbuf);
    std::cout.rdbuf(coutbuf);
    system("PAUSE");
 #endif
    return 0;
}
//devuelve par { n� rescatadores, n� max rescate}
pair<int, int> rescatar(BinTree<int> arbol) {
    if (arbol.empty()) {
        return { 0, 0 };
    }
    else {
        auto [rescatadores_izq, maxPerdidosIzq] = rescatar(arbol.left());
        auto [rescatadores_der, maxPerdidosDer] = rescatar(arbol.right());

        int maxPerdidos = arbol.root() + max(maxPerdidosDer, maxPerdidosIzq);
        int total_rescatadores = rescatadores_der + rescatadores_izq;

        //Si no hay rescatadores por esa ruta y hay perdidos en la raiz
        if (total_rescatadores == 0 && arbol.root() > 0) total_rescatadores = 1;

        return { total_rescatadores, maxPerdidos};

    }
}


// resuelve un caso de prueba, leyendo de la entrada la
// configuraci�n, y escribiendo la respuesta
void resuelveCaso() {

    BinTree<int> rutas = read_tree<int>(cin);
    pair<int,int> p = rescatar(rutas);

    cout << p.first << " " << p.second << "\n";


    // escribir soluci�n
}