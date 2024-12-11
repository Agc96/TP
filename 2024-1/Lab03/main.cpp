/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * Archivo: main.cpp
 * Autor:   Anthony Gutiérrez
 * Fecha:   28 de abril de 2024, 04:50 PM
 */

#include <iostream>
#include <fstream>
#include <iomanip>
using namespace std;
#include "funciones.h"

int main() {
    ifstream archCitas;
    ofstream archReporte;
    int dniMayor = 0;
    double total = 0.0, montoMayor = 0.0;
    abrirArchivoEntrada(archCitas, "CitasMedicas.txt");
    abrirArchivoSalida(archReporte, "Reporte.txt");
    imprimirCabecera(archReporte);
    procesarCitas(archCitas, archReporte, total, dniMayor, montoMayor);
    imprimirResumen(archReporte, total, dniMayor, montoMayor);
    return 0;
}
