/*
 * Archivo: funciones.h
 * Autor:   Anthony Gutiérrez
 *
 * Creado el 24 de noviembre de 2020, 08:58 AM
 */

#ifndef FUNCIONES_H
#define FUNCIONES_H

#include <stdio.h>
#include <stdlib.h>

/* Parte 1: Leer cursos */

void leerCursos(char **, char **, double *, char **, int *);
void ordenarCursos(char **, char **, double *, char **, int);

/* Parte 2: Leer alumnos */

void leerAlumnos(int *, char **, int *);
void ordenarAlumnos(int *, char **, int);

/* Parte 3: Leer notas */

void leerNotas(int *, double *, double *, double *, double *, int,
        char **, double *, int *, int *, int);
int buscarCurso(char**, char *, int);
int buscarAlumno(int *, int, int);

/* Parte 4: Imprimir reporte */

void imprimirReporte(int *, char **, double *, double *, double *, double *, int,
        char **, char **, double *, char **, int *, int *, int);
void imprimirAlumnos(FILE *, int *, char **, double *, double *, double *, double *, int);
void imprimirCursos(FILE *, char **, char **, double *, char **, int *, int *, int);
void liberarEspacios(char **, char **, char **, int, char **, int);

/* Funciones auxiliares */

FILE *abrirArchivo(const char *, const char *);
char *crearCadenaExacta(char *);
void intercambiarEntero(int *, int, int);
void intercambiarDouble(double *, int, int);
void intercambiarCadena(char **, int, int);
void separacion(char, FILE *);

#endif /* FUNCIONES_H */
