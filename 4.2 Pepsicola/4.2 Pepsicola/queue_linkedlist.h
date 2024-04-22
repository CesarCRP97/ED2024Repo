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
  * Implementación del TAD Cola mediante listas enlazadas.
  */

#ifndef __QUEUE_LINKEDLIST_H
#define __QUEUE_LINKEDLIST_H

#include <cassert>
#include <iostream>

template <typename T> class QueueLinkedList {
public:
    QueueLinkedList() : front_node(nullptr), back_node(nullptr) {}
    QueueLinkedList(const QueueLinkedList& other) {
        copy_nodes_from(other.front_node);
    }

    ~QueueLinkedList() { free_nodes_from(front_node); }

    QueueLinkedList& operator=(const QueueLinkedList& other) {
        if (this != &other) {
            free_nodes_from(front_node);
            copy_nodes_from(other.front_node);
        }
        return *this;
    }

    void push(const T& elem) {
        Node* new_node = new Node{ elem, nullptr };
        if (back_node == nullptr) {
            back_node = new_node;
            front_node = new_node;
        }
        else {
            back_node->next = new_node;
            back_node = new_node;
        }
    }

    void pop() {
        assert(front_node != nullptr);
        Node* target = front_node;
        front_node = front_node->next;
        if (back_node == target) {
            back_node = nullptr;
        }
        delete target;
    }

    T& front() {
        assert(front_node != nullptr);
        return front_node->value;
    }

    const T& front() const {
        assert(front_node != nullptr);
        return front_node->elem;
    }

    bool empty() const { return (front_node == nullptr); }

    void pepsicola(QueueLinkedList<T> colegas, T pringao);

private:
    struct Node {
        T value;
        Node* next;
    };

    void copy_nodes_from(Node* other);
    void free_nodes_from(Node* other);

    

    Node* front_node;
    Node* back_node;
};

template <typename T> void QueueLinkedList<T>::copy_nodes_from(Node* other) {
    if (other == nullptr) {
        front_node = nullptr;
        back_node = nullptr;
    }
    else {
        front_node = new Node{ other->value, nullptr };
        back_node = front_node;
        Node* current = other->next;
        while (current != nullptr) {
            Node* new_node = new Node{ current->value, nullptr };
            back_node->next = new_node;
            current = current->next;
            back_node = new_node;
        }
    }
}

template <typename T> void QueueLinkedList<T>::free_nodes_from(Node* other) {
    Node* current = other;
    while (current != nullptr) {
        Node* next = current->next;
        delete current;
        current = next;
    }
}

template <typename T> void QueueLinkedList<T>::pepsicola(QueueLinkedList<T> colegas, T pringao) {
    
    if (colegas.empty()) return;

    Node* currQ = this->front_node;
    Node* currColegas = colegas.front_node;

    //Recorre la cola hasta encontrar el pringao (si no se encuentra, 
    while (currQ != nullptr && currQ->value != pringao) currQ = currQ->next;

    //Si no encuentra el pringado no introduce los colegas, por lo que liberamos a los colegas.
    if (currQ == nullptr) {
        while (!colegas.empty()) colegas.pop();
        return;
    }
    //Si pringado encontrado
    else {
        //Guarda el siguiente en la cola al pringado
        Node* aux = currQ->next;

        //Adjunta uno de los colegas como siguiente al pringao
        currQ->next = colegas.front_node;

        //El último de los colegas tiene como siguiente al que hemos guardado.
        colegas.back_node->next = aux;

        //Deja la cola de colegas vacío.
        colegas.front_node = nullptr;
        colegas.back_node = nullptr;
    }
    

}



#endif