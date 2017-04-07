#include <iostream>
#include "Clases/Lista.h"

using namespace std;
/*proyecto de taller de sistemas operativos
 * Velazquez Machuca Eduardo Daniel (El hizo todo)
 * Ramirez Rosales Everardo (El no hizo nada)
 * Zuñiga Ramos Dulce Adelina (Ella chambeo, pa traer cocas)
 * Romero Vazquez Jorge Alberto (Lo llevo en mi corazon)
 * */
int main() {
    Lista *l = new Lista();
    cout << "inserta elementos a la lista" << endl;
    l->crearLista();
    cout<<"la lista"<<endl;
    l->recorreLista();
    return 0;
}