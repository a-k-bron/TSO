//
// Created by Everardo Ramirez on 30/03/2017.
//

#include <sstream>
#include "Nodo.h"


string Nodo::toString() {
    stringstream *convertir = new stringstream();
    *convertir << this->getPosicion();
    string cadena = "tipo " + getTipo() + " posicion " + convertir->str();
    delete convertir;
    convertir = new stringstream();
    *convertir << this->getUam();
    cadena += " uam " + convertir->str();
    delete convertir;
    convertir = new stringstream();
    *convertir << this->getId();
    cadena += " id " + convertir->str();
    delete convertir;
    return cadena;
}

Nodo::Nodo(int uam, int posicion, int id, int tamano, int residuo, const string &tipo, Nodo *enlace) : uam(uam),
                                                                                                       posicion(
                                                                                                               posicion),
                                                                                                       id(id),
                                                                                                       tamano(tamano),
                                                                                                       residuo(residuo),
                                                                                                       tipo(tipo),
                                                                                                       enlace(enlace) {}

Nodo::Nodo(int uam, int posicion, int id, int tamano, int residuo, const string &tipo) : uam(uam), posicion(posicion),
                                                                                         id(id), tamano(tamano),
                                                                                         residuo(residuo), tipo(tipo) {
    enlace = nullptr;
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

int Nodo::getId() const {
    return id;
}

void Nodo::setId(int id) {
    Nodo::id = id;
}

int Nodo::getTamano() const {
    return tamano;
}

void Nodo::setTamano(int tamano) {
    Nodo::tamano = tamano;
}

int Nodo::getResiduo() const {
    return residuo;
}

void Nodo::setResiduo(int residuo) {
    Nodo::residuo = residuo;
}

const string &Nodo::getTipo() const {
    return tipo;
}

void Nodo::setTipo(const string &tipo) {
    Nodo::tipo = tipo;
}

Nodo *Nodo::getEnlace() const {
    return enlace;
}

void Nodo::setEnlace(Nodo *enlace) {
    Nodo::enlace = enlace;
}




