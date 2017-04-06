//
// Created by Everardo Ramirez on 30/03/2017.
//

#ifndef ADMINISTRACION_DE_MEMORIA_LISTA_H
#define ADMINISTRACION_DE_MEMORIA_LISTA_H


#include "Nodo.h"

class Lista {
protected:
    Nodo* primero;
public:
    Lista();
    void crearLista();
    Nodo * ultimo();
    void insertarUltimo(string tipo, int posicion, int uam );
    void recorreLista();



};


#endif //ADMINISTRACION_DE_MEMORIA_LISTA_H
