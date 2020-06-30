/* 
 * Archivo: funciones.c
 * Autor:   Anita
 *
 * Creado el 2 de mayo de 2020, 05:55 PM
 */

#include <stdio.h>
#include <limits.h>
#include "funciones.h"
#define MAX_LINEA 80

void procesarDetalles(int fechaTope, int codAlmacen1, int codAlmacen2) {
    /* Declaración de variables */
    int codInterno, codProd, codProdAnterior = 0, codAlmacenLeido, fechaLeida,
            ingresosConteo = 0, salidasConteo = 0, fechaMenor = INT_MAX,
            fechaMayor = INT_MIN;
    double cantLeida, precioUnit, ingresosCant1 = 0, ingresosTotal1 = 0,
            salidasCant1 = 0, salidasTotal1 = 0, ingresosCant2 = 0,
            ingresosTotal2 = 0, salidasCant2 = 0, salidasTotal2 = 0,
            ingresosSumaPU = 0, salidasSumaPU = 0;
    /* Leer los datos de cada movimiento */
    while (1) {
        if (leerMovimiento(&codInterno, &codProd, &codAlmacenLeido, &cantLeida,
                &precioUnit, &fechaLeida)) break;
        /* Verificar si cambió el código del producto */
        if (codProdAnterior != 0 && codProdAnterior != codProd) {
            imprimirProducto(codProdAnterior, fechaTope, codAlmacen1, codAlmacen2,
                    &ingresosCant1, &ingresosTotal1, &salidasCant1, &salidasTotal1,
                    &ingresosCant2, &ingresosTotal2, &salidasCant2, &salidasTotal2,
                    &ingresosSumaPU, &salidasSumaPU, &ingresosConteo, &salidasConteo,
                    &fechaMenor, &fechaMayor);
        }
        codProdAnterior = codProd;
        /* Verificar si la fecha leída es mayor o igual al tope */
        if (fechaLeida >= fechaTope) {
            /* Verificar que el código del almacén esté dentro del rango */
            if (codAlmacenLeido == codAlmacen1) {
                actualizarContadores(codInterno, cantLeida, precioUnit, &ingresosCant1,
                        &ingresosTotal1, &ingresosSumaPU, &ingresosConteo, &salidasCant1,
                        &salidasTotal1, &salidasSumaPU, &salidasConteo, fechaLeida,
                        &fechaMenor, &fechaMayor);
            } else if (codAlmacenLeido == codAlmacen2) {
                actualizarContadores(codInterno, cantLeida, precioUnit, &ingresosCant2,
                        &ingresosTotal2, &ingresosSumaPU, &ingresosConteo, &salidasCant2,
                        &salidasTotal2, &salidasSumaPU, &salidasConteo, fechaLeida,
                        &fechaMenor, &fechaMayor);
            }
        }
    }
    /* Imprimir los datos del último producto */
    imprimirProducto(codProdAnterior, fechaTope, codAlmacen1, codAlmacen2,
            &ingresosCant1, &ingresosTotal1, &salidasCant1, &salidasTotal1,
            &ingresosCant2, &ingresosTotal2, &salidasCant2, &salidasTotal2,
            &ingresosSumaPU, &salidasSumaPU, &ingresosConteo, &salidasConteo,
            &fechaMenor, &fechaMayor);
}

int leerMovimiento(int* codInterno, int* codProd, int* codAlmacen,
        double* cantidad, double* precioUnit, int* fecha) {
    /* Declaración de variables */
    int dia, mes, anho, resultado;
    /* Leer el código del movimiento */
    resultado = scanf("%3d%4d%4d", codInterno, codProd, codAlmacen);
    if (resultado != 3) return 1;
    /* Leer el resto de datos del movimiento */
    scanf("%lf %lf %d/%d/%d", cantidad, precioUnit, &dia, &mes, &anho);
    *fecha = convertirFecha(dia, mes, anho);
    return 0;
}

void actualizarContadores(int codInterno, double cantidad, double precioUnit,
        double* ingresosCant, double* ingresosTotal, double* ingresosSumaPU,
        int* ingresosConteo, double* salidasCant, double* salidasTotal,
        double* salidasSumaPU, int* salidasConteo, int fechaLeida,
        int* fechaMenor, int* fechaMayor) {
    /* Verificar si es ingreso o salida */
    if (codInterno % 2 == 0) {
        *salidasCant += cantidad;
        *salidasTotal += (cantidad * precioUnit);
        *salidasSumaPU += precioUnit;
        (*salidasConteo)++;
    } else {
        *ingresosCant += cantidad;
        *ingresosTotal += (cantidad * precioUnit);
        *ingresosSumaPU += precioUnit;
        (*ingresosConteo)++;
    }
    /* Actualizar fechas */
    if (*fechaMenor > fechaLeida) {
        *fechaMenor = fechaLeida;
    }
    if (*fechaMayor < fechaLeida) {
        *fechaMayor = fechaLeida;
    }
}

void imprimirProducto(int codProducto, int fechaTope, int codAlmacen1, int codAlmacen2,
        double* ingresosCant1, double* ingresosTotal1, double* salidasCant1, double* salidasTotal1,
        double* ingresosCant2, double* ingresosTotal2, double* salidasCant2, double* salidasTotal2,
        double* ingresosSumaPU, double* salidasSumaPU, int* ingresosConteo, int* salidasConteo,
        int* fechaMenor, int* fechaMayor) {
    /* Declaración de variables */
    double puPromAdquisicion = calcularPuPromedio(*ingresosSumaPU, *ingresosConteo);
    double puPromVenta = calcularPuPromedio(*salidasSumaPU, *salidasConteo);
    /* Imprimir datos del producto */
    printf("PRODUCTO: %04d %20s: ", codProducto, "Fecha tope");
    imprimirFecha(fechaTope, 1);
    /* Imprimir datos de los almacenes */
    imprimirAlmacen(codAlmacen1, ingresosCant1, ingresosTotal1, salidasCant1, salidasTotal1);
    imprimirAlmacen(codAlmacen2, ingresosCant2, ingresosTotal2, salidasCant2, salidasTotal2);
    /* Imprimir estadísticas */
    printf("Precio unitario promedio de adquisicion: S/ %.2lf\n", puPromAdquisicion);
    printf("Precio unitario promedio de venta: S/ %.2lf\n", puPromVenta);
    printf("Primer registro: ");
    imprimirFecha(*fechaMenor, 1);
    printf("Ultimo registro: ");
    imprimirFecha(*fechaMayor, 1);
    repetir('-', MAX_LINEA, 1);
    /* Limpiar datos */
    *ingresosSumaPU = *salidasSumaPU = 0;
    *ingresosConteo = *salidasConteo = 0;
    *fechaMenor = INT_MAX;
    *fechaMayor = INT_MIN;
}

void imprimirAlmacen(int codAlmacen, double* ingresosCant, double* ingresosTotal,
        double* salidasCant, double* salidasTotal) {
    /* Imprimir cabecera del almacén */
    printf("ALMACEN:  %06d %20s %20s %15s\n", codAlmacen, "Total Ingresos",
            "Total Salidas", "Total Neto");
    /* Imprimir totales del almacén */
    repetir(' ', 20, 0);
    imprimirTotal(*ingresosCant, *ingresosTotal);
    repetir(' ', 5, 0);
    imprimirTotal(*salidasCant, *salidasTotal);
    repetir(' ', 5, 0);
    imprimirTotal(*ingresosCant - *salidasCant, *ingresosTotal - *salidasTotal);
    putchar('\n');
    /* Limpiar datos */
    *ingresosCant = *ingresosTotal = *salidasCant = *salidasTotal = 0.0;
}

void imprimirTotal(double cantidad, double total) {
    printf("%6.2lf S/ %8.2lf", cantidad, total);
}

double calcularPuPromedio(double sumaPU, int conteo) {
    return (conteo == 0) ? 0 : sumaPU / conteo;
}

/* Funciones auxiliares */

int convertirFecha(int dia, int mes, int anho) {
    return 10000 * anho + 100 * mes + dia;
}

void imprimirFecha(int fecha, int agregarFinLinea) {
    int dia, mes, anho;
    /* Verificar si la fecha es válida */
    if (fecha == INT_MIN || fecha == INT_MAX) {
        printf("--/--/----");
    } else {
        dia = fecha % 100;
        mes = (fecha / 100) % 100;
        anho = fecha / 10000;
        printf("%02d/%02d/%04d", dia, mes, anho);
    }
    if (agregarFinLinea) putchar('\n');
}

void separador(char caracter) {
    int i;
    for (i = 0; i < MAX_LINEA; i++) {
        putchar(caracter);
    }
    putchar('\n');
}
