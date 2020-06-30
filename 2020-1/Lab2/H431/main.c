/* 
 * Archivo: main.c
 * Autor:   Anthony Gutiérrez
 */

#include <stdio.h>
#include <stdlib.h>
#include "requisito.h"
#include "curso.h"
#include "funciones.h"

#define MAX_CURSOS 100

int main() {
    /* Declaración de variables */
    struct Curso cursos[MAX_CURSOS];
    int numCursos, numReqSolicitado;
    /* Leer el número de requisitos */
    printf("Ingrese el numero de requisitos: ");
    scanf("%d", &numReqSolicitado);
    /* Leer y ordenar los cursos */
    numCursos = leerDatos(cursos);
    ordenarDatos(cursos, numCursos);
    /* Imprimir el reporte */
    imprimirReporte(cursos, numCursos, numReqSolicitado);
    liberarDatos(cursos, numCursos);
    return 0;
}
