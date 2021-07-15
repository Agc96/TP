/* 
 * Archivo: autor.h
 * Autor:   Anthony Gutiérrez
 */

#ifndef AUTOR_H
#define AUTOR_H

#define MAX_NOMBRE 40

struct Autor {
    int codigo;
    char nombre[MAX_NOMBRE];
    int cantLibros;
    double regalias;
};

#endif /* AUTOR_H */
