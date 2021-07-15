/*
 * Archivo: main.c
 * Autor:   Anthony Gutiérrez
 *
 * Creado el 13 de octubre de 2020, 07:44 AM
 */

#include "funciones.h"
#define MAX_MEDICOS 100

int main() {
    int codigoMed[MAX_MEDICOS], pacAtend[MAX_MEDICOS], pacRes[MAX_MEDICOS];
    double factorAtenc[MAX_MEDICOS], factorRes[MAX_MEDICOS];
    int numMed = leerPacientes(codigoMed, factorAtenc, factorRes, pacAtend, pacRes);
    imprimirReporte(codigoMed, factorAtenc, factorRes, pacAtend, pacRes, numMed);
    return 0;
}
