/*
 * Archivo: Medico.h
 * Autor:   Anthony Gutiérrez
 *
 * Creado el 30 de noviembre de 2020, 08:23 PM
 */

#ifndef MEDICO_H
#define MEDICO_H

#include "Cita.h"

struct Medico {
    char *codigo;
    char *nombre;
    char *especialidad;
    double tarifa;
    struct Cita citas[100];
    int numCitas;
};

#endif /* MEDICO_H */
