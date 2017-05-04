#include <iostream>
#include "Clases/Lista.h"
#include "Clases/SuperLista.h"

using namespace std;
/*proyecto de taller de sistemas operativos
 * Velazquez Machuca Eduardo Daniel (El hizo todo)
 * Ramirez Rosales Everardo (El no hizo nada)
 * Zuñiga Ramos Dulce Adelina (Ella chambeo, pa traer cocas)
 * Romero Vazquez Jorge Alberto (Lo llevo en mi corazon)
 * */
int main() {
    int tamanoMemoria,tamanoUAM, procesoT;

    cout<<"tamaño de la memoria"<<endl;
    cin>>tamanoMemoria;
    cout<<"tamaño de la uam";
    cin>>tamanoUAM;
    SuperLista *sl = new SuperLista(tamanoMemoria,tamanoUAM);
    sl->crearLista();


    cout<<"la lista"<<endl;
    sl->l->recorreLista();

    do{
        cout<<"proceso a terminar";
        cin>>procesoT;
        sl->terminarProceso(procesoT);
        sl->l->recorreLista();
    }while (procesoT!=-1);

    do{
        cout<<"tamano proceso";
        cin>>procesoT;
        sl->mejorAjuste(procesoT);
        sl->l->recorreLista();
    }while (procesoT!=-1);



    return 0;
}