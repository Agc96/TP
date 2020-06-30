/* 
 * Archivo: alumno.h
 * Autor:   Anthony Gutiérrez
 */

#ifndef ALUMNO_H
#define ALUMNO_H

#include "curso.h"

#define MAX_CURSOS 10

struct Alumno {
    int codigo;
    char* nombre;
    int numCursos;
    struct Curso cursos[MAX_CURSOS];
    double pagoCredito;
};

#endif /* ALUMNO_H */

