/* 
 * Archivo: libro.h
 * Autor:   Anita
 *
 * Creado el 16 de julio de 2020, 05:31 PM
 */

#ifndef LIBRO_H
#define LIBRO_H

#include "registro.h"

#define MAX_CODIGO 10
#define MAX_TITULO 60
#define MAX_AUTOR 10

struct Libro {
    char codigo[MAX_CODIGO];
    char titulo[MAX_TITULO];
    double precio;
    int cantVenta;
    double totalVenta;
    struct Registro autores[MAX_AUTOR];
    int cantAutores;
};

#endif /* LIBRO_H */

