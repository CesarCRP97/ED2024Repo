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
  * Implementación del TAD Lista mediante listas doblemente enlazadas circulares.
  *
  * Esta versión introduce genericidad mediante plantillas.
  */

#ifndef __LIST_LINKED_DOUBLE_H
#define __LIST_LINKED_DOUBLE_H

#include <cassert>
#include <iostream>

template <typename Elem> class ListLinkedDouble {
private:
    struct Node {
        Elem value;
        Node* next;
        Node* prev;
    };

public:
    ListLinkedDouble() : num_elems(0) {
        head = new Node;
        head->next = head;
        head->prev = head;
    }

    ListLinkedDouble(const ListLinkedDouble& other) : ListLinkedDouble() {
        copy_nodes_from(other);
        num_elems = other.num_elems;
    }

    ~ListLinkedDouble() { delete_nodes(); }

    void push_front(const Elem& elem) {
        Node* new_node = new Node{ elem, head->next, head };
        head->next->prev = new_node;
        head->next = new_node;
        num_elems++;
    }

    void push_back(const Elem& elem) {
        Node* new_node = new Node{ elem, head, head->prev };
        head->prev->next = new_node;
        head->prev = new_node;
        num_elems++;
    }

    void pop_front() {
        assert(num_elems > 0);
        Node* target = head->next;
        head->next = target->next;
        target->next->prev = head;
        delete target;
        num_elems--;
    }

    void pop_back() {
        assert(num_elems > 0);
        Node* target = head->prev;
        target->prev->next = head;
        head->prev = target->prev;
        delete target;
        num_elems--;
    }

    int size() const { return num_elems; }

    bool empty() const { return num_elems == 0; };

    const Elem& front() const {
        assert(num_elems > 0);
        return head->next->value;
    }

    Elem& front() {
        assert(num_elems > 0);
        return head->next->value;
    }

    const Elem& back() const {
        assert(num_elems > 0);
        return head->prev->value;
    }

    Elem& back() {
        assert(num_elems > 0);
        return head->prev->value;
    }

    const Elem& operator[](int index) const {
        assert(0 <= index && index < num_elems);
        Node* result_node = nth_node(index);
        return result_node->value;
    }

    Elem& operator[](int index) {
        assert(0 <= index && index < num_elems);
        Node* result_node = nth_node(index);
        return result_node->value;
    }

    ListLinkedDouble& operator=(const ListLinkedDouble& other) {
        if (this != &other) {
            delete_nodes();
            head = new Node;
            head->next = head->prev = head;
            copy_nodes_from(other);
            num_elems = other.num_elems;
        }
        return *this;
    }

    void display(std::ostream& out) const;
    void add_to(int i, int m);

    void display() const { display(std::cout); }
    

private:
    Node* head;
    int num_elems;

    Node* nth_node(int n) const;
    void delete_nodes();
    void copy_nodes_from(const ListLinkedDouble& other);
};

template <typename Elem>
typename ListLinkedDouble<Elem>::Node*
ListLinkedDouble<Elem>::nth_node(int n) const {
    int current_index = 0;
    Node* current = head->next;

    while (current_index < n && current != head) {
        current_index++;
        current = current->next;
    }

    return current;
}

template <typename Elem> 
void ListLinkedDouble<Elem>::delete_nodes() {
    Node* current = head->next;
    while (current != head) {
        Node* target = current;
        current = current->next;
        delete target;
    }

    delete head;
}

template <typename Elem>
void ListLinkedDouble<Elem>::copy_nodes_from(const ListLinkedDouble& other) {
    Node* current_other = other.head->next;
    Node* last = head;

    while (current_other != other.head) {
        Node* new_node = new Node{ current_other->value, head, last };
        last->next = new_node;
        last = new_node;
        current_other = current_other->next;
    }
    head->prev = last;
}

template <typename Elem>
void ListLinkedDouble<Elem>::display(std::ostream& out) const {
    out << "[";
    if (head->next != head) {
        out << head->next->value;
        Node* current = head->next->next;
        while (current != head) {
            out << ", " << current->value;
            current = current->next;
        }
    }
    out << "]";
}

template<typename Elem>
inline void ListLinkedDouble<Elem>::add_to(int i, int m){
    //Encuentro el nodo el la posición dada, ya hay un método para eso.
    //Guardo los nodos anterior y posterior a ese para juntarlos
    //Utilizo los nodos para buscar su siguiente posición en la lista

    Node* changed = this->nth_node(i);
    Node* prev = changed->prev;
    Node* next = changed->next;

    //Juntar prev y next;
    prev->next = next;
    next->prev = prev;


    changed->value += m;
    if (prev->value > changed->value) {
        //bucle para recorrer la lista hasta que el nodo prev sea menor que el changed
        while (prev != head && prev->value > changed->value) {
            prev = prev->prev;
        }
        //Lo siguiente: introducir changed entre prev y su siguiente.
        prev->next->prev = changed;
        changed->next = prev->next;
        prev->next = changed;
        changed->prev = prev;
    }
    else if (next->value < changed->value) {
        while (next != head && next->value < changed->value) {
            next = next->next;
        }
        //Igual que caso anterior: introducir changed entre el previo a next y next.
        next->prev->next = changed;
        changed->prev = next->prev;
        next->prev = changed;
        changed->next = next;
    }
    else { 
        //Lo volvemos a colocar donde estaba
        prev->next = changed;
        next->prev = changed;
        
        //Las siguientes dos asignaciones no harían falta.
        changed->prev = prev;
        changed->next = next;

    }
}

template <typename Elem>
std::ostream& operator<<(std::ostream& out, const ListLinkedDouble<Elem>& l) {
    l.display(out);
    return out;
}


#endif