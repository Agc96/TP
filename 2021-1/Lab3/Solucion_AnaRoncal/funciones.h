/* 
 * File:   funciones.h
 * Author: anaro
 *
 * Created on 10 de mayo de 2021, 05:34 PM
 */

#ifndef FUNCIONES_H
#define FUNCIONES_H

void guardarProductos(int *, double *, int *);
void guardarTiendas(int *, int *, int *);
void ordenarTiendas(int *, int *, int);
void  generarReporte(FILE *, FILE *, int *, int *, int *, double *, int , int ,
                     int *, double *);
void leerArchivoCompras(FILE *, FILE *, int, int, int *, double *, int, int *,
                        int *, int *, int *, double *, double *);
int BuscarPrecio(int , int * , int);
void linea(FILE *, char, int);

#endif /* FUNCIONES_H */

