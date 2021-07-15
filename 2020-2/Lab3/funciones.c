/*
 * Archivo: funciones.c
 * Autor:   Anthony Gutiérrez
 *
 * Creado el 13 de octubre de 2020, 07:54 AM
 */

#include "funciones.h"
#define MAX_NOMBRE 50
#define MAX_LINEA 80

int leerPacientes(int* codigoMed, double* factorAtenc, double* factorRes,
        int* pacAtend, int* pacRes) {
    // Apertura del archivo y declaración de variables
    FILE* archAtencion = abrirArchivo("AtencionPacientes.txt", "r");
    FILE* archReporte = abrirArchivo("ReporteAtencion.txt", "w");
    int dd, mm, aaaa, fecha, codMed, numMed = 0;
    char estado, nombre[MAX_NOMBRE];
    double factor;
    // Leer línea por línea las fechas de atención
    while (1) {
        fscanf(archAtencion, "%d/%d/%d", &dd, &mm, &aaaa);
        if (feof(archAtencion)) break;
        fecha = 10000*aaaa + 100*mm + dd;
        while (1) {
            fscanf(archAtencion, " %c %s %lf %d", &estado, nombre, &factor, &codMed);
            // Validar que el factor está dentro del rango permitido
            if (factor >= 0 && factor <= 1) {
                agregarMedico(codigoMed, factorAtenc, factorRes, pacAtend, pacRes,
                        &numMed, estado, factor, codMed);
            } else {
                printf("%8.4lf\n", factor);
            }
            // Ver si llegamos al fin de línea
            if (fgetc(archAtencion) == '\n') break;
        }
    }
    // Impresión del reporte
    fprintf(archReporte, "Codigo  Fac.Atenc.  Fac.Res.  Pac.Atend.  Pac.Res.\n");
    imprimirLinea(archReporte, '=');
    for (int i = 0; i < numMed; i++) {
        fprintf(archReporte, "%6d  %10.4lf  %8.4lf  %10d  %8d\n", codigoMed[i],
                factorAtenc[i], factorRes[i], pacAtend[i], pacRes[i]);
    }
    // Cierre de archivos
    fclose(archAtencion);
    fclose(archReporte);
    return numMed;
}

void agregarMedico(int* codigoMed, double* factorAtenc, double* factorRes,
        int* pacAtend, int* pacRes, int* numMed, char estado, double factor,
        int codMed) {
    // Buscar al médico en el arreglo
    for (int i = 0; i < (*numMed); i++) {
        if (codigoMed[i] == codMed) {
            // Si se encontró, solo aumentar los contadores
            if (estado == 'A') {
                factorAtenc[i] += factor;
                pacAtend[i]++;
            } else {
                factorRes[i] += factor;
                pacRes[i]++;
            }
            return;
        }
    }
    // Si no se encontró, agregar los datos al final de la lista
    codigoMed[*numMed] = codMed;
    if (estado == 'A') {
        factorAtenc[*numMed] = factor;
        factorRes[*numMed] = 0.0;
        pacAtend[*numMed] = 1;
        pacRes[*numMed] = 0;
    } else {
        factorAtenc[*numMed] = 0.0;
        factorRes[*numMed] = factor;
        pacAtend[*numMed] = 0;
        pacRes[*numMed] = 1;
    }
    (*numMed)++;
}

void imprimirReporte(int* codigoMed, double* factorAtenc, double* factorRes,
        int* pacAtend, int* pacRes, int numMedicos) {
    // Apertura de archivos
    FILE* archMedicos = abrirArchivo("Medicos.txt", "r");
    FILE* archReporte = abrirArchivo("Reporte.txt", "w");
    // Cierre de archivos
    fclose(archMedicos);
    fclose(archReporte);
}

/* Funciones auxiliares */

FILE* abrirArchivo(const char* nomArch, const char* modoArch) {
    FILE* arch = fopen(nomArch, modoArch);
    if (arch == NULL) {
        fprintf(stderr, "No se pudo abrir el archivo %s\n", nomArch);
        exit(1);
    }
    return arch;
}

void imprimirLinea(FILE* arch, char c) {
    for (int i = 0; i < MAX_LINEA; i++) {
        fputc(c, arch);
    }
    fputc('\n', arch);
}
