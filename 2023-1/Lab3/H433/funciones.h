/*
 * Archivo: funciones.h
 * Autor:   Anthony Gutiérrez
 * Fecha:   25 de abril de 2023, 07:21 PM
 */

#ifndef FUNCIONES_H
#define FUNCIONES_H

#include <iostream>
#include <fstream>
using namespace std;

void generarReporte(ifstream &, ifstream &, ofstream &);
int procesarDistrito(ifstream &, ofstream &, int, char, int, int);
int procesarPeliculas(ifstream &, ofstream &, char, int, int);
void procesarNombrePelicula(ifstream &, ofstream &, char &, int &);
char ignorarNombrePelicula(ifstream &);

// Funciones auxiliares
void imprimirLinea(ofstream &, char);
int leerHora(ifstream &);
void imprimirHora(ofstream &, int);
char procesarNombre(ifstream &, ofstream &);

#endif /* FUNCIONES_H */
