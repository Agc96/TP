/* 
 * Archivo: main.c
 * Autor:   Anthony Gutiérrez
 *
 * Creado el 3 de mayo de 2020, 05:44 PM
 */

#include "funciones.h"

int main() {
    /* Declaración de variables */
    int distrito, anio, mes1, mes2, mes3, mesMayorPago, mesMenorPago;
    double mes1maniana, mes1tarde, mes2maniana, mes2tarde, mes3maniana,
            mes3tarde, mayorPago, menorPago;
    /* Lectura de datos */
    scanf("%d %d %d %d %d", &distrito, &anio, &mes1, &mes2, &mes3);
    leerDetalles(distrito, anio, mes1, mes2, mes3);
    /* Impresión de datos */
    imprimirDatos(distrito, anio, mes1, mes2, mes3);
    return 0;
}
