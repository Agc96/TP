/*
 * Archivo: funciones.c
 * Autor:   Anthony Gutiérrez
 *
 * Creado el 14 de noviembre de 2020, 10:17 PM
 */

#include "funciones.h"
#define MAX_NOMBRE 40
#define TAM_SEPARACION 80
#define NO_ENCONTRADO -1

void leerProductos(int *arrCodProd, int *arrStockProd, int *numProd) {
    FILE *arch = fopen("Productos.txt", "r");
    if (arch == NULL) {
        perror("No se pudo abrir el archivo Productos.txt");
        exit(1);
    }
    while (1) {
        // Leer el código y el stock del producto
        fscanf(arch, "%d %d", &arrCodProd[*numProd], &arrStockProd[*numProd]);
        if (feof(arch)) break;
        // Ignorar el resto de caracteres de la línea
        while (fgetc(arch) != '\n');
        // Incrementar contador de productos
        (*numProd)++;
    }
    fclose(arch);
}

void leerMovimientos(int *arrCodProd, int *arrStockProd, int *numProd,
        int *arrCodDeficit, int *arrStockDeficit, int *numDeficit) {
    // Apertura del archivo
    FILE *arch = fopen("Movimientos.txt", "r");
    if (arch == NULL) {
        perror("No se pudo abrir el archivo Movimientos.txt");
        exit(1);
    }
    int codProd, stock;
    char operacion;
    while (1) {
        // Descartar los dos primeros números y obtener el tipo de operación
        fscanf(arch, "%*d %*d %c", &operacion);
        if (feof(arch)) break;
        while (1) {
            fscanf(arch, "%d %d", &codProd, &stock);
            if (operacion == 'R') {
                reponerStock(arrCodProd, arrStockProd, numProd, arrCodDeficit,
                        arrStockDeficit, numDeficit, codProd, stock);
            } else if (operacion == 'P') {
                atenderPedido(arrCodProd, arrStockProd, numProd, arrCodDeficit,
                        arrStockDeficit, numDeficit, codProd, stock);
            }
            // Verificar si se terminó la línea
            if (fgetc(arch) == '\n') break;
        }
    }
    fclose(arch);
}

void reponerStock(int *arrCodProd, int *arrStockProd, int *numProd,
        int *arrCodDeficit, int *arrStockDeficit, int *numDeficit,
        int codProd, int stock) {
    // Buscar en la lista de productos con stock
    int pos = buscar(arrCodProd, codProd, *numProd);
    if (pos != NO_ENCONTRADO) {
        arrStockProd[pos] += stock;
    } else {
        // Buscar en la lista de productos con déficit
        pos = buscar(arrCodDeficit, codProd, *numDeficit);
        if (pos != NO_ENCONTRADO) {
            arrStockDeficit[pos] -= stock;
            if (arrStockDeficit[pos] < 0) {
                // Agregar el stock restante en el arreglo de productos con stock
                arrCodProd[*numProd] = arrCodDeficit[pos];
                arrStockProd[*numProd] = -arrStockDeficit[pos];
                (*numProd)++;
                // Eliminar el stock negativo del arreglo de productos con déficit
                (*numDeficit)--;
                for (int i = pos; i < *numDeficit; i++) {
                    arrCodDeficit[i] = arrCodDeficit[i+1];
                    arrStockDeficit[i] = arrStockDeficit[i+1];
                }
            }
        }
    }
}

void atenderPedido(int *arrCodProd, int *arrStockProd, int *numProd,
        int *arrCodDeficit, int *arrStockDeficit, int *numDeficit,
        int codProd, int stock) {
    // Buscar en la lista de productos con stock
    int pos = buscar(arrCodProd, codProd, *numProd);
    if (pos != NO_ENCONTRADO) {
        arrStockProd[pos] -= stock;
        if (arrStockProd[pos] < 0) {
            // Agregar el stock restante en el arreglo de productos con déficit
            arrCodDeficit[*numDeficit] = arrCodProd[pos];
            arrStockDeficit[*numDeficit] = -arrStockProd[pos];
            (*numDeficit)++;
            // Eliminar el stock negativo del arreglo de productos con stock
            (*numProd)--;
            for (int i = pos; i < *numProd; i++) {
                arrCodProd[i] = arrCodProd[i+1];
                arrStockProd[i] = arrStockProd[i+1];
            }
        }
    } else {
        // Buscar en la lista de productos con déficit
        pos = buscar(arrCodDeficit, codProd, *numDeficit);
        if (pos != NO_ENCONTRADO) {
            arrStockDeficit[pos] += stock;
        }
    }
}

int buscar(int *arr, int codigo, int num) {
    for (int i = 0; i < num; i++) {
        if (arr[i] == codigo)
            return i;
    }
    return NO_ENCONTRADO;
}

void ordenarArreglos(int *arrCod, int *arrStock, int numDatos) {
    for (int i = 0; i < numDatos-1; i++) {
        for (int j = i+1; j < numDatos; j++) {
            if (arrCod[i] > arrCod[j]) {
                intercambiar(arrCod, i, j);
                intercambiar(arrStock, i, j);
            }
        }
    }
}

void intercambiar(int *arr, int i, int j) {
    int aux = arr[i];
    arr[i] = arr[j];
    arr[j] = aux;
}

void imprimirReporte(int *arrCodProd, int *arrStockProd, int numProd,
        int *arrCodDeficit, int *arrStockDeficit, int numDeficit) {
    // Apertura del archivo
    FILE *arch = fopen("ReporteDeStockDeProductos.txt", "w");
    if (arch == NULL) {
        perror("No se pudo crear el archivo ReporteDeStockDeProductos.txt");
        exit(1);
    }
    // Imprimir cabecera del reporte
    fprintf(arch, "REPORTE DE STOCK Y DEFICIT DE PRODUCTOS\n");
    separacion(arch, '=');
    // Imprimir productos en stock
    fprintf(arch, "PRODUCTOS EN STOCK\n");
    imprimirProductos(arch, arrCodProd, arrStockProd, numProd);
    // Imprimir productos con déficit
    fprintf(arch, "PRODUCTOS CON DEFICIT\n");
    imprimirProductos(arch, arrCodDeficit, arrStockDeficit, numDeficit);
    // Cerrar el archivo
    fclose(arch);
}

void imprimirProductos(FILE *arch, int *arrCodProd, int *arrStock, int numProd) {
    // Imprimir cabecera de productos
    separacion(arch, '-');
    fprintf(arch, "%6s    %-40s    %5s\n", "CODIGO", "DESCRIPCION", "STOCK");
    separacion(arch, '-');
    // Imprimir lista de productos
    for (int i = 0; i < numProd; i++) {
        fprintf(arch, "%06d    ", arrCodProd[i]);
        imprimirNombre(arch, arrCodProd[i]);
        fprintf(arch, "    %5d\n", arrStock[i]);
    }
    // Imprimir resumen de productos
    separacion(arch, '=');
    fprintf(arch, "Total de productos: %d\n", numProd);
    separacion(arch, '=');
}

void imprimirNombre(FILE *archRep, int codProdBuscado) {
    FILE *archProd = fopen("Productos.txt", "r");
    if (archProd == NULL) {
        perror("No se pudo abrir el archivo Productos.txt durante el reporte");
        exit(1);
    }
    int codProdLeido, longitud = 0;
    char c;
    while (1) {
        // Buscar el código del producto e ignorar los espacios antes del nombre
        fscanf(archProd, "%d %*d ", &codProdLeido);
        if (feof(archProd)) break;
        // Ver si el código del producto leído es el buscado
        if (codProdLeido == codProdBuscado) {
            // Copiar el nombre del producto en el reporte
            while (1) {
                c = fgetc(archProd);
                if (c == '\n') break;
                fputc(c, archRep);
                longitud++;
            }
            // Colocar espacios para rellenar el nombre
            for (int i = longitud; i < MAX_NOMBRE; i++) {
                fputc(' ', archRep);
            }
            // Salir del bucle porque ya encontramos el nombre del producto
            break;
        } else {
            // Ignorar el resto de la línea y seguir buscando
            while (fgetc(archProd) != '\n');
        }
    }
    fclose(archProd);
}

void separacion(FILE *arch, char c) {
    for (int i = 0; i < TAM_SEPARACION; i++) {
        fputc(c, arch);
    }
    fputc('\n', arch);
}
