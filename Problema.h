#ifndef EL_PROBLEMA
#define EL_PROBLEMA

#include "Producto.h"
#include "Estado.h"
#include "Lista.h"

class Problema : public Producto {      
   public:
      // Retorna el estado inicial del problema
      virtual Estado * getEstadoInicial()=0;

      // Verifica si el estado que recibe soluciona el problema
      // Retorna 0 ( false ) o 1 (true) 
      virtual int esSolucion( Estado * )=0;

      // Retorna un valor estimado optimista que sugiere
      // en cuantos pasos cree que de ese estado que recibe
      // puede llegar a la solucionar el problema
      // Si no pueden calcularla retorne 1
      virtual int heuristica(Estado *)=0;

      // El problema retorna los siguientes estados
      // a partir del estado que recibe
      // Hagan su Estado derivado amigo de su Problema derivado
      virtual Lista * getSiguientes( Estado * )=0;

};

#endif
