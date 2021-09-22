#include "SolucionadorIDA.h"
#include "Estado.h"
#include "Solucion.h"
#include "Lista.h"
#include "Problema.h"
#include <bits/stdc++.h>

using namespace std;

SolucionadorIDA::SolucionadorIDA(){
    profundidad = 0;
}

Solucion * SolucionadorIDA::solucione( Problema * problema){
    Estado* estado = problema->getEstadoInicial();
    profundidad = problema->heuristica(estado);
    bool resuelto = false;
    /*
    

    Lista * pasos = new Lista();
    Solucion * solucion = new Solucion(pasos);
    
    while(!resuelto){

    }*/
}

Solucion * SolucionadorIDA::solucioneRec(Problema * problema){

}
