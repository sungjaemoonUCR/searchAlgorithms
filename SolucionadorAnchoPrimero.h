#ifndef SOLUCIONADOR_ANCHO_PRIMERO
#define SOLUCIONADOR_ANCHO_PRIMERO
#include "Solucionador.h"
#include <iostream>
#include <list>
#include <iterator>

using namespace std;

class Nodo {
public:
    Estado * estado;
    Nodo * padre;
};

class SolucionadorAnchoPrimero : public Solucionador {
   private:
      Lista * frontera; //agregado para sol Naza
      Lista * visitados; //agregado para sol Naza
      Lista * pasos; //agregado para sol Naza
      list <Nodo*> frontNodos;
      Nodo * cpadre;
      Nodo * f;
      Solucion * solucion; //agregado para sol Naza


   public:
      SolucionadorAnchoPrimero();
      Solucion * solucione(Problema *);
      Lista * revertPasos();
      void revertirSolucion(Nodo * final);
      void asignarPadre(Nodo* padre);
      void agregarAFrontera(Lista * siguientes); //agregado para sol Naza
      int comprobarSiSolucion(Problema * problema); //agregado para sol Naza
      void expandir(Problema* problema); //agregado para sol Naza
      Solucion * retornarSolucion();
};

#endif
