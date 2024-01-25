/*
 * Archivo: Solicitud.h
 * Autor:   Anthony Gutiérrez
 * Fecha:   19 de junio de 2023, 12:04 PM
 */

#ifndef SOLICITUD_H
#define SOLICITUD_H

#include "Libro.h"

struct Solicitud {
    int dniUsuario;
    char codLibro[MAX_CODIGO_LIBRO];
};

#endif /* SOLICITUD_H */
