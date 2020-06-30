/* 
 * Archivo: main.c
 * Autor:   Anthony Gutiérrez
 *
 * Creado el 2 de mayo de 2020, 05:40 PM
 */

#include "funciones.h"

int main() {
    /* Declaración de variables */
    int dia, mes, anho, fechaTope, codAlmacen1, codAlmacen2;

    /* Leer la cabecera */
    scanf("%d/%d/%d %d %d", &dia, &mes, &anho, &codAlmacen1, &codAlmacen2);
    fechaTope = convertirFecha(dia, mes, anho);
    /* Imprimir la cabecera */
    printf("%50s\n", "ALMACENES TP2020");
    separador('=');

    /* Leer uno por uno los movimientos */
    procesarDetalles(fechaTope, codAlmacen1, codAlmacen2);

    return 0;
}

