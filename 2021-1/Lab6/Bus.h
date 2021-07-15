/*
 * Archivo: Bus.h
 * Autor:   Anthony Gutiérrez
 *
 * Creado el 11 de julio de 2021, 08:14 PM
 */

#ifndef BUS_H
#define BUS_H

#include "Pasajero.h"

#define MAX_PLACA 8
#define MAX_CHOFER 50
#define MAX_CIUDADES 60
#define MAX_PASAJEROS 50

struct Bus {
    char placa[MAX_PLACA];
    char chofer[MAX_CHOFER];
    int numeroDeAsientos;
    char ciudadesDestino[MAX_CIUDADES];
    struct Pasajero pasajeros[MAX_PASAJEROS];
    int numeroDePasajeros;
};

#endif /* BUS_H */
