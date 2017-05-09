
#include "Lista.h"
#include <iostream>

using namespace std;

Lista::Lista() {
    primero = nullptr; // marca el primero a nulo
}


Nodo *Lista::ultimo() { // devuelve puntero al ultimo elemento de la lista
    Nodo *p = primero;
    if (p == nullptr)throw "Error, lista vacia";
    while (p->getEnlace() != nullptr) { //apunta al siguiente nodo hasta apuntar al ultimo y llegar a nulo
        p = p->getEnlace();
    }
    return p;
}

void Lista::insertarUltimo(string tipo, int posicion, int uam, int id, int tamano, int residuo) {
    if (primero == nullptr) {
        primero = new Nodo(uam, posicion, id, tamano, residuo, tipo);
    } else {
        Nodo *ultimo = this->ultimo();
        ultimo->setEnlace(new Nodo(uam, posicion, id, tamano, residuo, tipo));
    }

}

void Lista::recorreLista() {
    Nodo *p = primero;

    do {

        p->toString();
        p = p->getEnlace();
    } while (p != nullptr);


}

void Lista::insertarInicio(string tipo, int posicion, int uam, int id, int tamano, int residuo) {
    Nodo *nuevo = new Nodo(uam, posicion, id, tamano, residuo, tipo);
    if (primero == nullptr) { //inserta primer nodo al inicio de la lista si esta vacia
        primero = nuevo;
    } else { // si no esta vacia da la primer posicion al ultimo en llegar, moviendo las posiciones de los demas
        nuevo->setEnlace(primero);
        primero = nuevo;
    }

}

void Lista::insertarMedio(string tipo, int posicion, int uam, int id, int tamano, int residuo, Nodo *anterior) {
    Nodo *nuevo = new Nodo(uam, posicion, id, tamano, residuo, tipo);
    nuevo->setEnlace(anterior->getEnlace());//el metodo pide el enlace anterior, es decir la posicion en donde entrara el nuevo nodo y se posiciona delante de ese nodo.
    anterior->setEnlace(nuevo);

}

Nodo *Lista::getPrimero() const { //obtiene el primer elemento de la lista
    return primero;
}

Nodo *Lista::buscarPorID(int buscado) {
    Nodo *aux = getPrimero();//busca hasta llegar al nodo buscado recorriendo toda la lista
    while (aux != nullptr) {
        if (aux->getId() == buscado) {
            return aux;
        }
        aux = aux->getEnlace();
    }
    return aux;
}

void Lista::eliminar(string tipo) {
    Nodo *actual, *anterior;
    bool encontrado;
    actual = getPrimero();
    anterior = nullptr;
    encontrado = false;
    while ((actual != nullptr) && !encontrado) {// mientras no lleguemos al final de la lista y no encontremos el numero
        encontrado = (actual->getTipo() == tipo);//comparo tipo del nodo actual con el tipo a buscar
        if (!encontrado) {//mientras no lo encuentre sigo recorriendo la lista.
            anterior = actual;
            actual = actual->getEnlace();
        }
    }

    if (actual != nullptr) {//siempre mantengo el primer puntero para evitar errores y perder la lista
        if (actual == primero) {
            primero = actual->getEnlace();//si es el primero, da la posicion del primero al siguiente
        } else {
            anterior->setEnlace(actual->getEnlace());//le da la posicion al que esta despues al que quiero eliminar.
        }
        delete actual;
    }

}

void Lista::eliminar(int id) { //lo mismo que el anterior pero este elimina por el id
    Nodo *actual, *anterior;
    bool encontrado;
    actual = getPrimero();
    anterior = nullptr;
    encontrado = false;
    while ((actual != nullptr) && !encontrado) {
        encontrado = (actual->getId() == id);
        if (!encontrado) {
            anterior = actual;
            actual = actual->getEnlace();
        }
    }

    if (actual != nullptr) {
        if (actual == primero) {
            primero = actual->getEnlace();
        } else {
            anterior->setEnlace(actual->getEnlace());
        }
        delete actual;
    }

}




