/*
 * Archivo: main.c
 * Autor:   Anthony Gutiérrez
 *
 * Creado el 30 de noviembre de 2020, 08:12 PM
 */

#include "funcionesPacientes.h"


int main() {
    struct Medico medicos[50];
    struct Paciente pacientes[300];
    int numMedicos = 0, numPacientes = 0;

    leerMedicos(medicos, &numMedicos);
    leerPacientes(medicos, numMedicos, pacientes, &numPacientes);
    imprimirReporte(medicos, numMedicos, pacientes, numPacientes);
    liberarEspacios(medicos, numMedicos, pacientes, numPacientes);

    return 0;
}
