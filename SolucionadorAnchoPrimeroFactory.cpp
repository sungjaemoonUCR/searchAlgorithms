#include "SolucionadorAnchoPrimeroFactory.h"
#include "SolucionadorAnchoPrimero.h"

SolucionadorAnchoPrimero * SolucionadorAnchoPrimeroFactory::producir(){
   return new SolucionadorAnchoPrimero();
}
