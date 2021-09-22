#include "Registro.h"
#include "Fabrica.h"
// AGREGUE UNA FABRICA DE SOLUCIONADOR Y UNA DE PROBLEMA
// POR CADA MIEMBRO Z DE SU GRUPO XX EQUIPO YY
// MIEMBRO 0
#include "EightPuzzleFactory.h"
#include "SolucionadorAnchoPrimeroFactory.h"
// MIEMBRO 2
#include "Problem06051Factory.h"
// MIEMBRO 3


void Registro::add(const char * nombre, Fabrica * fabrica){
   if(cantidad<CAPACIDAD){
      if(fabrica){
         fabrica->setNombre(nombre);
         this->fabrica[cantidad++] = fabrica;
      }
   }
}

Registro::Registro(){
   // AL INICIO HAY 0 FABRICAS INSCRITAS
   cantidad = 0;
   // SE CREAN INSTANCIAS DE FABRICA Y SE REGISTRAN

   // Registran los del miembro 1 del equipo YY del grupo XX
   // Ejemplo:
  this->add("NazaP", new Problem06051Factory() );

   this->add("8Puzzle", new EightPuzzleFactory() );
   this->add("Solucionador8Puzzle", new SolucionadorAnchoPrimeroFactory() );

  
   // Registran los del miembro 2 del equipo YY del grupo XX
   // ... agregar lineas aqui
   // Registran los del miembro 3 del equipo YY del grupo XX
   // ... agregar lineas aqui
}

Registro::~Registro(){
   for(int i=0; i<cantidad; ++i){
      if(fabrica[i]){
         delete fabrica[i];
      }
   }
}

Fabrica * Registro::getFabrica(const char * nombre){
   Fabrica * fabricaPtr = 0;
   for(int i=0; !fabricaPtr && i<cantidad; ++i){
      if( this->fabrica[i]->produce( nombre ) ){
         fabricaPtr = this->fabrica[i];
      }
   }   
   return fabricaPtr;
}
