//
// Created by Everardo Ramirez on 19/04/2017.
//

#ifndef ADMINISTRACION_DE_MEMORIA_SUPERLISTA_H
#define ADMINISTRACION_DE_MEMORIA_SUPERLISTA_H


#include "Lista.h"

class SuperLista {
    int tamanoMemoria, tamanoUAM;

public:
    SuperLista(int tamanoMemoria, int tamanoUAM);

    Lista* l;

    int getTamanoMemoria() const;

    void setTamanoMemoria(int tamanoMemoria);

    int getTamanoUAM() const;

    void setTamanoUAM(int tamanoUAM);
};


#endif //ADMINISTRACION_DE_MEMORIA_SUPERLISTA_H