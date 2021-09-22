#ifndef SOLUCIONADOR_IDA_FACTORY
#define SOLUCIONADOR_IDA_FACTORY

#include "Fabrica.h"
#include "SolucionadorIDA.h"

class SolucionadorIDAFactory : public Fabrica {
    public:
       SolucionadorIDA * producir();
};

#endif
