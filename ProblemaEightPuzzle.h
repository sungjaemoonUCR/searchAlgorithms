#ifndef EIGHTPUZZLE_PROBLEM
#define EIGHTPUZZLE_PROBLEM

#include "Problema.h"
#include "Lista.h"
#include "Estado.h"
#include "EstadoEightPuzzle.h"

class ProblemaEightPuzzle : public Problema {
   private:
    EstadoEightPuzzle *inicial;
    EstadoEightPuzzle *solucion;
   
   public:
      ProblemaEightPuzzle();
      ~ProblemaEightPuzzle();
      Estado * getEstadoInicial();
      int distancia(char **solucion, int inicial, int objetivo);
      int esSolucion( Estado * );
      int heuristica(Estado *);
      Lista * getSiguientes( Estado * );      
};
#endif
