//
// Created by Everardo Ramirez on 30/03/2017.
//

#include "Lista.h"
#include <iostream>

using namespace std;

Lista::Lista() {
    primero = nullptr;
    contadorID=0;
}

void Lista::crearLista() {
    int numero = 0;
    int pos = 0;
    while (numero != -1) {
        cout << "uam" << endl;
        cin >> numero;
        this->insertarUltimo("p",pos,numero,contadorID,numero,0);
        pos += numero;
        contadorID++;
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

void Lista::insertarUltimo(string tipo, int posicion, int uam, int id,int tamano,int residuo) {
    if (primero == nullptr) {
        primero = new Nodo(uam,posicion,id,tamano,residuo,tipo);
    } else {
        Nodo *ultimo = this->ultimo();
        ultimo->setEnlace(new Nodo(uam,posicion,id,tamano,residuo,tipo));
    }

}

void Lista::recorreLista() {
    Nodo *p = primero;

    do {
        cout << p->toString() << endl;
        p = p->getEnlace();
    } while (p!= nullptr);


}

void Lista::insertarInicio(string tipo, int posicion, int uam, int id,int tamano,int residuo) {
    Nodo *nuevo;
    nuevo =new Nodo(uam,posicion,id,tamano,residuo,tipo);
    nuevo->setEnlace(primero);
    primero = nuevo;

}

void Lista::insertarMedio(string tipo, int posicion, int uam, int id,int tamano,int residuo, Nodo *anterior) {

}

int Lista::getContadorID() const {
    return contadorID;
}

void Lista::setContadorID(int contadorID) {
    Lista::contadorID = contadorID;
}




