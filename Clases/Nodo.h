//
// Created by Everardo Ramirez on 30/03/2017.
//

#ifndef ADMINISTRACION_DE_MEMORIA_NODO_H
#define ADMINISTRACION_DE_MEMORIA_NODO_H

#include <string>


using namespace std;
class Nodo {
public:
    void toString();

    Nodo(int uam, int posicion, int id, int tamano, int residuo, const string &tipo, Nodo *enlace);

    Nodo(int uam, int posicion, int id, int tamano, int residuo, const string &tipo);

    int getUam() const;

    void setUam(int uam);

    int getPosicion() const;

    void setPosicion(int posicion);

    int getId() const;

    void setId(int id);

    int getTamano() const;

    void setTamano(int tamano);

    int getResiduo() const;

    void setResiduo(int residuo);

    const string &getTipo() const;

    void setTipo(const string &tipo);

    Nodo *getEnlace() const;

    void setEnlace(Nodo *enlace);


protected:
    int uam, posicion, id, tamano, residuo;
    string tipo;
    Nodo *enlace;
};


#endif //ADMINISTRACION_DE_MEMORIA_NODO_H
