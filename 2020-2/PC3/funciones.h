/*
 * Archivo: funciones.h
 * Autor:   Anthony Gutiérrez
 *
 * Creado el 14 de noviembre de 2020, 10:15 PM
 */

#ifndef FUNCIONES_H
#define FUNCIONES_H

#include <stdio.h>
#include <stdlib.h>

void leerProductos(int *, int *, int *);

void leerMovimientos(int *, int *, int *, int *, int *, int *);
void reponerStock(int *, int *, int *, int *, int *, int *, int, int);
void atenderPedido(int *, int *, int *, int *, int *, int *, int, int);
int buscar(int *, int, int);

void ordenarArreglos(int *, int *, int);
void intercambiar(int *, int, int);

void imprimirReporte(int *, int *, int, int *, int *, int);
void imprimirProductos(FILE *, int *, int *, int);
void imprimirNombre(FILE *, int);
void separacion(FILE *, char);

#endif /* FUNCIONES_H */
