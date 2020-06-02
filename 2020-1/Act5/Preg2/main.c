/* 
 * Archivo: main.c
 * Autor:   Anthony Gutiérrez
 */

#include "funciones.h"
#define MAX_ARREGLO 50

int main() {
    int listaDni[MAX_ARREGLO], listaTelef[MAX_ARREGLO], cantDatos = 0;
    double listaSueldo[MAX_ARREGLO];
    ordenarDatos(listaDni, listaTelef, listaSueldo, &cantDatos);
    mostrarDatos(listaDni, listaTelef, listaSueldo, cantDatos);
    return 0;
}
