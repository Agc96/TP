/*
 * Archivo: funciones.c
 * Autor:   Anthony Gutiérrez
 *
 * Creado el 3 de noviembre de 2020, 08:16 AM
 */

#include <limits.h>
#include "funciones.h"

#define MAX_SEPARACION 120

/* Lectura de las salas */

int leerSalas(int* arrCodSala, int* arrButSala) {
    FILE* arch = fopen("salas.txt", "r");
    if (arch == NULL) {
        fprintf(stderr, "No se pudo abrir el archivo salas.txt\n");
        exit(1);
    }
    int numDatos = 0;
    while (1) {
        // Leer código de sala
        fscanf(arch, "%d", &arrCodSala[numDatos]);
        if (feof(arch)) break;
        // Leer cantidad de butacas disponibles
        fscanf(arch, "%d", &arrButSala[numDatos]);
        // Ignorar nombre de sala
        while (fgetc(arch) != '\n');
        numDatos++;
    }
    // Cierre de archivos
    fclose(arch);
    return numDatos;
}

/* Lectura de las películas */

int leerPeliculas(int* arrCodSala, int* arrButSala, int numSalas,
        int* arrCodPeli, int* arrFuncProg, int* arrButDisp) {
    // Apertura de archivos
    FILE* arch = fopen("peliculas.txt", "r");
    if (arch == NULL) {
        fprintf(stderr, "No se pudo abrir el archivo peliculas.txt\n");
        exit(1);
    }
    int numDatos = 0, numDias, numLeidos, sala, aux, pos, butacas;
    // Leer datos principales de la película
    while (1) {
        fscanf(arch, "%d", &arrCodPeli[numDatos]);
        if (feof(arch)) break;
        numDias = leerCantDias(arch);
        // Ignorar nombre de la película
        fgetc(arch);
        while (fgetc(arch) != ' ');
        // Leer lista de funciones y calcular cantidad de funciones programadas
        while (1) {
            numLeidos = fscanf(arch, "%d:%d", &sala, &aux);
            if (numLeidos == 1) {
                // Buscar la cantidad de butacas disponibles de la sala
                pos = buscarSala(arrCodSala, numSalas, sala);
                if (pos < 0) {
                    fprintf(stderr, "No se pudo encontrar la sala solicitada.\n");
                    fclose(arch);
                    exit(1);
                }
            } else {
                // Actualizar contadores
                arrFuncProg[numDatos] += numDias;
                arrButDisp[numDatos] += arrButSala[pos]*numDias;
            }
            if (fgetc(arch) == '\n') break;
        }
        numDatos++;
    }
    // Cierre de archivos
    fclose(arch);
    return numDatos;
}

int leerCantDias(FILE* arch) {
    int dia1, dia2, mes1, mes2, anho1, anho2;
    fscanf(arch, "%d.%d.%d", &dia1, &mes1, &anho1);
    fscanf(arch, "%d.%d.%d", &dia2, &mes2, &anho2);
    return (mes2-mes1)*30 + (dia2-dia1+1);
}

int buscarSala(int* arrCodSalas, int numSalas, int codSala) {
    for (int i = 0; i < numSalas; i++) {
        if (arrCodSalas[i] == codSala) return i;
    }
    return -1;
}

/* Lectura de las ventas */

void leerVentas(int* arrCodPeli, int* arrButVend, double* arrRecauda,
        int* arrButOcup, int numPelis) {
    // Apertura de archivos
    FILE* arch = fopen("ventas_y_ocupacion.txt", "r");
    if (arch == NULL) {
        fprintf(stderr, "No se pudo abrir el archivo ventas_y_ocupacion.txt\n");
        exit(1);
    }
    int codPeli, aux, vendidos, ocupados, pos;
    double monto;
    char c;
    // Leer datos de la función de la película
    while (1) {
        fscanf(arch, "%d", &codPeli);
        if (feof(arch)) break;
        fscanf(arch, "%d %d/%d/%d %d:%d %lf %d", &aux, &aux, &aux, &aux, &aux,
                &aux, &monto, &vendidos);
        // Leer lista de asientos ocupados
        ocupados = 0;
        while (1) {
            fscanf(arch, " %c%d", &c, &aux);
            ocupados++;
            if (fgetc(arch) == '\n') break;
        }
        // Buscar película, si se encontró colocar los datos
        pos = buscarPelicula(arrCodPeli, numPelis, codPeli);
        if (pos >= 0) {
            arrButVend[pos] += vendidos;
            arrRecauda[pos] += monto;
            arrButOcup[pos] += ocupados;
        }
    }
    // Cierre de archivos
    fclose(arch);
}

int buscarPelicula(int* arrCodPeli, int numPelis, int codPeli) {
    for (int i = 0; i < numPelis; i++) {
        if (arrCodPeli[i] == codPeli) return i;
    }
    return -1;
}

/* Ordenamiento de datos */

void ordenarDatos(int* arrCodPeli, int* arrFuncProg, int* arrButDisp,
        int* arrButVend, double* arrRecauda, int* arrButOcup, int numPelis) {
    int cond1, cond2, cond3;
    for (int i = 0; i < numPelis-1; i++) {
        for (int j = i+1; j < numPelis; j++) {
            cond1 = arrRecauda[i] > arrRecauda[j];
            cond2 = arrRecauda[i] == arrRecauda[j];
            cond3 = arrFuncProg[i] < arrFuncProg[j];
            if (cond1 || (cond2 && cond3)) { 
                intercambiarInt(arrCodPeli, i, j);
                intercambiarInt(arrFuncProg, i, j);
                intercambiarInt(arrButDisp, i, j);
                intercambiarInt(arrButVend, i, j);
                intercambiarDouble(arrRecauda, i, j);
                intercambiarInt(arrButOcup, i, j);
            }
        }
    }
}

void intercambiarInt(int* arr, int i, int j) {
    int aux = arr[i];
    arr[i] = arr[j];
    arr[j] = aux;
}

void intercambiarDouble(double* arr, int i, int j) {
    double aux = arr[i];
    arr[i] = arr[j];
    arr[j] = aux;
}

/* Impresión del reporte */

void imprimirReporte(int* arrCodPeli, int* arrFuncProg, int* arrButDisp,
        int* arrButVend, double* arrRecauda, int* arrButOcup,
        double* arrPorcOcup, int numPelis) {
    FILE* arch = fopen("reporte.txt", "w");
    if (arch == NULL) {
        fprintf(stderr, "No se pudo generar el archivo reporte.txt\n");
        exit(1);
    }
    int totalButOcup = 0, totalButDisp = 0, minOcup = INT_MAX, maxOcup = 0,
            minPos, maxPos;
    double totalRecauda = 0.0, totalPorcOcup = 0.0;
    // Imprimir cabecera
    imprimirCabeceraRep(arch);
    // Imprimir listado de películas
    for (int i = 0; i < numPelis; i++) {
        arrPorcOcup[i] = arrButOcup[i]*100.0/arrButDisp[i];
        fprintf(arch, "%04d %23d %20d %20.2lf %15d %16.2lf%%\n", arrCodPeli[i],
                arrFuncProg[i], arrButVend[i], arrRecauda[i], arrButOcup[i],
                arrPorcOcup[i]);
        // Actualizar contadores
        totalRecauda += arrRecauda[i];
        totalButOcup += arrButOcup[i];
        totalButDisp += arrButDisp[i];
        // Verificar máximos y mínimos
        if (arrButOcup[i] < minOcup) {
            minOcup = arrButOcup[i];
            minPos = i;
        }
        if (arrButOcup[i] > maxOcup) {
            maxOcup = arrButOcup[i];
            maxPos = i;
        }
    }
    // Imprimir resumen
    totalPorcOcup = totalButOcup*100.0/totalButDisp;
    imprimirResumenRep(arch, numPelis, totalRecauda, totalPorcOcup, arrCodPeli,
            arrButVend, arrPorcOcup, arrRecauda, minPos, maxPos);
    // Cierre de archivos
    fclose(arch);
}

void imprimirCabeceraRep(FILE* arch) {
    fprintf(arch, "%80s\n", "REPORTE DE VENTAS Y OCUPACION DE SALAS");
    separacion(arch, '=');
    fprintf(arch, "%-15s %-25s %-15s %-20s %-15s %s\n", "Cod. Pelicula",
            "Funciones Programadas", "But. Vend.", "Recaudacion (S/.)",
            "But. Ocup.", "% Ocupacion");
}

void imprimirResumenRep(FILE* arch, int numPelis, double totalRecauda,
        double totalPorcOcup, int* arrCodPeli, int* arrButVend,
        double* arrPorcOcup, double* arrRecauda, int minPos, int maxPos) {
    separacion(arch, '-');
    fprintf(arch, "RESUMEN:\n");
    fprintf(arch, "Cantidad de peliculas: %d\n", numPelis);
    fprintf(arch, "Recaudacion total: S/ %.2lf\n", totalRecauda);
    fprintf(arch, "%% Ocupacion total: %.2lf%%\n", totalPorcOcup);
    separacion(arch, '-');
    fprintf(arch, "Pelicula con menos espectadores: ");
    imprimirPeliEstad(arch, arrCodPeli[minPos], arrButVend[minPos],
            arrPorcOcup[minPos], arrRecauda[minPos]);
    fprintf(arch, "Pelicula con mas espectadores:   ");
    imprimirPeliEstad(arch, arrCodPeli[maxPos], arrButVend[maxPos],
            arrPorcOcup[maxPos], arrRecauda[maxPos]);
    separacion(arch, '=');
}

void imprimirPeliEstad(FILE* arch, int codPeli, int butVend, double porcOcup,
        double recauda) {
    fprintf(arch, "%04d %20s: %5d %15s: %.2lf%% %15s: S/ %10.2lf\n",
            codPeli, "Butacas vendidas", butVend, "% Ocupacion",
            porcOcup, "Recaudacion", recauda);
}

void separacion(FILE* arch, char c) {
    for (int i = 0; i < MAX_SEPARACION; i++) {
        fputc(c, arch);
    }
    fputc('\n', arch);
}
