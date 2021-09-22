#ifndef EL_REGISTRO
#define EL_REGISTRO

#define CAPACIDAD 120

#include "Fabrica.h"

class Registro {
   private:
      int cantidad;
      Fabrica * fabrica[CAPACIDAD];
      void add(const char *, Fabrica *);
   public:
      Registro();
      ~Registro();
      Fabrica * getFabrica(const char *);
};

#endif
