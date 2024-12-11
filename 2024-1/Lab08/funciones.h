/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * Archivo: funciones.h
 * Autor:   Anthony Gutiérrez
 * Fecha:   15 de junio de 2024, 02:10 PM
 */

#ifndef FUNCIONES_H
#define FUNCIONES_H

void leerCalificaciones(struct Alumno *, int &);
int buscarAlumno(struct Alumno *, int, int);
void leerAlumnos(struct Alumno *, int);
void leerFacultades(struct Alumno *, int);
void emitirReporte(struct Alumno *, int);

void abrirArchivoEntrada(ifstream &, const char *);
void abrirArchivoSalida(ofstream &, const char *);
void imprimirLinea(ofstream &, char);

#endif /* FUNCIONES_H */

