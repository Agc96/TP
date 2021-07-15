/*
 * Archivo: funciones.h
 * Autor:   Anthony Gutiérrez
 *
 * Creado el 26 de mayo de 2021, 04:40 PM
 */

#ifndef FUNCIONES_H
#define FUNCIONES_H

#include <stdio.h>
#include <stdlib.h>

/* Reporte de productos perdidos */
void llenarProd(int*, double*, int*);
void llenarAlmac(int*, double*, int, int*, double*, double*, double*, int*);
void ordenarAlmac(int*, double*, double*, double*, int);
void reporteProd(FILE*, int*, double*, double*, double*, int);

/* Reporte de platos que no se podrán preparar */
void llenarPlatPrep(int*, int*, int*);
void llenarPrecPlat(int*, int*, double*, double*, int, int*, double*, int,
        int*, int);
void calcularSubPlat(FILE*, int*, double*, double*, int, int*, double*, int,
        int*, int);
void ordenarPlatos(int*, int*, double*, double*, int);
void reportePlatos(FILE*, int*, int*, double*, double*, int);

/* Funciones auxiliares */
FILE* abrirArchivo(const char*, const char*);
int buscarEnArreglo(int*, int, int);
void intercambiarInt(int*, int, int);
void intercambiarDouble(double*, int, int);
void imprimirLinea(FILE*, char);

#endif /* FUNCIONES_H */
