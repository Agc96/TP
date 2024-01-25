/*
 * Archivo: funciones.h
 * Autor:   Anthony Gutiérrez
 * Fecha:   11 de abril de 2023, 09:37 PM
 */

#ifndef FUNCIONES_H
#define FUNCIONES_H

void procesarCabecera(int &, int &);
void procesarUsuarios(int, int, int &, double &, int &, double &);
void imprimirResumen(int, double, int, double);
void imprimirCabeceraUsuario(int, char, char);
void procesarLibro(char, char, int, int, double, int &, double &);
void imprimirResumenUsuario(int, double);

// Funciones auxiliares
int leerFecha();
void imprimirFecha(int);
void imprimirLinea(char);

#endif /* FUNCIONES_H */

