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

void llenarProd(int* arrProd, double* arrPrecProd, int* numProd) {
    FILE* archProd = abrirArchivo("ListaDePrecios.txt", "r");
    while (fgetc(archProd) != '\n'); // Ignorar primera línea
    while (1) {
        fscanf(archProd, "%d", &arrProd[*numProd]);
        if (feof(archProd)) break;
        while (fgetc(archProd) != ']'); // Ignorar nombre del producto
        fscanf(archProd, "%lf", &arrPrecProd[*numProd]);
        (*numProd)++;
    }
    fclose(archProd);
}

void llenarAlmac(int* arrProd, double* arrPrecProd, int numProd, int* arrAlmac,
        double* arrCantAlmac, double* arrPrecAlmac, double* arrSubAlmac,
        int* numAlmac) {
    FILE* archAlmac = abrirArchivo("ProductosAlmacenados.txt", "r");
    int indProd;
    double subtotal;
    while (1) {
        fscanf(archAlmac, "%d", &arrAlmac[*numAlmac]);
        if (feof(archAlmac)) break;
        fscanf(archAlmac, "%lf", &arrCantAlmac[*numAlmac]);
        // Verificar que el producto almacenado tenga un precio en la lista
        indProd = buscarEnArreglo(arrProd, numProd, arrAlmac[*numAlmac]);
        if (indProd != NO_ENCONTRADO) {
            arrPrecAlmac[*numAlmac] = arrPrecProd[indProd];
            subtotal = arrPrecProd[indProd] * arrCantAlmac[*numAlmac];
            arrSubAlmac[*numAlmac] = subtotal;
            (*numAlmac)++;
        }
    }
    fclose(archAlmac);
}

void ordenarAlmac(int* arrAlmac, double* arrCantAlmac, double* arrPrecAlmac,
        double* arrSubAlmac, int numAlmac) {
    for (int i = 0; i < (numAlmac-1); i++) {
        for (int j = i+1; j < numAlmac; j++) {
            if (arrSubAlmac[i] < arrSubAlmac[j]) {
                intercambiarInt(arrAlmac, i, j);
                intercambiarDouble(arrCantAlmac, i, j);
                intercambiarDouble(arrPrecAlmac, i, j);
                intercambiarDouble(arrSubAlmac, i, j);
            }
        }
    }
}

void reporteProd(FILE* archRep, int* arrAlmac, double* arrCantAlmac,
        double* arrPrecAlmac, double* arrSubAlmac, int numAlmac) {
    double costoTotal = 0;
    // Imprimir cabecera del reporte
    imprimirLinea(archRep, '=');
    fprintf(archRep, "PRODUCTOS PERDIDOS\n");
    imprimirLinea(archRep, '-');
    fprintf(archRep, "%10s %15s %25s %20s\n", "Producto", "Cantidad",
            "Precio Unitario (S/.)", "Sub-total (S/.)");
    // Imprimir lista de productos almacenados
    for (int i = 0; i < numAlmac; i++) {
        fprintf(archRep, "%3d) %05d %15.2lf %18.2lf %22.2lf\n", i + 1,
                arrAlmac[i], arrCantAlmac[i], arrPrecAlmac[i], arrSubAlmac[i]);
        costoTotal += arrSubAlmac[i];
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
        double* arrSubPlat, int numPlat, int* arrProd, double* arrPrecProd,
        int numProd, int* arrAlmac, int numAlmac) {
    FILE* archPlatos = abrirArchivo("Platos.txt", "r");
    int codPlat, indPlat, valido;
    while (1) {
        fscanf(archPlatos, "%d", &codPlat);
        if (feof(archPlatos)) break;
        // Buscar el plato leído en el arreglo
        indPlat = buscarEnArreglo(arrCodPlat, numPlat, codPlat);
        if (indPlat != NO_ENCONTRADO) {
            while (fgetc(archPlatos) != ')'); // Ignorar el nombre del plato
            calcularSubPlat(archPlatos, arrCantPlat, arrPrecPlat, arrSubPlat, 
                   indPlat, arrProd, arrPrecProd, numProd, arrAlmac, numAlmac);
        } else {
            while (fgetc(archPlatos) != '\n'); // Ignorar resto de la línea
        }
    }
    fclose(archPlatos);
}

void calcularSubPlat(FILE* archPlatos, int* arrCantPlat, double* arrPrecPlat,
        double* arrSubPlat, int indPlat, int* arrProd, double* arrPrecProd,
        int numProd, int* arrAlmac, int numAlmac) {
    int codProd, indProd, indPerdida, valido = 0;
    double cantProd;
    // Leer producto por producto e ir almacenando el precio del plato
    while (1) {
        fscanf(archPlatos, "%d %lf", &codProd, &cantProd);
        // Buscar el producto leído en el arreglo de precios de productos
        indProd = buscarEnArreglo(arrProd, numProd, codProd);
        if (indProd != NO_ENCONTRADO) {
            arrPrecPlat[indPlat] += arrPrecProd[indProd] * cantProd;
            printf("arrPrecPlat[%d] = %lf\n", indPlat, arrPrecPlat[indPlat]);
        }
        // Buscar el producto leído en el arreglo de productos almacenados
        indPerdida = buscarEnArreglo(arrAlmac, numAlmac, codProd);
        if (indPerdida != NO_ENCONTRADO) {
            valido = 1;
        }
        if (fgetc(archPlatos) == '\n') break;
    }
    // Verificar si tuvo al menos un producto perdido
    if (valido) {
        arrSubPlat[indPlat] += arrPrecPlat[indPlat] * arrCantPlat[indPlat];
    } else {
        arrSubPlat[indPlat] = NO_ENCONTRADO;
    }
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
    int numPlatReal = 0;
    double montoTotal = 0;
    // Imprimir cabecera del reporte
    imprimirLinea(archRep, '=');
    fprintf(archRep, "PLATOS QUE NO SE PODRAN PREPARAR\n");
    imprimirLinea(archRep, '-');
    fprintf(archRep, "%10s %15s %25s %20s\n", "Plato", "Cantidad",
            "Precio Productos (S/.)", "Sub-total (S/.)");
    // Imprimir lista de platos que no se podrán preparar
    for (int i = 0; i < numPlat; i++) {
        if (arrSubPlat[i] != NO_ENCONTRADO) {
            numPlatReal++;
            fprintf(archRep, "%3d) %06d %12d %18.2lf %25.2lf\n", numPlatReal,
                arrCodPlat[i], arrCantPlat[i], arrPrecPlat[i], arrSubPlat[i]);
            montoTotal += arrSubPlat[i];
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
