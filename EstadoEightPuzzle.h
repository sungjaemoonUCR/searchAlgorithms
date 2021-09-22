#ifndef _ESTADO_EIGHT_PUZZLE
#define _ESTADO_EIGHT_PUZZLE

//#include "ProblemaEightPuzzle.h"
#include "Estado.h"

class EstadoEightPuzzle : public Estado {
   friend class ProblemaEightPuzzle;
  
  /*
  friend ostream& operator<<(ostream& salida, EstadoEightPuzzle & prueba){
       return prueba.imprimir(salida);
   }
  */

   private:
      char** m;
	    int n;

   public:
      EstadoEightPuzzle();
      ~EstadoEightPuzzle();
      EstadoEightPuzzle * clonar();
      istream& cargar(istream&);
      ostream& imprimir(ostream&);
      int operator==(Estado *);
      int operator!=(Estado *);
      void pedirMemoria(int);
      void liberarMemoria();
      void llenar();
      void llenarAleatorio();
};


#endif