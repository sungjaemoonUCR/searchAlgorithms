#ifndef SOLUCIONADOR_IDA
#define SOLUCIONADOR_IDA
#include "Solucionador.h"
#include <iostream>
#include <list>
#include <iterator>

using namespace std;

class Nodo{
    Nodo * padre;
};
class SolucionadorIDA : public Solucionador {
   private:
    int profundidad;

   public:
      SolucionadorIDA();
      Solucion * solucione(Problema *);
      Solucion * solucioneRec(Problema *);
};


#endif
