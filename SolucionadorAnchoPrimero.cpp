///a.out 8Puzzle Solucionador8Puzzle

#include "SolucionadorAnchoPrimero.h"
#include "Estado.h"
#include "Solucion.h"
#include "Lista.h"
#include "Problema.h"
#include <bits/stdc++.h>

using namespace std;

SolucionadorAnchoPrimero::SolucionadorAnchoPrimero(){
  frontera = new Lista();
  visitados = new Lista();
  pasos = new Lista();
  solucion = 0;

}

Lista * SolucionadorAnchoPrimero::revertPasos(){
  Lista* ordenDePaso = new Lista(); //pasos
  Nodo* temp = f->padre;
  ordenDePaso->push_front(f->estado);
  while(temp != NULL){
    ordenDePaso->push_front(temp->estado);
    temp = temp->padre;
  }
  return ordenDePaso;
}

Solucion * SolucionadorAnchoPrimero::solucione( Problema * problema){
	Lista* siguientes;
	int resuelto = 0;

  Estado* estado = problema->getEstadoInicial();
  Nodo * raiz = new Nodo();
  raiz->estado = estado;
  raiz->padre = NULL;
  cpadre = raiz;
	resuelto = problema->esSolucion(estado);
	pasos->push_back(estado);

	if (resuelto == 0) {
    visitados->push_back(estado);
		frontera = problema->getSiguientes(estado);
    Lista::Iterador i = frontera->begin();
	  Lista::Iterador fin = frontera->end();
	  for(i; i != fin; ++i){
      Nodo * nuevo = new Nodo();
      nuevo->estado = *i;
      nuevo->padre = raiz;
      frontNodos.push_back(nuevo);
    }

    resuelto= comprobarSiSolucion(problema);

    if (resuelto == 0){

      while(resuelto != 1){//|| !(frontera->isEmpty())
        expandir(problema);
        resuelto = comprobarSiSolucion(problema);///////aca devuelve resuelto 1 o 0
        if(frontera->isEmpty()){
          break;
        }
      }
    }
	solucion = retornarSolucion();
	}
	return solucion;
}

Solucion * SolucionadorAnchoPrimero::retornarSolucion(){
  Lista * pfinal = revertPasos();
  solucion = new Solucion(pfinal);
  return solucion;
}

void SolucionadorAnchoPrimero::agregarAFrontera(Lista * siguientes){
	Lista::Iterador inicio = siguientes->begin();
	while(!siguientes->isEmpty()){//for(inicio; inicio != fin; ++inicio){
    
    if((visitados->esta(*inicio) == 0) && (frontera->esta(*inicio) == 0)){
      ++inicio;
      Estado * a = siguientes->pop_front();
			frontera->push_back(a);//frontera->push_back(*inicio);
      Nodo * nodoN = new Nodo();
      nodoN->estado = a;
      nodoN->padre = cpadre;
      frontNodos.push_back(nodoN);
		}
		else{
      ++inicio;
			siguientes->pop_front();
		}
	}
}

int SolucionadorAnchoPrimero::comprobarSiSolucion(Problema* problema){
	int resuelto = 0;
	Lista::Iterador i = frontera->begin();
	Lista::Iterador fin = frontera->end();
  list<Nodo *>::iterator j = frontNodos.begin();
	for(i; i != fin; ++i, ++j){
		resuelto = problema->esSolucion(*i);
		if(resuelto == 1){
      f = *j;
			break;
		}
		else{
			visitados->push_back(*i);
		}
	}
	return resuelto;
}

void SolucionadorAnchoPrimero::expandir(Problema* problema){
	Lista * auxiliar1 = new Lista(*frontera);
  Lista * auxiliar2 = new Lista();
  while(!frontera->isEmpty()){
    frontera->pop_back();
    frontNodos.pop_back();
  }

	Lista::Iterador i = auxiliar1->begin();
	Lista::Iterador fin = auxiliar1->end();
  Nodo * ogpadre = cpadre;
	for (i; i != fin; ++i){
    Nodo * nodoN = new Nodo();
    nodoN->estado = *i;
    nodoN->padre = ogpadre;
    cpadre = nodoN;
		auxiliar2 = problema->getSiguientes(*i);
		agregarAFrontera(auxiliar2);
	}
}

