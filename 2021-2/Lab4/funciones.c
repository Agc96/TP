/*
 * File:   funciones.c
 * Author: Anthony Gutiérrez
 *
 * Created on 2 de noviembre de 2021, 08:37 AM
 */

#include <ctype.h>
#include "funciones.h"

#define MAX_LINEA 80
#define MAX_NOMBRE 100
#define NO_ENCONTRADO -1

int leerProductos(int *arrCodProd, int *arrStockProd, double *arrPrecioProd) {
    FILE *arch = abrirArchivo("StockDeProductosAlmacenados.txt", "r");
    int cantProd = 0;
    while (1) {
        fscanf(arch, "%d", &arrCodProd[cantProd]);
        if (feof(arch)) break;
        fscanf(arch, "%d %lf", &arrStockProd[cantProd], &arrPrecioProd[cantProd]);
        (cantProd)++;
    }
    fclose(arch);
    return cantProd;
}

int leerPedidos(int *arrCodPed, int *arrFechaPed, int *arrHoraPed, int *arrCliPed) {
    FILE *arch = abrirArchivo("Pedidos.txt", "r");
    int dia, mes, anho, hora, min, seg, cantPed = 0;
    while (1) {
        fscanf(arch, "%d", &arrCodPed[cantPed]);
        if (feof(arch)) break;
        fscanf(arch, "%d/%d/%d %d:%d:%d", &dia, &mes, &anho, &hora, &min, &seg);
        arrFechaPed[cantPed] = 10000*anho + 100*mes + dia;
        arrHoraPed[cantPed] = 3600*hora + 60*min + seg;
        fscanf(arch, "%d", &arrCliPed[cantPed]);
        cantPed++;
    }
    fclose(arch);
    return cantPed;
}

int leerDetalles(int *arrCodPedDet, int *arrCodProdDet, int *arrCantProdDet) {
    FILE *arch = abrirArchivo("DetalleDeLosPedidos.txt", "r");
    int cantDet = 0;
    while (1) {
        fscanf(arch, "%d", &arrCodPedDet[cantDet]);
        if (feof(arch)) break;
        fscanf(arch, "%d %d", &arrCodProdDet[cantDet], &arrCantProdDet[cantDet]);
        cantDet++;
    }
    fclose(arch);
    return cantDet;
}

void ordenarProductos(int *arrCodProd, int *arrStockProd, double *arrPrecioProd,
        int cantProd) {
    for (int i = 0; i < cantProd-1; i++) {
        for (int j = i+1; j < cantProd; j++) {
            if (arrCodProd[i] > arrCodProd[j]) {
                intercambiarInt(arrCodProd, i, j);
                intercambiarInt(arrStockProd, i, j);
                intercambiarDouble(arrPrecioProd, i, j);
            }
        }
    }
}

void ordenarPedidos(int *arrCodPed, int *arrFechaPed, int *arrHoraPed,
        int *arrCliPed, int cantPed) {
    int cond1, cond2, cond3;
    for (int i = 0; i < cantPed-1; i++) {
        for (int j = i+1; j < cantPed; j++) {
            cond1 = arrFechaPed[i] > arrFechaPed[j];
            cond2 = arrFechaPed[i] == arrFechaPed[j]
                    && arrHoraPed[i] > arrHoraPed[j];
            cond3 = arrFechaPed[i] == arrFechaPed[j]
                    && arrHoraPed[i] == arrHoraPed[j]
                    && arrCodPed[i] > arrCodPed[j];
            if (cond1 || cond2 || cond3) {
                intercambiarInt(arrCodPed, i, j);
                intercambiarInt(arrFechaPed, i, j);
                intercambiarInt(arrHoraPed, i, j);
                intercambiarInt(arrCliPed, i, j);
            }
        }
    }
}

void imprimirReporte(int *arrCodProd, int *arrStockProd, double *arrPrecioProd,
        int cantProd, int *arrCodPed, int *arrFechaPed, int *arrHoraPed,
        int *arrCliPed, int cantPed, int *arrCodPedDet, int *arrCodProdDet,
        int *arrCantProdDet, int cantDet) {
    FILE *arch = abrirArchivo("ReporteDePedidos.txt", "w");
    double total;
    // Imprimir cabecera del reporte
    imprimirLinea(arch, '=');
    fprintf(arch, "%54s\n", "TIENDA VIRTUAL  LA MAGNIFICA");
    fprintf(arch, "%55s\n", "REPORTE DE ATENCION DE PEDIDOS");
    imprimirLinea(arch, '-');
    // Imprimir listado de pedidos
    for (int i = 0; i < cantPed; i++) {
        // Imprimir cabecera del pedido
        imprimirCabeceraPedido(arch, arrCodPed, arrFechaPed, arrHoraPed,
                arrCliPed, i);
        // Imprimir listado de detalles del pedido
        total = imprimirDetallesPedido(arch, arrCodProd, arrStockProd,
                arrPrecioProd, cantProd, arrCodPed[i], arrCodPedDet,
                arrCodProdDet, arrCantProdDet, cantDet);
        // Imprimir resumen del pedido
        fprintf(arch, "Total a cobrar: %.2lf\n", total);
        imprimirLinea(arch, '=');
    }
    fclose(arch);
}

void imprimirCabeceraPedido(FILE *arch, int *arrCodPed, int *arrFechaPed,
        int *arrHoraPed, int *arrCliPed, int i) {
    int dia, mes, anho, hora, min, seg;
    // Imprimir datos principales
    fprintf(arch, "%12s %10s %20s %18s %12s\n", "Nro. de pedido", "DNI",
            "Nombre", "Fecha", "Hora");
    fprintf(arch, "%10d %16d", arrCodPed[i], arrCliPed[i]);
    imprimirNombreCliente(arch, arrCliPed[i]);
    // Imprimir fecha del pedido
    anho = arrFechaPed[i] / 10000;
    mes = (arrFechaPed[i] % 10000) / 100;
    dia = arrFechaPed[i] % 100;
    fprintf(arch, "%5c%02d/%02d/%04d", ' ', dia, mes, anho);
    // Imprimir hora del pedido
    hora = arrHoraPed[i] / 3600;
    min = (arrHoraPed[i] % 3600) / 60;
    seg = arrHoraPed[i] % 60;
    fprintf(arch, "%5c%02d:%02d:%02d\n", ' ', hora, min, seg);
    imprimirLinea(arch, '-');
    // Imprimir cabecera del detalle del pedido
    fprintf(arch, "%10s %22s %20s %10s %12s\n", "Producto",
            "Cantidad solicitada", "Cantidad atendida", "Precio", "Subtotal");
}

void imprimirNombreCliente(FILE *archReporte, int codBuscado) {
    FILE *archClientes = fopen("ClientesRegistrados.txt", "r");
    char nomOriginal[MAX_NOMBRE], nomModificado[MAX_NOMBRE];
    int longitud, codLeido, continuar = 1;
    while (continuar) {
        longitud = 0;
        while (1) {
            nomOriginal[longitud] = fgetc(archClientes);
            if (nomOriginal[longitud] == ' ') break;
            longitud++;
        }
        nomOriginal[longitud] = 0;
        // Leer el código
        fscanf(archClientes, "%d\n", &codLeido);
        if (feof(archClientes) || codLeido == codBuscado) break;
    }
    fclose(archClientes);
    // Imprimir el nombre en el reporte
    modificarNombre(nomOriginal, nomModificado);
    fprintf(archReporte, "%5c%-20s", ' ', nomModificado);
}

void modificarNombre(const char *cad1, char *cad2) {
    int longitud = 0, mayusculas = 1, i;
    // Copiar el apellido paterno
    for (i = 0; cad1[i] != '/'; i++);
    for (i++; cad1[i] != '/'; i++) {
        if (mayusculas) {
            cad2[longitud++] = cad1[i];
            mayusculas = 0;
        } else {
            cad2[longitud++] = tolower(cad1[i]);
        }
    }
    cad2[longitud++] = ' ';
    // Copiar el primer nombre
    mayusculas = 1;
    for (i = 0; cad1[i] != '-' && cad1[i] != '/'; i++) {
        if (mayusculas) {
            cad2[longitud++] = cad1[i];
            mayusculas = 0;
        } else {
            cad2[longitud++] = tolower(cad1[i]);
        }
    }
    cad2[longitud] = 0;
}

double imprimirDetallesPedido(FILE *arch, int *arrCodProd, int *arrStockProd,
        double *arrPrecioProd, int cantProd, int codPed, int *arrCodPedDet,
        int *arrCodProdDet, int *arrCantProdDet, int cantDet) {
    double subtotal, total = 0;
    int indiceDet = 1, indiceProd, cantAtendida;
    for (int i = 0; i < cantDet; i++) {
        if (arrCodPedDet[i] == codPed) {
            // Imprimir datos principales del detalle
            fprintf(arch, "%2d) %5d %15d", indiceDet, arrCodProdDet[i],
                    arrCantProdDet[i]);
            // Buscar el índice del producto
            indiceProd = busquedaBinaria(arrCodProd, cantProd, arrCodProdDet[i]);
            if (indiceProd != NO_ENCONTRADO) {
                // Verificar que haya suficiente cantidad en stock
                if (arrStockProd[indiceProd] > arrCantProdDet[i]) {
                    cantAtendida = arrCantProdDet[i];
                    arrStockProd[indiceProd] -= arrCantProdDet[i];
                } else {
                    cantAtendida = arrStockProd[indiceProd];
                    arrStockProd[indiceProd] = 0;
                }
                // Calcular precio y subtotal
                subtotal = arrPrecioProd[indiceProd] * cantAtendida;
                total += subtotal;
                fprintf(arch, "%22d %18.2lf %12.2lf\n", cantAtendida,
                        arrPrecioProd[indiceProd], subtotal);
            }
            indiceDet++;
        }
    }
    imprimirLinea(arch, '-');
    return total;
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

int busquedaSecuencial(int *arr, int cant, int cod) {
    for (int i = 0; i < cant; i++) {
        if (arr[i] == cod) return i;
    }
    return NO_ENCONTRADO;
}

int busquedaBinaria(int *arr, int cant, int codBuscado) {
    int indInf = 0, indSup = cant - 1, indMedio, codMedio;
    while (1) {
        if (indInf > indSup) return NO_ENCONTRADO;
        indMedio = (indInf+indSup)/2;
        codMedio = arr[indMedio];
        if (codMedio == codBuscado) return indMedio;
        if (codMedio < codBuscado) {
            indInf = indMedio + 1;
        } else {
            indSup = indMedio - 1;
        }
    }
}

void imprimirLinea(FILE *arch, char c) {
    for (int i = 0; i < MAX_LINEA; i++) {
        fputc(c, arch);
    }
    fputc('\n', arch);
}
