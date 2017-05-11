
#include "Lista.h"
#include <iostream>

using namespace std;

Lista::Lista() {
    primero = nullptr; // marca el primero a nulo
}


Nodo *Lista::ultimo() { // devuelve puntero al ultimo elemento de la lista
    Nodo *p = primero;// da a p el primer nodo de la lista
    if (p == nullptr)throw "Error, lista vacia";// si p es nulo significa que esta la lista vacia
    while (p->getEnlace() != nullptr) { //busca hasta que el siguiente enlace sea nulo, entonces ese sera el ultimo
        p = p->getEnlace();// actualiza p al siguiente nodo
    }
    return p;
}

void Lista::insertarUltimo(string tipo, int posicion, int uam, int id, int tamano, int residuo) {
    if (primero == nullptr) {// Si el primer nodo es nulo significa que la lista esta vacia y ahi inserta el primer nodo
        primero = new Nodo(uam, posicion, id, tamano, residuo, tipo);
    } else {
        Nodo *ultimo = this->ultimo();//llama la funcion ultimo
        ultimo->setEnlace(new Nodo(uam, posicion, id, tamano, residuo, tipo));//inserta el nodo delante del ultimo que habia
    }

}

void Lista::recorreLista() {
    Nodo *p = primero;// asigna al puntero p el primer nodo

    do {

        p->toString();//llamada a la funcion to string que imprime la informacion del nodo
        p = p->getEnlace();//obtiene el siguiente enlace y lo asigna a p
    } while (p != nullptr);


}

void Lista::insertarInicio(string tipo, int posicion, int uam, int id, int tamano, int residuo) {
    Nodo *nuevo = new Nodo(uam, posicion, id, tamano, residuo, tipo);
    if (primero == nullptr) { //inserta primer nodo al inicio de la lista si esta vacia
        primero = nuevo;
    } else { // si no esta vacia da la primer posicion al ultimo en llegar, moviendo las posiciones de los demas
        nuevo->setEnlace(primero);//inserta el nuevo y enlaza al actual primero
        primero = nuevo;//el nuevo nodo ahora es el primero
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
        aux = aux->getEnlace();//obtiene el siguiente nodo
    }
    return aux;
}

void Lista::eliminar(string tipo) {//elimino segun el tipo
    Nodo *actual, *anterior;
    bool encontrado;
    actual = getPrimero();
    anterior = nullptr;//banderas
    encontrado = false;
    while ((actual != nullptr) && !encontrado) {// mientras no lleguemos al final de la lista y no encontremos el numero
        encontrado = (actual->getTipo() == tipo);//comparo tipo del nodo actual con el tipo a buscar
        if (!encontrado) {//mientras no lo encuentre sigo recorriendo la lista.
            anterior = actual;//actualizo las posiciones a las siguientes
            actual = actual->getEnlace();
        }
    }

    if (actual != nullptr) {//siempre mantengo el primer puntero para evitar errores y perder la lista
        if (actual == primero) {//Cuando el primer elemento de la lista es el que se va a eliminar, mantengo la lista al darle la primera posicion al elemento que sigue
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




