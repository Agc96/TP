/* 
 * Archivo: funciones.h
 * Autor:   Anthony Gutiérrez
 *
 * Creado el 28 de septiembre de 2020, 07:05 PM
 */

#ifndef FUNCIONES_H
#define FUNCIONES_H

#include <stdio.h>
#include <stdlib.h>

void generarReporte(FILE*, FILE*);
void imprimirCabeceraAlumno(FILE*, int, int, int, int, double, double);
void buscarCursos(FILE*, int, int, double, double, int*);
void buscarNotaCurso(FILE*, int, int, int, int*, int*, double*, double*, int*, double*, double*, double*);
void agregarNota(FILE*, int, double, double, int, int*, double*, double*, double*);
void imprimirResumenAlumno(FILE*, double, double, int, double, double, int, double, double, double, int*);
void imprimirResumenAlumnoFacultad(FILE*, int, double, double);
void imprimirResumenReporte(FILE*, int, int);

/* Funciones auxiliares */
FILE* abrirArchivo(const char*, const char*);
void separacion(FILE*, char);

#endif /* FUNCIONES_H */
