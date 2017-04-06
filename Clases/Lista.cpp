//
// Created by Everardo Ramirez on 30/03/2017.
//

#include "Lista.h"
#include <iostream>

using namespace std;

Lista::Lista() {
    primero = nullptr;
}

void Lista::crearLista() {
    int numero = 0;
    int pos = 0;
    while (numero != -1) {
        cout << "uam" << endl;
        cin >> numero;
        this->insertarUltimo("p", pos, numero);
        pos+=numero;
    }
}

Nodo *Lista::ultimo() {
    Nodo *p = primero;
    if (p == nullptr)throw "Error, lista vacia";
    while (p->getEnlace() != nullptr) {
        p = p->getEnlace();
    }
    return p;
}

void Lista::insertarUltimo(string tipo, int posicion, int uam) {
    if (primero == nullptr) {
        primero = new Nodo(tipo, posicion, uam);
    } else {
        Nodo *ultimo = this->ultimo();
        ultimo->setEnlace(new Nodo(tipo, posicion, uam));
    }

}

void Lista::recorreLista() {
    Nodo *p = primero;

    do{
        cout<<p->toString()<<endl;
        p=p->getEnlace();
    }while(p->getEnlace()!= nullptr);


}


