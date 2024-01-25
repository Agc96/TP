/*
 * Archivo: funciones.h
 * Autor:   Anthony Gutiérrez
 *
 * Creado el 12 de octubre de 2021, 08:01 AM
 */

#ifndef FUNCIONES_H
#define FUNCIONES_H

#include <stdio.h>
#include <stdlib.h>

void leerDistritos(int *, int *);
void leerPacientes(int *, int *, int *, int *);
void leerMedicos(int *, double *, int *);
void leerAtenciones(int *, int *, double *, int, int *, int *, int *, int *,
        int *, int *, double *, int, int *, double *, int);
int leerHora(FILE *);
void actualizarMedicoDistrito(int *, double *, int, int *, double *, int, int,
        int *, int *, double *, int, int);
int buscar(int *, int, int);
void ordenarDistritos(int *, int *, double *, int);
void intercambiarInt(int *, int, int);
void intercambiarDouble(double *, int, int);
void imprimirReporte(int *, int *, double *, int, int *, int *, int *, int *,
        int *, int *, double *, int);
void imprimirDistrito(FILE *, int);
void imprimirPacientes(FILE *, int, int, double, int *, int *, int *, int *,
        int *, int *, double *, int);
void imprimirFecha(FILE *, int);
void imprimirDuracion(FILE *, int);
/* Funciones auxiliares */
FILE *abrirArchivo(const char *, const char *);
void imprimirLinea(FILE *, char);

#endif /* FUNCIONES_H */
