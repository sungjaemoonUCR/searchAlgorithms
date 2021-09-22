#ifndef EL_SOLUCIONADOR
#define EL_SOLUCIONADOR
#include "Producto.h"
#include "Problema.h"
#include "Solucion.h"

class Solucionador : public Producto {
   public:
      virtual Solucion * solucione( Problema *)=0;
};

#endif
