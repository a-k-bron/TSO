#include <iostream>
#include "Clases/Lista.h"

using namespace std;
/*proyecto de taller de sistemas operativos*/
int main() {
    Lista *l = new Lista();
    cout << "inserta elementos a la lista" << endl;
    l->crearLista();
    cout<<"la lista"<<endl;
    l->recorreLista();
    return 0;
}