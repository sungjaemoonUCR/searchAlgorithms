#include "Registro.h"
#include "Fabrica.h"
#include "Producto.h"

// DOS PRODUCTOS ESPECÍFICOS SERÁN Solucionador Problema
#include "Solucionador.h"
#include "Problema.h"

// Lista de estados desde el inicial hasta la solucion final
#include "Solucion.h" 

#include<iostream>
using namespace std;

// Compilar con:  g++ -o solucionar *.cpp
// Uso: solucionar "nombreProblema" "nombreSolucionador"

int main(int argc, char **argv){
   Registro registro;

   Fabrica * fabricaDeProblema;
   Producto * producto1 = 0;
   Problema * problema=0;

   Fabrica * fabricaDeSolucionador;
   Producto * producto2 = 0;
   Solucionador * solucionador = 0;

   // PROGRAMA PRODUCE UNA SOLUCIÓN
   Solucion * solucion = 0;


   if(argc>2){
      fabricaDeProblema = registro.getFabrica( argv[1] );
      fabricaDeSolucionador = registro.getFabrica( argv[2] );
     
      if(fabricaDeProblema && fabricaDeSolucionador){
            producto1 = fabricaDeProblema->producir();  
            problema =   dynamic_cast< Problema * >( producto1 );

            producto2 = fabricaDeSolucionador->producir();
            solucionador = dynamic_cast< Solucionador * > ( producto2 );
            if(problema && solucionador) {
               solucion = solucionador->solucione( problema );
               cout << "Problema: " << argv[1] << endl;
               cout << "Solucinador: "<< argv[2] << endl;
               cout << "---------------------------------" << endl;
               cout << "---------- SOLUCION -------------" << endl;
               cout << "---------------------------------" << endl;
               if(solucion){
                  cout << solucion << endl;
               }
               else {
                  cout << "NO HAY SOLUCION" << endl;
               }
            }
            else {
               cout << "Warning: debe indicar una fabrica de problema primero luego de solucionador"<< endl;
               cout << "Uso: "<< argv[0] << " nombreProblema nombreSolucionador" << endl;
            }
      }
      else {
          cout << "Warning: Fábrica de Producto no registrado" << endl;
      }
   }
   else {
      cout << "Uso: "<< argv[0] << " nombreProblema nombreSolucionador" << endl;
   }

   // LAS FABRICAS SON DESTRUIDAS POR EL REGISTRO


   // Destruye instancias retornadas por las fábricas

   if(problema){
      delete problema;
   }
   else {
      if(producto1){
         delete producto1;
      }
   }

   if(solucionador){
      delete solucionador;
   }
   else {
      if(producto2){
         delete producto2;
      }
   }

   // Destruir la solución si no es nula 0
   if(solucion){
      delete solucion;
   }

   return 0;
}
