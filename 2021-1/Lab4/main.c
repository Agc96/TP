/*
 * Archivo: main.c
 * Autor:   Anthony Gutiérrez
 *
 * Creado el 26 de mayo de 2021, 04:39 PM
 */

#include <stdio.h>
#include <stdlib.h>
#include "funciones.h"

#define MAX_PROD 300
#define MAX_PLATOS 100

int main() {
    FILE* archRep = abrirArchivo("ReporteDePerdidas.txt", "w");
    int arrCodProd[MAX_PROD], arrCodPlat[MAX_PLATOS], arrCantPlat[MAX_PLATOS],
            numProd = 0, numPlat = 0;
    double arrPrecProd[MAX_PROD], arrCantAlmac[MAX_PROD] = {0},
            arrSubAlmac[MAX_PROD], arrPrecPlat[MAX_PLATOS] = {0},
            arrSubPlat[MAX_PLATOS] = {0};
    // Reporte de productos perdidos
    llenarProd(arrCodProd, arrPrecProd, &numProd);
    llenarAlmac(arrCodProd, arrPrecProd, arrCantAlmac, arrSubAlmac, numProd);
    ordenarProd(arrCodProd, arrPrecProd, arrCantAlmac, arrSubAlmac, numProd);
    reporteProd(archRep, arrCodProd, arrPrecProd, arrCantAlmac, arrSubAlmac,
            numProd);
    // Reporte de platos que no se podrán preparar
    llenarPlatPrep(arrCodPlat, arrCantPlat, &numPlat);
    llenarPrecPlat(arrCodPlat, arrCantPlat, arrPrecPlat, arrSubPlat, numPlat,
            arrCodProd, arrPrecProd, numProd);
    ordenarPlatos(arrCodPlat, arrCantPlat, arrPrecPlat, arrSubPlat, numPlat);
    reportePlatos(archRep, arrCodPlat, arrCantPlat, arrPrecPlat, arrSubPlat,
            numPlat);
    fclose(archRep);
    return 0;
}
