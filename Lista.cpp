#include "Lista.h"
#include "Estado.h"
#include<iostream>
using namespace std;

// METODOS DE CLASE ANIDADA CELDA   Lista::Celda
// LA LISTA AGREGA CLONES DE LOS ESTADOS QUE LE PASAN

Lista::Celda::Celda( Estado * elementoPtr ){
   this->elementoPtr = 0;
   if(elementoPtr){
      this->elementoPtr = elementoPtr->clonar();
   }
   anterior = 0;     // En C++  es necesario inicializar a nulo ( poner 0 ) a los punteros
   siguiente = 0;
}

Lista::Celda::~Celda(){
   if(siguiente){
       delete siguiente;
   }
   // CUIDADO... SI DEJAN ALGO EN LA LISTA 
   // LES VA A DESTRUIR EL ESTADO AL QUE APUNTA
   if(elementoPtr){
       delete elementoPtr;
   }
}

// METODOS DE LA CLASE ITERADOR

Lista::Iterador::Iterador(){
   actual = 0;
}

Lista::Iterador::Iterador(Celda * actual){
   this->actual = actual;
}
 
Estado * & Lista::Iterador::operator*(){
   return actual->elementoPtr;
}

Lista::Iterador& Lista::Iterador::operator++(){
   if(actual){
      actual = actual->siguiente;
   }
   return *this;
}

Lista::Iterador Lista::Iterador::operator++(int){
   Iterador viejo(actual);
   ++(*this);
   return viejo;
}

Lista::Iterador& Lista::Iterador::operator--(){
   if(actual){
      actual = actual->anterior;
   }
   return *this;
}

Lista::Iterador Lista::Iterador::operator--(int){
   Iterador viejo(actual);
   --(*this);
   return viejo;
}

               
int Lista::Iterador::operator==(Iterador otro){
    return this->actual == otro.actual;
}
               
int Lista::Iterador::operator!=(Iterador otro){
   return !(*this == otro);
}


// METODOS DE CLASE LISTA
Lista::Lista(){
   primera = 0;
   ultima = 0;
}

Lista & Lista::operator=(Lista& lista){
   if(primera){
      delete primera;
      primera=0;
   }
   ultima=0;
   Iterador fin = lista.end();
   for(Iterador i = lista.begin(); i!= fin; ++i){
       this->push_back( *i );
   }
   return *this;   
}

Lista::Lista(Lista& lista){
   primera=0;
   ultima=0;
   *this=lista; // uso operador de asignación
}
Lista::~Lista(){
   if(primera){
      delete primera; // destruye la primera Celda si existe valor es !=0
   }
}


int Lista::isEmpty(){
   return !primera;
}

Lista & Lista::push_front( Estado *  elemento){
  Celda * nueva = new Celda( elemento );
  if(isEmpty()){
     primera = nueva;
     ultima = nueva;
  }
  else {
     nueva->siguiente = primera;
     primera->anterior = nueva;
     primera = nueva;
  }
  return *this; //encadenamiento
}

Lista & Lista::push_back( Estado * elemento){
  Celda * nueva = new Celda( elemento );
  if(isEmpty()){
     primera = nueva;
     ultima = nueva;
  }
  else {
     ultima->siguiente = nueva;
     nueva->anterior = ultima;
     ultima = nueva;
  }
  return *this; //encadenamiento
}


ostream& Lista::imprimir(ostream & salida){
   Celda * actual = primera;
   while(actual){
     salida << actual->elementoPtr << endl << endl;
     actual = actual->siguiente;
   }
   return salida;
}

Lista::Iterador Lista::begin(){
   Iterador i( primera );
   return i;
}

Lista::Iterador Lista::rbegin(){
  Iterador i( ultima );
  return i;
}
Lista::Iterador Lista::end(){
   Iterador i;
   return i;
}

Lista::Iterador Lista::buscar( Estado *  elemento){
   Celda * actual = primera;
   while(actual && actual->elementoPtr!=elemento && (actual->elementoPtr!=0 && *(actual->elementoPtr)!= elemento)){
      actual= actual->siguiente;
   } 
   //Iterador i(actual);
   //if(actual->elementoPtr != elemento){
     //  Celda * actual = 0;
   //}
   Iterador i(actual);
   return i;
}

Estado *  Lista::pop_front(){
   Estado * elemento =0;
   if(this->primera){
      Celda * victima = primera;
      elemento = primera->elementoPtr;
      primera->elementoPtr = 0; // Quité elemento de la celda
      primera = primera->siguiente;
      victima->siguiente=0; // Desconectar Celda
      delete victima;
      if(primera){
         primera->anterior = 0;
      }
      else{
         ultima = 0;
      }
   }   

   return elemento;
}
Estado * Lista::peek() {
  Estado * elemento;
  return elemento = primera->elementoPtr;
}

Estado * Lista::pop_back(){
   Iterador i = rbegin();
   Iterador fin = end();
   Estado * encontrado = 0;
   if(i!=fin){
      encontrado = *i;
      *i = 0; // desconecta Estado de la lista antes de borrar la celda
      borrar(i);
   }
   return encontrado;
}

Lista & Lista::borrar( Iterador & i){
   if(!isEmpty()){
     if(primera==ultima){
        if(i.actual==primera){
          i++;
          delete primera;
          primera=0;
          ultima=0;
        }
        else {
          cerr << "Intento de borrar en lista vacia con iterador no nulo"<< endl;
        }
      } // 2 o más elementos
      else {
         Celda * victima = i.actual;
         ++i; // muevo a la derecha el iterador
         if(primera == victima){
           i.actual->anterior = 0;
           primera = i.actual;
           victima->siguiente = 0;
         }
         else {
           if(ultima == victima){
               ultima = victima->anterior;
               ultima->siguiente = 0;
               victima->anterior=0;          
           }// quedan 2 o más nodos y borro algo que no es primera ni ultima 
           else {
               victima->anterior->siguiente = victima->siguiente;
               victima->siguiente->anterior = victima->anterior;
               victima->anterior = 0;
               victima->siguiente = 0;
           }
         }
         delete victima;
      }
   }        // Liberar memoria de la Celda víctima      
   return *this;
}

Lista & Lista::insertar(Iterador i, Estado * elemento){
   Iterador inicio = this->begin();
   Iterador fin = this->end();
   if(!isEmpty()) {
      if(i == inicio){
          push_front(elemento);
      }
      else {
         if(i==fin){
            push_back(elemento);
         }
         else { // hay 2 o más elementos
            Celda * nueva = new Celda(elemento);
            nueva->anterior = i.actual->anterior;
            nueva->siguiente = i.actual;
            i.actual->anterior->siguiente = nueva;
            i.actual->anterior = nueva;

         }
      }
   }
   else { // Lista vacia
      if(i==fin){
         push_front(elemento);
      }
      else {
         cerr << "Intento de agregar en lista vacia con iterador no nulo"<< endl;
      }
   }
   return *this;
}


int Lista::esta( Estado * estadoAComparar){
   int esta = 0;
   Iterador fin = this->end();
   for(Iterador i = this->begin(); i != fin; i++){
     if( *(*i) == estadoAComparar){
     esta = 1;
    }
   }
   return esta;
  }