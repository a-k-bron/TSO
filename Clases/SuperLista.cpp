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
    contadorID = 0;//Genera lista y mete el primero, el cual es el hueco de toda la memoria
}

void SuperLista::crearLista() {

    int tamano = 0;
    int calculoUAM, residuo;
    cout << "tamano del proceso" << endl;
    cin >> tamano;
    while (tamano != -1 && !lleno()) {

        calculoUAM = tamano / getTamanoUAM();//obtiene cuantas uams necesita el proceso
        if (tamano % getTamanoUAM() > 0) {
            calculoUAM += 1;//si hay residuo, se le otorga otra uam
            residuo = getTamanoUAM() - (tamano % getTamanoUAM());//muestra el residuo no usado de la uam
        } else {
            residuo = 0;//en caso contrario no hubo residuo
        }
        if (getMayorHueco()->getUam() >= calculoUAM) {
            l->insertarInicio("p", 0, calculoUAM, contadorID, tamano, residuo);//tipo,posicion,uam,id,tamaño,residuo
            actualizarPosiciones();
            l->ultimo()->setUam(l->ultimo()->getUam() - calculoUAM);//obtiene el ultimo nodo que representa la memoria libre, actualiza las uam restando las aum que habia menos el tamaño del nuevo proceso
            l->ultimo()->setTamano(l->ultimo()->getTamano() - (calculoUAM * getTamanoUAM()));//hace lo mismo que el anterior pero usando el tamaño de la memoria (bytes)
            contadorID++;
        } else { cout << "falta espacio" << endl; }//cuando no cabe
        cin >> tamano;
    }

    if (l->ultimo()->getUam() == 0) {//si el ultimo hueco tiene 0 uam, se convierte el nodo en el tipo eliminar.
        l->ultimo()->setTipo("eliminar");//cambia el nombre del ultimo proceso a "eliminar" y elimina los tipos "eliminar"
        l->eliminar("eliminar");
    }
}

int SuperLista::getContadorID() const {
    return contadorID;
}

void SuperLista::setContadorID(int contadorID) {
    SuperLista::contadorID = contadorID;
}

void SuperLista::terminarProceso(int id) {
    Nodo *p = l->getPrimero(); //puntero que apunta al primer nodo
    int acumulado = 0;
    if (l->buscarPorID(id)) {//busco que exista el proceso
        l->buscarPorID(id)->setTipo("h");//cambio el tipo a h
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
            p->setTamano(p->getTamano() + p->getEnlace()->getTamano());//el tamaño del hueco es igual al nodo actual mas el nodo que sigue
            calculoUAM = p->getTamano() / getTamanoUAM();//saca el tamaño en uams
            if (p->getTamano() % getTamanoUAM() > 0) {
                calculoUAM += 1;
                p->setResiduo(getTamanoUAM() - (p->getTamano() % getTamanoUAM()));
            } else {
                p->setResiduo(0);
            }
            p->setUam(calculoUAM); //deja el tamaño de uam a ese hueco
            p->getEnlace()->setTipo("eliminar");
            l->eliminar("eliminar");
            terminarProceso();// se llama recursivamente para evitar que si hay tres huecos, solo se unan 2 y garantizar que la funcion se realice hasta que se cumpla el while
            //if (p == l->ultimo()) { break; }
        }

        p = p->getEnlace();
    }
}

void SuperLista::aumentarContadorID() {
    contadorID++;
}

bool SuperLista::lleno() {//obtiene las uams de los procesos y si la uam obtenida es igual a la memoria total, esta lleno
    int contador = 0;
    Nodo *p = l->getPrimero();

    while (p != nullptr) {
        if (p->getTipo() == "p") {
            contador += p->getUam();
        }
        p = p->getEnlace();
    }
    if (getTamanoMemoriaUAM() <= contador) { return true; }
    else { return false; }

}

int SuperLista::getTamanoMemoriaUAM() {//regresa el tamaño de la memoria en UAM
    return getTamanoMemoria() / getTamanoUAM();
}

Nodo *SuperLista::getMayorHueco() {
    Nodo *p = l->getPrimero(), *mayorTemporal=nullptr;
    while (p != nullptr) {//se usa el while hasta obtener el primer hueco
        if (p->getTipo() == "h") {
            mayorTemporal = p;
            break;
        }
        p = p->getEnlace();//en caso de no encontrar hueco pasa al siguiente enlace
    }
    p = l->getPrimero();//volvemos a poner p a primero
    while (p != nullptr) {
        if (p->getUam() > mayorTemporal->getUam() && p->getTipo() == "h") {
            mayorTemporal = p; //se realiza la busqueda utilizando como referencia el primer hueco, si este es mayor ahora ese es el mayor temporal
        }
        p = p->getEnlace();//se busca ahora con el siguiente enlace hasta llegar al final de la lista y encontrar el mayor
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

    if (getMayorHueco()->getUam() < calculoUAM) {
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

void SuperLista::peorAjuste(int tamano) {

    Nodo *p = l->getPrimero(), *menosJusto;       // obtener el primer nodo de la lista
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
    menosJusto = getMayorHueco();

    if (menosJusto == l->getPrimero()) {//si el menoss justo es el primero
        l->insertarInicio("p", 0, calculoUAM, getContadorID(), tamano, residuo);
        aumentarContadorID();
        menosJusto->setTamano(menosJusto->getTamano() - tamano);
        calculoUAM = menosJusto->getTamano() / getTamanoUAM();
        if (menosJusto->getTamano() % getTamanoUAM() > 0) {
            calculoUAM += 1;
            residuo = getTamanoUAM() - (menosJusto->getTamano() % getTamanoUAM());
        } else {
            residuo = 0;
        }
        menosJusto->setUam(calculoUAM);
        menosJusto->setResiduo(residuo);
        if (menosJusto->getUam() == 0) {
            menosJusto->setTipo("eliminar");
            l->eliminar("eliminar");
        }
    } else {
        p = l->getPrimero();
        while (p->getEnlace() != menosJusto) {
            p = p->getEnlace();
        }

        l->insertarMedio("p", 0, calculoUAM, getContadorID(), tamano, residuo, p);
        aumentarContadorID();
        menosJusto->setTamano(menosJusto->getTamano() - tamano);
        calculoUAM = menosJusto->getTamano() / getTamanoUAM();
        if (menosJusto->getTamano() % getTamanoUAM() > 0) {
            calculoUAM += 1;
            residuo = getTamanoUAM() - (menosJusto->getTamano() % getTamanoUAM());
        } else {
            residuo = 0;
        }
        menosJusto->setUam(calculoUAM);
        menosJusto->setResiduo(residuo);
        if (menosJusto->getUam() == 0) {
            menosJusto->setTipo("eliminar");
            l->eliminar("eliminar");
        }

    }
    actualizarPosiciones();


}
