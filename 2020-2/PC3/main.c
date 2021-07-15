/*
 * Archivo: main.c
 * Autor:   Anthony Gutiérrez
 *
 * Creado el 14 de noviembre de 2020, 10:14 PM
 */

#include "funciones.h"
#define MAX_PROD 100

void jpVerificarLecturaProductos(int *arrCod, int *arrStock, int num) {
    FILE *arch = fopen("JpVerificarProductos.txt", "w");
    if (arch == NULL) {
        perror("[JP] No se pudo crear el archivo del reporte de productos");
        exit(1);
    }
    fprintf(arch, "num=%d\n", num);
    for (int i = 0; i < num; i++) {
        fprintf(arch, "%d %d\n", arrCod[i], arrStock[i]);
    }
    printf("Verificacion de lectura de productos correcta\n");
    fclose(arch);
}

void jpVerificarLecturaMovimientos(int *arrCodProd, int *arrStockProd, int numStock,
        int *arrCodDeficit, int *arrStockDeficit, int numDeficit) {
    FILE *arch = fopen("JpVerificarMovimientos.txt", "w");
    if (arch == NULL) {
        perror("[JP] No se pudo crear el archivo del reporte de movimientos");
        exit(1);
    }
    fprintf(arch, "==== STOCK ====\nnumStock=%d\n", numStock);
    for (int i = 0; i < numStock; i++) {
        fprintf(arch, "%d %d\n", arrCodProd[i], arrStockProd[i]);
    }
    fprintf(arch, "==== DEFICIT ====\nnumDeficit=%d\n", numDeficit);
    for (int i = 0; i < numDeficit; i++) {
        fprintf(arch, "%d %d\n", arrCodDeficit[i], arrStockDeficit[i]);
    }
    printf("Verificacion de lectura de movimientos correcta\n");
    fclose(arch);
}

int main() {
    int arrCodProd[MAX_PROD], arrStockProd[MAX_PROD], arrCodDeficit[MAX_PROD],
            arrStockDeficit[MAX_PROD], numProd = 0, numDeficit = 0;
    leerProductos(arrCodProd, arrStockProd, &numProd);
    leerMovimientos(arrCodProd, arrStockProd, &numProd, arrCodDeficit,
            arrStockDeficit, &numDeficit);
    ordenarArreglos(arrCodProd, arrStockProd, numProd);
    ordenarArreglos(arrCodDeficit, arrStockDeficit, numDeficit);
    imprimirReporte(arrCodProd, arrStockProd, numProd, arrCodDeficit,
            arrStockDeficit, numDeficit);
    return 0;
}
