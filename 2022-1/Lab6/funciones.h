/*
 * Archivo:      funciones.h
 * Autor:        Anthony Gutiérrez
 * Fecha y hora: 28 de junio de 2022, 08:00 AM
 */

#ifndef FUNCIONES_H
#define FUNCIONES_H

#include <stdio.h>
#include <stdlib.h>
#include "Autor.h"
#include "Libro.h"

void leerAutores();
void imprimirAutores();

void leerLibros();
void imprimirLibros();

void actualizar();
void actualizarLibro(FILE *, int, struct Libro *);
int buscarAutor(FILE *, struct Autor *, char *, int);

void ordenar();
void intercambiar();

void imprimirReporte();
void imprimirReporteLibros(FILE *);
void imprimirDatosLibro(FILE *, struct Libro *);
void imprimirAutoresLibro(FILE *, struct Libro *, FILE *, int);
void imprimirReporteAutores(FILE *);

// Funciones auxiliares
int obtenerNumReg(FILE *, int);
void imprimirLinea(FILE *, char, int);

#endif /* FUNCIONES_H */
