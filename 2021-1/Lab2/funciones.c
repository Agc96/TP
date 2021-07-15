/*
 * Archivo: funciones.c
 * Autor:   Anthony Gutiérrez
 *
 * Creado el 4 de mayo de 2021, 08:08 AM
 */

#include <stdio.h>
#include <stdlib.h>
#include "funciones.h"

#define MAX_LINEA 120
#define MAX_SUBLINEA 40
#define MAX_NOMBRE 60

void generarReporte(FILE* archRep) {
    int numCur = 0, numAlu, codEsp, codCur, codCurMaxAp = 0;
    double cred, maxPorcAp = 0;
    // Imprimir cabecera del archivo de reporte
    imprimirCabeceraReporte(archRep);
    // Leer línea por línea del archivo de cursos
    FILE* archCur = abrirArchivo("Cursos.txt", "r");
    while (1) {
        fscanf(archCur, "%3d", &codEsp);
        if (feof(archCur)) break;
        fscanf(archCur, "%3d %lf ", &codCur, &cred);
        // Leer relación de alumnos del curso
        numAlu = obtenerNumAlumnos(codEsp, codCur);
        if (numAlu > 0) {
            imprimirCabeceraCurso(archRep, archCur, ++numCur, codEsp, codCur, cred);
            leerRelacionAlumnos(archRep, codEsp, codCur, &maxPorcAp, &codCurMaxAp);
        } else {
            ignorarLinea(archCur);
        }
    }
    fclose(archCur);
    // Imprimir resumen del reporte
    imprimirResumenReporte(archRep, numCur, maxPorcAp, codCurMaxAp);
}

void imprimirCabeceraReporte(FILE* archRep) {
    fprintf(archRep, "%70s\n", "INFORMACION ACADEMICA");
    fprintf(archRep, "%85s\n", "RELACION DE ALUMNOS QUE SE MATRICULARON POR CURSO");
}

int obtenerNumAlumnos(int codEspBusca, int codCurBusca) {
    int numAlu = 0, anioIng, codEspAlu, codEspCur, codCurLeido, anioCur, codAlu;
    // Buscar en todos los registros de los alumnos
    FILE* archAlu = abrirArchivo("Alumnos-Notas.txt", "r");
    while (1) {
        fscanf(archAlu, "%4d", &anioIng);
        if (feof(archAlu)) break;
        fscanf(archAlu, "%3d%d", &codEspAlu, &codAlu);
        ignorarLinea(archAlu);
        // Leer las notas del alumno
        while (1) {
            fscanf(archAlu, "%3d", &codEspCur);
            if (codEspCur == 0) break;
            fscanf(archAlu, "%3d %*d %*d/%*d/%d", &codCurLeido, &anioCur);
            // Verificar que se cumplan las condiciones para incluir al alumno
            if (validarAlumno(codCurBusca, codCurLeido, codEspBusca, codEspAlu,
                    codEspCur, anioIng, anioCur)) {
                numAlu++;
            }
        }
    }
    fclose(archAlu);
    // Devolver el número de alumnos
    return numAlu;
}

int validarAlumno(int codCurBusca, int codCurLeido, int codEspBusca, int codEspAlu,
        int codEspCur, int anioIng, int anioCur) {
    return codCurBusca == codCurLeido && codEspBusca == codEspAlu
            && codEspAlu == codEspCur && anioCur >= anioIng;
}

void imprimirCabeceraCurso(FILE* archRep, FILE* archCur, int numCur, int codEsp,
        int codCur, double cred) {
    imprimirLinea(archRep, '=', MAX_LINEA);
    fprintf(archRep, "%02d)  Curso: ", numCur);
    imprimirNombreCurso(archRep, archCur);
    fprintf(archRep, "Especialidad: %03d", codEsp);
    fprintf(archRep, "%3cCodigo: %03d", ' ', codCur);
    fprintf(archRep, "%3cCreditos: %.2lf\n", ' ', cred);
    imprimirLinea(archRep, '-', MAX_LINEA);
}

void imprimirNombreCurso(FILE* archRep, FILE* archCur) {
    int tamCur = 0, i;
    char c;
    while ((c = fgetc(archCur)) != '\n') {
        fputc(c, archRep); // Colocar los caracteres conforme se van leyendo
        tamCur++;
    }
    for (i = 0; i < (MAX_NOMBRE-tamCur); i++) {
        fputc(' ', archRep); // Rellenar el resto de caracteres en blanco
    }
}

void leerRelacionAlumnos(FILE* archRep, int codEspBusca, int codCurBusca,
        double* maxPorcAp, int* codCurMaxAp) {
    int anioIng, codEspAlu, codEspCur, codAlu, codCurLeido, nota, dd, mm, aaaa,
            numAlu = 0, numAprob = 0, numDesap = 0, notaMax = 0, notaMin = 20;
    // Imprimir cabecera de la relación de alumnos
    imprimirCabeceraAlumnos(archRep);
    // Leer línea por línea el archivo de alumnos
    FILE* archAlu = abrirArchivo("Alumnos-Notas.txt", "r");
    while (1) {
        fscanf(archAlu, "%4d", &anioIng);
        if (feof(archAlu)) break;
        fscanf(archAlu, "%3d%d", &codEspAlu, &codAlu);
        ignorarLinea(archAlu);
        // Leer las notas del alumno
        while (1) {
            fscanf(archAlu, "%3d", &codEspCur);
            if (codEspCur == 0) break;
            fscanf(archAlu, "%3d %d %d/%d/%d", &codCurLeido, &nota, &dd, &mm, &aaaa);
            // Verificar que se cumplan las condiciones para incluir al alumno
            if (validarAlumno(codCurBusca, codCurLeido, codEspBusca, codEspAlu,
                    codEspCur, anioIng, aaaa)) {
                fprintf(archRep, "%5c%03d  %-4d%-3d%-11d  %02d  %5d/%02d/%02d\n", ' ',
                        ++numAlu, anioIng, codEspAlu, codAlu, nota, aaaa, mm, dd);
                actualizarContadores(nota, &numAprob, &numDesap, &notaMax, &notaMin);
            }
        }
    }
    fclose(archAlu);
    // Imprimir resumen del curso con los datos obtenidos
    imprimirResumenCurso(archRep, codCurBusca, numAprob, numDesap, notaMax,
            notaMin, maxPorcAp, codCurMaxAp);
}

void imprimirCabeceraAlumnos(FILE* archRep) {
    fprintf(archRep, "%5c%s:\n", ' ', "RELACION DE ALUMNOS");
    fprintf(archRep, "%5c%-5s%-19s%-8s%s\n%5c", ' ', "No.",
            "CODIGO DEL ALUMNO", "NOTA", "FECHA", ' ');
    imprimirLinea(archRep, '-', MAX_SUBLINEA);
}

void actualizarContadores(int nota, int* numAprob, int* numDesap, int* notaMax,
        int* notaMin) {
    // Actualizar cantidad de aprobados y desaprobados
    if (nota > 10) {
        (*numAprob)++;
    } else {
        (*numDesap)++;
    }
    // Actualizar nota máxima
    if (nota > (*notaMax)) {
        *notaMax = nota;
    }
    // Actualizar nota mínima
    if (nota < (*notaMin)) {
        *notaMin = nota;
    }
}

void imprimirResumenCurso(FILE* archRep, int codCur, int numAprob, int numDesap,
        int notaMax, int notaMin, double* maxPorcAp, int* codCurMaxAp) {
    // Calcular los datos intermedios
    int numMat = numAprob + numDesap;
    double porcAprob = numAprob*100.0/numMat;
    double porcDesap = numDesap*100.0/numMat;
    double relApDes = numDesap == 0 ? 1.0 : numAprob*1.0/numDesap;
    // Imprimir datos en el archivo del reporte
    imprimirLinea(archRep, '=', MAX_LINEA);
    fprintf(archRep, "%5cRESUMEN:\n", ' ');
    fprintf(archRep, "%5cAlumnos matriculados de la especialidad: %5d\n", ' ', numMat);
    fprintf(archRep, "%5cAprobados: %35d %15.2lf%%\n", ' ', numAprob, porcAprob);
    fprintf(archRep, "%5cDesaprobados: %32d %15.2lf%%\n", ' ', numDesap, porcDesap);
    fprintf(archRep, "%5cRelacion aprobados/desaprobados: %31.4lf\n", ' ', relApDes);
    fprintf(archRep, "%5cNota maxima: %30c %02d\n", ' ', ' ', notaMax);
    fprintf(archRep, "%5cNota minima: %30c %02d\n", ' ', ' ', notaMin);
    // Actualizar porcentaje de aprobados
    if (porcAprob > (*maxPorcAp)) {
        *maxPorcAp = porcAprob;
        *codCurMaxAp = codCur;
    }
}

void imprimirResumenReporte(FILE* archRep, int numCur, double maxPorcAp, int codCurMaxAp) {
    int codCurLeido, codEsp;
    // Imprimir datos de los cursos
    imprimirLinea(archRep, '*', MAX_LINEA);
    fprintf(archRep, "%5cTOTAL DE CURSOS REGISTRADOS: %d\n", ' ', numCur);
    fprintf(archRep, "%5cCURSO CON MAYOR PORCENTAJE DE APROBADOS:\n%5c", ' ', ' ');
    // Buscar los datos del curso
    FILE* archCur = abrirArchivo("Cursos.txt", "r");
    while (1) {
        fscanf(archCur, "%3d", &codEsp);
        if (feof(archCur)) break;
        fscanf(archCur, "%3d %*lf ", &codCurLeido);
        // Leer relación de alumnos del curso
        if (codCurLeido == codCurMaxAp) {
            imprimirNombreCurso(archRep, archCur);
            fprintf(archRep, "Especialidad: %03d", codEsp);
            fprintf(archRep, "%3cCodigo: %03d", ' ', codCurLeido);
            fprintf(archRep, "%3cAprobados: %.2lf%%\n", ' ', maxPorcAp);
            break;
        } else {
            ignorarLinea(archCur);
        }
    }
    fclose(archCur);
    // TODO
    imprimirLinea(archRep, '*', MAX_LINEA);
}

/* Funciones auxiliares */

FILE* abrirArchivo(const char* nomArch, const char* modoArch) {
    FILE* arch = fopen(nomArch, modoArch);
    if (arch == NULL) {
        fprintf(stderr, "No se pudo abrir o crear el archivo %s\n", nomArch);
        exit(1);
    }
    return arch;
}

void imprimirLinea(FILE* arch, char c, int num) {
    for (int i = 0; i < num; i++) {
        fputc(c, arch);
    }
    fputc('\n', arch);
}

void ignorarLinea(FILE* arch) {
    char c;
    while ((c = fgetc(arch)) != '\n');
}
