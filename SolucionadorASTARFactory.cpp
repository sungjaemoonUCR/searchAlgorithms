#include "SolucionadorASTARFactory.h"
#include "SolucionadorASTAR.h"

SolucionadorASTAR * SolucionadorASTARFactory::producir(){
   return new SolucionadorASTAR();
}
