/*
 * Archivo: funciones.c
 * Autor:   Anthony Gutiérrez
 *
 * Creado el 12 de octubre de 2021, 08:01 AM
 */

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "funciones.h"

#define MAX_LINEA 100
#define NO_ENCONTRADO -1

void leerDistritos(int *arrCodDist, int *numDist) {
    FILE *arch = abrirArchivo("Distritos.txt", "r");
    while (1) {
        fscanf(arch, "%d", &arrCodDist[*numDist]);
        if (feof(arch)) break;
        while (fgetc(arch) != '\n');
        (*numDist)++;
    }
    fclose(arch);
}

void leerPacientes(int *arrCodPac, int *arrDistPac, int *arrFecIniPac,
        int *numPac) {
    FILE *arch = abrirArchivo("Pacientes.txt", "r");
    while (1) {
        fscanf(arch, "%d", &arrCodPac[*numPac]);
        if (feof(arch)) break;
        while (fgetc(arch) != '[');
        while (fgetc(arch) != ']');
        fscanf(arch, "%d", &arrDistPac[*numPac]);
        (*numPac)++;
    }
    for (int i = 0; i < *numPac; i++) {
        arrFecIniPac[i] = 99999999;
    }
    fclose(arch);
}

void leerMedicos(int *arrCodMed, double *arrTarifMed, int *numMed) {
    FILE *arch = abrirArchivo("Medicos.txt", "r");
    while (1) {
        fscanf(arch, "%d", &arrCodMed[*numMed]);
        if (feof(arch)) break;
        while (fgetc(arch) == ' ');
        while (fgetc(arch) != ' ');
        fscanf(arch, "%lf", &arrTarifMed[*numMed]);
        while (fgetc(arch) != '\n');
        (*numMed)++;
    }
    fclose(arch);
}

void leerAtenciones(int *arrCodDist, int *arrCitaDist, double *arrPagoDist,
        int numDist, int *arrCodPac, int *arrDistPac, int *arrFecIniPac,
        int *arrFecFinPac, int *arrDurPac, int *arrCitaPac, double *arrMontoPac,
        int numPac, int *arrCodMed, double *arrTarifMed, int numMed) {
    FILE *arch = abrirArchivo("AtencionesMedicas.txt", "r");
    int codMed, dd, mm, aaaa, fecha, codPac, horaIni, horaFin, indPac, duracion;
    while (1) {
        fscanf(arch, "%d", &codMed);
        if (feof(arch)) break;
        fscanf(arch, "%d/%d/%d", &dd, &mm, &aaaa);
        fecha = 10000*aaaa + 100*mm + dd;
        while (1) {
            fscanf(arch, "%d", &codPac);
            horaIni = leerHora(arch);
            horaFin = leerHora(arch);
            duracion = horaFin - horaIni;
            // Buscar el paciente en el arreglo
            indPac = buscar(arrCodPac, codPac, numPac);
            if (indPac != NO_ENCONTRADO) {
                if (fecha < arrFecIniPac[indPac]) arrFecIniPac[indPac] = fecha;
                if (fecha > arrFecFinPac[indPac]) arrFecFinPac[indPac] = fecha;
                arrDurPac[indPac] += duracion;
                arrCitaPac[indPac]++;
                // Actualizar los datos del médico y del distrito
                actualizarMedicoDistrito(arrDistPac, arrMontoPac, indPac,
                        arrCodMed, arrTarifMed, numMed, codMed, arrCodDist,
                        arrCitaDist, arrPagoDist, numDist, duracion);
            } else {
                printf("No se pudo encontrar el paciente %d\n", codPac);
            }
            if (fgetc(arch) == '\n') break;
        }
    }
    fclose(arch);
}

void actualizarMedicoDistrito(int *arrDistPac, double *arrMontoPac, int indPac,
        int *arrCodMed, double *arrTarifMed, int numMed, int codMed,
        int *arrCodDist, int *arrCitaDist, double *arrPagoDist, int numDist,
        int duracion) {
    int indMed, indDist, mmDur, ssDur;
    double monto;
    // Calcular duración y monto
    mmDur = duracion / 60;
    ssDur = duracion % 60;
    // Actualizar datos del médico
    indMed = buscar(arrCodMed, codMed, numMed);
    if (indMed != NO_ENCONTRADO) {
        if (ssDur > 0) mmDur++;
        monto = mmDur * (arrTarifMed[indMed]);
        arrMontoPac[indPac] += monto;
        // Actualizar datos del distrito
        indDist = buscar(arrCodDist, arrDistPac[indPac], numDist);
        if (indDist != NO_ENCONTRADO) {
            arrPagoDist[indDist] += monto;
            arrCitaDist[indDist]++;
        } else {
            printf("No se pudo encontrar el distrito %d\n", arrDistPac[indPac]);
        }
    } else {
        printf("No se pudo encontrar el medico %d\n", codMed);
    }
}

int leerHora(FILE *arch) {
    int hh, mm, ss, cant;
    cant = fscanf(arch, "%d:%d:%d", &hh, &mm, &ss);
    if (cant == 1) {
        mm = ss = 0;
    } else if (cant == 2) {
        ss = 0;
    }
    return 3600*hh + 60*mm + ss;
}

int buscar(int *arr, int cod, int num) {
    for (int i = 0; i < num; i++) {
        if (arr[i] == cod) return i;
    }
    return NO_ENCONTRADO;
}

void ordenarDistritos(int *arrCodDist, int *arrCitaDist, double *arrPagoDist,
        int numDist) {
    for (int i = 0; i < numDist-1; i++) {
        for (int j = i+1; j < numDist; j++) {
            if (arrCitaDist[i] > arrCitaDist[j] ||
                    (arrCitaDist[i] == arrCitaDist[j] &&
                    arrPagoDist[i] < arrPagoDist[j])) {
                intercambiarInt(arrCodDist, i, j);
                intercambiarInt(arrCitaDist, i, j);
                intercambiarDouble(arrPagoDist, i, j);
            }
        }
    }
}

void intercambiarInt(int *arr, int i, int j) {
    int aux = arr[i];
    arr[i] = arr[j];
    arr[j] = aux;
}

void intercambiarDouble(double *arr, int i, int j) {
    double aux = arr[i];
    arr[i] = arr[j];
    arr[j] = aux;
}

void imprimirReporte(int *arrCodDist, int *arrCitaDist, double *arrPagoDist,
        int numDist, int *arrCodPac, int *arrDistPac, int *arrFecIniPac,
        int *arrFecFinPac, int *arrDurPac, int *arrCitaPac, double *arrMontoPac,
        int numPac) {
    FILE *arch = abrirArchivo("ReporteDeAtencionesPorDistrito.txt", "w");
    int codDistMayor, codDistMenor;
    double pagoDistMayor = 0, pagoDistMenor = 99999999.99;
    // Imprimir cabecera del reporte
    fprintf(arch, "%64s\n", "EMPRESA PRESTADORA DE SALUD");
    fprintf(arch, "%67s\n", "ATENCION DE PACIENTES POR DISTRITO");
    imprimirLinea(arch, '=');
    // Imprimir atenciones médicas de pacientes
    for (int i = 0; i < numDist; i++) {
        imprimirPacientes(arch, arrCodDist[i], arrCitaDist[i], arrPagoDist[i],
                arrCodPac, arrDistPac, arrFecIniPac, arrFecFinPac, arrDurPac,
                arrCitaPac, arrMontoPac, numPac);
        if (arrPagoDist[i] > pagoDistMayor) {
            pagoDistMayor = arrPagoDist[i];
            codDistMayor = arrCodDist[i];
        }
        if (arrPagoDist[i] < pagoDistMenor) {
            pagoDistMenor = arrPagoDist[i];
            codDistMenor = arrCodDist[i];
        }
    }
    // Imprimir resumen del reporte
    fprintf(arch, "DISTRITO CON MAYOR PAGO REALIZADO: %d - S/ %8.2lf\n",
            codDistMayor, pagoDistMayor);
    fprintf(arch, "DISTRITO CON MENOR PAGO REALIZADO: %d - S/ %8.2lf\n",
            codDistMenor, pagoDistMenor);
    fclose(arch);
}

void imprimirDistrito(FILE *archRep, int codBuscado) {
    FILE *archDist = abrirArchivo("Distritos.txt", "r");
    int codLeido;
    char c;
    fprintf(archRep, "%5cDistrito: %5d - ", ' ', codBuscado);
    while (1) {
        fscanf(archDist, "%d", &codLeido);
        if (feof(archDist)) break;
        if (codBuscado == codLeido) {
            fscanf(archDist, " %c", &c);
            while (1) {
                fputc(toupper(c), archRep);
                c = fgetc(archDist);
                if (c == '\n') break;
            }
            break;
        } else {
            while (fgetc(archDist) != '\n');
        }
    }
    fputc('\n', archRep);
    fclose(archDist);
}

void imprimirPacientes(FILE *arch, int codDist, int citaDist, double pagoDist,
        int *arrCodPac, int *arrDistPac, int *arrFecIniPac, int *arrFecFinPac,
        int *arrDurPac, int *arrCitaPac, double *arrMontoPac, int numPac) {
    // Imprimir cabecera de pacientes
    imprimirDistrito(arch, codDist);
    imprimirLinea(arch, '-');
    fprintf(arch, "%10s %12s %12s %20s %18s %15s\n", "PACIENTE", "INICIO",
            "FIN", "DURACION CITAS", "CANTIDAD CITAS", "MONTO PAGADO");
    imprimirLinea(arch, '-');
    // Imprimir listado de pacientes
    int cantPacxDist = 0;
    for (int i = 0; i < numPac; i++) {
        if (codDist == arrDistPac[i]) {
            fprintf(arch, "%10d", arrCodPac[i]);
            imprimirFecha(arch, arrFecIniPac[i]);
            imprimirFecha(arch, arrFecFinPac[i]);
            imprimirDuracion(arch, arrDurPac[i]);
            fprintf(arch, "%16d %20.2lf\n", arrCitaPac[i], arrMontoPac[i]);
            cantPacxDist++;
        }
    }
    if (cantPacxDist == 0) {
        fprintf(arch, "Sin registros de atenciones medicas\n");
    }
    // Imprimir resumen de pacientes
    imprimirLinea(arch, '-');
    fprintf(arch, "CANTIDAD TOTAL DE CITAS: %3d\n", citaDist);
    fprintf(arch, "PAGO TOTAL:    S/ %10.2lf\n", pagoDist);
    imprimirLinea(arch, '=');
}

void imprimirFecha(FILE *arch, int fecha) {
    int aaaa = fecha / 10000;
    int mm = (fecha % 10000) / 100;
    int dd = fecha % 100;
    fprintf(arch, "%5c%02d/%02d/%04d", ' ', dd, mm, aaaa);
}

void imprimirDuracion(FILE *arch, int duracion) {
    int hh = duracion / 3600;
    int mm = (duracion % 3600) / 60;
    int ss = duracion % 60;
    fprintf(arch, "%5c%02d:%02d:%02d", ' ', hh, mm, ss);
}
/* Funciones auxiliares */

FILE *abrirArchivo(const char *nomArch, const char *modo) {
    FILE *arch = fopen(nomArch, modo);
    if (arch == NULL) {
        fprintf(stderr, "No se pudo abrir el archivo %s\n", nomArch);
        exit(1);
    }
    return arch;
}

void imprimirLinea(FILE *arch, char c) {
    for (int i = 0; i < MAX_LINEA; i++) {
        fputc(c, arch);
    }
    fputc('\n', arch);
}
