/*
 * Archivo:      Libro.h
 * Autor:        Anthony Gutiérrez
 * Fecha y hora: 28 de junio de 2022, 08:08 AM
 */

#ifndef LIBRO_H
#define LIBRO_H

#include "LibroAutor.h"

struct Libro {
    char codigo[9];
    char nombre[60];
    double precio;
    struct LibroAutor autores[10];
    int cantAutores;
    int cantLibros;
    double totRecaudado;
    double totSinRegalias;
};

#endif /* LIBRO_H */
