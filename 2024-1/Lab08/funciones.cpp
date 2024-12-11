/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * Archivo: funciones.cpp
 * Autor:   Anthony Gutiérrez
 * Fecha:   15 de junio de 2024, 02:10 PM
 */

#include <iostream>
#include <iomanip>
#include <fstream>
#include <cstdlib>
#include <cstring>
using namespace std;
#include "Facultad.h"
#include "Alumno.h"
#include "funciones.h"

#define MAX_COD_CURSO 10
#define MAX_LINEA 150
#define NO_ENCONTRADO -1

void leerCalificaciones(struct Alumno *alumnos, int &numAlumnos) {
    ifstream arch;
    abrirArchivoEntrada(arch, "Calificaciones.txt");
    char codCurso[MAX_COD_CURSO];
    double creditos;
    int codAlumno, nota, posAlu;
    while (true) {
        arch >> codCurso;
        if (arch.eof()) break;
        arch >> creditos;
        while (arch.get() != '\n') {
            arch >> codAlumno >> nota;
            posAlu = buscarAlumno(alumnos, numAlumnos, codAlumno);
            if (posAlu != NO_ENCONTRADO) {
                alumnos[posAlu].numCreditos += creditos;
                alumnos[posAlu].sumaPond += creditos * nota;
                alumnos[posAlu].numCursos++;
            } else {
                alumnos[numAlumnos].codigo = codAlumno;
                alumnos[numAlumnos].numCreditos = creditos;
                alumnos[numAlumnos].sumaPond = creditos * nota;
                alumnos[numAlumnos].numCursos = 1;
                numAlumnos++;
            }
        }
    }
    // Calcular promedio ponderado
    for (int i = 0; i < numAlumnos; i++) {
        alumnos[i].promPond = alumnos[i].sumaPond / alumnos[i].numCreditos;
    }
}

int buscarAlumno(struct Alumno *alumnos, int numAlumnos, int codAlumno) {
    for (int i = 0; i < numAlumnos; i++) {
        if (alumnos[i].codigo == codAlumno)
            return i;
    }
    return NO_ENCONTRADO;
}

void leerAlumnos(struct Alumno *alumnos, int numAlumnos) {
    ifstream arch;
    abrirArchivoEntrada(arch, "Alumnos.csv");
    char nomAlumno[MAX_NOM_ALUMNO], codFacultad[MAX_COD_FACULTAD];
    int codAlumno, posAlu;
    while (true) {
        arch >> codAlumno;
        if (arch.eof()) break;
        arch.get();
        arch.getline(nomAlumno, MAX_NOM_ALUMNO, ',');
        arch.getline(codFacultad, MAX_COD_FACULTAD);
        // Buscar y colocar datos del alumno
        posAlu = buscarAlumno(alumnos, numAlumnos, codAlumno);
        if (posAlu != NO_ENCONTRADO) {
            strcpy(alumnos[posAlu].nombre, nomAlumno);
            strcpy(alumnos[posAlu].facultad.codigo, codFacultad);
        }
    }
}

void leerFacultades(struct Alumno *alumnos, int numAlumnos) {
    ifstream arch;
    abrirArchivoEntrada(arch, "Facultades.txt");
    char codFacultad[MAX_COD_FACULTAD], nomFacultad[MAX_NOM_FACULTAD];
    while (true) {
        arch >> nomFacultad;
        if (arch.eof()) break;
        arch >> codFacultad;
        // Reemplazar guión bajo por espacios
        for (int i = 0; nomFacultad[i]; i++) {
            if (nomFacultad[i] == '_') nomFacultad[i] = ' ';
        }
        // Reemplazar el nombre de la facultad para todos los alumnos
        for (int i = 0; i < numAlumnos; i++) {
            if (strcmp(alumnos[i].facultad.codigo, codFacultad) == 0)
                strcpy(alumnos[i].facultad.nombre, nomFacultad);
        }
    }
}

void emitirReporte(struct Alumno *alumnos, int numAlumnos) {
    ofstream arch;
    abrirArchivoSalida(arch, "ReporteDePagoPorAlumno.txt");
    double maxCred = 0;
    int posMaxCred = 0;
    // Imprimir cabecera
    arch << setw(87) << "INSTITUCION EDUCATIVA TP" << endl;
    arch << setw(98) << "PROMEDIO PONDERADO DE LOS ALUMNOS MATRICULADOS" << endl;
    arch << setw(81) << "CICLO: 2024-1" << endl;
    arch << setw(85) << "TODAS LAS FACULTADES" << endl;
    imprimirLinea(arch, '=');
    arch << left << setw(MAX_NOM_ALUMNO+10) << "Alumno" << setw(15) << "No. de Cursos"
            << setw(16) << "Suma Ponderada" << setw(17) << "No. de Creditos"
            << setw(16) << "Prom Ponderado" << "Facultad" << endl;
    imprimirLinea(arch, '-');
    // Imprimir listado de alumnos
    arch << fixed << setprecision(2);
    for (int i = 0; i < numAlumnos; i++) {
        arch << alumnos[i].codigo << " - " << setw(MAX_NOM_ALUMNO) << alumnos[i].nombre
                << right << setw(7) << alumnos[i].numCursos << setw(18) << alumnos[i].sumaPond
                << setw(16) << alumnos[i].numCreditos << setw(16) << alumnos[i].promPond
                << setw(6) << ' ' << alumnos[i].facultad.nombre << left << endl;
        if (alumnos[i].numCreditos > maxCred) {
            maxCred = alumnos[i].numCreditos;
            posMaxCred = i;
        }
    }
    imprimirLinea(arch, '=');
    arch << "Alumno con mayor numero de creditos matriculados:" << endl;
    arch << setw(20) << ' ' << alumnos[posMaxCred].nombre << " [" << alumnos[posMaxCred].codigo
            << "] con " << alumnos[posMaxCred].numCreditos << " creditos de la "
            << alumnos[posMaxCred].facultad.nombre << endl;
}

void abrirArchivoEntrada(ifstream &arch, const char *nomArch) {
    arch.open(nomArch, ios::in);
    if (!arch) {
        cerr << "No se pudo abrir el archivo " << nomArch << endl;
        exit(1);
    }
}

void abrirArchivoSalida(ofstream &arch, const char *nomArch) {
    arch.open(nomArch, ios::out);
    if (!arch) {
        cerr << "No se pudo abrir el archivo " << nomArch << endl;
        exit(1);
    }
}

void imprimirLinea(ofstream &arch, char car) {
    for (int i = 0; i < MAX_LINEA; i++)
        arch.put(car);
    arch << endl;
}
