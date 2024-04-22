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
  * Implementación inicial del TAD de los árboles binarios.
  *
  * Cuidado: ¡Esta implementación no libera la memoria que reserva!
  */


#include <cassert>
#include <iostream>

template <class T> class BinTree {
public:
    BinTree() : root_node(nullptr) {}
    BinTree(const T& elem) : root_node(new TreeNode(nullptr, elem, nullptr)) {}
    BinTree(const BinTree& left, const T& elem, const BinTree& right)
        : root_node(new TreeNode(left.root_node, elem, right.root_node)) {}

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

private:
    struct TreeNode {
        T elem;
        TreeNode* left, * right;

        TreeNode(TreeNode* left, const T& elem, TreeNode* right)
            : elem(elem), left(left), right(right) {}
    };

    TreeNode* root_node;

    static void display_node(const TreeNode* root, std::ostream& out) {
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
};

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

template <typename T> BinTree<T> read_tree() {
    char c;
    cin >> c;
    if (c == '.') {
        return BinTree<T>();
    }
    else {
        assert(c == '*');
        BinTree<T> left = read_tree<T>();
        BinTree<T> right = read_tree<T>();
        return BinTree<T>(left, c, right);
    }
}


template <typename T> int num_nodos(const BinTree<T>& tree) {
    if (tree.empty()) {
        return 0;
    }
    else {
        int nodos_left = num_nodos(tree.left());
        int nodos_right = num_nodos(tree.right());
        return nodos_left + nodos_right + 1;
    }
}

template <typename T> bool es_zurdo(const BinTree<T>& tree) {
    if (tree.empty()) {
        return true;
    }
    else if (tree.left().empty() && tree.right().empty()) {//si es una hoja
        return true;
    }
    else {
        int nodos_left = num_nodos(tree.left());
        int nodos_right = num_nodos(tree.right());
        bool zurdo_left = es_zurdo(tree.left());
        bool zurdo_right = es_zurdo(tree.right());
        return zurdo_left && zurdo_right && nodos_left > nodos_right;
    }
}


template <typename T> std::pair<bool, int> es_zurdo_num_nodos(const BinTree<T>& tree) {
    if (tree.empty()) {
        return { true, 0 };
    }
    else if (tree.left().empty() && tree.right.empty()) {
        return { true, 1 };
    }
    else {
        std::pair<bool, int> result_left = es_zurdo_num_nodos(tree.left);
        bool es_zurdo_left = result_left.first;
        int num_nodos_left = result_left.second;
        auto [es_zurdo_right, num_nodos_right] = es_zurdo_num_nodos(tree.right());
        bool es_zurdo = es_zurdo_left && es_zurdo_right && num_nodos_left > num_nodos_right;
        int num_nodos = num_nodos_left + num_nodos_right + 1;
        return { es_zurdo, num_nodos };
    }
}

template <typename T> std::pair<bool, int> es_zurdo_bien(const BinTree<T>& tree) {
    if (tree.empty()) {
        return { true, 0 };
    }
    else if (tree.left().empty() && tree.right().empty()) {//si es una hoja
        return { true, 1 };
    }
    else {
        auto [is_zurdoIzq, num_hijosIzq] = es_zurdo_bien(tree.left());
        auto [is_zurdoDer, num_hijosDer] = es_zurdo_bien(tree.right());

        return { is_zurdoIzq && is_zurdoDer && num_hijosIzq > num_hijosDer , num_hijosIzq + num_hijosDer + 1 };
    }
}

template <typename T> std::pair<bool, int> es_balanceado(const BinTree<T>& tree) {
    if (tree.empty()) {
        return { true, 0 };
    }
    else {
        auto res_iz = es_balanceado(tree.left());
        auto res_der = es_balanceado(tree.right());
        int altura = max(res_iz.second(), altura_der);
        bool balanceado = es_bal_iz && es_bal_der && abs(altura_der - altura_izq <= 1);

        
        return { balanceado, altura + 1 };
    }
}

template <typename T> std::pair<int, int> diametro_altura(const BinTree<T>& tree) {
    if (tree.empty()) {
        return { 0, 0 };
    }
    else if (tree.left().empty() && tree.right().empty()) {
        return { 1, 1 };
    }
    else {
        auto [diametro_left, altura_left] = diametro_altura(tree.left());
        auto [diametro_right, altura_right] = diametro_altura(tree.right());
        int diametro_tree = std::max(altura_left + altura_right + 1, std::max(diametro_left, diametro_right));
        int altura_tree = 1 + std::max(altura_left, altura_right);
        return { diametro_tree, altura_tree };
    }
}


template <typename T> std::pair<int, int> maximo_num_grupos(const BinTree<int>& tree) {}