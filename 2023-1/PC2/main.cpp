/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/cppFiles/main.cc to edit this template
 */

/* 
 * File:   main.cpp
 * Author: USUARIO
 *
 * Created on 8 de mayo de 2023, 05:15 PM
 */

#include <iostream>
#include <fstream>
#include <iomanip>
using namespace std;

#include "funciones.h"

/*
 * 
 */
int main(int argc, char** argv) {
    int fechaIni, fechaFin;
    int arrCodLibro[MAX_LIBROS], arrCodAutor[MAX_REG_AUTORES], 
            arrAutorCodLibro[MAX_REG_AUTORES], arrCantidadLibro[MAX_LIBROS]={},
            cantLibros=0, cantRegAutores=0;
    double arrPrecioLibro[MAX_LIBROS],
            arrRecaudadoLibro[MAX_LIBROS]={}, arrRegaliaAutorLibro[MAX_REG_AUTORES];
    
    leerDatosLibro(arrCodLibro, arrPrecioLibro, cantLibros);
    leerRegistrosAutores(arrCodAutor, arrAutorCodLibro, arrRegaliaAutorLibro, cantRegAutores);
    leerRangoFechas(fechaIni, fechaFin);
    
//    for (int i=0; i<cantLibros; i++){
//        cout << arrCodLibro[i] << " "<< arrPrecioLibro[i] <<endl;
//    }
//    
//    for (int i=0; i<cantRegAutores; i++){
//        cout << arrCodAutor[i] << " "<< arrAutorCodLibro[i] <<" "<<arrRegaliaAutorLibro[i]<<endl;
//    }
    
    leerVentas(arrCodLibro, arrPrecioLibro, arrCantidadLibro, arrRecaudadoLibro, cantLibros, fechaIni, fechaFin);
    mostrarReporte(arrCodLibro, arrCodAutor, arrAutorCodLibro, arrCantidadLibro, arrRegaliaAutorLibro, arrRecaudadoLibro, arrPrecioLibro, cantLibros, cantRegAutores, fechaIni, fechaFin);
    
    
    return 0;
}

