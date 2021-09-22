/**
 * Clase Problem06051Factory  
 * 
 * @author Nazareth Rojas 
 * @version 11-07-2021
 */

#include "Problem06051Factory.h"

/**
 * Método producir crea problemas de tipo Problem051
 * @return retorna un puntero a un problema Problem051
 */
 Problem051 * Problem06051Factory::producir(){
   return new Problem051();  
 }