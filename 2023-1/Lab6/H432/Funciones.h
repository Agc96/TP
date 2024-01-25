/*
 * Archivo: Funciones.h
 * Autor:   Anthony Gutiérrez
 * Fecha:   19 de junio de 2023, 12:22 PM
 */

#ifndef FUNCIONES_H
#define FUNCIONES_H

#include <iostream>
#include <fstream>
#include "Libro.h"
#include "Usuario.h"
#include "Solicitud.h"
using namespace std;

void leerDatos(Libro *, int &, Usuario *, int &, Solicitud *, int &);
void leerLibros(Libro *, int &);
void leerUsuarios(Usuario *, int &);
void leerSolicitudes(Solicitud *, int &);

void imprimirReporte(Libro *, int, Usuario *, int, Solicitud *, int,
        const char *);
void imprimirLibros(ofstream &, Libro *, int);
void imprimirUsuarios(ofstream &, Usuario *, int);
void imprimirSolicitudes(ofstream &, Solicitud *, int);

void ordenarUsuarios(Usuario *, int);

void atenderSolicitudes(Libro *, int, Usuario *, int, Solicitud *, int);
int obtenerMaxPrestamos(char);
int buscarLibro(Libro *, const char *, int);
void agregarSolicitudDenegada(ofstream &, Usuario &, Solicitud &, bool &);

/* Funciones auxiliares */
void abrirArchivoEntrada(ifstream &, const char *);
void abrirArchivoSalida(ofstream &, const char *);
void imprimirLinea(ofstream &, char);

#endif /* FUNCIONES_H */

