//
// Created by Everardo Ramirez on 19/04/2017.
//

#ifndef ADMINISTRACION_DE_MEMORIA_SUPERLISTA_H
#define ADMINISTRACION_DE_MEMORIA_SUPERLISTA_H


#include "Lista.h"

class SuperLista {
private:
    int tamanoMemoria, tamanoUAM, contadorID;
    Nodo* testigoUltimo= nullptr;
public:
    int getContadorID() const;

    void setContadorID(int contadorID);

    void aumentarContadorID();

    bool lleno();

    int getTamanoMemoriaUAM();

    SuperLista(int tamanoMemoria, int tamanoUAM);

    Lista *l;

    int getTamanoMemoria() const;

    void setTamanoMemoria(int tamanoMemoria);

    int getTamanoUAM() const;

    void setTamanoUAM(int tamanoUAM);

    void crearLista();

    Nodo * getMayorHueco();

    void buscar();

    void terminarProceso(int id);

    void terminarProceso();

    void mejorAjuste(int tamano);

    void siguienteAjuste(int  tamano);

    void PrimerAjuste (int tamano);

    void peorAjuste(int tamano);

    void actualizarPosiciones();

};


#endif //ADMINISTRACION_DE_MEMORIA_SUPERLISTA_H
