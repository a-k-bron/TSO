//
// Created by Everardo Ramirez on 30/03/2017.
//

#ifndef ADMINISTRACION_DE_MEMORIA_NODO_H
#define ADMINISTRACION_DE_MEMORIA_NODO_H


class Nodo {
public:
    Nodo(char tipo, int posicion, int uam);

    Nodo(char tipo, int posicion, int uam, Nodo *n);

    int getUam() const;

    void setUam(int uam);

    int getPosicion() const;

    void setPosicion(int posicion);

    char getTipo() const;

    void setTipo(char tipo);

    Nodo *getEnlace() const;

    void setEnlace(Nodo *enlace);


protected:
    int uam, posicion;
    char tipo;
    Nodo *enlace;
};


#endif //ADMINISTRACION_DE_MEMORIA_NODO_H
