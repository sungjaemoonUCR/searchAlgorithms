#ifndef LA_FABRICA
#define LA_FABRICA

#define NOMBRE_MAX_SIZE 100

#include "Producto.h"
#include<cstring>

class Fabrica {
   protected:
      // NOMBRE DEL PRODUCTO AL REGISTRARLO
      char nombre[NOMBRE_MAX_SIZE];

   public:
      // PARA ASIGNARLE NOMBRE EN EL REGISTRO
      virtual void setNombre(const char * nombre){
         strncpy(this->nombre,nombre,NOMBRE_MAX_SIZE - 1);
      }

      virtual ~Fabrica(){};
      
      virtual Producto * producir()=0;

      // PARA USAR EN EL REGISTRO
      virtual int produce(const char * nombre){
          return !(strcmp(this->nombre,nombre));
      }
};
       
#endif
