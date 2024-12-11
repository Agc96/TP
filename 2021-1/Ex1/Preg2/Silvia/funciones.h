/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   funciones.h
 * Author: Código:--------------
 *         Nombre: Silvia Vargas Cáceres
 *          Silvia
 *
 * Created on 21 de mayo de 2021, 10:00 PM
 */

#ifndef FUNCIONES_H
#define FUNCIONES_H

void cargarProductos(int *,double *,int *);
void cargarProdAlmacenados(int *,double *,int , double *, double *);
int buscar(int *,int , int );
void ordenarSubTotalProducto(int *,double *,double *,double *,int );
void cambiarInt(int *,int ,int );
void cambiarDouble(double *,int,int );
void generarReporte(int *,double *,
        double *,double *,int ,
        int *,int *,double *,
        double *,int );
void imprimirLinea(FILE *,char ,int );
void cargarPlatosPreparar(int *,int *,int *);
void cargarPlatosPrecios(int *,int *,int , int *,double *,int ,double *);
void actualizarSubTotalPlatos(int *,int *,int , double *,double *);
void ordenarSubTotalPlato(int *,double *,  int *,double *,int );
#endif /* FUNCIONES_H */

