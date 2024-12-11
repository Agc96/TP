/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * Archivo: funciones.h
 * Autor:   Anthony Gutiérrez
 * Fecha:   1 de junio de 2024, 03:38 PM
 */

#ifndef FUNCIONES_H
#define FUNCIONES_H

int leerCodigoFacultad();
void leerCalificaciones(ifstream &, int *, int *, double *, double *, int &);
int busquedaBinaria(int *, int, int);
void insertarOrdenado(int *, int *, double *, double *, int, int, double, int);
void emitirReporte(ifstream &, ifstream &, ofstream &, int *, int *, double *,
        double *, int, int);
void imprimirCabecera(ifstream &, ofstream &, int);
void arreglarNomAlumno(char *, char *);

void abrirArchivoEntrada(ifstream &, const char *);
void abrirArchivoSalida(ofstream &, const char *);
void imprimirLinea(ofstream &, char);

#endif /* FUNCIONES_H */
