//
// Created by Everardo Ramirez on 30/03/2017.
//

#ifndef ADMINISTRACION_DE_MEMORIA_NODO_H
#define ADMINISTRACION_DE_MEMORIA_NODO_H

#include <string>


using namespace std;
class Nodo {
public:
    Nodo(string tipo, int posicion, int uam);

    Nodo(string tipo, int posicion, int uam, Nodo *n);

    int getUam() const;

    void setUam(int uam);

    int getPosicion() const;

    void setPosicion(int posicion);

    string getTipo() const;

    void setTipo(string tipo);

    Nodo *getEnlace() const;

    void setEnlace(Nodo *enlace);

    string toString();


protected:
    int uam, posicion;
    string tipo;
    Nodo *enlace;
};


#endif //ADMINISTRACION_DE_MEMORIA_NODO_H
