#include "EstadoEightPuzzle.h"
#include <random>
#include <time.h>
#include <algorithm>
#include <iostream>
using namespace std;

EstadoEightPuzzle::EstadoEightPuzzle(){
  n = 3;
  pedirMemoria(n);
  llenarAleatorio();
}

EstadoEightPuzzle::~EstadoEightPuzzle(){
  if(m){
    liberarMemoria();
  }
}

EstadoEightPuzzle * EstadoEightPuzzle::clonar(){
	EstadoEightPuzzle * nuevoEstado= new EstadoEightPuzzle();  
  for(int f=0; f < n; ++f){
    for(int c=0; c < n; ++c){
			nuevoEstado->m[f][c]= this->m[f][c];
   	}
  }
  return nuevoEstado;
}

istream& EstadoEightPuzzle::cargar(istream& entrada){
  for(int f = 0; f<n; ++f){
  	for(int c = 0; c < n; ++c){
  		entrada >> m[f][c];
	  }
  }
  return entrada;
}

ostream& EstadoEightPuzzle::imprimir(ostream& salida){
  for(int f = 0; f < n; ++f){
    for(int c = 0; c < n; ++c){
  		salida << m[f][c] << " ";
	  }
	  salida << endl;
  }
  salida << endl;
  return salida;
}

int EstadoEightPuzzle::operator==(Estado * otroEstado){
  EstadoEightPuzzle * estado = dynamic_cast<EstadoEightPuzzle *>(otroEstado);
  int esIgual = 1; 

  for(int f = 0; f < n; ++f){
    for(int c = 0; c < n; ++c){
      if (this->m[f][c] != estado->m[f][c]){
  			esIgual = 0;
  			f=n;
        c=n;
			}
	 	}
  }
  return esIgual;
}

int EstadoEightPuzzle::operator!=(Estado * otroEstado){
   return !(*this==otroEstado);
}

void EstadoEightPuzzle::pedirMemoria(int tamanio){
	this->n = 0;
  this->m = 0;

  if(tamanio >0){
    this-> n = tamanio;
    m = new char * [n];
    for (int i = 0; i < n; ++i){
      m[i] = new char[n];
    }
  }
}

void EstadoEightPuzzle::liberarMemoria(){
	for (int f = n-1; f >= 0; --f){
        delete[]m[f];
    }
    delete[]m;
    this -> m = 0;
}

void EstadoEightPuzzle::llenar(){
	for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            m[i][j] = '0';
        }
    }
}


void EstadoEightPuzzle::llenarAleatorio(){
  char randomizer [] = {'0','2','3','4','5','6','7','8','9'};
  srand(time(0));
  int pos = 0;
  random_shuffle(begin(randomizer), end(randomizer));
	for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            m[i][j] = randomizer[pos];
            pos++;
        }
    }
    
}
