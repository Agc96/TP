/*
 * Archivo: funciones.h
 * Autor:   Anthony Gutiérrez
 *
 * Creado el 25 de mayo de 2021, 10:26 AM
 */

#ifndef FUNCIONES_H
#define FUNCIONES_H

#include <stdio.h>
#include <stdlib.h>

void generarReporte(FILE*, FILE*, FILE*, FILE*);
void imprimirCabecera(FILE*, FILE*);
void colocarNombrePlato(FILE*, FILE*, int);
int buscarCantPreparar(FILE*, int);
void colocarDetallesPlato(FILE*, FILE*, FILE*, int, double*);
double buscarPrecioProducto(FILE*, int);
void cerrarArchivos(FILE*, FILE*, FILE*, FILE*);

/* Funciones auxiliares */
FILE* abrirArchivo(const char*, const char*);
void imprimirLinea(FILE*, char);

#endif /* FUNCIONES_H */
