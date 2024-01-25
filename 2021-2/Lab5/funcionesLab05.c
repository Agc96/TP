/*
 * File:   funcionesLab05.c
 * Author: Anthony Gutiérrez
 *
 * Created on 16 de noviembre de 2021, 08:07 AM
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "funcionesCadenas.h"
#include "funcionesLab05.h"

#define MAX_BUFFER 100
#define MAX_PALABRAS 10
#define MAX_LINEA 100
#define NO_ENCONTRADO -1

void leerEscalas(char **arrCodEsc, double *arrPrecEsc, int *cantEsc) {
    FILE *arch = abrirArchivo("Escalas.txt", "r");
    char buffer[MAX_BUFFER], *palabras[MAX_PALABRAS];
    int cantPalabras;
    // Leer el archivo de escalas
    *cantEsc = 0;
    while (1) {
        leerCadena(buffer, MAX_BUFFER, arch);
        if (feof(arch)) break;
        sacaPalabras(buffer, palabras, &cantPalabras, ' ');
        // Asignar las palabras en los arreglos
        arrCodEsc[*cantEsc] = palabras[0];
        arrPrecEsc[*cantEsc] = atof(palabras[1]);
        free(palabras[1]);
        (*cantEsc)++;
    }
    fclose(arch);
}

void leerCursos(char **arrCodCur, char **arrNomCur, double *arrCredCur,
        int *cantCur) {
    FILE *arch = abrirArchivo("Cursos.csv", "r");
    char buffer[MAX_BUFFER], *palabras[MAX_PALABRAS];
    int cantPalabras;
    // Leer el archivo de cursos
    *cantCur = 0;
    while (1) {
        leerCadena(buffer, MAX_BUFFER, arch);
        if (feof(arch)) break;
        sacaPalabras(buffer, palabras, &cantPalabras, ',');
        // Asignar las palabras en los arreglos
        arrCodCur[*cantCur] = palabras[0];
        arrNomCur[*cantCur] = palabras[1];
        arrCredCur[*cantCur] = atof(palabras[2]);
        free(palabras[2]);
        (*cantCur)++;
    }
    fclose(arch);
}

void procesarMatricula(char **arrCodEsc, double *arrPrecEsc, double *arrRecEsc,
        int cantEsc, char **arrCodCur, char **arrNomCur, double *arrCredCur,
        double *arrRecCur, int cantCur) {
    FILE *arch = abrirArchivo("Matricula.csv", "r");
    char buffer[MAX_BUFFER], *palabras[MAX_PALABRAS];
    int cantPalabras, posEsc, posCur;
    double pago;
    // Leer el archivo de matrículas
    while (1) {
        leerCadena(buffer, MAX_BUFFER, arch);
        if (feof(arch)) break;
        sacaPalabras(buffer, palabras, &cantPalabras, ',');
        // Buscar la escala
        posEsc = buscarCadena(arrCodEsc, cantEsc, palabras[2]);
        if (posEsc != NO_ENCONTRADO) {
            // Procesar cada curso
            for (int i = 3; i < cantPalabras; i++) {
                posCur = buscarCadena(arrCodCur, cantCur, palabras[i]);
                if (posCur != NO_ENCONTRADO) {
                    // Sumar el monto recaudado donde corresponda
                    pago = arrPrecEsc[posEsc] * arrCredCur[posCur];
                    arrRecEsc[posEsc] += pago;
                    arrRecCur[posCur] += pago;
                } else {
                    printf("No se encontró el curso %s\n", palabras[i]);
                }
            }
        } else {
            printf("No se encontró la escala %s\n", palabras[2]);
        }
    }
    fclose(arch);
}

int buscarCadena(char **arr, int cant, char *cad) {
    for (int i = 0; i < cant; i++) {
        if (strcmp(arr[i], cad) == 0) return i;
    }
    return NO_ENCONTRADO;
}

void ordenarEscalas(char **arrCodEsc, double *arrPrecEsc, double *arrRecEsc,
        int cantEsc) {
    for (int i = 0; i < cantEsc-1; i++) {
        for (int j = i+1; j < cantEsc; j++) {
            if (arrRecEsc[i] < arrRecEsc[j]) {
                intercambiarCadena(arrCodEsc, i, j);
                intercambiarDouble(arrPrecEsc, i, j);
                intercambiarDouble(arrRecEsc, i, j);
            }
        }
    }
}

void intercambiarCadena(char **arr, int i, int j) {
    char *aux = arr[i];
    arr[i] = arr[j];
    arr[j] = aux;
}

void intercambiarDouble(double *arr, int i, int j) {
    double aux = arr[i];
    arr[i] = arr[j];
    arr[j] = aux;
}

void ordenarCursos(char **arrCodCur, char **arrNomCur, double *arrCredCur,
        double *arrRecCur, int cantCur) {
    int result;
    for (int i = 0; i < cantCur-1; i++) {
        for (int j = i+1; j < cantCur; j++) {
            result = evaluarCadenas(arrNomCur[i], arrNomCur[j]);
            if (result > 0 || (result == 0 && arrRecCur[i] < arrRecCur[j])) {
                intercambiarCadena(arrCodCur, i, j);
                intercambiarCadena(arrNomCur, i, j);
                intercambiarDouble(arrCredCur, i, j);
                intercambiarDouble(arrRecCur, i, j);
            }
        }
    }
}

int evaluarCadenas(const char *cad1, const char *cad2) {
    int i = 0;
    while (cad1[i] == cad2[i]) {
        if (i == 3) return 0;
        i++;
    }
    return cad1[i] - cad2[i];
}

void imprimirReporte(char **arrCodEsc, double *arrPrecEsc, double *arrRecEsc,
        int cantEsc, char **arrCodCur, char **arrNomCur, double *arrCredCur,
        double *arrRecCur, int cantCur) {
    FILE *arch = abrirArchivo("Reporte.txt", "w");
    double total = 0;
    // Imprimir cabecera del reporte
    fprintf(arch, "%56s\n", "INSTITUTO ABC");
    fprintf(arch, "%74s\n", "RECAUDACION OBTENIDA POR EL PROCESO DE MATRICULA");
    imprimirLinea(arch, '=');
    // Imprimir recaudación por escalas
    fprintf(arch, "%62s\n", "Recaudacion Por Escalas");
    imprimirLinea(arch, '-');
    fprintf(arch, "%10s %20s %15s\n", "Escala", "Valor de Credito",
            "Recaudacion");
    for (int i = 0; i < cantEsc; i++) {
        fprintf(arch, "%2d) %4s %18.2lf %18.2lf\n", i+1, arrCodEsc[i],
                arrPrecEsc[i], arrRecEsc[i]);
    }
    imprimirLinea(arch, '=');
    // Imprimir recaudación por curso
    fprintf(arch, "%60s\n", "Recaudacion Por Curso");
    imprimirLinea(arch, '-');
    fprintf(arch, "%12s %8s %58s %15s\n", "Codigo", "Nombre", "Creditos",
            "Recaudacion");
    for (int i = 0; i < cantCur; i++) {
        fprintf(arch, "%2d) %8s %c %-54s %8.2lf %15.2lf\n", i+1, arrCodCur[i],
                ' ', arrNomCur[i], arrCredCur[i], arrRecCur[i]);
        total += arrRecCur[i];
    }
    imprimirLinea(arch, '=');
    // Imprimir resumen del reporte
    fprintf(arch, "TOTAL RECAUDADO: %.2lf\n", total);
    fclose(arch);
}

void imprimirLinea(FILE *arch, char c) {
    for (int i = 0; i < MAX_LINEA; i++) {
        fputc(c, arch);
    }
    fputc('\n', arch);
}
