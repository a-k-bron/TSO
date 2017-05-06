#include <iostream>
#include <cstdlib>
#include "Clases/Lista.h"
#include "Clases/SuperLista.h"

using namespace std;

/*proyecto de taller de sistemas operativos
 * Velazquez Machuca Eduardo Daniel (El hizo todo)
 * Ramirez Rosales Everardo (El no hizo nada)
 * Zuñiga Ramos Dulce Adelina (Ella chambeo, pa traer cocas)
 * Romero Vazquez Jorge Alberto (Lo llevo en mi corazon)
 *
 * */


int main() {
    int tamanoMemoria, tamanoUAM, opcion, procesoT, tamano;

    cout << "tamaño de la memoria" << endl;
    cin >> tamanoMemoria;
    cout << "tamaño de la uam";
    cin >> tamanoUAM;
    SuperLista *sl = new SuperLista(tamanoMemoria, tamanoUAM);
    sl->crearLista();

    cout << "La Lista:" << endl;
    sl->l->recorreLista();

    do {
        //system("cls");
        cout << "Procesos creados de forma satisfactoria" << endl;
        cout << "Introduce la opcion deseada, presiona otro numero para salir" << endl;
        cout << "1.- Mostrar Lista" << endl;
        cout << "2.- Terminar Procesos" << endl;
        cout << "Metodos de asignacion de memoria:" << endl;
        cout << "3.- Primet Ajuste" << endl;
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
                    cout << "Introduce el ID del proceso a terminar";
                    cin >> procesoT;
                    sl->terminarProceso(procesoT);
                    sl->l->recorreLista();
                } while (procesoT != -1);
                break;
            case 3:
                cout << "Introduce el tamaño del proceso:" << endl;
                cin >> tamano;
                sl->PrimerAjuste(tamano);
                break;
            case 4:
                cout << "Introduce el tamaño del proceso:" << endl;
                cin >> tamano;
                sl->siguienteAjuste(tamano);
                break;
            case 5:
                cout << "Introduce el tamaño del proceso:" << endl;
                cin >> tamano;
                sl->mejorAjuste(tamano);
                break;
            case 6:
                cout << "Introduce el tamaño del proceso:" << endl;
                cin >> tamano;
                sl->peorAjuste(tamano);
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
