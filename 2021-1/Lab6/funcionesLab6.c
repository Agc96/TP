/*
 * Archivo: funcionesLab6.c
 * Autor:   Anthony Gutiérrez
 *
 * Creado el 11 de julio de 2021, 08:21 PM
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Pasajero.h"
#include "Bus.h"
#include "funcionesCadenas.h"
#include "funcionesLab6.h"

#define MAX_PALABRAS 50
#define MAX_LINEA_VERIF 136
#define MAX_LINEA_FINAL 80
#define NO_ENCONTRADO -1

/* Pregunta 1 */

void crearArchBinBuses() {
    FILE *archTexto = abrirArchivo("Buses.csv", "r");
    FILE *archBin = abrirArchivo("Buses.bin", "wb");
    char *linea, *palabras[MAX_PALABRAS];
    int numPalabras;
    struct Bus bus;
    // Leer línea por línea
    while (1) {
        linea = leeCadenaExacta(archTexto);
        if (linea == NULL) break;
        sacaPalabras(linea, palabras, &numPalabras, ',');
        // Guardar los datos en las estructuras
        strcpy(bus.placa, palabras[0]);
        strcpy(bus.chofer, palabras[1]);
        bus.numeroDeAsientos = atoi(palabras[numPalabras-1]);
        bus.numeroDePasajeros = 0;
        // Formar la cadena de ciudades de destino uniendo los nombres
        strcpy(bus.ciudadesDestino, palabras[2]);
        for (int i = 3; i < numPalabras-1; i++) {
            strcat(bus.ciudadesDestino, " - ");
            strcat(bus.ciudadesDestino, palabras[i]);
        }
        // Liberar los espacios de memoria
        for (int i = 0; i < numPalabras; i++) {
            free(palabras[i]);
        }
        free(linea);
        // Guardar los datos en el archivo binario
        fwrite(&bus, sizeof(struct Bus), 1, archBin);
    }
    fclose(archBin);
    fclose(archTexto);
}

/* Verificación de la pregunta 1 */

void verificarArchBinBuses() {
    FILE *archBuses = abrirArchivo("Buses.bin", "rb");
    FILE *archRep = abrirArchivo("Verificacion.txt", "w");
    int numReg = obtenerNumRegArchBin(archBuses, sizeof(struct Bus));
    struct Bus bus;
    // Imprimir cabecera
    fprintf(archRep, "%-8s %-45s %-60s %-10s %s\n", "Placa", "Chofer",
            "Ciudades de destino", "Asientos", "Pasajeros");
    imprimirLinea(archRep, '=', MAX_LINEA_VERIF);
    // Imprimir lista de buses
    for (int i = 0; i < numReg; i++) {
        fread(&bus, sizeof(struct Bus), 1, archBuses);
        fprintf(archRep, "%-8s %-45s %-60s %5d %10d\n", bus.placa, bus.chofer,
                bus.ciudadesDestino, bus.numeroDeAsientos, bus.numeroDePasajeros);
    }
    fclose(archRep);
    fclose(archBuses);
}

int obtenerNumRegArchBin(FILE *archBin, int tamReg) {
    fseek(archBin, 0, SEEK_END);
    int numReg = ftell(archBin);
    fseek(archBin, 0, SEEK_SET);
    return numReg / tamReg;
}

void imprimirLinea(FILE *arch, char c, int num) {
    for (int i = 0; i < num; i++) {
        fputc(c, arch);
    }
    fputc('\n', arch);
}

/* Parte 2: Llenado de los pasajeros */

void llenarPasajeros() {
    FILE *archPasajeros = abrirArchivo("Pasajeros.csv", "r");
    FILE *archBuses = abrirArchivo("Buses.bin", "r+b");
    FILE *archEspera = abrirArchivo("ListaDeEspera.bin", "wb");
    char *linea, *palabras[MAX_PALABRAS];
    int numReg, numPalabras, pos;
    struct Bus bus;
    struct Pasajero pasajero;
    // Leer línea por línea
    numReg = obtenerNumRegArchBin(archBuses, sizeof(struct Bus));
    while (1) {
        linea = leeCadenaExacta(archPasajeros);
        if (linea == NULL) break;
        sacaPalabras(linea, palabras, &numPalabras, ',');
        llenarDatosPasajero(linea, palabras, numPalabras, &pasajero);
        // Buscar una ciudad donde se pueda asignar al pasajero
        pos = buscarBus(archBuses, numReg, &bus, &pasajero);
        if (pos != NO_ENCONTRADO) {
            actualizarBusEnArchBin(&bus, &pasajero, archBuses, pos);
        } else {
            fwrite(&pasajero, sizeof(struct Pasajero), 1, archEspera);
        }
    }
    fclose(archEspera);
    fclose(archBuses);
    fclose(archPasajeros);
}

void llenarDatosPasajero(char *linea, char **palabras, int numPalabras,
        struct Pasajero *pasajero) {
    // Asignar datos del pasajero
    pasajero->dni = atoi(palabras[0]);
    strcpy(pasajero->nombre, palabras[1]);
    strcpy(pasajero->destino, palabras[2]);
    // Liberar espacios
    for (int i = 0; i < numPalabras; i++) {
        free(palabras[i]);
    }
    free(linea);
}

int buscarBus(FILE *archBus, int numReg, struct Bus *bus, struct Pasajero* pasajero) {
    fseek(archBus, 0, SEEK_SET);
    for (int i = 0; i < numReg; i++) {
        fread(bus, sizeof(struct Bus), 1, archBus);
        // Verificar si el bus pasa por el destino y está disponible
        if (strstr(bus->ciudadesDestino, pasajero->destino) != NULL
                && bus->numeroDePasajeros < bus->numeroDeAsientos) {
            return i;
        }
    }
    return NO_ENCONTRADO;
}

void actualizarBusEnArchBin(struct Bus *bus, struct Pasajero *pasajero,
        FILE *archBuses, int pos) {
    // Actualizar estructura del bus
    bus->pasajeros[bus->numeroDePasajeros].dni = pasajero->dni;
    strcpy(bus->pasajeros[bus->numeroDePasajeros].nombre, pasajero->nombre);
    strcpy(bus->pasajeros[bus->numeroDePasajeros].destino, pasajero->destino);
    bus->numeroDePasajeros++;
    // Guardar estructura en el archivo binario
    fseek(archBuses, sizeof(struct Bus)*pos, SEEK_SET);
    fwrite(bus, sizeof(struct Bus), 1, archBuses);
}

/* Parte 3: Ordenar buses */

void ordenarArchBinBuses() {
    FILE *archBuses = abrirArchivo("Buses.bin", "r+b");
    int numReg, cantCiudades1, cantCiudades2;
    struct Bus bus1, bus2;
    // Recorrer la lista de buses para el ordenamiento
    numReg = obtenerNumRegArchBin(archBuses, sizeof(struct Bus));
    for (int i = 0; i < numReg-1; i++) {
        for (int j = i+1; j < numReg; j++) {
            fseek(archBuses, sizeof(struct Bus)*i, SEEK_SET);
            fread(&bus1, sizeof(struct Bus), 1, archBuses);
            fseek(archBuses, sizeof(struct Bus)*j, SEEK_SET);
            fread(&bus2, sizeof(struct Bus), 1, archBuses);
            // Calcular la cantidad de ciudades de cada bus
            cantCiudades1 = calcularCantDestinos(&bus1);
            cantCiudades2 = calcularCantDestinos(&bus2);
            if (cantCiudades1 < cantCiudades2) {
                fseek(archBuses, sizeof(struct Bus)*j, SEEK_SET);
                fwrite(&bus1, sizeof(struct Bus), 1, archBuses);
                fseek(archBuses, sizeof(struct Bus)*i, SEEK_SET);
                fwrite(&bus2, sizeof(struct Bus), 1, archBuses);
            }
        }
    }
    fclose(archBuses);
}

int calcularCantDestinos(struct Bus *bus) {
    int numCiudades = 1;
    for (int i = 0; bus->ciudadesDestino[i] != 0; i++) {
        if (bus->ciudadesDestino[i] == '-') numCiudades++;
    }
    return numCiudades;
}

/* Parte 4: Impresión del reporte */

void imprimirReporte() {
    FILE *archBuses = abrirArchivo("Buses.bin", "rb");
    FILE *archEspera = abrirArchivo("ListaDeEspera.bin", "rb"); 
    FILE *archRep = abrirArchivo("Reporte.txt", "w");
    int numRegBus = obtenerNumRegArchBin(archBuses, sizeof(struct Bus));
    int numRegEspera = obtenerNumRegArchBin(archEspera, sizeof(struct Pasajero));
    struct Bus bus;
    struct Pasajero pasajero;
    // Imprimir cabecera de lista de buses
    fprintf(archRep, "%50s\n", "Lista de pasajeros");
    imprimirLinea(archRep, '=', MAX_LINEA_FINAL);
    // Imprimir lista de buses
    for (int i = 0; i < numRegBus; i++) {
        fread(&bus, sizeof(struct Bus), 1, archBuses);
        if (i != 0) imprimirLinea(archRep, '-', MAX_LINEA_FINAL);
        imprimirDatosBus(archRep, &bus, i+1);
    }
    // Imprimir cabecera de lista de pasajeros en espera
    imprimirLinea(archRep, '=', MAX_LINEA_FINAL);
    fprintf(archRep, "PASAJEROS EN LISTA DE ESPERA\n");
    imprimirLinea(archRep, '-', MAX_LINEA_FINAL);
    fprintf(archRep, "%-7s%-8s%-42s%s\n", "No.", "DNI", "Nombre", "Destino");
    // Imprimir lista de pasajeros en espera
    for (int i = 0; i < numRegEspera; i++) {
        fread(&pasajero, sizeof(struct Pasajero), 1, archEspera);
        fprintf(archRep, "%3d  %8d  %-40s  %s\n", i+1, pasajero.dni,
                pasajero.nombre, pasajero.destino);
    }
    fclose(archRep);
    fclose(archEspera);
    fclose(archBuses);
}

void imprimirDatosBus(FILE *archRep, struct Bus *bus, int indice) {
    char *palabras[MAX_PALABRAS];
    int numPalabras, indPasajeros;
    // Imprimir datos principales
    fprintf(archRep, "Vehiculo No. %d\n", indice);
    fprintf(archRep, "Placa: %s\n", bus->placa);
    fprintf(archRep, "Chofer: %s\n", bus->chofer);
    fprintf(archRep, "Ruta: %s\n", bus->ciudadesDestino);
    fprintf(archRep, "Pasajeros:\n");
    // Listar ciudades de destino
    sacaPalabras(bus->ciudadesDestino, palabras, &numPalabras, '-');
    for (int i = 0; i < numPalabras; i++) {
        corregirPalabraDestino(palabras[i]);
        // Imprimir cabecera de lista de pasajeros
        fprintf(archRep, "%s:\n", palabras[i]);
        fprintf(archRep, "%-7s%-8s%s\n", "No.", "DNI", "Nombre");
        // Imprimir lista de pasajeros
        indPasajeros = 0;
        for (int j = 0; j < bus->numeroDePasajeros; j++) {
            if (strcmp(palabras[i], bus->pasajeros[j].destino) == 0) {
                fprintf(archRep, "%3d  %8d  %s\n", ++indPasajeros,
                        bus->pasajeros[j].dni, bus->pasajeros[j].nombre);
            }
        }
        // Liberar espacio de memoria
        free(palabras[i]);
    }
}

void corregirPalabraDestino(char *destino) {
    int longitud = strlen(destino);
    // Verificar si hay un espacio en blanco al final
    if (destino[longitud-1] == ' ') {
        destino[longitud-1] = 0;
    }
    // Verificar si hay un espacio en blanco al inicio
    if (destino[0] == ' ') {
        for (int i = 0; i < longitud; i++) {
            destino[i] = destino[i+1];
        }
    }
}
