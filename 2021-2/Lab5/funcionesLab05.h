/*
 * File:   funcionesLab05.h
 * Author: Anthony Gutiérrez
 *
 * Created on 16 de noviembre de 2021, 08:07 AM
 */

#ifndef FUNCIONESLAB05_H
#define FUNCIONESLAB05_H

void leerEscalas(char **, double *, int *);

void leerCursos(char **, char **, double *, int *);

void procesarMatricula(char **, double *, double *, int, char **, char **,
        double *, double *, int);
int buscarCadena(char **, int , char *);

void ordenarEscalas(char **, double *, double *, int);
void intercambiarCadena(char **, int, int);
void intercambiarDouble(double *, int, int);

void ordenarCursos(char **, char **, double *, double *, int);
int evaluarCadenas(const char *, const char *);

void imprimirReporte(char **, double *, double *, int, char **, char **,
        double *, double *, int);
void imprimirLinea(FILE *, char);

#endif /* FUNCIONESLAB05_H */
