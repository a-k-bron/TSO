//
// Created by Everardo Ramirez on 30/03/2017.
//

#include "Nodo.h"


Nodo::Nodo(char tipo, int posicion, int uam) {
    this->tipo=tipo;
    this->posicion=posicion;
    this->uam =  uam;
    enlace= nullptr;

}

Nodo::Nodo(char tipo, int posicion, int uam, Nodo *n) {
    this->tipo=tipo;
    this->posicion=posicion;
    this->uam =  uam;
    this->enlace=n;

}

int Nodo::getUam() const {
    return uam;
}

void Nodo::setUam(int uam) {
    Nodo::uam = uam;
}

int Nodo::getPosicion() const {
    return posicion;
}

void Nodo::setPosicion(int posicion) {
    Nodo::posicion = posicion;
}

char Nodo::getTipo() const {
    return tipo;
}

void Nodo::setTipo(char tipo) {
    Nodo::tipo = tipo;
}

Nodo *Nodo::getEnlace() const {
    return enlace;
}

void Nodo::setEnlace(Nodo *enlace) {
    Nodo::enlace = enlace;
}


