/*
 * Archivo: funciones.h
 * Autor:   Anthony Gutiérrez
 *
 * Creado el 4 de mayo de 2021, 08:08 AM
 */

#ifndef FUNCIONES_H
#define FUNCIONES_H

#include <stdio.h>
#include <stdlib.h>

void generarReporte(FILE*);
void imprimirCabeceraReporte(FILE*);
int obtenerNumAlumnos(int, int);
int validarAlumno(int, int, int, int, int, int, int);
void imprimirCabeceraCurso(FILE*, FILE*, int, int, int, double);
void imprimirNombreCurso(FILE*, FILE*);
void leerRelacionAlumnos(FILE*, int, int, double*, int*);
void imprimirCabeceraAlumnos(FILE*);
void actualizarContadores(int, int*, int*, int*, int*);
void imprimirResumenCurso(FILE*, int, int, int, int, int, double*, int*);
void imprimirResumenReporte(FILE*, int, double, int);

/* Funciones auxiliares */

FILE* abrirArchivo(const char*, const char*);
void imprimirLinea(FILE*, char, int);
void ignorarLinea(FILE*);

#endif /* FUNCIONES_H */
