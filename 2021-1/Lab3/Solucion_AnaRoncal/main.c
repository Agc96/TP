/* 
 * File:   main.c
 * Author: anaro
 *
 * Created on 10 de mayo de 2021, 05:28 PM
 */

#include <stdio.h>
#include <stdlib.h>
#include "funciones.h"

int main(int argc, char** argv) {
    
    FILE * archCompras, * reporte;
    int codProd[50], codTienda[20], cantProductos = 0, cantTiendas = 0;
    int codPostal[20], cantidadProd[50], maximo = -1, minimo = 9999999, codMin, codMax;
    double precios[50], totalProd[50], totalMin, totalMax, totalVentas = 0.0;
   
    archCompras = fopen("compras.txt", "r");
    reporte = fopen("reporte.txt", "w");
    if(archCompras == NULL){
        printf("Archivo de Compras vacio");
        exit(1);
    }
    for(int i =0; i<50; i++){
        cantidadProd[i] = 0;
        totalProd[i] = 0;
    }
    /*Leer los datos del archivo y los guarda en arreglos*/
    guardarProductos(codProd, precios, &cantProductos);
    guardarTiendas(codTienda, codPostal, &cantTiendas);
    ordenarTiendas(codTienda, codPostal, cantTiendas);
    generarReporte(reporte, archCompras, codTienda, codPostal, codProd, precios, 
                   cantProductos, cantTiendas, cantidadProd, totalProd);
    /* Calcular totales, máximo y mínimo */
    for(int i = 0; i<cantProductos; i++){
        if(cantidadProd[i]<minimo){
            minimo = cantidadProd[i];
            codMin = codProd[i];
            totalMin = totalProd[i];
        }
        if(cantidadProd[i]>maximo){
            maximo = cantidadProd[i];
            codMax = codProd[i];
            totalMax = totalProd[i];
        }
        totalVentas += totalProd[i];
    }
    fprintf(reporte, "\nRESUMEN TOTAL\n");
    fprintf(reporte, "Producto con mas entregas: %d  Cantidad: %d  Total Ventas "
                     "%lf\n", codMax, maximo, totalMax);
    fprintf(reporte, "Producto con menos entregas: %d Cantidad: %d  Total Ventas "
                      "%lf\n", codMin, minimo, totalMin);
    fprintf(reporte, "Total Ventas: %lf\n", totalVentas);
    
    fclose(archCompras);
    fclose(reporte);
    return (EXIT_SUCCESS);
}

