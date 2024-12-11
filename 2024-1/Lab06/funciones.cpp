/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * Archivo: funciones.cpp
 * Autor:   Anthony Gutiérrez
 * Fecha:   1 de junio de 2024, 03:38 PM
 */

#include <iostream>
#include <iomanip>
#include <fstream>
#include <cstdlib>
#include <cstring>
using namespace std;
#include "funciones.h"

#define MAX_CURSO 10
#define MAX_NOMBRE 40
#define MAX_LINEA 120
#define NO_ENCONTRADO -1

int leerCodigoFacultad() {
    int codFacultad;
    cout << "Ingrese el codigo de la facultad: ";
    cin >> codFacultad;
    return codFacultad;
}

void leerCalificaciones(ifstream &archCalif, int *arrCodAlumnos, int *arrNumCursos,
        double *arrSumaPond, double *arrNumCreditos, int &numAlumnos) {
    char codCurso[MAX_CURSO];
    int codAlumno, nota, posAlumno;
    double cred;
    while (true) {
        archCalif >> codCurso;
        if (archCalif.eof()) break;
        archCalif >> cred;
        while (true) {
            archCalif >> codAlumno >> nota;
            posAlumno = busquedaBinaria(arrCodAlumnos, numAlumnos, codAlumno);
            if (posAlumno == NO_ENCONTRADO) {
                insertarOrdenado(arrCodAlumnos, arrNumCursos, arrSumaPond,
                        arrNumCreditos, numAlumnos, codAlumno, cred, nota);
                numAlumnos++;
            } else {
                arrNumCursos[posAlumno]++;
                arrSumaPond[posAlumno] += cred * nota;
                arrNumCreditos[posAlumno] += cred;
            }
            if (archCalif.get() == '\n') break;
        }
    }
}

int busquedaBinaria(int *arreglo, int cantDatos, int datoBuscado) {
    int izq = 0, der = cantDatos - 1, medio;
    while (izq <= der) {
        medio = (izq + der) / 2;
        if (arreglo[medio] == datoBuscado)
            return medio;
        if (arreglo[medio] > datoBuscado) // datoBuscado < arreglo[medio]
            der = medio - 1;
        else // arreglo[medio] < datoBuscado // datoBuscado > arreglo[medio]
            izq = medio + 1;
    }
    return NO_ENCONTRADO;
}

void insertarOrdenado(int *arrCodAlumnos, int *arrNumCursos, double *arrSumaPond,
        double *arrNumCreditos, int numAlumnos, int codAlumno, double cred,
        int nota) {
    int pos;
    for (pos = numAlumnos - 1; pos >= 0; pos--) { // && codAlumno < arrCodAlumnos[pos]
        if (arrCodAlumnos[pos] < codAlumno) break; // 
        arrCodAlumnos[pos+1] = arrCodAlumnos[pos];
        arrNumCursos[pos+1] = arrNumCursos[pos];
        arrSumaPond[pos+1] = arrSumaPond[pos];
        arrNumCreditos[pos+1] = arrNumCreditos[pos];
    }
    arrCodAlumnos[pos+1] = codAlumno;
    arrNumCursos[pos+1] = 1;
    arrSumaPond[pos+1] = cred * nota;
    arrNumCreditos[pos+1] = cred;
}

void emitirReporte(ifstream &archAlu, ifstream &archFac, ofstream &archRep,
        int *arrCodAlumnos, int *arrNumCursos, double *arrSumaPond,
        double *arrNumCreditos, int numAlumnos, int codFacBuscado) {
    archRep << fixed << setprecision(2);
    char nomAlumno[MAX_NOMBRE], nomArreglado[MAX_NOMBRE]{};
    int codAlumno, codFacLeido, posAlu;
    imprimirCabecera(archFac, archRep, codFacBuscado);
    while (true) {
        archAlu >> codAlumno;
        if (archAlu.eof()) break;
        archAlu >> nomAlumno >> codFacLeido;
        if (codFacBuscado != codFacLeido) continue;
        // Imprimir nombre del alumno
        arreglarNomAlumno(nomAlumno, nomArreglado);
        archRep << left << codAlumno << " - " << setw(MAX_NOMBRE) << nomArreglado;
        // Imprimir datos del alumno
        posAlu = busquedaBinaria(arrCodAlumnos, numAlumnos, codAlumno);
        if (posAlu != NO_ENCONTRADO) {
            archRep << right << setw(10) << arrNumCursos[posAlu] << setw(16)
                    << arrSumaPond[posAlu] << setw(17) << arrNumCreditos[posAlu]
                    << setw(16) << arrSumaPond[posAlu] / arrNumCreditos[posAlu];
        }
        archRep << endl;
    }
    imprimirLinea(archRep, '=');
}

void arreglarNomAlumno(char *nomOriginal, char *nomArreglado) {
    int ultimoSlash = 0, tamNombre = 0;
    bool mayus = true;
    for (int i = 0; nomOriginal[i]; i++) {
        // Obtener posición del último slash
        if (nomOriginal[i] == '/')
            ultimoSlash = i;
        // Alternar mayúsculas y minúsculas
        if (nomOriginal[i] == '/' || nomOriginal[i] == '-') {
            mayus = true;
        } else if (mayus) {
            mayus = false;
        } else {
            nomOriginal[i] += 'a' - 'A';
        }
    }
    // Colocar nombres
    for (int i = ultimoSlash + 1; nomOriginal[i]; i++) {
        if (nomOriginal[i] == '-')
            nomOriginal[i] = ' ';
        nomArreglado[tamNombre++] = nomOriginal[i];
    }
    nomArreglado[tamNombre++] = ' ';
    // Colocar apellidos
    for (int i = 0; i < ultimoSlash; i++) {
        if (nomOriginal[i] == '/')
            nomOriginal[i] = ' ';
        nomArreglado[tamNombre++] = nomOriginal[i];
    }
    nomArreglado[tamNombre] = 0;
}

void imprimirCabecera(ifstream &archFac, ofstream &archRep, int codFacBuscado) {
    char nomFac[MAX_NOMBRE];
    int codFacLeido;
    archRep << "INSTITUCION EDUCATIVA TP" << endl;
    archRep << "PROMEDIO PONDERADO DE LOS ALUMNOS MATRICULADOS" << endl;
    archRep << "CICLO: 2024-1" << endl;
    while (true) {
        archFac >> nomFac;
        if (archFac.eof()) break;
        archFac >> codFacLeido;
        if (codFacBuscado != codFacLeido) continue;
        // Actualizar nombre
        for (int i = 0; nomFac[i]; i++) {
            if (nomFac[i] == '_') nomFac[i] = ' ';
        }
        // Imprimir nombre
        archRep << nomFac << endl;
    }
    imprimirLinea(archRep, '=');
    archRep << left << setw(12+MAX_NOMBRE) << "ALUMNO" << setw(15) << "No. de Cursos"
            << setw(16) << "Suma Ponderada" << setw(17) << "No. de Creditos"
            << "Prom Ponderado" << endl;
    imprimirLinea(archRep, '-');
}

/* Funciones auxiliares */

void abrirArchivoEntrada(ifstream &arch, const char *nomArch) {
    arch.open(nomArch, ios::in);
    if (!arch) {
        cout << "No se pudo abrir el archivo " << nomArch << endl;
        exit(1);
    }
}

void abrirArchivoSalida(ofstream &arch, const char *nomArch) {
    arch.open(nomArch, ios::out);
    if (!arch) {
        cout << "No se pudo abrir el archivo " << nomArch << endl;
        exit(1);
    }
}

void imprimirLinea(ofstream &arch, char car) {
    for (int i = 0; i < MAX_LINEA; i++)
        arch.put(car);
    arch << endl;
}
