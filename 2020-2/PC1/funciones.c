/* 
 * Archivo: funciones.c
 * Autor:   Anthony Gutiérrez
 *
 * Creado el 14 de septiembre de 2020, 07:58 PM
 */

#include <stdio.h>
#include <stdlib.h>
#include "funciones.h"

void leerDatosCuenta(int *numCuenta, double *saldoInicial, double *haber, double *debe, char *estado, int *cantDepositos, int *cantRetiros) {
    /* Leer datos principales de la cuenta */
    printf("Ingrese el numero de cuenta y el saldo inicial: ");
    scanf("%d %lf", numCuenta, saldoInicial);
    /* Calcular datos derivados de la cuenta */
    if (*saldoInicial >= 0) {
        *haber = *saldoInicial;
        *debe = 0;
        *estado = 'H';
    } else {
        *haber = 0;
        *debe = -(*saldoInicial);
        *estado = 'I';
    }
    /* Inicializar contadores */
    *cantDepositos = *cantRetiros = 0;
}

void leerTransaccion(char *transaccion, double *monto) {
    printf("Ingrese una transaccion: ");
    scanf(" %c %lf", transaccion, monto);
}

void imprimirEstadoCuenta(int numCuenta, double saldoInicial, double haber, double debe, char estado) {
    printf("Estado de la cuenta: %d\n", numCuenta);
    printf("%15s %10s %10s %10s\n", "SALDO INICIAL", "HABER", "DEBE", "ESTADO");
    printf("%15.2lf %10.2lf %10.2lf %10c\n", saldoInicial, haber, debe, estado);
}

void procesarDeposito(double *haber, double *debe, char *estado, double monto, int *cantDepositos) {
    if (*estado == 'H') {
        /* Caso 1: el saldo está en la variable "haber" */
        *haber += monto;
    } else {
        /* Caso 2: el saldo está en la variable "debe" */
        *debe -= monto;
        if (*debe < 0) {
            *haber = -(*debe);
            *debe = 0;
            *estado = 'H';
        }
    }
    /* Actualizar contador de depósitos */
    (*cantDepositos)++;
}

void procesarRetiro(double *haber, double *debe, char *estado, double monto, int *cantRetiros) {
    if (*estado == 'H') {
        /* Caso 1: el saldo está en la variable "haber" */
        *haber -= monto;
        if (*haber < 0) {
            *debe = -(*haber);
            *haber = 0;
            *estado = 'I';
        }
    } else {
        /* Caso 2: el saldo está en la variable "debe" */
        *debe += monto;
    }
    /* Actualizar contador de retiros */
    (*cantRetiros)++;
}

void imprimirResumenCuenta(double haber, double debe, char estado, int cantDepositos, int cantRetiros) {
    /* Imprimir saldo final */
    if (estado == 'H') {
        printf("SALDO FINAL: %.2lf - Cuenta habilitada\n", haber);
    } else {
        printf("SALDO FINAL: %.2lf - Cuenta inhabilitada\n", -debe);
    }
    /* Imprimir cantidades de depósitos y retiros */
    printf("Cantidad de depositos: %d     Cantidad de retiros: %d\n", cantDepositos, cantRetiros);
}

void imprimirResumenFinal(int cantClientes) {
    printf("*** FIN DEL PROCESO ***\n");
    printf("Numero de clientes atendidos: %d\n", cantClientes);
}
