/* 
 * File:   main.c
 * Author: Código
 *         Nombre: Silvia Vargas Cáceres
 * Silvia
 *
 * Created on 21 de mayo de 2021, 09:39 PM
 */

#include <stdio.h>
#include <stdlib.h>
#include "funciones.h"

#define MAX_PRODUCTOS 300
#define MAX_PLATOS 100


int main(int argc, char** argv) {
    int arrCodProducto[MAX_PRODUCTOS],arrCodPlato[MAX_PLATOS],
            arrCantPlato[MAX_PLATOS];
    double arrPrePlato[MAX_PLATOS]={0};
    double arrPreProducto[MAX_PRODUCTOS],arrCantProdAlm[MAX_PRODUCTOS]={0},
            arrSubTotalProd[MAX_PRODUCTOS],arrSubTotalPlato[MAX_PLATOS];
    int cantProductos=0,cantPlatos=0;
    cargarProductos(arrCodProducto,arrPreProducto,&cantProductos);
    cargarProdAlmacenados(arrCodProducto,arrPreProducto,cantProductos,arrCantProdAlm,
            arrSubTotalProd); 
    cargarPlatosPreparar(arrCodPlato,arrCantPlato,&cantPlatos);    
    cargarPlatosPrecios(arrCodPlato,arrCantPlato,cantPlatos,arrCodProducto,
            arrPreProducto,cantProductos,arrPrePlato);
    actualizarSubTotalPlatos(arrCodPlato,arrCantPlato,cantPlatos,arrPrePlato,arrSubTotalPlato);
    ordenarSubTotalProducto(arrCodProducto,arrPreProducto,arrCantProdAlm,arrSubTotalProd,cantProductos);
    ordenarSubTotalPlato(arrCodPlato,arrPrePlato,arrCantPlato,arrSubTotalPlato,cantPlatos);
    generarReporte(arrCodProducto,arrPreProducto,arrCantProdAlm,arrSubTotalProd,cantProductos,
        arrCodPlato,arrCantPlato,arrPrePlato,arrSubTotalPlato,cantPlatos);
    return (EXIT_SUCCESS);
}

