/*
 * Archivo:      funciones.h
 * Autor:        Anthony Gutiérrez
 * Fecha y hora: 4 de junio de 2022, 03:53 PM
 */

#ifndef FUNCIONES_H
#define FUNCIONES_H

#include <stdio.h>
#include <stdlib.h>

void leerCursos(int *, double *, int *);

void leerAlumnos(int *, double *, double *, double *, int *);

void leerNotas(int *, double *, int *, int *, int, int *, int *, int *,
        double *, double *, double *, double *, double *, int);
int buscar(int *, int, int);

void ordenarAlumnos(int *, int *, int *, double *, double *, double *,
        double *, double *, double *, int);
double calcularPromPond(double, double);
void intercambiarInt(int *, int, int);
void intercambiarDouble(double *, int, int);

void imprimirReporte(int *, int *, int *, int, int *, int *, int *, double *,
        double *, double *, double *, double *, double *, int);
void imprimirNombreCurso(FILE *, int);
void imprimirAlumno(FILE *, int *, int *, int *, double *, double *, double *,
        double *, double *, double *, int, int *);
void buscarNombreAlumno(FILE *, int);
void imprimirApellidos(FILE *, char *, int, int *);
void imprimirNombres(FILE *, char *, int, int *);

FILE *abrirArchivo(const char *, const char *);
void imprimirLinea(FILE *, char);
void imprimirEspacios(FILE *, int);

#endif /* FUNCIONES_H */
