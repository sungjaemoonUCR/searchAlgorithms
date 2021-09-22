/**
 * Clase Problem06051Factory  
 * 
 * @author Nazareth Rojas 
 * @version 11-07-2021
 */

#ifndef _PROBLEM06051_FACTORY
#define _PROBLEM06051_FACTORY

#define NOMBRE_MAX_SIZE 100

#include "Fabrica.h"
#include "Problem051.h"
#include "Producto.h"
#include<cstring>

class Problem06051Factory : public Fabrica{
   public:
      Problem051 * producir(); 
      
};
       
#endif
