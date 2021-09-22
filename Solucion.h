#ifndef LA_SOLUCION
#define LA_SOLUCION
#include <iostream>
using namespace std;

class Solucion {
    friend ostream& operator<<(ostream& salida , Solucion * solucion){
        return salida << solucion->lista << endl;
    }
    private:
       Lista * lista;
    public:
       Solucion(Lista *);
       ~Solucion();
};

#endif

