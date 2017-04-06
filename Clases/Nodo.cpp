//
// Created by Everardo Ramirez on 30/03/2017.
//

#include <sstream>
#include "Nodo.h"


Nodo::Nodo(string tipo, int posicion, int uam) {
    this->tipo = tipo;
    this->posicion = posicion;
    this->uam = uam;
    enlace = nullptr;

}

Nodo::Nodo(string tipo, int posicion, int uam, Nodo *n) {
    this->tipo = tipo;
    this->posicion = posicion;
    this->uam = uam;
    this->enlace = n;

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

string Nodo::getTipo() const {
    return tipo;
}

void Nodo::setTipo(string tipo) {
    Nodo::tipo = tipo;
}

Nodo *Nodo::getEnlace() const {
    return enlace;
}

void Nodo::setEnlace(Nodo *enlace) {
    Nodo::enlace = enlace;
}

string Nodo::toString() {
    stringstream *convertir = new stringstream();
    *convertir << this->getPosicion();
    string cadena = "tipo " + getTipo() + " posicion " + convertir->str();
    delete convertir;
    convertir = new stringstream();
    *convertir << this->getUam();
    cadena += " uam " + convertir->str();
    delete convertir;
    return cadena;
}


