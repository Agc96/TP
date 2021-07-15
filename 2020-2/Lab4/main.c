/*
 * Archivo: main.c
 * Autor:   Anthony Gutiérrez
 *
 * Creado el 3 de noviembre de 2020, 08:02 AM
 */

#include "funciones.h"
#define MAX_SALA 10
#define MAX_PELI 20

int main() {
    // Declaración de variables
    int arrCodSala[MAX_SALA], arrButSala[MAX_SALA], arrCodPeli[MAX_PELI],
            arrFuncProg[MAX_PELI] = {0}, arrButDisp[MAX_PELI] = {0},
            arrButVend[MAX_PELI] = {0}, arrButOcup[MAX_PELI] = {0};
    double arrRecauda[MAX_PELI] = {0.0}, arrPorcOcup[MAX_PELI] = {0.0};
    // Leer los archivos y guardar los datos en los arreglos
    int numSalas = leerSalas(arrCodSala, arrButSala);
    int numPelis = leerPeliculas(arrCodSala, arrButSala, numSalas, arrCodPeli,
            arrFuncProg, arrButDisp);
    leerVentas(arrCodPeli, arrButVend, arrRecauda, arrButOcup, numPelis);
    // Ordenar los datos de los arreglos
    ordenarDatos(arrCodPeli, arrFuncProg, arrButDisp, arrButVend, arrRecauda,
            arrButOcup, numPelis);
    // Imprimir el reporte
    imprimirReporte(arrCodPeli, arrFuncProg, arrButDisp, arrButVend, arrRecauda,
            arrButOcup, arrPorcOcup, numPelis);
    return 0;
}
