/* 
 * Archivo: funciones.c
 * Autor:   Anthony Gutiérrez
 */

#include <stdio.h>
#include <stdlib.h>
#include "funciones.h"

void calcPromAsistencia(int *arrCodCur, int *arrNumAlu, double *arrPorcAsist, int cicloBuscado) {
    /* Declaración de variables */
    int cicAnho, cicPer, cicloLeido, codCur, codHor, numAlu, numCur = 0, pos;
    double porcAsist;
    /* Apertura de archivos */
    FILE *arch = fopen("Asistencia_clases.txt", "r");
    if (arch == NULL) {
        fprintf(stderr, "No se pudo abrir el archivo Asistencia_clases.txt");
        exit(1);
    }
    /* Leer línea por línea los datos del horario */
    while (1) {
        fscanf(arch, "%d %d %d %d %d %lf", &cicAnho, &cicPer, &codCur, &codHor, &numAlu, &porcAsist);
        if (feof(arch)) break;
        /* */
        cicloLeido = cicAnho*10 + cicPer;
        if (cicloLeido == cicloBuscado) {
            /* Buscar el código del curso en el arreglo */
            pos = buscarCodCurso(arrCodCur, numCur, codCur);
            if (pos >= 0) {
                /* Actualizar las sumatorias */
                arrNumAlu[pos] += numAlu;
                arrPorcAsist[pos] += (numAlu*porcAsist);
            } else {
                /* Añadir curso y sumatorias al arreglo */
                arrCodCur[numCur] = codCur;
                arrNumAlu[numCur] = numAlu;
                arrPorcAsist[numCur] = (numAlu*porcAsist);
                numCur++;
            }
        } else {
            /* Ignorar el resto de la línea */
            while (fgetc(arch) != '\n');
        }
    }
    /* Calcular el promedio ponderado para cada alumno */
    for (pos = 0; pos < numCur; pos++) {
        arrPorcAsist[pos] = arrPorcAsist[pos] / arrNumAlu[pos];
    }
    /* Cerrar el archivo */
    fclose(arch);
}

int buscarCodCurso(int *arrCodCur, int numCur, int codCur) {
    int pos;
    for (pos = 0; pos < numCur; pos++) {
        if (arrCodCur[pos] == codCur) return pos;
    }
    return -1;
}
