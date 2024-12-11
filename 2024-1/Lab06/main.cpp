/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * Archivo: main.cpp
 * Autor:   Anthony Gutiérrez
 * Fecha:   1 de junio de 2024, 03:30 PM
 */

#include <iostream>
#include <fstream>
using namespace std;
#include "funciones.h"

#define MAX_ALUMNOS 100

void jpReporte(int *arrCodigoAlumnos, int *arrNumCursos, double *arrSumaPonderada,
        double *arrNumCreditos, int numAlumnos) {
    ofstream arJpRep("JpResumen.csv", ios::out);
    if (!arJpRep) {
        cerr << "JP: No se pudo crear resumen" << endl;
        exit(1);
    }
    for (int i = 0; i < numAlumnos; i++) {
        arJpRep << arrCodigoAlumnos[i] << ',' << arrNumCursos[i] << ','
                << arrSumaPonderada[i] << ',' << arrNumCreditos[i] << endl;
    }
}
/*
 * 
 */
int main(int argc, char** argv) {
    ifstream archCalif, archAlu, archFac;
    ofstream archRep;
    abrirArchivoEntrada(archCalif, "Calificaciones.txt");
    abrirArchivoEntrada(archAlu, "Alumnos.txt");
    abrirArchivoEntrada(archFac, "Facultades.txt");
    abrirArchivoSalida(archRep, "ReporteDePagoPorAlumno.txt");
    int codFacultad, arrCodAlumnos[MAX_ALUMNOS], arrNumCursos[MAX_ALUMNOS],
            numAlumnos = 0;
    double arrSumaPond[MAX_ALUMNOS], arrNumCreditos[MAX_ALUMNOS];
    codFacultad = 300103;//leerCodigoFacultad();
    leerCalificaciones(archCalif, arrCodAlumnos, arrNumCursos, arrSumaPond,
            arrNumCreditos, numAlumnos);
    jpReporte(arrCodAlumnos, arrNumCursos, arrSumaPond,
            arrNumCreditos, numAlumnos);
    emitirReporte(archAlu, archFac, archRep, arrCodAlumnos, arrNumCursos,
            arrSumaPond, arrNumCreditos, numAlumnos, codFacultad);
    return 0;
}
