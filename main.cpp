#include <iostream>
#include <cstdlib>
#include "Clases/Lista.h"
#include "Clases/SuperLista.h"

using namespace std;

int main() {
    int tamanoMemoria, tamanoUAM, opcion, procesoT, tamano;

    cout << "tamano de la memoria: ";
    cin >> tamanoMemoria;
    cout << "tamano de la uam: ";
    cin >> tamanoUAM;
    SuperLista *sl = new SuperLista(tamanoMemoria, tamanoUAM);
    cout << "****    Para terminal la creacion de la lista    ****" << endl
         << "**** y todos los demas procedimientos escriba -1 ****" << endl;
    sl->crearLista();
    cout << "Procesos creados de forma satisfactoria" << endl;
    cout << "La Lista:" << endl;

    sl->l->recorreLista();

    do {
        cout << "Introduce la opcion deseada, presiona otro numero para salir" << endl;
        cout << "1.- Mostrar Lista" << endl;
        cout << "2.- Terminar Procesos" << endl;
        cout << "**** Metodos de asignacion de memoria ****" << endl;
        cout << "3.- Primer Ajuste" << endl;
        cout << "4.- Siguiente Ajuste" << endl;
        cout << "5.- Mejor Ajuste" << endl;
        cout << "6.- Peor Ajuste" << endl;
        cin >> opcion;

        switch (opcion) {
            case 1:
                cout << "La Lista:" << endl;
                sl->l->recorreLista();
                break;
            case 2:
                do {
                    cout << "Introduce el ID del proceso a terminar: ";
                    cin >> procesoT;
                    sl->terminarProceso(procesoT);
                    sl->l->recorreLista();
                } while (procesoT != -1);
                break;
            case 3:
                do {
                    cout << "Introduce el tamano del proceso:" << endl;
                    cin >> tamano;
                    if(tamano==-1){ break;}
                    sl->PrimerAjuste(tamano);
                } while (tamano != -1);
                break;
            case 4:
                do {
                    cout << "Introduce el tamaño del proceso:" << endl;
                    cin >> tamano;
                    if(tamano==-1){ break;}
                    sl->siguienteAjuste(tamano);
                } while (tamano != -1);
                break;
            case 5:
                do {
                    cout << "Introduce el tamaño del proceso:" << endl;
                    cin >> tamano;
                    if(tamano==-1){ break;}
                    sl->mejorAjuste(tamano);
                } while (tamano != -1);
                break;
            case 6:
                do {
                    cout << "Introduce el tamaño del proceso:" << endl;
                    cin >> tamano;
                    if(tamano==-1){ break;}
                    sl->peorAjuste(tamano);
                } while (tamano != -1);
                break;
        }

    } while ((opcion < 7) & (opcion > 0));

}



/*do {
    cout << "tamano proceso";
    cin >> procesoT;
    //sl->mejorAjuste(procesoT);
    sl->siguienteAjuste(procesoT);
    sl->l->recorreLista();
} while (procesoT != -1);*/
