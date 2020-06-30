/* 
 * Archivo: funciones.h
 * Autor:   Anthony Gutiérrez
 */

#ifndef FUNCIONES_H
#define FUNCIONES_H

#include <stdio.h>
#include <stdlib.h>
#include "requisito.h"
#include "curso.h"

/* Parte 1: Leer la lista de cursos */

int leerDatos(struct Curso[]);
void analizarCurso(char*, struct Curso*);

/* Parte 2: Ordenar el arreglo de cursos */

void ordenarDatos(struct Curso[], int);
void intercambiarCurso(struct Curso[], int, int);

/* Parte 3: Imprimir el reporte */

void imprimirReporte(struct Curso[], int, int);
void imprimirCurso(FILE*, struct Curso*);

/* Parte 4: Liberar los espacios dinámicos */

void liberarDatos(struct Curso[], int);

/* Funciones auxiliares */

FILE* abrirArchivo(const char*, const char*);
void leerCadena(char*, int, FILE*);
int separarPalabras(char*, char**, char);
void separacion(FILE*, char);

#endif /* FUNCIONES_H */
