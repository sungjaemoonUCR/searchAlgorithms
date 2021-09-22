#ifndef EL_ESTADO
#define EL_ESTADO
#include<iostream>
using namespace std;

// AYUDA: Recuerden que para que su problema vea los atributos
// privados de su implementación de Estado entonces:
// la clase derivada de Estado debe tener un 
// friend class de derivada de su Problema

class Estado {

   friend istream& operator>>(istream& entrada, Estado * estadoPtr){
       return estadoPtr->cargar(entrada);
   }
   friend ostream& operator<<(ostream& salida, Estado * estadoPtr){
       if(estadoPtr){
          estadoPtr->imprimir(salida);
       }
       else {
          salida << "null";
       }
       return salida;
   }

   public:
      virtual ~Estado(){};

      virtual Estado * clonar()=0;

      // Todo estado tiene que poder cargar e imprimir
      virtual istream& cargar(istream&)=0;
      virtual ostream& imprimir(ostream&)=0;
      virtual int operator==(Estado *)=0;
      virtual int operator!=(Estado *)=0;
};



#endif
