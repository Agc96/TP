/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * Archivo: funciones.c
 * Autor:   Anita
 *
 * Creado el 12 de mayo de 2020, 11:02 AM
 */

#include "funciones.h"

/* Funciones auxiliares */

FILE* abrirArchivo(const char* nombre, const char* modo) {
    FILE* archivo = fopen(nombre, modo);
    if (archivo == NULL) {
        fprintf(stderr, "No se pudo abrir o guardar el archivo %s\n", nombre);
        exit(1);
    }
    return archivo;
}
