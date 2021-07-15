/*
 * Archivo: Pasajero.h
 * Autor:   Anthony Gutiérrez
 *
 * Creado el 11 de julio de 2021, 08:14 PM
 */

#ifndef PASAJERO_H
#define PASAJERO_H

#define MAX_NOMBRE 50
#define MAX_DESTINO 20

struct Pasajero {
    int dni;
    char nombre[MAX_NOMBRE];
    char destino[MAX_DESTINO];
};

#endif /* PASAJERO_H */
