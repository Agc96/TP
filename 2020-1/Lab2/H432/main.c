/* 
 * Archivo: main.c
 * Autor:   Anthony Gutiérrez
 */

#include <stdio.h>
#include <stdlib.h>
#include "curso.h"
#include "alumno.h"
#include "funciones.h"

#define MAX_ALUMNOS 100

int main() {
    /* Declaración de variables */
    struct Alumno alumnos[MAX_ALUMNOS];
    int numAlumnos, numCursosSolicitado;
    /* Leer el número de requisitos */
    printf("Ingrese el numero de cursos: ");
    scanf("%d", &numCursosSolicitado);
    /* Leer y ordenar los cursos */
    numAlumnos = leerDatos(alumnos);
    ordenarDatos(alumnos, numAlumnos);
    /* Imprimir el reporte */
    imprimirReporte(alumnos, numAlumnos, numCursosSolicitado);
    liberarDatos(alumnos, numAlumnos);
    return 0;
}
