/*
 * File:   main.c
 * Author: Anthony Gutiérrez
 *
 * Created on 2 de noviembre de 2021, 08:36 AM
 */

#include "funciones.h"

#define MAX_CLIENTES 100
#define MAX_PRODUCTOS 100
#define MAX_PEDIDOS 50
#define MAX_ARTICULOS 500

int main() {
    int cantProd, cantPed, cantDet, arrCodProd[MAX_PRODUCTOS],
            arrStockProd[MAX_PRODUCTOS], arrCodPed[MAX_PEDIDOS],
            arrFechaPed[MAX_PEDIDOS], arrHoraPed[MAX_PEDIDOS],
            arrCliPed[MAX_PEDIDOS], arrCodPedDet[MAX_ARTICULOS],
            arrCodProdDet[MAX_ARTICULOS], arrCantProdDet[MAX_ARTICULOS];
    double arrPrecioProd[MAX_PRODUCTOS];
    cantProd = leerProductos(arrCodProd, arrStockProd, arrPrecioProd);
    cantPed = leerPedidos(arrCodPed, arrFechaPed, arrHoraPed, arrCliPed);
    cantDet = leerDetalles(arrCodPedDet, arrCodProdDet, arrCantProdDet);
    ordenarProductos(arrCodProd, arrStockProd, arrPrecioProd, cantProd);
    ordenarPedidos(arrCodPed, arrFechaPed, arrHoraPed, arrCliPed, cantPed);
    imprimirReporte(arrCodProd, arrStockProd, arrPrecioProd, cantProd,
            arrCodPed, arrFechaPed, arrHoraPed, arrCliPed, cantPed,
            arrCodPedDet, arrCodProdDet, arrCantProdDet, cantDet);
    return (EXIT_SUCCESS);
}
