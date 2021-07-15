/* 
 * Archivo: auxiliar.c
 * Autor:   Anthony Gutiérrez
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "funciones.h"

FILE* abrirArchivo(const char* nomArch, const char* modo) {
    FILE* arch = fopen(nomArch, modo);
    if (arch == NULL) {
        fprintf(stderr, "No se pudo abrir o crear el archivo %s.\n", nomArch);
        exit(1);
    }
    return arch;
}

char* leerLinea(FILE* archivo, char* cadena, int numCar) {
    /* Leer hasta que encontremos el cambio de línea o el fin del archivo */
    char* resultado = fgets(cadena, numCar, archivo);
    if (resultado == NULL) return NULL;
    /* Si se leyó correctamente, quitar el cambio de línea */
    int longitud = strlen(cadena);
    if (cadena[longitud-1] == '\n') {
        cadena[longitud-1] = '\0';
    }
    return resultado;
}

int separarPalabras(char* cadena, char** palabras, char separador) {
    int numPalabras = 0, i = 0, numCaracteres;
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

void liberarPalabras(char** palabras, int numPalabras) {
    for (int i = 0; i < numPalabras; i++) {
        free(palabras[i]);
    }
}

void repetir(FILE* archivo, char c, int cantidad) {
    for (int i = 0; i < cantidad; i++) {
        fputc(c, archivo);
    }
    fputc('\n', archivo);
}

int obtenerNumRegistros(FILE* archBin, int tamReg) {
    fseek(archBin, 0, SEEK_END);
    int tamArch = ftell(archBin);
    fseek(archBin, 0, SEEK_SET);
    return tamArch / tamReg;
}
