//
// Created by Everardo Ramirez on 19/04/2017.
//

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
}
