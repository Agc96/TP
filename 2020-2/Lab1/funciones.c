/*
 * Archivo: funciones.c
 * Autor: 20130095 Anthony Gutiérrez
 * Creado el 08/09/2020 a las 8:47
 */

#include <stdio.h>
#include <stdlib.h>
#include "funciones.h"

double solucionDeEcuacion(double c2, double c1, double c0, double x) {
    double fxx;
    fxx = c2*x*x + c1*x + c0;
    return fxx;
}
