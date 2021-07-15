/* 
 * Archivo: autores.c
 * Autor:   Anthony Gutiérrez
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "autor.h"
#include "funciones.h"

void leerAutores(FILE* archBin) {
    FILE* archTexto = abrirArchivo("Autores.csv", "r");
    /* Leer línea por línea */
    struct Autor autor;
    char buffer[MAX_LINEA], *palabras[MAX_PALABRAS];
    int numPalabras;
    while (1) {
        leerLinea(archTexto, buffer, MAX_LINEA);
        if (feof(archTexto)) break;
        numPalabras = separarPalabras(buffer, palabras, ',');
        /* Guardar datos en el archivo binario */
        colocarAutor(&autor, palabras);
        fwrite(&autor, sizeof(struct Autor), 1, archBin);
        liberarPalabras(palabras, numPalabras);
    }
    /* Cerrar los archivos */
    fclose(archTexto);
}

void colocarAutor(struct Autor* autor, char** palabras) {
    autor->codigo = atoi(palabras[0]);
    strcpy(autor->nombre, palabras[1]);
    autor->cantLibros = 0;
    autor->regalias = 0;
}

void imprimirAutores(FILE* archRep, FILE* archBin, int esReporteFinal) {
    double totalRegalias = 0;
    /* Imprimir la cabecera */
    fprintf(archRep, "%-6s  %-40s  %-15s  %-8s\n", "CODIGO", "NOMBRE",
            "LIBROS VENDIDOS", "REGALIAS");
    repetir(archRep, '-', MAX_SEPARACION);
    /* Imprimir todos los registros */
    int numRegistros = obtenerNumRegistros(archBin, sizeof(struct Autor));
    struct Autor autor;
    for (int i = 0; i < numRegistros; i++) {
        fread(&autor, sizeof(struct Autor), 1, archBin);
        fprintf(archRep, "%06d  %-40s  %15d  %8.2lf\n", autor.codigo,
                autor.nombre, autor.cantLibros, autor.regalias);
        totalRegalias += autor.regalias;
    }
    /* Imprimir total de regalías para el reporte final */
    if (esReporteFinal) {
        repetir(archRep, '-', MAX_SEPARACION);
        fprintf(archRep, "Total a pagar por regalias: %.2lf\n", totalRegalias);
    }
}
