/* 
 * Archivo: funciones.c
 * Autor:   Anthony Gutiérrez
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "curso.h"
#include "alumno.h"
#include "funciones.h"

#define MAX_PALABRAS 30
#define MAX_LINEA 120

/* Parte 1: Leer la lista de cursos */

int leerDatos(struct Alumno alumnos[]) {
    /* Abrir el archivo */
    FILE* archivo = abrirArchivo("Matricula.csv", "r");
    struct Alumno aux;
    char linea[MAX_LINEA], *resultado;
    int numAlumnos = 0;
    /* Leer línea por línea */
    while (1) {
        resultado = leerCadena(linea, MAX_LINEA, archivo);
        if (resultado == NULL) break; /* feof(archivo) */
        analizarAlumno(linea, &aux);
        alumnos[numAlumnos++] = aux;
    }
    /* Cerrar el archivo */
    fclose(archivo);
    return numAlumnos;
}

void analizarAlumno(char* linea, struct Alumno* alumno) {
    /* Leer la cadena de caracteres y separar las palabras */
    char *palabras[MAX_PALABRAS];
    int numPalabras, numCursos = 0, i;
    numPalabras = separarPalabras(linea, palabras, ',');
    /* Asignar los datos prinicpales a la estructura del curso */
    alumno->codigo = atoi(palabras[0]);
    alumno->nombre = palabras[1];
    alumno->pagoCredito = strtod(palabras[numPalabras-1], NULL);
    free(palabras[0]);
    free(palabras[numPalabras-1]);
    /* Asignar los requisitos a la estructura del curso */
    for (i = 2; i < numPalabras - 1; i += 2) {
        alumno->cursos[numCursos].codigo = palabras[i];
        alumno->cursos[numCursos].creditos = strtod(palabras[i+1], NULL);
        numCursos++;
        free(palabras[i+1]);
    }
    alumno->numCursos = numCursos;
}

/* Parte 2: Ordenar el arreglo de cursos */

void ordenarDatos(struct Alumno alumnos[], int numAlumnos) {
    int i, j, numCursosMenor, numCursosIgual, nombreMayor;
    /* Ordenar los alumnos con el algoritmo bubble sort */
    for (i = 0; i < numAlumnos - 1; i++) {
        for (j = i+1; j < numAlumnos; j++) {
            /* Ordenar por el número de cursos de mayor a menor, si es igual
             * entonces ordenar por el nombre de menor a mayor */
            numCursosMenor = alumnos[i].numCursos < alumnos[j].numCursos;
            numCursosIgual = alumnos[i].numCursos == alumnos[j].numCursos;
            nombreMayor = strcmp(alumnos[i].nombre, alumnos[j].nombre) > 0;
            if (numCursosMenor || (numCursosIgual && nombreMayor)) {
                intercambiarAlumno(alumnos, i, j);
            }
        }
    }
}

void intercambiarAlumno(struct Alumno alumnos[], int i, int j) {
    struct Alumno aux = alumnos[i];
    alumnos[i] = alumnos[j];
    alumnos[j] = aux;
}

/* Parte 3: Imprimir el reporte */

void imprimirReporte(struct Alumno alumnos[], int numAlumnos, int numCursosSolicitado) {
    /* Abrir el archivo */
    FILE* reporte = abrirArchivo("SolicitudDeAlumnos.txt", "w");
    int i, numAlumnosSolicitado = 0;
    /* Imprimir la cabecera del reporte */
    fprintf(reporte, "Numero de cursos solicitado: %d\n", numCursosSolicitado);
    separacion(reporte, '=');
    fprintf(reporte, "%-8s  %-40s  %-10s  %-26s  %-10s\n", "Codigo", "Alumno",
            "PagoXCred.", "Cursos (Codigo/Creditos)", "Tot. pagar");
    separacion(reporte, '=');
    /* Mostrar todos los cursos con el número de requisitos especificado */
    for (i = 0; i < numAlumnos; i++) {
        if (alumnos[i].numCursos == numCursosSolicitado) {
            imprimirAlumno(reporte, &(alumnos[i]));
            numAlumnosSolicitado++;
        }
    }
    /* Imprimir el resumen del reporte */
    separacion(reporte, '=');
    fprintf(reporte, "Total de alumnos: %d\n", numAlumnosSolicitado);
    /* Cerrar el archivo */
    fclose(reporte);
}

void imprimirAlumno(FILE* reporte, struct Alumno* alumno) {
    double totalPagar = 0;
    int j;
    /* Imprimir el código, nombre y cantidad de créditos del curso */
    fprintf(reporte, "%08d  %-40s  %10.2lf  ", alumno->codigo, alumno->nombre,
            alumno->pagoCredito);
    /* Imprimir la lista de requisitos y calcular el promedio de niveles */
    for (j = 0; j < alumno->numCursos; j++) {
        fprintf(reporte, "%6s/%4.2lf  ", alumno->cursos[j].codigo,
                alumno->cursos[j].creditos);
        totalPagar += (alumno->cursos[j].creditos) * (alumno->pagoCredito);
    }
    /* Imprimir el promedio de niveles */
    fprintf(reporte, "  %10.2lf\n", totalPagar);
}

/* Parte 4: Liberar los espacios dinámicos */

void liberarDatos(struct Alumno alumnos[], int numAlumnos) {
    int i, j;
    for (i = 0; i < numAlumnos; i++) {
        free(alumnos[i].nombre);
        for (j = 0; j < alumnos[i].numCursos; j++) {
            free(alumnos[i].cursos[j].codigo);
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

char* leerCadena(char* cadena, int max, FILE* archivo) {
    /* Leer la cadena del archivo de texto */
    char *resultado = fgets(cadena, max, archivo);
    if (resultado == NULL) return NULL;
    /* Quitar el cambio de línea de la cadena */
    int longitud = strlen(cadena);
    if (cadena[longitud-1] == '\n') {
        cadena[longitud-1] = '\0';
    }
    return resultado;
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
