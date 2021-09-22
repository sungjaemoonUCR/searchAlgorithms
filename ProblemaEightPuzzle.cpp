#include "ProblemaEightPuzzle.h"
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <math.h>

using namespace std;

ProblemaEightPuzzle::ProblemaEightPuzzle(){
  inicial = new EstadoEightPuzzle();

cout << "inicial state"<< endl;
  inicial->m[0][0] = '1';
  inicial->m[0][1] = '3';
  inicial->m[0][2] = '0';
  inicial->m[1][0] = '6';
  inicial->m[1][1] = '2';
  inicial->m[1][2] = '4';
  inicial->m[2][0] = '8';
  inicial->m[2][1] = '7';
  inicial->m[2][2] = '5';
  cout << inicial <<endl;
    cout<<endl;

  solucion = inicial->clonar();

  cout << "desired solution"<< endl;
  solucion->m[0][0] = '1';
  solucion->m[0][1] = '2';
  solucion->m[0][2] = '3';
  solucion->m[1][0] = '8';
  solucion->m[1][1] = '0';
  solucion->m[1][2] = '4';
  solucion->m[2][0] = '7';
  solucion->m[2][1] = '6';
  solucion->m[2][2] = '5';
  cout << solucion <<endl;
    cout<<endl;
}

ProblemaEightPuzzle::~ProblemaEightPuzzle() {

}

Estado * ProblemaEightPuzzle::getEstadoInicial(){
   return this->inicial; //new EstadoEightPuzzle();
}

int ProblemaEightPuzzle::esSolucion( Estado * estadoAComparar){
    EstadoEightPuzzle * est = dynamic_cast< EstadoEightPuzzle * >(estadoAComparar);
    int esSolucion = 0;
    if(*solucion == est){
        esSolucion = 1;
    }
 cout << "esSolucion: " << esSolucion << endl;
    return esSolucion;
}

int ProblemaEightPuzzle::heuristica(Estado * estado){
  // Se podria evaluar cantidad de valores que están fuera de posición
   EstadoEightPuzzle * estadoC = dynamic_cast< EstadoEightPuzzle * >(estado);
   int erroneos = 0;
   if(estadoC) { 
      for(int i=0; i<3 ; i++){
        for(int j=0; j<3; j++){
          /*
          int goalI = estadoC->m[i][j]/3
          int goalJ = estadoC->n[i][j]%3

          erroneos += abs(i-goalI)+abs(j-goalJ);

          */
//cout << "heuristica problema 3" << "\n";
          if(0){
            ++erroneos;
          }
        }
      }
   }
   return erroneos;
}


Lista * ProblemaEightPuzzle::getSiguientes( Estado * estado){
   EstadoEightPuzzle * estadoC = dynamic_cast< EstadoEightPuzzle * >(estado);
   Lista * siguientes = new Lista();
  //arriba (f-1)
  // abajo (f+1)
  // izq (c-1)
  // derecha (c+1)
  int n = estadoC->n;
  int fila;
  int columna;

  for(int f = 0; f < n; ++f){
    for(int c = 0; c < n; ++c){
//cout << "getSiguientes  problema 4" << "\n";
      if (estadoC->m[f][c] == '0'){
        fila = f;
        columna = c;
      }
    }
  }

  int tempfila;
  int tempcolumna;
  if(estadoC){
    //arriba
    EstadoEightPuzzle * clon1 = estadoC->clonar();
    int tempfila = fila-1;
    if(tempfila >= 0){
        clon1->m[fila][columna] = estadoC->m[tempfila][columna];
        clon1->m[tempfila][columna] = '0';
        siguientes->push_back( clon1 );
    }
    delete clon1;
    
    //abajo
    EstadoEightPuzzle * clon2 = estadoC->clonar();
    tempfila = fila+1;
    if(tempfila <= 2){
      clon2->m[fila][columna] = estadoC->m[tempfila][columna];
      clon2->m[tempfila][columna] = '0';
      siguientes->push_back( clon2 );
    }
    delete clon2; 
    
    //izq (c-1)
    EstadoEightPuzzle * clon3 = estadoC->clonar();
    tempcolumna = columna -1;
    if(tempcolumna >= 0){
      clon3->m[fila][columna] = estadoC->m[fila][tempcolumna];
      clon3->m[fila][tempcolumna] = '0';
      siguientes->push_back( clon3 );
    }
    delete clon3;
    
    //derecha
    EstadoEightPuzzle * clon4 = estadoC->clonar();
    tempcolumna = columna+1;
    if(tempcolumna <= 2){
      clon4->m[fila][columna] = estadoC->m[fila][tempcolumna];
      clon4->m[fila][tempcolumna] = '0';
        siguientes->push_back( clon4 );
    } 
    delete clon4;
  }
  
  return siguientes;
}      

