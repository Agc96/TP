/* 
 * Archivo: main.c
 * Autor:   Anthony Gutiérrez
 */

#include <stdio.h>
#include <stdlib.h>
#include "funciones.h"

int main() {
    int codCur[MAX_CUR] = {0}, numAlu[MAX_CUR] = {0}, cicAnho, cicPer, ciclo;
    double porcAsist[MAX_CUR] = {0.0}, encuestaReal[MAX_CUR] = {0.0};
    /* Leer el ciclo a calcular */
    printf("Ingrese el anho y periodo del ciclo: ");
    scanf("%d %d", &cicAnho, &cicPer);
    ciclo = cicAnho*10 + cicPer;
    /* Calcular los promedios ponderados de asistencia */
    calcPromAsistencia(codCur, numAlu, porcAsist, ciclo);
    return 0;
}
