/*
 * Archivo: main.c
 * Autor:   Anthony Gutiérrez
 *
 * Creado el 25 de mayo de 2021, 10:24 AM
 */

#include <stdio.h>
#include <stdlib.h>
#include "funciones.h"

int main() {
    FILE* archListPrec = abrirArchivo("ListaDePrecios.txt", "r");
    FILE* archPlatos = abrirArchivo("Platos.txt", "r");
    FILE* archPreparar = abrirArchivo("PlatosAPreparar.txt", "r");
    FILE* archReporte = abrirArchivo("Reporte.txt", "w");
    generarReporte(archListPrec, archPlatos, archPreparar, archReporte);
    return 0;
}
