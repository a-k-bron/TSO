//
// Created by Everardo Ramirez on 19/04/2017.
//

#include <iostream>
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
    contadorID = 0;
}

void SuperLista::crearLista() {

    int tamano = 0;
    int calculoUAM, residuo;
    Nodo *p;
    cout << "tamano del proceso" << endl;
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

void SuperLista::setContadorID(int contadorID) {
    SuperLista::contadorID = contadorID;
}

void SuperLista::buscar() {
    int aux;
    cout << "numero con que buscar: ";
    cin >> aux;
    l->buscarPorID(aux)->toString();

}

void SuperLista::terminarProceso(int id) {
    Nodo *p = l->getPrimero();
    int acumulado = 0;
    if (l->buscarPorID(id)) {
        l->buscarPorID(id)->setTipo("h");//cambio el tipo a h
        l->buscarPorID(id)->setId(-1);
        terminarProceso();

        while (p != nullptr) {
            p->setPosicion(acumulado);
            acumulado += p->getUam();
            p = p->getEnlace();
        }
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
            calculoUAM = p->getTamano() / getTamanoUAM();
            if (p->getTamano() % getTamanoUAM() > 0) {
                calculoUAM += 1;
                p->setResiduo(getTamanoUAM() - (p->getTamano() % getTamanoUAM()));
            } else {
                p->setResiduo(0);
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
    if (getTamanoMemoriaUAM() == contador) { return true; }
    else { return false; }

}

int SuperLista::getTamanoMemoriaUAM() {
    return getTamanoMemoria() / getTamanoUAM();
}

Nodo *SuperLista::getMayorHueco() {
    Nodo *p = l->getPrimero(), *mayorTemporal;
    while (p != nullptr) {
        if (p->getTipo() == "h") {
            mayorTemporal = p;
            break;
        }
        p = p->getEnlace();
    }
    p = l->getPrimero();
    while (p != nullptr) {
        if (p->getUam() > mayorTemporal->getUam()) {
            mayorTemporal = p;
        }
        p = p->getEnlace();
    }

    return mayorTemporal;
}

void SuperLista::mejorAjuste(int tamano) {
    Nodo *p = l->getPrimero(), *masJusto;       // obtener el primer nodo de la lista
    int calculoUAM, residuo;                    //
    calculoUAM = tamano / getTamanoUAM();
    if (tamano % getTamanoUAM() > 0) {
        calculoUAM += 1;
        residuo = getTamanoUAM() - (tamano % getTamanoUAM());
    } else {
        residuo = 0;
    }

    if (lleno() || getMayorHueco()->getUam() < calculoUAM) {
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
        masJusto->setTamano(masJusto->getTamano() - tamano);
        calculoUAM = masJusto->getTamano() / getTamanoUAM();
        if (masJusto->getTamano() % getTamanoUAM() > 0) {
            calculoUAM += 1;
            residuo = getTamanoUAM() - (masJusto->getTamano() % getTamanoUAM());
        } else {
            residuo = 0;
        }
        masJusto->setUam(calculoUAM);
        masJusto->setResiduo(residuo);
        if (masJusto->getUam() == 0) {
            masJusto->setTipo("eliminar");
            l->eliminar("eliminar");
        }
    } else {
        p = l->getPrimero();
        while (p->getEnlace() != masJusto) {
            p = p->getEnlace();
        }

        l->insertarMedio("p", 0, calculoUAM, getContadorID(), tamano, residuo, p);
        aumentarContadorID();
        masJusto->setTamano(masJusto->getTamano() - tamano);
        calculoUAM = masJusto->getTamano() / getTamanoUAM();
        if (masJusto->getTamano() % getTamanoUAM() > 0) {
            calculoUAM += 1;
            residuo = getTamanoUAM() - (masJusto->getTamano() % getTamanoUAM());
        } else {
            residuo = 0;
        }
        masJusto->setUam(calculoUAM);
        masJusto->setResiduo(residuo);
        if (masJusto->getUam() == 0) {
            masJusto->setTipo("eliminar");
            l->eliminar("eliminar");
        }

    }
    //l->insertarMedio("p", 0, calculoUAM, getContadorID(), tamano, residuo); }
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

    if (getMayorHueco()->getUam() < calculoUAM) {
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
        bool segundaVuelta=false;
        p=testigoUltimo;
        while(p!= nullptr or !segundaVuelta){
            if(p== nullptr){
                p=l->getPrimero();
                segundaVuelta=true;
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
    p->setTamano(p->getTamano() - tamano);
    calculoUAM = p->getTamano() / getTamanoUAM();
    if (p->getTamano() % getTamanoUAM() > 0) {
        calculoUAM += 1;
        residuo = getTamanoUAM() - (p->getTamano() % getTamanoUAM());
    } else {
        residuo = 0;
    }

    p->setUam(calculoUAM);
    p->setResiduo(residuo);

    if (p->getUam() == 0) {
        p->setTipo("eliminar");
        l->eliminar("eliminar");
    }
    actualizarPosiciones();
}

void SuperLista::PrimerAjuste (int tamano){
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

    if (getMayorHueco()->getUam() < calculoUAM) {
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
    p->setTamano(p->getTamano() - tamano);
    calculoUAM = p->getTamano() / getTamanoUAM();
    if (p->getTamano() % getTamanoUAM() > 0) {
        calculoUAM += 1;
        residuo = getTamanoUAM() - (p->getTamano() % getTamanoUAM());
    } else {
        residuo = 0;
    }

    p->setUam(calculoUAM);
    p->setResiduo(residuo);

    if (p->getUam() == 0) {
        p->setTipo("eliminar");
        l->eliminar("eliminar");
    }
    actualizarPosiciones();

}
