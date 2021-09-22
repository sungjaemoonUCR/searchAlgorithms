/**
 * Clase Problem051  
 * 
 * @author Nazareth Rojas 
 * @version 11-07-2021
 */

#ifndef _NAZA_PROBLEM
#define _NAZA_PROBLEM

#include <stdlib.h>
#include<iostream>
using namespace std;

#include "Problema.h"
#include "Lista.h"
#include "Estado.h"
#include "NazaEstado.h"

class Problem051 : public Problema {
   private:
      NazaEstado *inicial;
      NazaEstado *solucion; //el estado final
     

   public:
      Problem051();
      ~Problem051();
      Estado * getEstadoInicial(); 
      int esSolucion( Estado * ); 
      int heuristica(Estado *); 
      Lista * getSiguientes( Estado * );

};
#endif