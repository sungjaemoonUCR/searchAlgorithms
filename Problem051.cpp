/**
 * Clase Problem051
 *
 * @author Nazareth Rojas
 * @version 11-07-2021
 */
#include "Problem051.h"
#include "Lista.h"
#include "Problema.h"



/** Constructor por omisión de la clase Problem051 
*/
Problem051::Problem051(){
    inicial = new NazaEstado();
    solucion = inicial->clonar();
    solucion->m[solucion->murciFila][solucion->murciCol] = '.'; //PONER ESTOS EN UN MÉTODO PARA SOLO LLAMARLO Y QUE NO QUEDE TAN FEO EL CONSTRUCTOR
    solucion->m[solucion->rFila][solucion->rCol] = 'M';
    solucion->murciFila = solucion->rFila;
    solucion->murciCol = solucion->rCol;

}


/** 
* Destructor de la clase Problem051 
*/
Problem051::~Problem051(){
    //if(inicial){
    //  delete [] inicial;
    //}
}

/** Método getEstadoInicial devuelve el Estado almacenado en el atributo inicial
 * @ return retorna el Estado inicial
 */
Estado * Problem051::getEstadoInicial(){
    return this->inicial;
}


/** Método esSolucion permite comparar un Estado de interes con el Estado solucion
 * @ param estadoAComparar recibe un puntero al estado que se desea comparar
 * @ return esSolucion retorna 1 si el estado comparado es la solucion al problema, y 0 si no lo es
 */
int Problem051::esSolucion( Estado * estadoAComparar){
    NazaEstado * est = dynamic_cast< NazaEstado * >(estadoAComparar);
    int esSolucion = 0;
    if(*solucion == est){
        esSolucion = 1;
    }

    return esSolucion;
}

/** Método heuristica permite calcular un estimado "optimista" de la distancia del estado actual al estado solucion
* @ param estado recibe el estado del que se desea conocer la heuristica
* @ return heuristica retorna el valor de la menor heuristica calculada
*/
int Problem051::heuristica(Estado * estado){
    NazaEstado * est = dynamic_cast< NazaEstado * >(estado);
    int heuristica = 1;
    int distanciaFilas = 0;
    int distanciaCol = 0;
    int auxiliar1 = 0;
    int auxiliar2 = 0;
    int n = inicial->n;

    distanciaFilas = est->rFila - est->murciFila;
    distanciaCol = est->rCol - est->murciCol;
    auxiliar1 = abs(distanciaFilas) + abs(distanciaCol);

    if(est->rFila > est->murciFila){
        distanciaFilas = ((n-1) - est->rFila) + (est->murciFila + 1);
    }
    else{
        distanciaFilas = ((n-1) - est->murciFila) + (est->rFila +1);
    }

    if(est->rCol > est->murciCol){
        distanciaCol = ((n-1)- est->rCol) + (est->murciCol +1);
    }
    else{
        distanciaCol = ((n-1) - est->murciCol) + (est->rCol +1);
    }

    auxiliar2 = distanciaFilas + distanciaCol;

    //seleccionar menor heuristica
    if(auxiliar1 < auxiliar2){
        heuristica = auxiliar1;
    }
    else{
        heuristica = auxiliar2;
    }

    return heuristica;
}


/** Método getSiguientes permite expandir un estado en sus posibles estados siguientes
* @ param estado recibe un puntero al estado que se desea expandir
* @ return listaSiguientes retorna la lista de los posibles estados siguientes a partir del estado que se expandió
*/
Lista * Problem051::getSiguientes( Estado * estado){
    NazaEstado * est = dynamic_cast< NazaEstado * >(estado);
    Lista * listaSiguientes = new Lista();
    if(est){
        int n = est->n;
        //filas y columnas
        int fArriba = (est->murciFila-1) % n;
        int col = est->murciCol % n;
        int fAbajo = (est->murciFila+1) % n;
        int fil = est->murciFila % n;
        int colDerecha = (est->murciCol+1) % n;
        int colIzquierda = (est->murciCol-1) % n;

        //solucionando error de acceso de memoria
        if( fArriba < 0){
            fArriba = n-1;
        }
        if(colIzquierda < 0){
            colIzquierda = n-1;
        }

        if(est->m[fArriba][col] != '#'){
            NazaEstado * norte = est->clonar();
            norte->m[norte->murciFila][norte->murciCol] = '.';
            norte->m[fArriba][col] = 'M';
            norte->murciFila = fArriba;
            norte->murciCol = col;
            listaSiguientes->push_back(norte);
        }

        if(est->m[fAbajo][col] != '#'){
            NazaEstado * sur = est->clonar();
            sur->m[sur->murciFila][sur->murciCol] = '.';
            sur->m[fAbajo][col] = 'M';
            sur->murciFila = fAbajo;
            sur->murciCol = col;
            listaSiguientes->push_back(sur);
        }

        if(est->m[fil][colDerecha] != '#'){
            NazaEstado * este = est->clonar();
            este->m[este->murciFila][este->murciCol] = '.';
            este->m[fil][colDerecha] = 'M';
            este->murciFila = fil;
            este->murciCol = colDerecha;
            listaSiguientes->push_back(este);
        }

        if(est->m[fil][colIzquierda] != '#'){
            NazaEstado * oeste = est->clonar();
            oeste->m[oeste->murciFila][oeste->murciCol] = '.';
            oeste->m[fil][colIzquierda] = 'M';
            oeste->murciFila = fil;
            oeste->murciCol = colIzquierda;
            listaSiguientes->push_back(oeste);
        }

    }
    return listaSiguientes;
}
