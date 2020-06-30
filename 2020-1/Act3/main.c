/* 
 * Archivo: main.c
 * Autor:   Anthony Gutiérrez
 *
 * Creado el 12 de mayo de 2020, 10:24 AM
 */

#include "funciones.h"

int main() {
    // Abrir archivos
    FILE* archPrecipit = abrirArchivo("Precipitaciones.txt", "r");
    FILE* archRegiones = abrirArchivo("Regiones.txt", "r");
    FILE* archRangos = abrirArchivo("RangosHoras.txt", "r");
    FILE* archReporte = abrirArchivo("Reporte.txt", "w");
    // Cerrar archivos
    fclose(archPrecipit);
    fclose(archRegiones);
    fclose(archRangos);
    fclose(archReporte);
    return 0;
}
