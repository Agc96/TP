/*
 * Archivo:      main.c
 * Autor:        Anthony Gutiérrez
 * Fecha y hora: 28 de junio de 2022, 07:54 AM
 */

#include "funciones.h"

int main() {
    leerAutores();
    imprimirAutores();
    leerLibros();
    imprimirLibros();
    actualizar();
    imprimirAutores();
    imprimirLibros();
    ordenar();
    imprimirReporte();
    return 0;
}
