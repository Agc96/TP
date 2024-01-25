/*
 * File:   funciones.h
 * Author: Anthony Gutiérrez
 *
 * Created on 2 de noviembre de 2021, 08:37 AM
 */

#ifndef FUNCIONES_H
#define FUNCIONES_H

#include <stdio.h>
#include <stdlib.h>

int leerProductos(int *, int *, double *);
int leerPedidos(int *, int *, int *, int *);
int leerDetalles(int *, int *, int *);
void ordenarProductos(int *, int *, double *, int);
void ordenarPedidos(int *, int *, int *, int *, int);
void imprimirReporte(int *, int *, double *, int, int *, int *, int *, int *,
        int, int *, int *, int *, int);
void imprimirCabeceraPedido(FILE *, int *, int *, int *, int *, int i);
void imprimirNombreCliente(FILE *, int);
void modificarNombre(const char *, char *);
double imprimirDetallesPedido(FILE *, int *, int *, double *, int, int, int *,
        int *, int *, int);

/* Funciones auxiliares */
FILE *abrirArchivo(const char *, const char *);
void intercambiarInt(int *, int, int);
void intercambiarDouble(double *, int, int);
int busquedaSecuencial(int *, int, int);
int busquedaBinaria(int *, int, int);
void imprimirLinea(FILE *, char);

#endif /* FUNCIONES_H */
