/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/cppFiles/file.h to edit this template
 */

/* 
 * File:   funciones.h
 * Author: USUARIO
 *
 * Created on 8 de mayo de 2023, 05:18 PM
 */

#ifndef FUNCIONES_H
#define FUNCIONES_H

#include <fstream>
using namespace std;

//Nombre de archivos
#define ARCHIVO_LIBROS "Libros.txt"
#define ARCHIVO_AUTORES "Autores.txt"
#define ARCHIVO_VENTAS "Ventas.txt"
#define ARCHIVO_REPORTE "Reporte.txt"

//Máximo tamaño de arreglos
#define MAX_LIBROS 100
#define MAX_REG_AUTORES 400
#define ERROR -1
#define CANT_LINEAS 100

void leerRangoFechas(int &, int &);
void leerDatosLibro(int* , double* ,int &);
void leerRegistrosAutores(int* , int* , double *, int&);
void leerVentas(int* , double* , int *, double *,
        int , int , int, double*, double*, int*, int*, int); 
int buscarEntero(int* ,int, int);

void mostrarReporte(int* arrCodLibro, int* arrCodAutor, int* arrAutorCodLibro, 
        int* arrCantidadLibro, double* arrRegaliaAutorLibro, double* arrRecaudadoLibro,
        double * arrPrecioLibro,
        int cantLibros, int cantRegAutores, int fechaIni, int fechaFin,
        double *arrRegaliaAutorLibroRecaudado);

void imprimirLinea(ofstream&, char);

#endif /* FUNCIONES_H */

