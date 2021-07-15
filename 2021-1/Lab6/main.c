/*
 * Archivo: main.c
 * Autor:   Anthony Gutiérrez
 *
 * Creado el 11 de julio de 2021, 08:08 PM
 */

#include "funcionesLab6.h"

int main() {
    crearArchBinBuses();
    verificarArchBinBuses();
    llenarPasajeros();
    ordenarArchBinBuses();
    imprimirReporte();
    return 0;
}
