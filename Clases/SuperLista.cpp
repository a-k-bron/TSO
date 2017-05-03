//
// Created by Everardo Ramirez on 19/04/2017.
//

#include <iostream>
#include "SuperLista.h"
#include "Lista.h"

int SuperLista::getTamanoMemoria() const {
    return tamanoMemoria;
}

void SuperLista::setTamanoMemoria(int tamanoMemoria) {
    SuperLista::tamanoMemoria = tamanoMemoria;
}

int SuperLista::getTamanoUAM() const {
    return tamanoUAM;
}

void SuperLista::setTamanoUAM(int tamanoUAM) {
    SuperLista::tamanoUAM = tamanoUAM;
}

SuperLista::SuperLista(int tamanoMemoria, int tamanoUAM) : tamanoMemoria(tamanoMemoria), tamanoUAM(tamanoUAM) {
    l = new Lista();
    l->insertarUltimo("h", 0, getTamanoMemoria() / getTamanoUAM(), -1, getTamanoMemoria(),
                      getTamanoMemoria() % getTamanoUAM());
    contadorID = 0;
}

void SuperLista::crearLista() {

    int tamano = 0, acumulado = 0;
    int calculoUAM, residuo;
    Nodo *p;
    cout << "tamano del proceso" << endl;
    cin >> tamano;
    while (tamano != -1) {

        calculoUAM = tamano / getTamanoUAM();
        if (tamano % getTamanoUAM() > 0) {
            calculoUAM += 1;
            residuo = getTamanoUAM() - (tamano % getTamanoUAM());
        } else {
            residuo = 0;
        }
        l->insertarInicio("p", 0, calculoUAM, contadorID, tamano, residuo);//tipo,posicion,uam,id,tamaño,residuo
        l->ultimo()->setUam(l->ultimo()->getUam() - calculoUAM);
        l->ultimo()->setTamano(l->ultimo()->getTamano() - (calculoUAM * getTamanoUAM()));
        contadorID++;
        cin >> tamano;
    }

}

int SuperLista::getContadorID() const {
    return contadorID;
}

void SuperLista::setContadorID(int contadorID) {
    SuperLista::contadorID = contadorID;
}

void SuperLista::buscar() {
    int aux;
    cout << "numero con que buscar: ";
    cin >> aux;
    l->buscarPorID(aux)->toString();

}

void SuperLista::terminarProceso(int id) {
    if (l->buscarPorID(id)) {
        l->buscarPorID(id)->setTipo("h");//cambio el tipo a h
        l->buscarPorID(id)->setId(-1);
        terminarProceso();
    } else{
        cout<<"el proceso "<<id<<" no existe"<<endl;
    }


}

void SuperLista::terminarProceso() {
    int calculoUAM;
    Nodo *p = l->getPrimero();//proceso de verificacion de huecos juntos
    while (p != nullptr && p->getEnlace() != nullptr) {
        if (p->getTipo() == "h" && p->getEnlace()->getTipo() == "h") {
            p->setTamano(p->getTamano() + p->getEnlace()->getTamano());
            calculoUAM = p->getTamano() / getTamanoUAM();
            if (p->getTamano() % getTamanoUAM() > 0) {
                calculoUAM += 1;
                p->setResiduo(getTamanoUAM() - (p->getTamano() % getTamanoUAM()));
            } else {
                p->setResiduo(0);
            }
            p->setUam(calculoUAM);
            p->getEnlace()->setTipo("eliminar");
            l->eliminar("eliminar");
            terminarProceso();
            //if (p == l->ultimo()) { break; }
        }

        p = p->getEnlace();
    }
}

void SuperLista::aumentarContadorID() {
    contadorID++;
}
