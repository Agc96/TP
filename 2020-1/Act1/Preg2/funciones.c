/* 
 * Archivo: funciones.c
 * Autor:   Anita
 *
 * Creado el 3 de mayo de 2020, 05:47 PM
 */

#include <stdio.h>
#define MAX_LINEA 80

void imprimirDatos(int distrito, int anho, int mes1, double mes1maniana,
        double mes1tarde, int mes2, double mes2maniana, double mes2tarde,
        int mes3, double mes3maniana, double mes3tarde) {
    /* Declaración de variables */
    int menorMes, mayorMes;
    double mes1total = mes1maniana + mes1tarde;
    double mes2total = mes2maniana + mes2tarde;
    double mes3total = mes3maniana + mes3tarde;
    double menorPago, mayorPago;
    /* Imprimir cabecera */
    printf("PAGOS AL PROVEEDOR DE ENTREGA A DOMICILIO TP2020\n");
    printf("Distrito: %d\n", distrito);
    printf("Año: %d\n", anho);
    repetir('=', MAX_LINEA, 1);
    /* Imprimir datos de cada mes */
    imprimirMes(mes1, mes1maniana, mes1tarde, mes1total);
    imprimirMes(mes2, mes2maniana, mes2tarde, mes2total);
    imprimirMes(mes3, mes3maniana, mes3tarde, mes3total);
    /* Calcular e imprimir estadísticas */
    calcularEstadistica(mes1, mes2,);
    calcularEstadistica();
    printf("Mes con mayor pago al proveedor: %02d - S/ %8.2lf\n", mayorMes, mayorPago);
    printf("Mes con menor pago al proveedor: %02d - S/ %8.2lf\n", menorMes, menorPago);
}

void imprimirMes(int mes, double maniana, double tarde, double total) {
    printf("Mes: %02d\n\n", mes);
    printf("Por la entrega en la mañana: S/ %4.2lf\n", maniana);
    printf("Por la entrega por la tarde: S/ %4.2lf\n", tarde);
    printf("Total por la entrega: S/ %4.2lf\n", total);
    repetir('=', MAX_LINEA, 1);
}

void calcularEstadistica(int mes1, double mes1total, int mes2, double mes2total,
        int mes3, double mes3total, int* estMes, int* estPago, int mayor) {
    /* Comenzamos asumiendo que el mes 1 es el mayor/menor */
    *estMes = mes1;
    *estPago = mes1total;
    /* Verificar si el mes 2 es mayor/menor */
    if (comparar(mes2total, *estPago, mayor)) {
        *estMes = mes2;
        *estPago = mes2total;
    }
    /* Verificar si el mes 3 es mayor/menor */
    if (comparar(mes3total, *estPago, mayor)) {
        *estMes = mes3;
        *estPago = mes3total;
    }
}

int comparar(double valor1, double valor2, int mayor) {
    return mayor ? valor1 > valor2 : valor1 < valor2;
}

/* Funciones auxiliares */

int crearFecha(int dia, int mes, int anio) {
    return 10000 * anio + 100 * mes + dia;
}

int crearHora(int hora, int minuto, int segundo) {
    return 3600 * hora + 60 * minuto + segundo;
}

void repetir(char caracter, int cantidad, int agregarFinLinea) {
    int i;
    for (i = 0; i < cantidad; i++) {
        putchar(caracter);
    }
    if (agregarFinLinea) putchar('\n');
}
