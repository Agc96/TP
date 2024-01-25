/*
 * Archivo: main.c
 * Autor:   Anthony Gutiérrez
 *
 * Creado el 12 de octubre de 2021, 08:00 AM
 */

#include "funciones.h"

#define MAX_DISTRITOS 30
#define MAX_PACIENTES 40
#define MAX_MEDICOS 20

int main() {
    int numDist = 0, numPac = 0, numMed = 0, arrCodDist[MAX_DISTRITOS],
            arrCitaDist[MAX_DISTRITOS] = {0}, arrCodPac[MAX_PACIENTES],
            arrDistPac[MAX_PACIENTES], arrFecIniPac[MAX_PACIENTES],
            arrFecFinPac[MAX_PACIENTES] = {0}, arrDurPac[MAX_PACIENTES] = {0},
            arrCitaPac[MAX_PACIENTES] = {0}, arrCodMed[MAX_MEDICOS];
    double arrPagoDist[MAX_DISTRITOS] = {0}, arrMontoPac[MAX_PACIENTES] = {0},
            arrTarifMed[MAX_MEDICOS];
    leerDistritos(arrCodDist, &numDist);
    leerPacientes(arrCodPac, arrDistPac, arrFecIniPac, &numPac);
    leerMedicos(arrCodMed, arrTarifMed, &numMed);
    leerAtenciones(arrCodDist, arrCitaDist, arrPagoDist, numDist, arrCodPac,
            arrDistPac, arrFecIniPac, arrFecFinPac, arrDurPac, arrCitaPac,
            arrMontoPac, numPac, arrCodMed, arrTarifMed, numMed);
    ordenarDistritos(arrCodDist, arrCitaDist, arrPagoDist, numDist);
    imprimirReporte(arrCodDist, arrCitaDist, arrPagoDist, numDist, arrCodPac,
            arrDistPac, arrFecIniPac, arrFecFinPac, arrDurPac, arrCitaPac,
            arrMontoPac, numPac);
    return 0;
}
