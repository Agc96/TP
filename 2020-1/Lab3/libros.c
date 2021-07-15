/* 
 * Archivo: libros.c
 * Autor:   Anthony Gutiérrez
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "libro.h"
#include "funciones.h"

void leerLibros(FILE* archBin) {
    FILE* archTexto = abrirArchivo("Libros.csv", "r");
    /* Leer línea por línea el archivo de texto */
    struct Libro libro;
    char buffer[MAX_LINEA] = {'\0'}, *palabras[MAX_PALABRAS];
    int numPalabras;
    while (1) {
        leerLinea(archTexto, buffer, MAX_LINEA);
        if (feof(archTexto)) break;
        numPalabras = separarPalabras(buffer, palabras, ',');
        /* Guardar datos del libro en el archivo binario */
        colocarLibro(&libro, palabras, numPalabras);
        fwrite(&libro, sizeof(struct Libro), 1, archBin);
        liberarPalabras(palabras, numPalabras);
    }
    /* Cerrar los archivos */
    fclose(archTexto);
}

void colocarLibro(struct Libro* libro, char** palabras, int numPalabras) {
    /* Colocar datos principales del libro */
    strcpy(libro->codigo, palabras[0]);
    strcpy(libro->titulo, palabras[1]);
    libro->precio = atof(palabras[2]);
    /* Colocar lista de autores */
    libro->cantAutores = (numPalabras-3) / 2;
    for (int i = 0; i < libro->cantAutores; i++) {
        libro->autores[i].codigo = atoi(palabras[2*i+3]);
        libro->autores[i].regalias = atof(palabras[2*i+4]);
    }
    /* Inicializar contadores y sumas en 0 */
    libro->cantVenta = 0;
    libro->totalVenta = 0;
}

void imprimirLibros(FILE* archRep, FILE* archBin, int esReporteFinal) {
    double totalRecaudado = 0;
    /* Imprimir la cabecera de los libros */
    fprintf(archRep, "%-8s  %-60s  %-8s  %-15s  %-15s\n", "CODIGO", "TITULO",
            "PRECIO", "LIBROS VENDIDOS", "TOTAL RECAUDADO");
    repetir(archRep, '-', MAX_SEPARACION);
    /* Imprimir todos los libros */
    int numRegistros = obtenerNumRegistros(archBin, sizeof(struct Libro));
    struct Libro libro;
    for (int i = 0; i < numRegistros; i++) {
        fread(&libro, sizeof(struct Libro), 1, archBin);
        imprimirLibro(archRep, &libro, esReporteFinal);
        totalRecaudado += libro.totalVenta;
    }
    /* Imprimir total recaudado para el reporte final */
    if (esReporteFinal) {
        repetir(archRep, '-', MAX_SEPARACION);
        fprintf(archRep, "Total recaudado: %.2lf\n", totalRecaudado);
    }
}

void imprimirLibro(FILE* archRep, struct Libro* libro, int esReporteFinal) {
    /* Imprimir datos principales del libro */
    fprintf(archRep, "%-8s  %-60s  %8.2lf  %15d  %15.2lf\n", libro->codigo,
            libro->titulo, libro->precio, libro->cantVenta, libro->totalVenta);
    /* Imprimir lista de autores en el reporte del libro */
    if (!esReporteFinal) {
        for (int j = 0; j < libro->cantAutores; j++) {
            fprintf(archRep, "  %06d  %8.2lf\n", libro->autores[j].codigo,
                    libro->autores[j].regalias);
        }
        repetir(archRep, '-', MAX_SEPARACION);
    }
}
