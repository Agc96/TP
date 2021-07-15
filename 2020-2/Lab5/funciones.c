/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * Archivo: funciones.c
 * Autor:   Anthony Gutiérrez
 *
 * Creado el 24 de noviembre de 2020, 09:04 AM
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "funciones.h"

#define MAX_LINEA 100
#define MAX_SEPARACION 132
#define MIN_APROBADO 11
#define NO_ENCONTRADO -1

/* Parte 1: Leer cursos */

void leerCursos(char **arrCodCur, char **arrNomCur, double *arrCredCur,
        char **arrFacCur, int *cantCur) {
    // Declaración de variables
    FILE *arch = abrirArchivo("Cursos.txt", "r");
    char buffCodCur[MAX_LINEA], buffFacCur[MAX_LINEA], buffNomCur[MAX_LINEA];
    double credCur;
    // Leer línea por línea
    while (1) {
        fscanf(arch, "%s %lf %s\n", buffCodCur, &credCur, buffFacCur);
        if (feof(arch)) break;
        fgets(buffNomCur, MAX_LINEA, arch);
        // Agregar datos a los arreglos
        arrCodCur[*cantCur] = crearCadenaExacta(buffCodCur);
        arrNomCur[*cantCur] = crearCadenaExacta(buffNomCur);
        arrCredCur[*cantCur] = credCur;
        arrFacCur[*cantCur] = crearCadenaExacta(buffFacCur);
        (*cantCur)++;
    }
    fclose(arch);
}

void ordenarCursos(char **arrCodCur, char **arrNomCur, double *arrCredCur,
        char **arrFacCur, int cantCur) {
    for (int i = 0; i < cantCur-1; i++) {
        for (int j = i+1; j < cantCur; j++) {
            if (strcmp(arrCodCur[i], arrCodCur[j]) > 0) {
                intercambiarCadena(arrCodCur, i, j);
                intercambiarCadena(arrNomCur, i, j);
                intercambiarDouble(arrCredCur, i, j);
                intercambiarCadena(arrFacCur, i, j);
            }
        }
    }
}

/* Parte 2: Leer alumnos */

void leerAlumnos(int *arrCodAlu, char **arrNomAlu, int *cantAlu) {
    FILE *arch = abrirArchivo("Alumnos.txt", "r");
    char nomAlu[MAX_LINEA];
    int codAlu;
    // Leer línea por línea
    while (1) {
        fscanf(arch, "%d\n", &codAlu);
        if (feof(arch)) break;
        fgets(nomAlu, MAX_LINEA, arch);
        // Agregar datos a los arreglos
        arrCodAlu[*cantAlu] = codAlu;
        arrNomAlu[*cantAlu] = crearCadenaExacta(nomAlu);
        (*cantAlu)++;
    }
    fclose(arch);
}

void ordenarAlumnos(int *arrCodAlu, char **arrNomAlu, int cantAlu) {
    for (int i = 0; i < cantAlu-1; i++) {
        for (int j = i+1; j < cantAlu; j++) {
            if (arrCodAlu[i] > arrCodAlu[j]) {
                intercambiarEntero(arrCodAlu, i, j);
                intercambiarCadena(arrNomAlu, i, j);
            }
        }
    }
}

/* Parte 3: Leer notas */

void leerNotas(int *arrCodAlu, double *arrSumNotas, double *arrSumAprob,
        double *arrCredAprob, double *arrCredDesap, int cantAlu,
        char **arrCodCur, double *arrCredCur, int *arrNumAluCur,
        int *arrNumAprobCur, int cantCur) {
    // Declaración de variables
    FILE *arch = abrirArchivo("Notas.txt", "r");
    int codAlu, nota, posAlu, posCur;
    char codCur[MAX_LINEA];
    // Leer línea por línea
    while (1) {
        fscanf(arch, "%d %s %d", &codAlu, codCur, &nota);
        if (feof(arch)) break;
        // Buscar datos del alumno y del curso
        posAlu = buscarAlumno(arrCodAlu, codAlu, cantAlu);
        posCur = buscarCurso(arrCodCur, codCur, cantCur);
        if (posAlu != NO_ENCONTRADO && posCur != NO_ENCONTRADO) {
            arrSumNotas[posAlu] += nota*arrCredCur[posCur];
            arrNumAluCur[posCur]++;
            if (nota >= MIN_APROBADO) {
                arrSumAprob[posAlu] += nota*arrCredCur[posCur];
                arrCredAprob[posAlu] += arrCredCur[posCur];
                arrNumAprobCur[posCur]++;
            } else {
                arrCredDesap[posAlu] += arrCredCur[posCur];
            }
        }
    }
}

int buscarCurso(char **arrCodCur, char *codCur, int cantCur) {
    int limiteInf = 0, limiteSup = cantCur-1, puntoMedio, resultado;
    while (1) {
        if (limiteInf > limiteSup) return NO_ENCONTRADO;
        // Calcular el punto medio
        puntoMedio = (limiteInf+limiteSup)/2;
        // Comparar el punto medio con el valor buscado
        resultado = strcmp(arrCodCur[puntoMedio], codCur);
        if (resultado == 0) return puntoMedio;
        // Si no son iguales, actualizar los límites
        if (resultado > 0) {
            limiteSup = puntoMedio-1;
        } else {
            limiteInf = puntoMedio+1;
        }
    }
}

int buscarAlumno(int *arrCodAlu, int codAlu, int cantAlu) {
    int limiteInf = 0, limiteSup = cantAlu-1, puntoMedio;
    while (1) {
        if (limiteInf > limiteSup) return NO_ENCONTRADO;
        // Calcular el punto medio
        puntoMedio = (limiteInf+limiteSup)/2;
        if (arrCodAlu[puntoMedio] == codAlu) return puntoMedio;
        // Si no son iguales, actualizar los límites
        if (arrCodAlu[puntoMedio] > codAlu) {
            limiteSup = puntoMedio-1;
        } else {
            limiteInf = puntoMedio+1;
        }
    }
}

/* Parte 4: Imprimir reporte */

void imprimirReporte(int *arrCodAlu, char **arrNomAlu, double *arrSumNotas,
        double *arrSumAprob, double *arrCredAprob, double *arrCredDesap,
        int cantAlu, char **arrCodCur, char **arrNomCur, double *arrCredCur,
        char **arrFacCur, int *arrNumAluCur, int *arrNumAprobCur, int cantCur) {
    // Imprimir cabecera
    FILE *arch = abrirArchivo("Reporte.txt", "w");
    fprintf(arch, "%80s\n", "INSTITUCION EDUCATIVA ABC");
    // Imprimir lista de alumnos
    fprintf(arch, "%82s\n", "RESULTADO FINAL DE LOS ALUMNOS");
    separacion('=', arch);
    imprimirAlumnos(arch, arrCodAlu, arrNomAlu, arrSumNotas, arrSumAprob,
            arrCredAprob, arrCredDesap, cantAlu);
    separacion('-', arch);
    // Imprimir lista de cursos
    fprintf(arch, "%81s\n", "RESULTADO FINAL DE LOS CURSOS");
    separacion('=', arch);
    imprimirCursos(arch, arrCodCur, arrNomCur, arrCredCur, arrFacCur,
            arrNumAluCur, arrNumAprobCur, cantCur);
    separacion('-', arch);
    // Imprimir resumen
    fprintf(arch, "%s: %d  %50s: %d\n", "Cantidad de alumnos", cantAlu,
            "Cantidad de cursos", cantCur);
    fclose(arch);
}

void imprimirAlumnos(FILE *arch, int *arrCodAlu, char **arrNomAlu,
        double *arrSumNotas, double *arrSumAprob, double *arrCredAprob,
        double *arrCredDesap, int cantAlu) {
    // Declaración de variables
    double promGeneral, promAprob;
    // Imprimir cabecera de alumnos
    fprintf(arch, "%-8s  %-40s  %s  %s  %s  %s\n", "Codigo", "Nombre",
            "Promedio General", "Promedio Aprobados", "Creditos Aprobados",
            "Creditos Desaprobados");
    // Imprimir lista de alumnos
    for (int i = 0; i < cantAlu; i++) {
        promGeneral = arrSumNotas[i] / (arrCredAprob[i] + arrCredDesap[i]);
        promAprob = arrSumAprob[i] / arrCredAprob[i];
        fprintf(arch, "%8d  %-40s  %10.2lf  %18.2lf  %18.2lf  %18.2lf\n",
                arrCodAlu[i], arrNomAlu[i], promGeneral, promAprob,
                arrCredAprob[i], arrCredDesap[i]);
    }
}

void imprimirCursos(FILE *arch, char **arrCodCur, char **arrNomCur, double *arrCredCur,
        char **arrFacCur, int *arrNumAluCur, int *arrNumAprobCur, int cantCur) {
    // Declaración de variables
    double porcAluAprob;
    // Imprimir cabecera de cursos
    fprintf(arch, "%s  %-60s  %-8s  %-8s  %s\n", "Codigo", "Curso", "Creditos",
            "Facultad", "% de Alumnos que aprobo");
    // Imprimir lista de cursos
    for (int i = 0; i < cantCur; i++) {
        porcAluAprob = 0.0;
        if (arrNumAluCur[i] > 0) {
            porcAluAprob = arrNumAprobCur[i] * 100.0 / arrNumAluCur[i];
        }
        fprintf(arch, "%s  %-60s  %6.2lf  %10s  %14.2lf%%\n", arrCodCur[i],
                arrNomCur[i], arrCredCur[i], arrFacCur[i], porcAluAprob);
    }
}

void liberarEspacios(char **arrCodCur, char **arrNomCur, char **arrFacCur,
        int cantCur, char **arrNomAlu, int cantAlu) {
    for (int i = 0; i < cantCur; i++) {
        free(arrCodCur[i]);
        free(arrNomCur[i]);
        free(arrFacCur[i]);
    }
    for (int i = 0; i < cantAlu; i++) {
        free(arrNomAlu[i]);
    }
}

/* Funciones auxiliares */

FILE *abrirArchivo(const char *nomArch, const char *modo) {
    FILE *arch = fopen(nomArch, modo);
    if (arch == NULL) {
        fprintf(stderr, "No se pudo abrir o crear el archivo %s\n", nomArch);
        exit(1);
    }
    return arch;
}

char *crearCadenaExacta(char *buffer) {
    int longitud = strlen(buffer);
    // Verificar que no haya cambio de línea al final
    if (buffer[longitud-1] == '\n') {
        buffer[longitud-1] = '\0';
        longitud--;
    }
    // Copiar la cadena
    char *cad = (char*)malloc(sizeof(char)*(longitud+1));
    strcpy(cad, buffer);
    return cad;
}

void intercambiarEntero(int *arr, int i, int j) {
    int aux = arr[i];
    arr[i] = arr[j];
    arr[j] = aux;
}

void intercambiarDouble(double *arr, int i, int j) {
    double aux = arr[i];
    arr[i] = arr[j];
    arr[j] = aux;
}

void intercambiarCadena(char **arr, int i, int j) {
    char *aux = arr[i];
    arr[i] = arr[j];
    arr[j] = aux;
}

void separacion(char c, FILE *arch) {
    for (int i = 0; i < MAX_SEPARACION; i++) {
        fputc(c, arch);
    }
    fputc('\n', arch);
}
