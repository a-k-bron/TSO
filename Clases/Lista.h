//
// Created by Everardo Ramirez on 30/03/2017.
//

#ifndef ADMINISTRACION_DE_MEMORIA_LISTA_H
#define ADMINISTRACION_DE_MEMORIA_LISTA_H


#include "Nodo.h"

class Lista {
protected:
    Nodo *primero;
    int contadorID;
public:


    Lista();

    void crearLista();

    Nodo *ultimo();

    void recorreLista();


    void insertarUltimo(string tipo, int posicion, int uam, int id, int tamano, int residuo);

    void insertarInicio(string tipo, int posicion, int uam, int id, int tamano, int residuo);

    void insertarMedio(string tipo, int posicion, int uam, int id, int tamano, int residuo, Nodo *anterior);

    int getContadorID() const;

    void setContadorID(int contadorID);
};


#endif //ADMINISTRACION_DE_MEMORIA_LISTA_H
