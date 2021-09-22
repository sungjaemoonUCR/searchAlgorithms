#ifndef LISTA_DE_ESTADOS
#define LISTA_DE_ESTADOS
#include<iostream>
using namespace std;

#include "Estado.h"

class Lista {
   friend class Iterador;

   friend ostream& operator<<( ostream& salida, Lista * lista){
      if(lista){
         lista->imprimir(salida);
      }
      else {
         salida << "lista_null" << endl;
      }
      return salida;
   }

   private:
       class Celda {
          public:
              Estado * elementoPtr;
              Celda * anterior;
              Celda * siguiente;
              Celda(Estado * );
              ~Celda();
       };

       Celda * primera;
       Celda * ultima;
   public:     
       class Iterador {
           friend class Lista;
           private:
               Celda * actual;
           public:
               Iterador();
               Iterador(Celda *);
               Estado * &operator*();         
               Iterador& operator++();
               Iterador operator++(int);
               Iterador& operator--();
               Iterador operator--(int);
               int operator==(Iterador);
               int operator!=(Iterador);
       };
   
       Lista();

       // RULE OF THREE
       Lista(Lista &);       
       ~Lista();
       Lista& operator=(Lista&);
       // -- SI TENGO UNO DE ESTOS MÉTODOS DEBEN ESTAR LOS 3 --


       int isEmpty();

       Estado * pop_front();
       Estado * pop_back();
       Estado * peek();
       Lista & push_back(Estado *);  // encadenamiento de métodos      
       Lista & push_front( Estado * );

       ostream& imprimir(ostream&);

       Iterador buscar( Estado * ); // retorna iterador del Celda con valor igual a int
       Lista & borrar( Iterador &); // Borra Celda a la que apunta el iterador
       Lista & insertar(Iterador, Estado * );

       Iterador begin();
       Iterador rbegin(); // A solicitud de Thomas
       // end() es el final que es después del último
       Iterador end(); // su valor actual es null siempre
       int esta( Estado * estadoAComparar);//AGREGADO POR NAZA******************************************

};

#endif
