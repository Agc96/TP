/*
 * Archivo: funciones.c
 * Autor:   Anthony Gutiérrez
 *
 * Creado el 26 de mayo de 2021, 04:40 PM
 */

#include <stdio.h>
#include <stdlib.h>
#include "funciones.h"

#define MAX_LINEA 80
#define NO_ENCONTRADO -1

/* Reporte de productos perdidos */

void llenarProd(int* arrCodProd, double* arrPrecProd, int* numProd) {
    FILE* archProd = abrirArchivo("ListaDePrecios.txt", "r");
    while (fgetc(archProd) != '\n'); // Ignorar primera línea
    while (1) {
        fscanf(archProd, "%d", &arrCodProd[*numProd]);
        if (feof(archProd)) break;
        while (fgetc(archProd) != ']'); // Ignorar nombre del producto
        fscanf(archProd, "%lf", &arrPrecProd[*numProd]);
        (*numProd)++;
    }
    fclose(archProd);
}

void llenarAlmac(int* arrCodProd, double* arrPrecProd, double* arrCantAlmac,
        double* arrSubAlmac, int numProd) {
    FILE* archAlmac = abrirArchivo("ProductosAlmacenados.txt", "r");
    int codProd, indProd;
    double cantAlmac;
    while (1) {
        fscanf(archAlmac, "%d", &codProd);
        if (feof(archAlmac)) break;
        fscanf(archAlmac, "%lf", &cantAlmac);
        // Verificar que el producto almacenado tenga un precio en la lista
        indProd = buscarEnArreglo(arrCodProd, numProd, codProd);
        if (indProd != NO_ENCONTRADO) {
            arrCantAlmac[indProd] = cantAlmac;
            arrSubAlmac[indProd] = arrPrecProd[indProd] * cantAlmac;
        }
    }
    fclose(archAlmac);
}

void ordenarProd(int* arrCodProd, double* arrPrecProd, double* arrCantAlmac,
        double* arrSubAlmac, int numProd) {
    for (int i = 0; i < (numProd-1); i++) {
        for (int j = i+1; j < numProd; j++) {
            if (arrSubAlmac[i] < arrSubAlmac[j]) {
                intercambiarInt(arrCodProd, i, j);
                intercambiarDouble(arrPrecProd, i, j);
                intercambiarDouble(arrCantAlmac, i, j);
                intercambiarDouble(arrSubAlmac, i, j);
            }
        }
    }
}

void reporteProd(FILE* archRep, int* arrCodProd, double* arrPrecProd,
        double* arrCantAlmac, double* arrSubAlmac, int numProd) {
    double costoTotal = 0;
    int indice = 0;
    // Imprimir cabecera del reporte
    imprimirLinea(archRep, '=');
    fprintf(archRep, "PRODUCTOS PERDIDOS\n");
    imprimirLinea(archRep, '-');
    fprintf(archRep, "%10s %15s %25s %20s\n", "Producto", "Cantidad",
            "Precio Unitario (S/.)", "Sub-total (S/.)");
    // Imprimir lista de productos almacenados
    for (int i = 0; i < numProd; i++) {
        if (arrCantAlmac[i] > 0) {
            fprintf(archRep, "%3d) %05d %15.2lf %18.2lf %22.2lf\n", indice + 1,
                    arrCodProd[i], arrCantAlmac[i], arrPrecProd[i],
                    arrSubAlmac[i]);
            costoTotal += arrSubAlmac[i];
            indice++;
        }
    }
    // Imprimir resumen del reporte
    imprimirLinea(archRep, '-');
    fprintf(archRep, "Costo total de productos perdidos: S/. %.2lf\n",
            costoTotal);
    imprimirLinea(archRep, '=');
    fputc('\n', archRep);
}

/* Reporte de platos que no se podrán preparar */

void llenarPlatPrep(int* arrCodPlat, int* arrCantPlat, int* numPlat) {
    FILE* archPlatPrep = abrirArchivo("PlatosAPreparar.txt", "r");
    while (1) {
        fscanf(archPlatPrep, "%d", &arrCodPlat[*numPlat]);
        if (feof(archPlatPrep)) break;
        fscanf(archPlatPrep, "%d", &arrCantPlat[*numPlat]);
        (*numPlat)++;
    }
    fclose(archPlatPrep);
}

void llenarPrecPlat(int* arrCodPlat, int* arrCantPlat, double* arrPrecPlat, 
        double* arrSubPlat, int numPlat, int* arrCodProd, double* arrPrecProd,
        int numProd) {
    FILE* archPlatos = abrirArchivo("Platos.txt", "r");
    int codPlat, indPlat;
    while (1) {
        fscanf(archPlatos, "%d", &codPlat);
        if (feof(archPlatos)) break;
        // Buscar el plato leído en el arreglo
        indPlat = buscarEnArreglo(arrCodPlat, numPlat, codPlat);
        if (indPlat != NO_ENCONTRADO) {
            while (fgetc(archPlatos) != ')'); // Ignorar el nombre del plato
            calcularSubPlat(archPlatos, arrCantPlat, arrPrecPlat, arrSubPlat, 
                   indPlat, arrCodProd, arrPrecProd, numProd);
        } else {
            while (fgetc(archPlatos) != '\n'); // Ignorar resto de la línea
        }
    }
    fclose(archPlatos);
}

void calcularSubPlat(FILE* archPlatos, int* arrCantPlat, double* arrPrecPlat,
        double* arrSubPlat, int indPlat, int* arrCodProd, double* arrPrecProd,
        int numProd) {
    int codProd, indProd;
    double cantProd;
    // Leer producto por producto e ir almacenando el precio del plato
    while (1) {
        fscanf(archPlatos, "%d %lf", &codProd, &cantProd);
        // Buscar el producto leído en el arreglo de precios de productos
        indProd = buscarEnArreglo(arrCodProd, numProd, codProd);
        if (indProd != NO_ENCONTRADO) {
            arrPrecPlat[indPlat] += arrPrecProd[indProd] * cantProd;
        }
        // Buscar el producto leído en el arreglo de productos almacenados
        if (fgetc(archPlatos) == '\n') break;
    }
    // Agregar al subtotal de precio de productos de los platos. Asumimos que
    // siempre van a haber pérdidas de los platos no importa el ingrediente
    arrSubPlat[indPlat] = arrPrecPlat[indPlat] * arrCantPlat[indPlat];
}

void ordenarPlatos(int* arrCodPlat, int* arrCantPlat, double* arrPrecPlat, 
        double* arrSubPlat, int numPlat) {
    int condCant, condCantSub;
    for (int i = 0; i < (numPlat-1); i++) {
        for (int j = i+1; j < numPlat; j++) {
            // Verificar las condiciones de ordenamiento
            condCant = arrCantPlat[i] > arrCantPlat[j];
            condCantSub = arrCantPlat[i] == arrCantPlat[j]
                    && arrSubPlat[i] < arrSubPlat[j];
            // Si estas se cumplen, intercambiar los datos de ambos índices
            if (condCant || condCantSub) {
                intercambiarInt(arrCodPlat, i, j);
                intercambiarInt(arrCantPlat, i, j);
                intercambiarDouble(arrPrecPlat, i, j);
                intercambiarDouble(arrSubPlat, i, j);
            }
        }
    }
}

void reportePlatos(FILE* archRep, int* arrCodPlat, int* arrCantPlat,
        double* arrPrecPlat, double* arrSubPlat, int numPlat) {
    int indice = 0;
    double montoTotal = 0;
    // Imprimir cabecera del reporte
    imprimirLinea(archRep, '=');
    fprintf(archRep, "PLATOS QUE NO SE PODRAN PREPARAR\n");
    imprimirLinea(archRep, '-');
    fprintf(archRep, "%10s %15s %25s %20s\n", "Plato", "Cantidad",
            "Precio Productos (S/.)", "Sub-total (S/.)");
    // Imprimir lista de platos que no se podrán preparar
    for (int i = 0; i < numPlat; i++) {
        if (arrSubPlat[i] > 0) {
            fprintf(archRep, "%3d) %06d %12d %18.2lf %25.2lf\n", indice + 1,
                arrCodPlat[i], arrCantPlat[i], arrPrecPlat[i], arrSubPlat[i]);
            montoTotal += arrSubPlat[i];
            indice++;
        }
    }
    // Imprimir resumen del reporte
    imprimirLinea(archRep, '-');
    fprintf(archRep, "Monto total de pedidos sin preparar: S/. %.2lf\n",
            montoTotal);
    imprimirLinea(archRep, '=');
}

/* Funciones auxiliares */

FILE* abrirArchivo(const char* nomArch, const char* modo) {
    FILE* arch = fopen(nomArch, modo);
    if (arch == NULL) {
        fprintf(stderr, "No se pudo abrir el archivo %s\n", nomArch);
        exit(1);
    }
    return arch;
}

int buscarEnArreglo(int* arr, int num, int codigo) {
    for (int i = 0; i < num; i++) {
        if (arr[i] == codigo) return i;
    }
    return NO_ENCONTRADO;
}

void imprimirLinea(FILE* arch, char c) {
    for (int i = 0; i < MAX_LINEA; i++) {
        fputc(c, arch);
    }
    fputc('\n', arch);
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
