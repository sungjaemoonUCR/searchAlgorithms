#include "EightPuzzleFactory.h"
#include "ProblemaEightPuzzle.h"

ProblemaEightPuzzle * EightPuzzleFactory::producir(){
   return new ProblemaEightPuzzle();
}
