/*
 * Archivo: main.cpp
 * Autor:   Anthony Gutiérrez
 * Fecha:   15 de junio de 2024, 02:02 PM
 */

#include <iostream>
#include <cstdlib>
using namespace std;
#include "Facultad.h"
#include "Alumno.h"
#include "funciones.h"

#define MAX_ALUMNOS 100

int main() {
    struct Alumno alumnos[MAX_ALUMNOS];
    int numAlumnos = 0;
    leerCalificaciones(alumnos, numAlumnos);
    leerAlumnos(alumnos, numAlumnos);
    leerFacultades(alumnos, numAlumnos);
    emitirReporte(alumnos, numAlumnos);
    return 0;
}
