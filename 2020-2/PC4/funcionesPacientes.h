/*
 * Archivo: funciones.h
 * Autor:   Anthony Gutiérrez
 *
 * Creado el 30 de noviembre de 2020, 08:20 PM
 */

#ifndef FUNCIONESPACIENTES_H
#define FUNCIONESPACIENTES_H

#include <stdio.h>
#include <stdlib.h>
#include "Medico.h"
#include "Paciente.h"

/* Parte 1: Leer el archivo de médicos */

void leerMedicos(struct Medico *, int *);

/* Parte 2: Leer el archivo de citas */

void leerPacientes(struct Medico *, int, struct Paciente *, int *);
void agregarPaciente(int, struct Medico *, int, struct Paciente *, int *, int,
        char *, double, char *);
int buscarMedico(struct Medico *, int, char *);
int buscarPaciente(struct Paciente *, int, int);

/* Parte 3: Imprimir el reporte */

void imprimirReporte(struct Medico *, int, struct Paciente *, int);
void imprimirCitas(FILE *, struct Medico *, int);
void liberarEspacios(struct Medico *, int, struct Paciente *, int);

/* Funciones auxiliares */

void separacion(char, FILE *);

#endif /* FUNCIONESPACIENTES_H */
