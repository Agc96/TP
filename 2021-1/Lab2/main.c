/*
 * Archivo: main.c
 * Autor:   Anthony Gutiérrez
 *
 * Creado el 4 de mayo de 2021, 08:06 AM
 */

#include "funciones.h"

int main() {
    FILE* archRep = abrirArchivo("Reporte.txt", "w");
    generarReporte(archRep);
    fclose(archRep);
    return 0;
}
