/* 
 * Archivo: funciones.c
 * Autor:   Anthony Gutiérrez
 */

#include <stdio.h>
#include <stdlib.h> // atoi, atof
#include <string.h>
#include "autor.h"
#include "libro.h"
#include "funciones.h"

/* Actualizar los archivos binarios */

void leerVentas(FILE* archAutores, FILE* archLibros) {
    FILE* archVentas = abrirArchivo("Ventas.csv", "r");
    /* Leer línea por línea */
    char buffer[MAX_LINEA] = {'\0'}, *palabras[MAX_PALABRAS];
    int numPalabras, posLibro, cantidad;
    while (1) {
        leerLinea(archVentas, buffer, MAX_LINEA);
        if (feof(archVentas)) break;
        numPalabras = separarPalabras(buffer, palabras, ',');
        /* Buscar libro y actualizar si es que se encontró */
        cantidad = atoi(palabras[2]);
        posLibro = buscarLibro(archLibros, palabras[1]);
        if (posLibro >= 0) {
            actualizarLibro(archAutores, archLibros, posLibro, cantidad);
        }
        /* Liberar espacios de las palabras */
        liberarPalabras(palabras, numPalabras);
    }
    /* Cerrar los archivos */
    fclose(archVentas);
}

int buscarLibro(FILE* archLibros, char* codLibro) {
    /* Obtener la cantidad de libros y colocar el archivo al inicio */
    int cantLibros = obtenerNumRegistros(archLibros, sizeof(struct Libro));
    struct Libro libro;
    /* Buscar por el código del libro (cadena de caracteres) */
    for (int i = 0; i < cantLibros; i++) {
        fread(&libro, sizeof(struct Libro), 1, archLibros);
        if (strcmp(libro.codigo, codLibro) == 0) return i;
    }
    return -1;
}

void actualizarLibro(FILE* archAutores, FILE* archLibros, int posLibro, int cantidad) {
    struct Libro libro;
    /* Leer los datos del libro */
    fseek(archLibros, posLibro * sizeof(struct Libro), SEEK_SET);
    fread(&libro, sizeof(struct Libro), 1, archLibros);
    /* Actualizar los datos del libro */
    libro.cantVenta += cantidad;
    libro.totalVenta += libro.precio * cantidad;
    /* Guardar los datos del libro */
    fseek(archLibros, posLibro * sizeof(struct Libro), SEEK_SET);
    fwrite(&libro, sizeof(struct Libro), 1, archLibros);
    /* Actualizar los datos de los autores del libro */
    for (int i = 0; i < libro.cantAutores; i++) {
        int posAutor = buscarAutor(archAutores, libro.autores[i].codigo);
        if (posAutor >= 0) {
            actualizarAutor(archAutores, posAutor, cantidad, libro.precio,
                    libro.autores[i].regalias);
        }
    }
}

int buscarAutor(FILE* archAutores, int codAutor) {
    /* Obtener la cantidad de autores y colocar el archivo al inicio */
    int cantAutores = obtenerNumRegistros(archAutores, sizeof(struct Autor));
    struct Autor autor;
    /* Buscar por el código del autor (entero) */
    for (int i = 0; i < cantAutores; i++) {
        fread(&autor, sizeof(struct Autor), 1, archAutores);
        if (autor.codigo == codAutor) return i;
    }
    return -1;
}

void actualizarAutor(FILE* archAutores, int posAutor, int cantidad,
        double precio, double regalias) {
    /* Leer los datos del autor */
    struct Autor autor;
    fseek(archAutores, posAutor * sizeof(struct Autor), SEEK_SET);
    fread(&autor, sizeof(struct Autor), 1, archAutores);
    /* Actualizar los datos del autor */
    autor.cantLibros += cantidad;
    autor.regalias += cantidad * precio * regalias / 100;
    /* Guardar los datos del autor */
    fseek(archAutores, posAutor * sizeof(struct Autor), SEEK_SET);
    fwrite(&autor, sizeof(struct Autor), 1, archAutores);
}

/* Imprimir el reporte */

void imprimirReporte(FILE* archRep, FILE* archAutores, FILE* archLibros) {
    /* Imprimir cabecera */
    fprintf(archRep, "%72s\n", "Editorial LP1 Horario 0432");
    repetir(archRep, '=', MAX_SEPARACION);
    /* Imprimir lista de autores */
    fprintf(archRep, "PAGO A LOS AUTORES:\n");
    repetir(archRep, '-', MAX_SEPARACION);
    imprimirAutores(archRep, archAutores, 1);
    repetir(archRep, '=', MAX_SEPARACION);
    /* Imprimir lista de libros */
    fprintf(archRep, "RECAUDACION POR LIBROS VENDIDOS:\n");
    repetir(archRep, '-', MAX_SEPARACION);
    imprimirLibros(archRep, archLibros, 1);
    /* Cerrar los archivos */
    fclose(archAutores);
    fclose(archLibros);
    fclose(archRep);
}
