/*
 * Archivo:      Autor.h
 * Autor:        Anthony Gutiérrez
 * Fecha y hora: 28 de junio de 2022, 08:06 AM
 */

#ifndef AUTOR_H
#define AUTOR_H

struct Autor {
    char codigo[8];
    char nombre[40];
    int cantLibros;
    double monto;
};

#endif /* AUTOR_H */
