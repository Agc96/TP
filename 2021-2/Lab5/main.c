/*
 * File:   main.c
 * Author: Anthony Gutiérrez
 *
 * Created on 16 de noviembre de 2021, 08:05 AM
 */

#include <stdio.h>
#include "funcionesLab05.h"
#include "funcionesCadenas.h"

#define MAX_ESCALA 50
#define MAX_CURSO 50

int main() {
    char *arrCodEsc[MAX_ESCALA], *arrCodCur[MAX_CURSO], *arrNomCur[MAX_CURSO];
    double arrPrecEsc[MAX_ESCALA], arrRecEsc[MAX_ESCALA] = {0},
            arrCredCur[MAX_CURSO], arrRecCur[MAX_CURSO] = {0};
    int cantEsc, cantCur;
    leerEscalas(arrCodEsc, arrPrecEsc, &cantEsc);
    leerCursos(arrCodCur, arrNomCur, arrCredCur, &cantCur);
    procesarMatricula(arrCodEsc, arrPrecEsc, arrRecEsc, cantEsc,
            arrCodCur, arrNomCur, arrCredCur, arrRecCur, cantCur);
    ordenarEscalas(arrCodEsc, arrPrecEsc, arrRecEsc, cantEsc);
    ordenarCursos(arrCodCur, arrNomCur, arrCredCur, arrRecCur, cantCur);
    imprimirReporte(arrCodEsc, arrPrecEsc, arrRecEsc, cantEsc,
            arrCodCur, arrNomCur, arrCredCur, arrRecCur, cantCur);
    return 0;
}
