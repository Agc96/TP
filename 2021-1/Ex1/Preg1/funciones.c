/*
 * Archivo: funciones.c
 * Autor:   Anthony Gutiérrez
 *
 * Creado el 25 de mayo de 2021, 10:30 AM
 */

#include <stdio.h>
#include <stdlib.h>
#include "funciones.h"

#define MAX_LINEA 100
#define MAX_NOM_PLATO 30
#define NO_ENCONTRADO -1

void generarReporte(FILE* archListPrec, FILE* archPlatos, FILE* archPreparar,
        FILE* archReporte) {
    int numPlatos = 0, codPlato, cantPreparar;
    double costoTotal = 0;
    // Imprimir cabecera
    imprimirCabecera(archListPrec, archReporte);
    // Imprimir listado de platos
    while (1) {
        fscanf(archPlatos, "%d", &codPlato);
        if (feof(archPlatos)) break;
        // Imprimir índice y nombre del plato
        // Buscar la cantidad de platos a preparar
        cantPreparar = buscarCantPreparar(archPreparar, codPlato);
        if (cantPreparar != NO_ENCONTRADO) {
            numPlatos++;
            colocarNombrePlato(archPlatos, archReporte, numPlatos);
            colocarDetallesPlato(archPlatos, archListPrec, archReporte,
                    cantPreparar, &costoTotal);
        } else {
            // Ignorar el resto de la línea
            while (fgetc(archPlatos) != '\n');
        }
    }
    // Imprimir resumen
    imprimirLinea(archReporte, '-');
    fprintf(archReporte, "%3cCosto total: %.2lf\n", ' ', costoTotal);
    imprimirLinea(archReporte, '=');
}

void imprimirCabecera(FILE* archListPrec, FILE* archReporte) {
    char c;
    // Imprimir título del reporte
    fprintf(archReporte, "COSTOS DE LOS PLATOS OFRECIDOS:\n");
    imprimirLinea(archReporte, '=');
    // Imprimir nombre del proveedor
    fprintf(archReporte, "Proveedor: ");
    while (1) {
        c = fgetc(archListPrec);
        fputc(c, archReporte);
        if (c == '\n') break;
    }
    imprimirLinea(archReporte, '-');
    // Imprimir cabecera del listado de platos
    fprintf(archReporte, "%20s %35s %20s %18s\n", "Plato",
            "Cantidad a elaborar", "Costo por plato", "Costo total");
    imprimirLinea(archReporte, '-');
}

void colocarNombrePlato(FILE* archPlatos, FILE* archReporte, int indice) {
    int tamNombre = 0;
    char c;
    // Colocar el índice del plato
    fprintf(archReporte, "%5d.- ", indice);
    // Ignorar los caracteres hasta el inicio del paréntesis
    while (fgetc(archPlatos) != '(');
    // Colocar los caracteres hasta el final del paréntesis
    while (1) {
        c = fgetc(archPlatos);
        if (c == ')') break;
        fputc(c, archReporte);
        tamNombre++;
    }
    // Rellenar el resto de caracteres con espacios
    for (int i = tamNombre; i < MAX_NOM_PLATO; i++) {
        fputc(' ', archReporte);
    }
}

int buscarCantPreparar(FILE* archPreparar, int codPlato) {
    int codLeido, cant;
    rewind(archPreparar);
    while (1) {
        fscanf(archPreparar, "%d", &codLeido);
        if (feof(archPreparar)) break;
        fscanf(archPreparar, "%d", &cant);
        if (codLeido == codPlato) {
            return cant;
        }
    }
    return NO_ENCONTRADO;
}

void colocarDetallesPlato(FILE* archPlatos, FILE* archListPrec,
        FILE* archReporte, int cantPreparar, double* costoTotal) {
    int codProd, valido = 1;
    double cantProd, precioProd, subTotalProd, costoPorPlato = 0, totalPlato;
    while (1) {
        fscanf(archPlatos, "%d %lf", &codProd, &cantProd);
        precioProd = buscarPrecioProducto(archListPrec, codProd);
        if (precioProd != NO_ENCONTRADO) {
            subTotalProd = cantProd * precioProd;
            costoPorPlato += subTotalProd;
        } else {
            if (valido) {
                fprintf(archReporte, "No se puede calcular por falta del "
                        "producto: %d\n", codProd);
                valido = 0;
            }
        }
        if (fgetc(archPlatos) == '\n') break;
    }
    // Actualizar el costo total del reporte
    if (valido) {
        totalPlato = cantPreparar * costoPorPlato;
        fprintf(archReporte, "%10d %25.2lf %20.2lf\n", cantPreparar,
                costoPorPlato, totalPlato);
        (*costoTotal) += totalPlato;
    }
}

double buscarPrecioProducto(FILE* archListPrec, int codProd) {
    int codLeido;
    double precio;
    // Volver al principio del archivo e ignorar primera línea
    rewind(archListPrec);
    while (fgetc(archListPrec) != '\n');
    // Leer línea por línea los productos
    while (1) {
        fscanf(archListPrec, "%d", &codLeido);
        if (feof(archListPrec)) break;
        // Verificar si es el producto deseado
        if (codLeido == codProd) {
            // Ignorar nombre del producto
            while (fgetc(archListPrec) != ']');
            // Devolver el precio del producto
            fscanf(archListPrec, "%lf", &precio);
            return precio;
        } else {
            // Ignorar la línea del producto
            while (fgetc(archListPrec) != '\n');
        }
    }
    return NO_ENCONTRADO;
}

void cerrarArchivos(FILE* archListPrec, FILE* archPlatos, FILE* archPreparar,
        FILE* archReporte) {
    fclose(archListPrec);
    fclose(archPlatos);
    fclose(archPreparar);
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
