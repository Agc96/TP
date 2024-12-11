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
    int arrProd[MAX_PROD], arrAlmac[MAX_PROD], arrCodPlat[MAX_PLATOS],
            arrCantPlat[MAX_PLATOS], numProd = 0, numAlmac = 0, numPlat = 0;
    double arrPrecProd[MAX_PROD], arrCantAlmac[MAX_PROD],
            arrPrecAlmac[MAX_PROD], arrSubAlmac[MAX_PROD],
            arrPrecPlat[MAX_PLATOS] = {0}, arrSubPlat[MAX_PLATOS] = {0};
    // Reporte de productos perdidos
    llenarProd(arrProd, arrPrecProd, &numProd);
    llenarAlmac(arrProd, arrPrecProd, numProd, arrAlmac, arrCantAlmac,
            arrPrecAlmac, arrSubAlmac, &numAlmac);
    ordenarAlmac(arrAlmac, arrCantAlmac, arrPrecAlmac, arrSubAlmac, numAlmac);
    reporteProd(archRep, arrAlmac, arrCantAlmac, arrPrecAlmac, arrSubAlmac,
            numAlmac);
    // Reporte de platos que no se podrán preparar
    llenarPlatPrep(arrCodPlat, arrCantPlat, &numPlat);
    llenarPrecPlat(arrCodPlat, arrCantPlat, arrPrecPlat, arrSubPlat, numPlat,
            arrProd, arrPrecProd, numProd, arrAlmac, numAlmac);
    ordenarPlatos(arrCodPlat, arrCantPlat, arrPrecPlat, arrSubPlat, numPlat);
    reportePlatos(archRep, arrCodPlat, arrCantPlat, arrPrecPlat, arrSubPlat,
            numPlat);
    fclose(archRep);
    return 0;
}
