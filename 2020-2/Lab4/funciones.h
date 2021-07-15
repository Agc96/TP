/*
 * Archivo: funciones.h
 * Autor:   Anthony Gutiérrez
 *
 * Creado el 3 de noviembre de 2020, 08:05 AM
 */

#ifndef FUNCIONES_H
#define FUNCIONES_H

#include <stdio.h>
#include <stdlib.h>

/* Lectura de las salas */

int leerSalas(int*, int*);

/* Lectura de las películas */

int leerPeliculas(int*, int*, int, int*, int*, int*);
int leerCantDias(FILE*);
int buscarSala(int*, int, int);

/* Lectura de las ventas */

void leerVentas(int*, int*, double*, int*, int);
int buscarPelicula(int*, int, int);

/* Ordenamiento de datos */

void ordenarDatos(int*, int*, int*, int*, double*, int*, int);
void intercambiarInt(int*, int, int);
void intercambiarDouble(double*, int, int);

/* Impresión del reporte */

void imprimirReporte(int*, int*, int*, int*, double*, int*, double*, int);
void imprimirCabeceraRep(FILE*);
void imprimirResumenRep(FILE*, int, double, double, int*, int*, double*,
        double*, int, int);
void imprimirPeliEstad(FILE*, int, int, double, double);
void separacion(FILE*, char);

#endif /* FUNCIONES_H */
