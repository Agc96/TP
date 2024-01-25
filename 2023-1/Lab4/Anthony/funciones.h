/*
 * Archivo: funciones.h
 * Autor:   Anthony Gutiérrez
 * Fecha:   9 de mayo de 2023, 07:57 PM
 */

#ifndef FUNCIONES_H
#define FUNCIONES_H

#include <iostream>
#include <fstream>
using namespace std;

void leerLibros(int *, double *, int &);
void leerAutores(int *, int *, double *, int &);
void leerFechas(int &, int &);
int leerFecha(istream &);
void procesarVentas(int *, double *, int *, double *, int, int *, int *,
        double *, double *, int, int, int);
int buscarLibro(int *, int, int);
void imprimirReporte(int *, double *, int *, double *, int, int *, int *,
        double *, double *, int, int, int);
void imprimirFecha(ofstream &, int);
void imprimirLinea(ofstream &, char);

#endif /* FUNCIONES_H */
