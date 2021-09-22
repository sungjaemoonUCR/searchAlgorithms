/**
 * Clase NazaEstado permite crear estados de tipo NazaEstado
 * 
 * @author Nazareth Rojas 
 * @version 11-07-2021
 */
#include "NazaEstado.h"

/** Constructor por omisión de la clase NazaEstado
 */
NazaEstado::NazaEstado(){
  n = 8;
  pedirMemoria(n);
  llenarVacia();
  ponerObstaculos();
  ponerMurciRefugio();
}

/** Constructor con parametros de la clase NazaEstado
 * @param noUsar no se utiliza
 */
NazaEstado::NazaEstado(int noUsar){
  n = 8;
  pedirMemoria(n);
  llenarVacia();
}

NazaEstado::~NazaEstado(){
  if(m){
        liberarMemoria();
    }
}

 /** Método clonar permite hacer una copia de un estado
 * @ return nuevoEstado retorna el nuevo estado generado tras copiar los atributos del estado actual
 */
 NazaEstado * NazaEstado::clonar(){
   NazaEstado * nuevoEstado = new NazaEstado();
   for(int f = 0; f < n; f++){
     for(int c = 0; c < n; c++){
       nuevoEstado->m[f][c] = this->m[f][c];
     }
   }
   nuevoEstado->rFila = this->rFila;
   nuevoEstado->rCol = this->rCol;
   nuevoEstado->murciCol = this->murciCol;
   nuevoEstado->murciFila = this->murciFila;

   return nuevoEstado;
 }

 /** Método cagar permite recibir datos desde teclado
 * @ param entrada recibe una referencia al flujo de entrada estandar
 * @ return entrada retorna el flujo de entrada estandar
 */
 istream & NazaEstado::cargar(istream & entrada){
   entrada >> rFila >> rCol >> murciFila >> murciCol; 
   return entrada;  
 }

 /** Método impriimir, perite lanzar al flujo de salida estandar los valores a mostrar en pantalla
 * @ param salida recibe una referencia al flujo de salida estandar
 * @ return salida retorna el flujo de salida estandar
 */
 ostream & NazaEstado::imprimir(ostream & salida){
   for(int i = 0; i < n; i++){ 
     for(int j = 0; j < n; j++){
       salida << m[i][j] << " ";
     }
     salida << endl;
   }
   salida << endl;
   return salida;
}

 /** Operator == sobrecarga que permite comparar dos estados y determinar si son iguales
 * @ param otroEstado recibe un puntero al estado que se desea comparar
 * @ return esIgual retorna 0 si los estados comparados son diferentes, y 1 si son iguales
 */
 int NazaEstado::operator==(Estado * otroEstado){
   NazaEstado * est = dynamic_cast<NazaEstado *>(otroEstado);
   int esIgual = 0;
   if(est){
     if(this->murciFila == est->murciFila && this->murciCol == est->murciCol){
       esIgual = 1; 
     }
   }
   return esIgual;
 }

 /** operator!= sobrecarga que permite comparar dos estados y determinar si son diferentes
 * @ param otroEstado recibe un puntero al estado que se desea comparar
 * @ return retorna 0 si los estados comparados son iguales, y diferente de 0 si son diferentes
 */
 int NazaEstado::operator!=(Estado * otroEstado){
   return !(this==otroEstado);
 }

 
 /** Método liberarMemoria permite liberar la memoria que ha sido asignada a m
 */
void NazaEstado::liberarMemoria(){
    for (int f = n-1; f >= 0; --f){
        delete[]m[f];
    }
    delete[]m;
    this -> n = 0;
    m = 0;
    this -> rFila = 0;
    this -> rCol = 0;
    this -> murciFila = 0;
    this -> murciCol = 0; 
}

 /** Método pedirMemoria permite asignar memoria a m de acuerdo al tamaño de matriz requerido
 * @ param tamano recibe un entero que indica el tamaño de la matriz cuadrada m
 */
void NazaEstado::pedirMemoria(int tamano){
    this->n = 0;
    m = 0;

    if(tamano >0){
        this-> n = tamano;
        m = new char * [n];
        for (int i = 0; i < n; ++i){
            m[i] = new char[n];
        }
    }
}

 /** 
  * Método llenarVacia permite dar el valor '.' a cada una de las casillas de m
 */
 void NazaEstado::llenarVacia(){
    for(int j = 0; j < n; j++){
        for(int k = 0; k < n; k++){
            m[j][k] = '.';
        }
    }
}

 /** Método verificarVecinos permite contar cuales casillas contienen el valor '#', entre aquellas que rodean la posición dada por la coordenada (f, c)
 * @ param f indica la fila de interes
 * @ param c indica la columna de interes
 * @ return i retorna un entero que indica cuantos caracteres '#' se contaron
 */
int NazaEstado::verificarVecinos(int f, int c){
    int i = 0;

    //filas y columnas
    int fArriba = (f-1) % n;
    int col = c % n;
    int fAbajo = (f+1) % n;
    int fil = f % n;
    int colDerecha = (c+1) % n;
    int colIzquierda = (c-1) % n;

    //solucionando error de acceso de memoria
    if( fArriba < 0){
        fArriba = n-1;
    }
    if(colIzquierda < 0){
        colIzquierda = n-1;
    }

    //ver vecinos
    if(m[fArriba][col]=='#'){
        i++;
    }
    if(m[fAbajo][col]=='#'){
        i++;
    }
    if(m[fil][colDerecha]=='#'){
        i++;
    }
    if(m[fil][colIzquierda]=='#'){
        i++;
    }
    if(m[fArriba][colIzquierda]=='#'){
        i++;
    }
    if(m[fArriba][colDerecha]=='#'){
        i++;
    }
    if(m[fAbajo][colIzquierda]=='#'){
        i++;
    }
    if(m[fAbajo][colDerecha]=='#'){
        i++;
    }
    return i;
}

/**
 * Método ponerObstaculos coloca caracteres # semi-aleatoriamente en 1/4 de las celdas de la matriz
 */
 void NazaEstado::ponerObstaculos(){
    int obstaculos = (n * n)/4;
    int colocados = 0;
    int aleatorio;
    int f;
    int c;
    srand(time(NULL));

    while (colocados != obstaculos){
        aleatorio = 0 + rand()%64;
        f = aleatorio / n;
        c = aleatorio % n;
        if (m[f][c] == '.'){
            if(verificarVecinos(f, c) <= 2){
                m[f][c] = '#';
                colocados++;
            }
        }
        else{
            aleatorio = aleatorio + 1;
            if(aleatorio > (n -1)){
                aleatorio = aleatorio - n;
                f = aleatorio / n;
                c = aleatorio % n;
                if (m[f][c] == '.'){
                    if(verificarVecinos(f, c) <= 2){
                        m[f][c] = '#';
                        colocados++;
                    }
                }
            }
            else{
                f = aleatorio / n;
                c = aleatorio % n;
                if (m[f][c] == '.'){
                    if(verificarVecinos(f, c) <= 2){
                        m[f][c] = '#';
                        colocados++;
                    }
                }
            }
        }
    }
}


/**
 * Método ponerMurciRefugio coloca 'R' y 'M' en posiciones semi-aleatorias de la matriz
 */
 void NazaEstado::ponerMurciRefugio(){
    int aleatorio;
    int aleatorio2;
    int f;
    int c;

  //poner murci
    do{
        aleatorio = 0 + rand()%64;
        f = aleatorio / n;
        c = aleatorio % n;
    }while(m[f][c] == '#');

   this->murciFila = f; 
   this->murciCol = c; 
    m[f][c] = 'M';

    //poner refugio
    do{
        aleatorio2 = 0 + rand()%64;
        f = aleatorio2 / n;
        c = aleatorio2 % n;
    }while (aleatorio2 == aleatorio || m[f][c] == '#');

    this->rFila = f;
    this->rCol = c;
    m[f][c] = 'R';
}