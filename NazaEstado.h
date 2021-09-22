/**
 * Clase NazaEstado permite crear estados de tipo NazaEstado
 * 
 * @author Nazareth Rojas 
 * @version 11-07-2021
 */

#ifndef _NAZA_ESTADO
#define _NAZA_ESTADO
#include <stdlib.h>
#include <time.h>
#include "Estado.h"

class NazaEstado : public Estado {
  friend class Problem051;

   private:
      char **m;
      int n;
      int rFila; //para almacenar fila del refugio
      int rCol; //almacena columna del refugio
      int murciFila; //almacena fila del murci
      int murciCol; //almacena columna del murci
	
   public:
      NazaEstado();
      NazaEstado(int); 
      NazaEstado * clonar();
      ~NazaEstado();
      istream& cargar(istream&);
      ostream& imprimir(ostream&);
      int operator==(Estado *);
      int operator!=(Estado *);

      void pedirMemoria(int);
      void liberarMemoria();
      void llenarVacia();
      int verificarVecinos(int, int);
      void ponerObstaculos();
      void ponerMurciRefugio();

};
#endif