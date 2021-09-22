#ifndef SOLUCIONADOR_ANCHO_PRIMERO_FACTORY
#define SOLUCIONADOR_ANCHO_PRIMERO_FACTORY

#include "Fabrica.h"
#include "SolucionadorAnchoPrimero.h"

class SolucionadorAnchoPrimeroFactory : public Fabrica {
    public:
       SolucionadorAnchoPrimero * producir();
};

#endif
