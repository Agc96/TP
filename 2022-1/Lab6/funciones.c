/*
 * Archivo:      funciones.c
 * Autor:        Anthony Gutiérrez
 * Fecha y hora: 28 de junio de 2022, 08:01 AM
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Autor.h"
#include "Libro.h"
#include "funciones.h"
#include "funcionesCadenas.h"

#define MAX_LIN_AUT 50
#define MAX_LIN_LIBRO 150
#define MAX_LIN_REPORTE 130
#define NO_ENCONTRADO -1

void leerAutores() {
    FILE *archTxt = abrirArchivo("Autores.csv", "r");
    FILE *archBin = abrirArchivo("Autores.bin", "wb");
    char linea[MAX_LIN_AUT], *palabras[2];
    int numPal;
    struct Autor autor;
    // Inicializar autor
    autor.cantLibros = 0;
    autor.monto = 0;
    // Leer línea por línea
    while (1) {
        leerCadena(linea, MAX_LIN_AUT, archTxt);
        if (feof(archTxt)) break;
        sacaPalabras(linea, palabras, &numPal, ',');
        // Guardar en el archivo binario
        strcpy(autor.codigo, palabras[0]);
        strcpy(autor.nombre, palabras[1]);
        fwrite(&autor, sizeof(struct Autor), 1, archBin);
        // Liberar espacios de memoria
        for (int i = 0; i < numPal; i++)
            free(palabras[i]);
    }
    // Cerrar archivos
    fclose(archBin);
    fclose(archTxt);
}

void imprimirAutores() {
    FILE *archBin = abrirArchivo("Autores.bin", "rb");
    FILE *archTxt = abrirArchivo("Autores.txt", "w");
    struct Autor autor;
    // Imprimir cabecera
    fprintf(archTxt, "%-10s %-40s %-10s %s\n", "Codigo", "Nombre", "Cantidad",
            "Monto");
    imprimirLinea(archTxt, '=', 70);
    // Imprimir listado
    while (1) {
        fread(&autor, sizeof(struct Autor), 1, archBin);
        if (feof(archBin)) break;
        fprintf(archTxt, "%-10s %-40s %8d %9.2lf\n", autor.codigo, autor.nombre,
                autor.cantLibros, autor.monto);
    }
    // Cerrar archivos
    fclose(archTxt);
    fclose(archBin);
}

void leerLibros() {
    FILE *archTxt = abrirArchivo("Libros.csv", "r");
    FILE *archBin = abrirArchivo("Libros.bin", "wb");
    char linea[MAX_LIN_LIBRO], *palabras[30];
    int numPal;
    struct Libro libro;
    // Inicializar libro
    libro.totRecaudado = 0;
    libro.totSinRegalias = 0;
    // Leer línea por línea
    while (1) {
        leerCadena(linea, MAX_LIN_LIBRO, archTxt);
        if (feof(archTxt)) break;
        sacaPalabras(linea, palabras, &numPal, ',');
        // Guardar en el archivo binario
        strcpy(libro.codigo, palabras[0]);
        strcpy(libro.nombre, palabras[1]);
        libro.precio = atof(palabras[2]);
        libro.cantAutores = (numPal-4)/2;
        for (int i = 0; i < libro.cantAutores; i++) {
            strcpy(libro.autores[i].codigo, palabras[2*i+3]);
            libro.autores[i].porcRegalias = atof(palabras[2*i+4]);
            libro.autores[i].montoRegalias = 0;
            libro.autores[i].montoSinRegalias = 0;
        }
        libro.cantLibros = atoi(palabras[numPal-1]);
        fwrite(&libro, sizeof(struct Libro), 1, archBin);
        // Liberar espacios de memoria
        for (int i = 0; i < numPal; i++)
            free(palabras[i]);
    }
    // Cerrar archivos
    fclose(archBin);
    fclose(archTxt);
}

void imprimirLibros() {
    FILE *archBin = abrirArchivo("Libros.bin", "rb");
    FILE *archTxt = abrirArchivo("Libros.txt", "w");
    struct Libro libro;
    // Imprimir listado de libros
    while (1) {
        fread(&libro, sizeof(struct Libro), 1, archBin);
        if (feof(archBin)) break;
        // Imprimir datos del libro
        fprintf(archTxt, "%-10s %-60s %6s %10s %10s %15s\n", "Codigo", "Nombre",
                "Precio", "Cantidad", "Recaudado", "Sin regalías");
        fprintf(archTxt, "%-10s %-60s %6.2lf %10d %10.2lf %14.2lf\n", libro.codigo,
                libro.nombre, libro.precio, libro.cantLibros, libro.totRecaudado,
                libro.totSinRegalias);
        imprimirLinea(archTxt, '-', 120);
        // Imprimir datos de los autores
        fprintf(archTxt, "%-10s %10s %15s %20s\n", "Autor", "% regalias",
                "Monto regalias", "Monto sin regalias");
        for (int i = 0; i < libro.cantAutores; i++) {
            fprintf(archTxt, "%-10s %10.2lf %15.2lf %20.2lf\n", libro.autores[i].codigo,
                    libro.autores[i].porcRegalias, libro.autores[i].montoRegalias,
                    libro.autores[i].montoSinRegalias);
        }
        imprimirLinea(archTxt, '=', 120);
    }
    // Cerrar archivos
    fclose(archTxt);
    fclose(archBin);
}

void actualizar() {
    FILE *archLibros = abrirArchivo("Libros.bin", "rb+");
    FILE *archAutores = abrirArchivo("Autores.bin", "rb+");
    int numRegLibros, numRegAutores;
    struct Libro libro;
    // Obtener números de registros
    numRegLibros = obtenerNumReg(archLibros, sizeof(struct Libro));
    numRegAutores = obtenerNumReg(archAutores, sizeof(struct Autor));
    // Actualizar datos libro por libro
    for (int i = 0; i < numRegLibros; i++) {
        fseek(archLibros, i*sizeof(struct Libro), SEEK_SET);
        fread(&libro, sizeof(struct Libro), 1, archLibros);
        // Actualizar datos del libro
        actualizarLibro(archAutores, numRegAutores, &libro);
        // Escribir datos del libro
        fseek(archLibros, i*sizeof(struct Libro), SEEK_SET);
        fwrite(&libro, sizeof(struct Libro), 1, archLibros);
    }
    fclose(archAutores);
    fclose(archLibros);
}

void actualizarLibro(FILE *archAutores, int numRegAutores, struct Libro *libro) {
    double totRegalias = 0;
    int posAutor;
    struct Autor autor;
    libro->totRecaudado = libro->precio * libro->cantLibros;
    for (int j = 0; j < libro->cantAutores; j++) {
        // Calcular datos de los autores
        libro->autores[j].montoRegalias = libro->autores[j].porcRegalias
                * libro->totRecaudado / 100;
        libro->autores[j].montoSinRegalias = libro->totRecaudado
                - libro->autores[j].montoRegalias;
        totRegalias += libro->autores[j].montoRegalias;
        // Actualizar datos de los autores
        posAutor = buscarAutor(archAutores, &autor, libro->autores[j].codigo,
                numRegAutores);
        if (posAutor != NO_ENCONTRADO) {
            autor.cantLibros += libro->cantLibros;
            autor.monto += libro->autores[j].montoRegalias;
            // Escribir datos de los autores
            fseek(archAutores, posAutor*sizeof(struct Autor), SEEK_SET);
            fwrite(&autor, sizeof(struct Autor), 1, archAutores);
        }
    }
    libro->totSinRegalias = libro->totRecaudado - totRegalias;
}

int buscarAutor(FILE *arch, struct Autor *autor, char *codigo, int numReg) {
    fseek(arch, 0, SEEK_SET);
    for (int i = 0; i < numReg; i++) {
        fread(autor, sizeof(struct Autor), 1, arch);
        if (strcmp(autor->codigo, codigo) == 0) return i;
    }
    return NO_ENCONTRADO;
}

void ordenar() {
    FILE *arch = fopen("Libros.bin", "rb+");
    int numReg = obtenerNumReg(arch, sizeof(struct Libro));
    struct Libro libroI, libroJ;
    for (int i = 0; i < numReg-1; i++) {
        for (int j = i+1; j < numReg; j++) {
            // Leer y evaluar las estructuras
            fseek(arch, i*sizeof(struct Libro), SEEK_SET);
            fread(&libroI, sizeof(struct Libro), 1, arch);
            fseek(arch, j*sizeof(struct Libro), SEEK_SET);
            fread(&libroJ, sizeof(struct Libro), 1, arch);
            if (libroI.cantLibros > libroJ.cantLibros ||
                    (libroI.cantLibros == libroJ.cantLibros &&
                    strcmp(libroI.nombre, libroJ.nombre) < 0)) {
                // Intercambiar las estructuras de ser necesario
                fseek(arch, j*sizeof(struct Libro), SEEK_SET);
                fwrite(&libroI, sizeof(struct Libro), 1, arch);
                fseek(arch, i*sizeof(struct Libro), SEEK_SET);
                fwrite(&libroJ, sizeof(struct Libro), 1, arch);
            }
        }
    }
    fclose(arch);
}

void imprimirReporte() {
    FILE *archReporte = fopen("Recaudacion.txt", "w");
    // Reporte de libros
    fprintf(archReporte, "%80s\n", "RECAUDACION POR LIBROS VENDIDOS");
    imprimirLinea(archReporte, '=', MAX_LIN_REPORTE);
    imprimirReporteLibros(archReporte);
    // Reporte de autores
    fprintf(archReporte, "%75s\n", "REGALIAS POR AUTORES");
    imprimirLinea(archReporte, '=', MAX_LIN_REPORTE);
    imprimirReporteAutores(archReporte);
    fclose(archReporte);
}

void imprimirReporteLibros(FILE *archReporte) {
    FILE *archLibros = fopen("Libros.bin", "rb");
    FILE *archAutores = fopen("Autores.bin", "rb");
    double totRecaudado = 0, totSinRegalias = 0;
    int numRegAutores, totLibros = 0;
    struct Libro libro;
    // Obtener número de registros de autores para la búsqueda
    numRegAutores = obtenerNumReg(archAutores, sizeof(struct Autor));
    // Imprimir libro por libro
    while (1) {
        fread(&libro, sizeof(struct Libro), 1, archLibros);
        if (feof(archLibros)) break;
        // Imprimir datos principales del libro y listado de autores
        imprimirDatosLibro(archReporte, &libro);
        imprimirAutoresLibro(archReporte, &libro, archAutores, numRegAutores);
        // Actualizar los contadores
        totLibros += libro.cantLibros;
        totRecaudado += libro.totRecaudado;
        totSinRegalias += libro.totSinRegalias;
    }
    // Imprimir resumen de libros
    fprintf(archReporte, "Total de libros vendidos: %9d\n", totLibros);
    fprintf(archReporte, "Total recaudado: S/ %15.2lf\n", totRecaudado);
    fprintf(archReporte, "Total sin regalias: S/ %12.2lf\n", totSinRegalias);
    imprimirLinea(archReporte, '=', MAX_LIN_REPORTE);
    // Cerrar los archivos
    fclose(archAutores);
    fclose(archLibros);
}

void imprimirDatosLibro(FILE *archReporte, struct Libro *libro) {
        // Imprimir cabecera del libro
    fprintf(archReporte, "%-10s%-60s%15s%18s%20s\n", "CODIGO", "NOMBRE",
                "LIBROS VENDIDOS", "TOTAL RECAUDADO", "TOTAL SIN REGALIAS");
    imprimirLinea(archReporte, '-', MAX_LIN_REPORTE);
    // Imprimir datos del libro
    fprintf(archReporte, "%-10s%-60s%15d%18.2lf%20.2lf\n", libro->codigo,
            libro->nombre, libro->cantLibros, libro->totRecaudado,
            libro->totSinRegalias);
    imprimirLinea(archReporte, '-', MAX_LIN_REPORTE);
}

void imprimirAutoresLibro(FILE *archReporte, struct Libro *libro,
        FILE *archAutores, int numRegAutores) {
    struct Autor autor;
    // Imprimir cabecera de autores
    fprintf(archReporte, "Autores:\n");
    imprimirLinea(archReporte, '-', MAX_LIN_REPORTE);
    fprintf(archReporte, "%-10s%-40s%22s\n", "CODIGO", "NOMBRE", "REGALIAS POR EL LIBRO");
    imprimirLinea(archReporte, '-', MAX_LIN_REPORTE);
    // Imprimir listado de autores
    for (int i = 0; i < libro->cantAutores; i++) {
        int posAutor = buscarAutor(archAutores, &autor, libro->autores[i].codigo,
                numRegAutores);
        if (posAutor != NO_ENCONTRADO) {
            fprintf(archReporte, "%-10s%-40s%22.2lf\n", libro->autores[i].codigo,
                    autor.nombre, libro->autores[i].montoRegalias);
        }
    }
    imprimirLinea(archReporte, '=', MAX_LIN_REPORTE);
}

void imprimirReporteAutores(FILE *archReporte) {
    FILE *archAutores = fopen("Autores.bin", "rb");
    struct Autor autor;
    double totRegalias = 0;
    fprintf(archReporte, "%-10s%-40s%25s%10s\n", "CODIGO", "NOMBRE",
            "TOTAL DE LIBROS VENDIDOS", "REGALIAS");
    imprimirLinea(archReporte, '-', MAX_LIN_REPORTE);
    while (1) {
        fread(&autor, sizeof(struct Autor), 1, archAutores);
        if (feof(archAutores)) break;
        fprintf(archReporte, "%-10s%-40s%15d%20.2lf\n", autor.codigo, autor.nombre,
                autor.cantLibros, autor.monto);
        totRegalias += autor.monto;
    }
    imprimirLinea(archReporte, '-', MAX_LIN_REPORTE);
    fprintf(archReporte, "Total a pagar por regalias: S/ %.2lf\n", totRegalias);
    imprimirLinea(archReporte, '=', MAX_LIN_REPORTE);
    fclose(archAutores);
}

/* Funciones auxiliares */

int obtenerNumReg(FILE *archBin, int tamReg) {
    fseek(archBin, 0, SEEK_END);
    int tamArch = ftell(archBin);
    fseek(archBin, 0, SEEK_SET);
    return tamArch/tamReg;
}

void imprimirLinea(FILE *arch, char car, int cant) {
    for (int i = 0; i < cant; i++) {
        fputc(car, arch);
    }
    fputc('\n', arch);
}
