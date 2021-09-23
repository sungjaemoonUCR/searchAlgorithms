#ifndef SOLUCIONADOR_ASTAR_FACTORY
#define SOLUCIONADOR_ASTAR_FACTORY

#include "Fabrica.h"
#include "SOLUCIONADOR_ASTAR_FACTORY.h"

class SolucionadorASTARFactory : public Fabrica {
    public:
       SolucionadorASTARFactory * producir();
};

#endif