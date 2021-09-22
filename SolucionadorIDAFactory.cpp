#include "SolucionadorIDAFactory.h"
#include "SolucionadorIDAFactory.h"

SolucionadorIDA * SolucionadorIDAFactory::producir(){
   return new SolucionadorIDA();
}
