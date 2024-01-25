/*
 * Archivo: funciones.h
 * Autor:   Anthony Gutiérrez
 * Fecha:   11 de abril de 2023, 05:32 PM
 */

#ifndef FUNCIONES_H
#define FUNCIONES_H

void procesarCabecera(int &, int &);
void procesarUsuarios(int, int, int &, double &, int &, double &, int &,
        int &, int &, int &);
void imprimirResumen(int, double, int, double, int, int, int, int);
void imprimirCabeceraUsuario(int, char);
void procesarLibro(int, int, char, int, int, double, int &, double &);
void imprimirResumenUsuario(int, double);

// Funciones auxiliares
int leerFecha();
void imprimirFecha(int);
void imprimirLinea(char);

#endif /* FUNCIONES_H */

