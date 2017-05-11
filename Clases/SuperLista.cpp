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
    l = new Lista();//l es la nueva lista
    l->insertarUltimo("h", 0, getTamanoMemoria() / getTamanoUAM(), -1, getTamanoMemoria(),
                      getTamanoMemoria() % getTamanoUAM());// crea un hueco del tamaño de la memoria
    contadorID = 0;
}

void SuperLista::crearLista() {

    int tamano = 0;
    int calculoUAM, residuo;
    cout << "tamano del proceso: " << endl;
    cin >> tamano;
    while (tamano != -1 && !lleno()) {// inserta procesos hasta que el usuario ingrese -1 o este lleno

        calculoUAM = tamano / getTamanoUAM();//se calcula la cantidad de uams dividiendo tamaño entre uam dada por el usuario
        if (tamano % getTamanoUAM() > 0) {// verifica si existe residuo
            calculoUAM += 1;// si existe toma una uam extra
            residuo = getTamanoUAM() - (tamano % getTamanoUAM());// asigna el residuo
        } else {
            residuo = 0;// si no hay residuo pone el residuo a 0 del proceso
        }
        if (getMayorHueco()->getUam() >= calculoUAM) {//calcula que el tamaño de uams del proceso sea menor al del mayor hueco, es decir, que quepa.
            Nodo *p;
            int acumulado = 0;
            l->insertarInicio("p", 0, calculoUAM, contadorID, tamano, residuo);//tipo,posicion,uam,id,tamaño,residuo
            p = l->getPrimero();
            while (p != nullptr) {
                p->setPosicion(acumulado);
                acumulado += p->getUam();
                p = p->getEnlace();
            }
            l->ultimo()->setUam(l->ultimo()->getUam() - calculoUAM);//actualiza las uam del hueco
            l->ultimo()->setTamano(l->ultimo()->getTamano() - (calculoUAM * getTamanoUAM()));//actualiza el tamaño del hueco
            contadorID++;
        } else { cout << "falta espacio" << endl; }
        cin >> tamano;
    }

    if (l->ultimo()->getUam() == 0) {// si el hueco se hace 0, elimina ese nodo
        l->ultimo()->setTipo("eliminar");
        l->eliminar("eliminar");
    }
}

int SuperLista::getContadorID() const {// retorna el id del proceso
    return contadorID;
}

void SuperLista::terminarProceso(int id) {

    if (l->buscarPorID(id)) {// verifica que el id del proceso existe
        l->buscarPorID(id)->setTipo("h");// le da tipo h al proceso
        l->buscarPorID(id)->setTamano(l->buscarPorID(id)->getUam() * getTamanoUAM());//obtiene tamaño y uam
        l->buscarPorID(id)->setResiduo(0);//pone el residuo a 0
        l->buscarPorID(id)->setId(-1);// cambia el id a -1
        terminarProceso();
        actualizarPosiciones();

    } else {
        cout << "el proceso " << id << " no existe" << endl;// si no lo encuentra
    }


}

void SuperLista::terminarProceso() {
    int calculoUAM;
    Nodo *p = l->getPrimero();//da a p el primer elemento de la lista
    while (p != nullptr && p->getEnlace() != nullptr) {//verifica que este dentro de la lista
        if (p->getTipo() == "h" && p->getEnlace()->getTipo() == "h") {// Si hay dos huecos seguidos
            p->setTamano(p->getTamano() + p->getEnlace()->getTamano());//obtiene el tamaño de los dos huecos
            p->setResiduo(0);// pone el residuo a 0
            calculoUAM = p->getTamano() / getTamanoUAM();//calcula las uam
            if (p->getTamano() % getTamanoUAM() > 0) {// da una uam extra si es que hay residuo
                calculoUAM++;
            }
            p->setUam(calculoUAM);
            p->getEnlace()->setTipo("eliminar");//como guardo todo en p, el siguiente enlace que es hueco se poner de tipo eliminar para eliminarlo
            l->eliminar("eliminar");
            terminarProceso();// se llama a si mismo recursivamente para evitar que haya un 3er hueco junto
            //if (p == l->ultimo()) { break; }
        }

        p = p->getEnlace();// obtiene el siguiente enlace y se lod a a p, actualizacion para la recursividad
    }
}

void SuperLista::aumentarContadorID() {
    contadorID++;// aumenta el contador en 1 para cada proceso
}

bool SuperLista::lleno() {
    int contador = 0;
    Nodo *p = l->getPrimero();

    while (p != nullptr) {// verifica que este dentro de la lista
        if (p->getTipo() == "p") {// verifica que p sea de tipo proceso
            contador += p->getUam();//obtiene y suma las uam de ese proceso
        }
        p = p->getEnlace();// obtiene siguiente nodo
    }
    return getTamanoMemoriaUAM() <= contador;// retorna como booleano

}

int SuperLista::getTamanoMemoriaUAM() {// obtiene el tamaño total de uams
    return getTamanoMemoria() / getTamanoUAM();
}

Nodo *SuperLista::getMayorHueco() {
    Nodo *p = l->getPrimero(), *mayorTemporal = nullptr;
    while (p != nullptr) {
        if (p->getTipo() == "h") {//obtiene el primer hueco y lo asigna a mayor temporal
            mayorTemporal = p;
            break;
        }
        p = p->getEnlace();//busca hasta obtener un nodo tipo h
    }
    if (mayorTemporal == nullptr) { return nullptr; }// si el mayor quedo como nulo significa que no hay hueco
    p = l->getPrimero();//obtiene el primer nodo
    while (p != nullptr) {
        if (p->getUam() > mayorTemporal->getUam() && p->getTipo() == "h") {//si las uams de p son mayores al mayor temporal y es de tipo hueco
            mayorTemporal = p;//asigna a valor temporar ese nodo
        }
        p = p->getEnlace();//actualiza al siguiente nodo
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
