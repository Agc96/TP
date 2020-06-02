/* 
 * Archivo: main.c
 * Autor:   Anthony Gutiérrez
 */

#include "funciones.h"
#define MAX_ARREGLO 50

int main() {
    int listaDni[MAX_ARREGLO], cantDatos = 0;
    ordenarDatos(listaDni, &cantDatos);
    mostrarDatos(listaDni, cantDatos);
    return 0;
}
