/*
 * Archivo: Usuario.h
 * Autor:   Anthony Gutiérrez
 * Fecha:   19 de junio de 2023, 12:02 PM
 */

#ifndef USUARIO_H
#define USUARIO_H

#define MAX_NOMBRE_USUARIO 40

struct Usuario {
    int dni;
    char nombre[MAX_NOMBRE_USUARIO];
    char categoria;
    double calificacion;
    int cantPrestados; // = 0
    int cantNoPrestados; // = 0
};

#endif /* USUARIO_H */

