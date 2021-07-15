/* 
 * Archivo: main.c
 * Autor:   Anthony Gutiérrez
 *
 * Creado el 14 de septiembre de 2020, 07:07 PM
 */

#include <stdio.h>
#include <stdlib.h>
#include "funciones.h"

int main() {
    /* Declaración de variables */
    int numCuenta, continuar = 1, cantDepositos, cantRetiros, cantClientes = 1;
    double saldoInicial, haber, debe, monto;
    char estado, transaccion;
    /* Leer datos y transacciones de una cuenta */
    leerDatosCuenta(&numCuenta, &saldoInicial, &haber, &debe, &estado, &cantDepositos, &cantRetiros);
    while (continuar) {
        /* Imprimir estado de la cuenta y leer una nueva transacción */
        imprimirEstadoCuenta(numCuenta, saldoInicial, haber, debe, estado);
        leerTransaccion(&transaccion, &monto);
        /* Determinar acciones según el tipo de transacción */
        switch (transaccion) {
            case 'D':
                procesarDeposito(&haber, &debe, &estado, monto, &cantDepositos);
                break;
            case 'R':
                procesarRetiro(&haber, &debe, &estado, monto, &cantRetiros);
                break;
            case 'C':
                imprimirResumenCuenta(haber, debe, estado, cantDepositos, cantRetiros);
                leerDatosCuenta(&numCuenta, &saldoInicial, &haber, &debe, &estado, &cantDepositos, &cantRetiros);
                cantClientes++;
                break;
            case 'F':
                imprimirResumenFinal(cantClientes);
                continuar = 0;
                break;
        }
    }
    return 0;
}
