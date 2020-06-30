/* 
 * Archivo: funciones.h
 * Autor:   Anthony Gutiérrez
 *
 * Created on 2 de mayo de 2020, 05:48 PM
 */

#ifndef FUNCIONES_H
#define FUNCIONES_H

void procesarCabecera(int*, int*, int*);
void procesarDetalles(int, int, int);

int leerMovimiento(int*, int*, int*, double*, double*, int*);
void actualizarContadores(int, double, double, double*, double*, double*, int*,
        double*, double*, double*, int*, int, int*, int*);
void imprimirProducto(int, int, int, int, double*, double*, double*, double*,
        double*, double*, double*, double*, double*, double*, int*, int*,
        int*, int*);
void imprimirAlmacen(int, double*, double*, double*, double*);
void imprimirTotal(double, double);
double calcularPuPromedio(double, int);

int convertirFecha(int, int, int);
void imprimirFecha(int, int);
void repetir(char, int, int);

#endif /* FUNCIONES_H */
