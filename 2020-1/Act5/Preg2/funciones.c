/* 
 * Archivo: funciones.c
 * Autor:   Anthony Gutiérrez
 */

#include <stdio.h>
#include <stdlib.h>
#include "funciones.h"

void ordenarDatos(int *arrDni, int *arrTelef, double *arrSueldo, int *cantDatos) {
    /* Abrir el archivo */
    FILE* arch = fopen("Personas.txt", "r");
    if (arch == NULL) {
        fprintf(stderr, "No se pudo abrir el archivo Personas.txt\n");
        exit(1);
    }
    /* Iterar línea por línea */
    int dni, telef, posicion;
    double sueldo;
    while (1) {
        /* Leer los datos */
        fscanf(arch, "%d %d %lf", &dni, &telef, &sueldo);
        if (feof(arch)) break;
        /* Bajar los datos hasta encontrar la posición a insertar */
        for (posicion = *cantDatos; posicion > 0; posicion--) {
            arrDni[posicion] = arrDni[posicion-1];
            arrTelef[posicion] = arrTelef[posicion-1];
            arrSueldo[posicion] = arrSueldo[posicion-1];
            if (arrSueldo[posicion-1] < sueldo) break;
        }
        /* Insertar ordenadamente y actualizar la cantidad de datos */
        arrDni[posicion] = dni;
        arrTelef[posicion] = telef;
        arrSueldo[posicion] = sueldo;
        (*cantDatos)++;
    }
    /* Cerrar el archivo */
    fclose(arch);
}

void mostrarDatos(int *arrDni, int *arrTelef, double *arrSueldo, int cantDatos) {
    /* Abrir el archivo */
    FILE* arch = fopen("Personas_ordenado.txt", "w");
    if (arch == NULL) {
        fprintf(stderr, "No se pudo crear el archivo Personas_ordenado.txt\n");
        exit(1);
    }
    /* Imprimir los datos ordenadamente */
    int i;
    for (i = 0; i < cantDatos; i++) {
        fprintf(arch, "%08d %12d %10.2lf\n", arrDni[i], arrTelef[i], arrSueldo[i]);
    }
    /* Cerrar el archivo */
    fclose(arch);
}
