/* 
 * Archivo: funciones.c
 * Autor:   Anthony Gutiérrez
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "requisito.h"
#include "curso.h"
#include "funciones.h"

#define MAX_PALABRAS 30
#define MAX_LINEA 120

/* Parte 1: Leer la lista de cursos */

int leerDatos(struct Curso cursos[]) {
    /* Abrir el archivo */
    FILE* archivo = abrirArchivo("Cursos.csv", "r");
    struct Curso aux;
    char linea[MAX_LINEA];
    int numCursos = 0;
    /* Leer línea por línea */
    while (1) {
        leerCadena(linea, MAX_LINEA, archivo);
        if (feof(archivo)) break;
        analizarCurso(linea, &aux);
        cursos[numCursos++] = aux;
    }
    /* Cerrar el archivo */
    fclose(archivo);
    return numCursos;
}

void analizarCurso(char* linea, struct Curso* curso) {
    /* Leer la cadena de caracteres y separar las palabras */
    char *palabras[MAX_PALABRAS];
    int numPalabras, numRequisitos = 0, i;
    numPalabras = separarPalabras(linea, palabras, ',');
    /* Asignar los datos prinicpales a la estructura del curso */
    curso->codigo = palabras[0];
    curso->nombre = palabras[1];
    curso->creditos = strtod(palabras[numPalabras-1], NULL);
    free(palabras[numPalabras-1]);
    /* Asignar los requisitos a la estructura del curso */
    for (i = 2; i < numPalabras - 1; i += 2) {
        curso->requisitos[numRequisitos].codigo = palabras[i];
        curso->requisitos[numRequisitos].nivel = atoi(palabras[i+1]);
        numRequisitos++;
        free(palabras[i+1]);
    }
    curso->numRequisitos = numRequisitos;
}

/* Parte 2: Ordenar el arreglo de cursos */

void ordenarDatos(struct Curso cursos[], int numCursos) {
    int i, j, numReqMenor, numReqIgual, codigoMayor;
    /* Ordenar los cursos con el algoritmo bubble sort */
    for (i = 0; i < numCursos - 1; i++) {
        for (j = i+1; j < numCursos; j++) {
            /* Ordenar por el número de requisitos de mayor a menor, si es
             * igual entonces ordenar por el código de menor a mayor */
            numReqMenor = cursos[i].numRequisitos < cursos[j].numRequisitos;
            numReqIgual = cursos[i].numRequisitos == cursos[j].numRequisitos;
            codigoMayor = strcmp(cursos[i].codigo, cursos[j].codigo) > 0;
            if (numReqMenor || (numReqIgual && codigoMayor)) {
                intercambiarCurso(cursos, i, j);
            }
        }
    }
}

void intercambiarCurso(struct Curso cursos[], int i, int j) {
    struct Curso aux = cursos[i];
    cursos[i] = cursos[j];
    cursos[j] = aux;
}

/* Parte 3: Imprimir el reporte */

void imprimirReporte(struct Curso cursos[], int numCursos, int numReqSolicitado) {
    /* Abrir el archivo */
    FILE* reporte = abrirArchivo("CursosSolicitados.txt", "w");
    int i, numCursosMostrados = 0;
    /* Imprimir la cabecera del reporte */
    fprintf(reporte, "Numero de requisitos ingresado: %d\n", numReqSolicitado);
    separacion(reporte, '=');
    fprintf(reporte, "%-6s  %-55s  %-8s  %-30s  %-8s\n", "Codigo", "Curso",
            "Creditos", "Requisitos (Codigo/Nivel)", "Prom Niv");
    separacion(reporte, '=');
    /* Mostrar todos los cursos con el número de requisitos especificado */
    for (i = 0; i < numCursos; i++) {
        if (cursos[i].numRequisitos == numReqSolicitado) {
            imprimirCurso(reporte, &(cursos[i]));
            numCursosMostrados++;
        }
    }
    /* Imprimir el resumen del reporte */
    separacion(reporte, '=');
    fprintf(reporte, "Total de cursos: %d\n", numCursosMostrados);
    /* Cerrar el archivo */
    fclose(reporte);
}

void imprimirCurso(FILE* reporte, struct Curso* curso) {
    int sumaNiveles = 0, j;
    /* Imprimir el código, nombre y cantidad de créditos del curso */
    fprintf(reporte, "%-6s  %-55s  %8.2lf  ", curso->codigo, curso->nombre,
            curso->creditos);
    /* Imprimir la lista de requisitos y calcular el promedio de niveles */
    for (j = 0; j < curso->numRequisitos; j++) {
        fprintf(reporte, "%6s/%d  ", curso->requisitos[j].codigo,
                curso->requisitos[j].nivel);
        sumaNiveles += curso->requisitos[j].nivel;
    }
    /* Imprimir el promedio de niveles */
    fprintf(reporte, "  %8.2lf\n", (double)sumaNiveles/(curso->numRequisitos));
}

/* Parte 4: Liberar los espacios dinámicos */

void liberarDatos(struct Curso cursos[], int numCursos) {
    int i, j;
    for (i = 0; i < numCursos; i++) {
        free(cursos[i].codigo);
        free(cursos[i].nombre);
        for (j = 0; j < cursos[i].numRequisitos; j++) {
            free(cursos[i].requisitos[j].codigo);
        }
    }
}

/* Funciones auxiliares */

FILE* abrirArchivo(const char* nomArch, const char* modo) {
    FILE* arch = fopen(nomArch, modo);
    if (arch == NULL) {
        fprintf(stderr, "No se pudo abrir o crear el archivo %s.\n", nomArch);
        exit(1);
    }
    return arch;
}

void leerCadena(char* cadena, int max, FILE* archivo) {
    /* Leer la cadena del archivo de texto */
    fgets(cadena, max, archivo);
    /* Quitar el cambio de línea de la cadena */
    int longitud = strlen(cadena);
    if (cadena[longitud-1] == '\n') {
        cadena[longitud-1] = '\0';
    }
}

int separarPalabras(char* cadena, char** palabras, char separador) {
    int i = 0, numPalabras = 0, numCaracteres;
    char buffer[MAX_LINEA], *puntero;
    /* Separar la cadena en palabras y asignar memoria dinámica */
    while (1) {
        /* Descartar los caracteres que coincidan con el caracter separador */
        while (cadena[i] == separador) i++;
        /* Verificar si se terminó la cadena */
        if (cadena[i] == '\0') break;
        /* Copiar los caracteres de la palabra en el búfer */
        numCaracteres = 0;
        while (cadena[i] != separador && cadena[i] != '\0') {
            buffer[numCaracteres++] = cadena[i++];
        }
        buffer[numCaracteres++] = '\0';
        /* Asignar memoria dinámica para la palabra */
        puntero = (char*)malloc(sizeof(char)*numCaracteres);
        strcpy(puntero, buffer);
        palabras[numPalabras++] = puntero;
    }
    return numPalabras;
}

void separacion(FILE* reporte, char c) {
    int i;
    for (i = 0; i < MAX_LINEA; i++) {
        fputc(c, reporte);
    }
    fputc('\n', reporte);
}
