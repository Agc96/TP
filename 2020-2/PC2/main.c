/* 
 * Archivo: main.c
 * Autor:   Anthony Gutiérrez
 *
 * Creado el 28 de septiembre de 2020, 06:59 PM
 */

#include "funciones.h"

int main() {
    FILE* archAlumnos = abrirArchivo("Alumnos.txt", "r");
    FILE* archReporte = abrirArchivo("Reporte.txt", "w");
    generarReporte(archAlumnos, archReporte);
    fclose(archAlumnos);
    fclose(archReporte);
    return 0;
}
