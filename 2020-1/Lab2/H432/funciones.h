/* 
 * Archivo: funciones.h
 * Autor:   Anthony Gutiérrez
 */

#ifndef FUNCIONES_H
#define FUNCIONES_H

#include <stdio.h>
#include <stdlib.h>
#include "curso.h"
#include "alumno.h"

/* Parte 1: Leer la lista de cursos */

int leerDatos(struct Alumno[]);
void analizarAlumno(char*, struct Alumno*);

/* Parte 2: Ordenar el arreglo de cursos */

void ordenarDatos(struct Alumno[], int);
void intercambiarAlumno(struct Alumno[], int, int);

/* Parte 3: Imprimir el reporte */

void imprimirReporte(struct Alumno[], int, int);
void imprimirAlumno(FILE*, struct Alumno*);

/* Parte 4: Liberar los espacios dinámicos */

void liberarDatos(struct Alumno[], int);

/* Funciones auxiliares */

FILE* abrirArchivo(const char*, const char*);
char* leerCadena(char*, int, FILE*);
int separarPalabras(char*, char**, char);
void separacion(FILE*, char);

#endif /* FUNCIONES_H */
