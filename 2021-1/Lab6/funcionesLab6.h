/*
 * Archivo: funcionesLab6.h
 * Autor:   Anthony Gutiérrez
 *
 * Creado el 11 de julio de 2021, 08:21 PM
 */

#ifndef FUNCIONES_H
#define FUNCIONES_H

#include <stdio.h>
#include <stdlib.h>
#include "Pasajero.h"
#include "Bus.h"

void crearArchBinBuses();
void verificarArchBinBuses();

void llenarPasajeros();
void llenarDatosPasajero(char *, char **, int, struct Pasajero *);
int buscarBus(FILE *, int, struct Bus *, struct Pasajero*);
void actualizarBusEnArchBin(struct Bus *, struct Pasajero *, FILE *, int);

void ordenarArchBinBuses();
int calcularCantDestinos(struct Bus *);

void imprimirReporte();
void imprimirDatosBus(FILE *, struct Bus *, int);
void corregirPalabraDestino(char *);

// Funciones auxiliares
int obtenerNumRegArchBin(FILE *, int);
void imprimirLinea(FILE *, char, int);

#endif /* FUNCIONES_H */
