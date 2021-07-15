/* 
 * Archivo: funciones.h
 * Autor:   Anthony Gutiérrez
 *
 * Creado el 14 de septiembre de 2020, 07:58 PM
 */

#ifndef FUNCIONES_H
#define FUNCIONES_H

void leerDatosCuenta(int *, double *, double *, double *, char *, int *, int *);
void imprimirEstadoCuenta(int, double, double, double, char);
void leerTransaccion(char *, double *);
void procesarDeposito(double *, double *, char *, double, int *);
void procesarRetiro(double *, double *, char *, double, int *);
void imprimirResumenCuenta(double, double, char, int, int);
void imprimirResumenFinal(int);

#endif /* FUNCIONES_H */
