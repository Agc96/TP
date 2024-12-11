/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * Archivo: main.cpp
 * Autor:   Anthony Gutiérrez
 * Fecha:   29 de junio de 2024, 08:56 PM
 */

#include <iostream>
#include <fstream>
using namespace std;
#include "funciones.h"

/*
 * 
 */
int main(int argc, char** argv) {
    leerClientes("Clientes.csv", "Clientes.bin");
    leerLibros("Libros.csv", "Libros.bin");
    leerVentas("Ventas.csv", "Clientes.bin", "Libros.bin");
    determinarRanking("Libros.bin");
    ordenarLibros("Libros.bin");
    generarReporte("Libros.bin", "ReporteDePagoPorAlumno.txt");
    return 0;
}
