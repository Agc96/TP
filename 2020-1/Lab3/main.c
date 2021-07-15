/* 
 * Archivo: main.c
 * Autor:   Anthony Gutiérrez
 */

#include "funciones.h"

int main() {
    /* Abrir los archivos */
    FILE *archAutores = abrirArchivo("Autores.bin", "wb+");
    FILE *archLibros = abrirArchivo("Libros.bin", "wb+");
    FILE* archReporte = abrirArchivo("Autores.txt", "w");
    /* Crear el archivo binario de autores */
    leerAutores(archAutores);
    imprimirAutores(archReporte, archAutores, 0);
    fclose(archReporte);
    /* Crear el archivo binario de libros */
    archReporte = abrirArchivo("Libros.txt", "w");
    leerLibros(archLibros);
    imprimirLibros(archReporte, archLibros, 0);
    fclose(archReporte);
    /* Actualizar los archivos binarios */
    archReporte = abrirArchivo("Reporte.txt", "w");
    leerVentas(archAutores, archLibros);
    imprimirReporte(archReporte, archAutores, archLibros);
    return 0;
}
