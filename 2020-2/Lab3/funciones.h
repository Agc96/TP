/*
 * Archivo: funciones.h
 * Autor:   Anthony Gutiérrez
 *
 * Creado el 13 de octubre de 2020, 07:50 AM
 */

#ifndef FUNCIONES_H
#define FUNCIONES_H

#include <stdio.h>
#include <stdlib.h>

/* Parte 1 */
int leerPacientes(int*, double*, double*, int*, int*);
void agregarMedico(int*, double*, double*, int*, int*, int*, char, double, int);

/* Parte 2 */
void imprimirReporte(int*, double*, double*, int*, int*, int);

/* Funciones auxiliares */
FILE* abrirArchivo(const char*, const char*);
void imprimirLinea(FILE*, char);

#endif /* FUNCIONES_H */

