/* 
 * Archivo: funciones.c
 * Autor:   Anthony Gutiérrez
 */

#include <stdio.h>
#include <stdlib.h>
#include "funciones.h"

void ordenarDatos(int *arrDni, int *cantDatos) {
    /* Abrir el archivo */
    FILE* arch = fopen("DNIs.txt", "r");
    if (arch == NULL) {
        fprintf(stderr, "No se pudo abrir el archivo DNIs.txt\n");
        exit(1);
    }
    /* Iterar línea por línea */
    int dni, posicion;
    while (1) {
        /* Leer los datos */
        fscanf(arch, "%d", &dni);
        if (feof(arch)) break;
        /* Bajar los datos hasta encontrar la posición para insertar */
        for (posicion = *cantDatos; posicion > 0; posicion--) {
            arrDni[posicion] = arrDni[posicion-1];
            if (arrDni[posicion-1] < dni) break;
        }
        /* Insertar ordenadamente y actualizar la cantidad de datos */
        arrDni[posicion] = dni;
        (*cantDatos)++;
    }
    /* Cerrar el archivo */
    fclose(arch);
}

void mostrarDatos(int *arrDni, int cantDatos) {
    /* Abrir el archivo */
    FILE* arch = fopen("DNIs_ordenado.txt", "w");
    if (arch == NULL) {
        fprintf(stderr, "No se pudo crear el archivo DNIs_ordenado.txt\n");
        exit(1);
    }
    /* Imprimir los DNIs ordenadamente */
    int i;
    for (i = 0; i < cantDatos; i++) {
        fprintf(arch, "%08d\n", arrDni[i]);
    }
    /* Cerrar el archivo */
    fclose(arch);
}
