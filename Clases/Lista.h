//
// Created by Everardo Ramirez on 30/03/2017.
//

#ifndef ADMINISTRACION_DE_MEMORIA_LISTA_H
#define ADMINISTRACION_DE_MEMORIA_LISTA_H


#include "Nodo.h"

class Lista {
protected:
    Nodo *primero; // almacena direccion
public:
    Nodo *getPrimero() const; // devuelve informacion

public:


    Lista(); // primer punto apunto a nulo ya que no hay nada en la lista
    Nodo *ultimo();

    void recorreLista();
    Nodo *buscarPorID(int buscado);
    void eliminar(string tipo);
    void eliminar(int id);

    void insertarUltimo(string tipo, int posicion, int uam, int id, int tamano, int residuo);

    void insertarInicio(string tipo, int posicion, int uam, int id, int tamano, int residuo);

    void insertarMedio(string tipo, int posicion, int uam, int id, int tamano, int residuo, Nodo *anterior);

};


#endif //ADMINISTRACION_DE_MEMORIA_LISTA_H
