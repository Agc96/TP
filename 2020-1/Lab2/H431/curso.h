/* 
 * Archivo: curso.h
 * Autor:   Anthony Gutiérrez
 */

#ifndef CURSO_H
#define CURSO_H

#include "requisito.h"

#define MAX_REQUISITOS 10

struct Curso {
    char* codigo;
    char* nombre;
    int numRequisitos;
    struct Requisito requisitos[MAX_REQUISITOS];
    double creditos;
};

#endif /* CURSO_H */
