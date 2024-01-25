/*
 * Archivo:      main.c
 * Autor:        Anthony Gutiérrez
 * Fecha y hora: 4 de junio de 2022, 03:52 PM
 */

#include <stdio.h>
#include <stdlib.h>
#include "funciones.h"

#define MAX_CURSOS 50
#define MAX_ALUMNOS 100

int main() {
    int arrCodCur[MAX_CURSOS], arrCodAlu[MAX_CURSOS], arrAluApCur[MAX_CURSOS]={},
            arrAluDesCur[MAX_CURSOS]={}, arrCurApAlu[MAX_ALUMNOS]={},
            arrCurDesAlu[MAX_ALUMNOS]={}, cantCur, cantAlu;
    double arrCredCur[MAX_CURSOS], arrCredApAlu[MAX_ALUMNOS],
            arrCredDesAlu[MAX_ALUMNOS], arrCredFacuAlu[MAX_ALUMNOS],
            arrSumaNotasAlu[MAX_ALUMNOS]={}, arrCredApCurso[MAX_ALUMNOS]={},
            arrCredDesCurso[MAX_ALUMNOS]={};
    leerCursos(arrCodCur, arrCredCur, &cantCur);
    leerAlumnos(arrCodAlu, arrCredApAlu, arrCredDesAlu, arrCredFacuAlu, &cantAlu);
    leerNotas(arrCodCur, arrCredCur, arrAluApCur, arrAluDesCur, cantCur, arrCodAlu,
            arrCurApAlu, arrCurDesAlu, arrSumaNotasAlu, arrCredApCurso, arrCredDesCurso,
            arrCredApAlu, arrCredDesAlu, cantAlu);
    ordenarAlumnos(arrCodAlu, arrCurApAlu, arrCurDesAlu, arrSumaNotasAlu,
            arrCredApCurso, arrCredDesCurso, arrCredApAlu, arrCredDesAlu,
            arrCredFacuAlu, cantAlu);
    imprimirReporte(arrCodCur, arrAluApCur, arrAluDesCur, cantCur, arrCodAlu,
            arrCurApAlu, arrCurDesAlu, arrSumaNotasAlu, arrCredApCurso, arrCredDesCurso,
            arrCredApAlu, arrCredDesAlu, arrCredFacuAlu, cantAlu);
    return 0;
}
