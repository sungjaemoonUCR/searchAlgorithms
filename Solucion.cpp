#include "Lista.h"
#include "Solucion.h"

Solucion::Solucion(Lista * listaPtr){
   this->lista= listaPtr;
}

Solucion::~Solucion(){
   if(lista){
      delete lista;
   }
}

