/*
 * Archivo: main.c
 * Autor:   Anthony Gutiérrez
 *
 * Creado el 24 de noviembre de 2020, 08:18 AM
 */

#include <stdio.h>
#include <stdlib.h>
#include "funciones.h"

#define MAX_CURSOS 100
#define MAX_ALUMNOS 50

int main() {
    char *arrCodCur[MAX_CURSOS], *arrNomCur[MAX_CURSOS], *arrFacCur[MAX_CURSOS],
            *arrNomAlu[MAX_ALUMNOS];
    double arrCredCur[MAX_CURSOS], arrSumNotas[MAX_ALUMNOS] = {0.0},
            arrSumAprob[MAX_ALUMNOS] = {0.0}, arrCredAprob[MAX_ALUMNOS] = {0.0},
            arrCredDesap[MAX_ALUMNOS] = {0.0};
    int arrCodAlu[MAX_ALUMNOS], arrNumAprobCur[MAX_CURSOS] = {0},
            arrNumAluCur[MAX_CURSOS] = {0}, cantCur = 0, cantAlu = 0;

    leerCursos(arrCodCur, arrNomCur, arrCredCur, arrFacCur, &cantCur);
    ordenarCursos(arrCodCur, arrNomCur, arrCredCur, arrFacCur, cantCur);

    leerAlumnos(arrCodAlu, arrNomAlu, &cantAlu);
    ordenarAlumnos(arrCodAlu, arrNomAlu, cantAlu);

    leerNotas(arrCodAlu, arrSumNotas, arrSumAprob, arrCredAprob, arrCredDesap, cantAlu,
            arrCodCur, arrCredCur, arrNumAluCur, arrNumAprobCur, cantCur);

    imprimirReporte(arrCodAlu, arrNomAlu, arrSumNotas, arrSumAprob, arrCredAprob, arrCredDesap, cantAlu,
            arrCodCur, arrNomCur, arrCredCur, arrFacCur, arrNumAluCur,
            arrNumAprobCur, cantCur);
    liberarEspacios(arrCodCur, arrNomCur, arrFacCur, cantCur, arrNomAlu, cantAlu);

    return 0;
}
