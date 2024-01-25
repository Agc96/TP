/*
 * Archivo: Libro.h
 * Autor:   Anthony Gutiérrez
 * Fecha:   19 de junio de 2023, 12:00 PM
 */

#ifndef LIBRO_H
#define LIBRO_H

#define MAX_CODIGO_LIBRO 10
#define MAX_TITULO_LIBRO 35
#define MAX_AUTOR_LIBRO 32

struct Libro {
    char codigo[MAX_CODIGO_LIBRO];
    char titulo[MAX_TITULO_LIBRO];
    char autor[MAX_AUTOR_LIBRO];
    int cantVolumenes;
    double precio;
    int cantPrestados; // = 0
};

#endif /* LIBRO_H */
