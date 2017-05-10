//
// Created by Everardo Ramirez on 19/04/2017.
//

#include <iostream>
#include "SuperLista.h"


int SuperLista::getTamanoMemoria() const {
    return tamanoMemoria;
}

int SuperLista::getTamanoUAM() const {
    return tamanoUAM;
}

SuperLista::SuperLista(int tamanoMemoria, int tamanoUAM) : tamanoMemoria(tamanoMemoria), tamanoUAM(tamanoUAM) {
    l = new Lista();
    l->insertarUltimo("h", 0, getTamanoMemoria() / getTamanoUAM(), -1, getTamanoMemoria(),
                      getTamanoMemoria() % getTamanoUAM());
    contadorID = 0;
}

void SuperLista::crearLista() {

    int tamano = 0;
    int calculoUAM, residuo;
    cout << "tamano del proceso: " << endl;
    cin >> tamano;
    while (tamano != -1 && !lleno()) {

        calculoUAM = tamano / getTamanoUAM();
        if (tamano % getTamanoUAM() > 0) {
            calculoUAM += 1;
            residuo = getTamanoUAM() - (tamano % getTamanoUAM());
        } else {
            residuo = 0;
        }
        if (getMayorHueco()->getUam() >= calculoUAM) {
            Nodo *p;
            int acumulado = 0;
            l->insertarInicio("p", 0, calculoUAM, contadorID, tamano, residuo);//tipo,posicion,uam,id,tamaño,residuo
            p = l->getPrimero();
            while (p != nullptr) {
                p->setPosicion(acumulado);
                acumulado += p->getUam();
                p = p->getEnlace();
            }
            l->ultimo()->setUam(l->ultimo()->getUam() - calculoUAM);
            l->ultimo()->setTamano(l->ultimo()->getTamano() - (calculoUAM * getTamanoUAM()));
            contadorID++;
        } else { cout << "falta espacio" << endl; }
        cin >> tamano;
    }

    if (l->ultimo()->getUam() == 0) {
        l->ultimo()->setTipo("eliminar");
        l->eliminar("eliminar");
    }
}

int SuperLista::getContadorID() const {
    return contadorID;
}

void SuperLista::terminarProceso(int id) {

    if (l->buscarPorID(id)) {
        l->buscarPorID(id)->setTipo("h");
        l->buscarPorID(id)->setTamano(l->buscarPorID(id)->getUam() * getTamanoUAM());
        l->buscarPorID(id)->setResiduo(0);//cambio el tipo a h
        l->buscarPorID(id)->setId(-1);
        terminarProceso();
        actualizarPosiciones();

    } else {
        cout << "el proceso " << id << " no existe" << endl;
    }


}

void SuperLista::terminarProceso() {
    int calculoUAM;
    Nodo *p = l->getPrimero();//proceso de verificacion de huecos juntos
    while (p != nullptr && p->getEnlace() != nullptr) {
        if (p->getTipo() == "h" && p->getEnlace()->getTipo() == "h") {
            p->setTamano(p->getTamano() + p->getEnlace()->getTamano());
            p->setResiduo(0);
            calculoUAM = p->getTamano() / getTamanoUAM();
            if (p->getTamano() % getTamanoUAM() > 0) {
                calculoUAM++;
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

bool SuperLista::lleno() {
    int contador = 0;
    Nodo *p = l->getPrimero();

    while (p != nullptr) {
        if (p->getTipo() == "p") {
            contador += p->getUam();
        }
        p = p->getEnlace();
    }
    return getTamanoMemoriaUAM() <= contador;

}

int SuperLista::getTamanoMemoriaUAM() {
    return getTamanoMemoria() / getTamanoUAM();
}

Nodo *SuperLista::getMayorHueco() {
    Nodo *p = l->getPrimero(), *mayorTemporal = nullptr;
    while (p != nullptr) {
        if (p->getTipo() == "h") {
            mayorTemporal = p;
            break;
        }
        p = p->getEnlace();
    }
    if (mayorTemporal == nullptr) { return nullptr; }
    p = l->getPrimero();
    while (p != nullptr) {
        if (p->getUam() > mayorTemporal->getUam() && p->getTipo() == "h") {
            mayorTemporal = p;
        }
        p = p->getEnlace();
    }

    return mayorTemporal;
}

void SuperLista::mejorAjuste(int tamano) {
    Nodo *p = l->getPrimero(), *masJusto = nullptr;       // obtener el primer nodo de la lista
    int calculoUAM, residuo;                    //
    calculoUAM = tamano / getTamanoUAM();
    if (tamano % getTamanoUAM() > 0) {
        calculoUAM += 1;
        residuo = getTamanoUAM() - (tamano % getTamanoUAM());
    } else {
        residuo = 0;
    }

    if (getMayorHueco() == nullptr || lleno() || getMayorHueco()->getUam() < calculoUAM) {
        cout << "sin espacio suficiente" << endl;
        return;
    }

    while (p != nullptr) {//encontrar el primer hueco
        if (p->getTipo() == "h" && p->getUam() >= calculoUAM) {
            masJusto = p;
            break;
        }
        p = p->getEnlace();
    }
    p = l->getPrimero();
    while (p != nullptr) {
        if (p->getTipo() == "h" && p->getUam() >= calculoUAM && p->getUam() < masJusto->getUam()) {//ajustar
            masJusto = p;
        }
        p = p->getEnlace();
    }
    if (masJusto == l->getPrimero()) {//si el mas justo es el primero
        l->insertarInicio("p", 0, calculoUAM, getContadorID(), tamano, residuo);
        aumentarContadorID();

    } else {
        p = l->getPrimero();
        while (p->getEnlace() != masJusto) {
            p = p->getEnlace();
        }

        l->insertarMedio("p", 0, calculoUAM, getContadorID(), tamano, residuo, p);
        aumentarContadorID();


    }
    masJusto->setUam(masJusto->getUam() - calculoUAM);
    masJusto->setTamano(masJusto->getUam() * tamanoUAM);
    masJusto->setResiduo(0);
    if (masJusto->getUam() == 0) {
        masJusto->setTipo("eliminar");
        l->eliminar("eliminar");
    }
    actualizarPosiciones();

}

void SuperLista::actualizarPosiciones() {
    Nodo *p;
    int acumulado = 0;
    p = l->getPrimero();
    while (p != nullptr) {
        p->setPosicion(acumulado);
        acumulado += p->getUam();
        p = p->getEnlace();
    }

}

void SuperLista::siguienteAjuste(int tamano) {
    int calculoUAM, residuo;
    Nodo *p;
    Nodo *aux;

    calculoUAM = tamano / getTamanoUAM();
    if (tamano % getTamanoUAM() > 0) {
        calculoUAM += 1;
        residuo = getTamanoUAM() - (tamano % getTamanoUAM());
    } else {
        residuo = 0;
    }

    if (getMayorHueco() == nullptr || getMayorHueco()->getUam() < calculoUAM) {
        cout << "sin espacio suficiente" << endl;
        return;
    }

    if (testigoUltimo == nullptr) {
        p = l->getPrimero();
        while (p != nullptr) {
            if (p->getTipo() == "h" && p->getUam() >= calculoUAM) {
                break;
            } else {
                p = p->getEnlace();
            }
        }

    } else {
        bool segundaVuelta = false;
        p = testigoUltimo;
        while (p != nullptr or !segundaVuelta) {
            if (p == nullptr) {
                p = l->getPrimero();
                segundaVuelta = true;
            }
            if (p->getTipo() == "h" && p->getUam() >= calculoUAM) {
                break;
            } else {
                p = p->getEnlace();
            }

        }


    }
    if (p == l->getPrimero()) {
        l->insertarInicio("p", 0, calculoUAM, getContadorID(), tamano, residuo);
        aumentarContadorID();
    } else {
        aux = l->getPrimero();

        while (aux->getEnlace() != p) {
            aux = aux->getEnlace();
        }
        l->insertarMedio("p", 0, calculoUAM, getContadorID(), tamano, residuo, aux);
        aumentarContadorID();
        testigoUltimo = aux->getEnlace();
    }

    p->setUam(p->getUam() - calculoUAM);
    p->setTamano(p->getUam() * tamanoUAM);
    p->setResiduo(0);

    if (p->getUam() == 0) {
        p->setTipo("eliminar");
        l->eliminar("eliminar");
    }
    actualizarPosiciones();
}

void SuperLista::PrimerAjuste(int tamano) {
    int calculoUAM, residuo;
    Nodo *p;
    Nodo *aux;

    calculoUAM = tamano / getTamanoUAM();
    if (tamano % getTamanoUAM() > 0) {
        calculoUAM += 1;
        residuo = getTamanoUAM() - (tamano % getTamanoUAM());
    } else {
        residuo = 0;
    }

    if (getMayorHueco() == nullptr || getMayorHueco()->getUam() < calculoUAM) {
        cout << "sin espacio suficiente" << endl;
        return;
    }


    p = l->getPrimero();
    while (p != nullptr) {
        if (p->getTipo() == "h" && p->getUam() >= calculoUAM) {
            break;
        } else {
            p = p->getEnlace();
        }
    }


    if (p == l->getPrimero()) {
        l->insertarInicio("p", 0, calculoUAM, getContadorID(), tamano, residuo);
        aumentarContadorID();
    } else {
        aux = l->getPrimero();

        while (aux->getEnlace() != p) {
            aux = aux->getEnlace();
        }
        l->insertarMedio("p", 0, calculoUAM, getContadorID(), tamano, residuo, aux);
        aumentarContadorID();
    }


    p->setUam(p->getUam() - calculoUAM);
    p->setTamano(p->getUam() * tamanoUAM);
    p->setResiduo(0);

    if (p->getUam() == 0) {
        p->setTipo("eliminar");
        l->eliminar("eliminar");
    }
    actualizarPosiciones();

}

void SuperLista::peorAjuste(int tamano) {

    Nodo *p, *menosJusto;       // obtener el primer nodo de la lista
    int calculoUAM, residuo;                    //
    calculoUAM = tamano / getTamanoUAM();
    if (tamano % getTamanoUAM() > 0) {
        calculoUAM += 1;
        residuo = getTamanoUAM() - (tamano % getTamanoUAM());
    } else {
        residuo = 0;
    }

    if (getMayorHueco() == nullptr || lleno() || getMayorHueco()->getUam() < calculoUAM) {
        cout << "sin espacio suficiente" << endl;
        return;
    }
    menosJusto = getMayorHueco();

    if (menosJusto == l->getPrimero()) {//si el menoss justo es el primero
        l->insertarInicio("p", 0, calculoUAM, getContadorID(), tamano, residuo);
        aumentarContadorID();

    } else {
        p = l->getPrimero();
        while (p->getEnlace() != menosJusto) {
            p = p->getEnlace();
        }

        l->insertarMedio("p", 0, calculoUAM, getContadorID(), tamano, residuo, p);
        aumentarContadorID();
    }
    menosJusto->setUam(menosJusto->getUam() - calculoUAM);
    menosJusto->setTamano(menosJusto->getUam() * tamanoUAM);
    menosJusto->setResiduo(0);
    if (menosJusto->getUam() == 0) {
        menosJusto->setTipo("eliminar");
        l->eliminar("eliminar");
    }
    actualizarPosiciones();
}
