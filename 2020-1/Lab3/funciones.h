/* 
 * Archivo: funciones.h
 * Autor:   Anthony Gutiérrez
 */

#ifndef FUNCIONES_H
#define FUNCIONES_H

#include <stdio.h>
#include "autor.h"
#include "libro.h"

#define MAX_LINEA 150
#define MAX_PALABRAS 30
#define MAX_SEPARACION 120

/* Crear el archivo binario de autores */
void leerAutores(FILE*);
void colocarAutor(struct Autor*, char**);
void imprimirAutores(FILE*, FILE*, int);

/* Crear el archivo binario de libros */
void leerLibros(FILE*);
void colocarLibro(struct Libro*, char**, int);
void imprimirLibros(FILE*, FILE*, int);
void imprimirLibro(FILE*, struct Libro*, int);

/* Actualizar los archivos binarios */
void leerVentas(FILE*, FILE*);
int buscarLibro(FILE*, char*);
void actualizarLibro(FILE*, FILE*, int, int);
int buscarAutor(FILE*, int);
void actualizarAutor(FILE*, int, int, double, double);

/* Imprimir el reporte */
void imprimirReporte(FILE*, FILE*, FILE*);

/* Funciones auxiliares */
FILE* abrirArchivo(const char*, const char*);
char* leerLinea(FILE*, char*, int);
int separarPalabras(char*, char**, char);
void liberarPalabras(char**, int);
int obtenerNumRegistros(FILE*, int);
void repetir(FILE*, char, int);

#endif /* FUNCIONES_H */
