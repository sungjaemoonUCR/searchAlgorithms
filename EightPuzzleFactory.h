#ifndef EIGHTPUZZLE_FACTORY
#define EIGHTPUZZLE_FACTORY
#include "Fabrica.h"
#include "ProblemaEightPuzzle.h"

class EightPuzzleFactory : public Fabrica {
    public:
       ProblemaEightPuzzle * producir();
};

#endif
