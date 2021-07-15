/*
 * Archivo: funciones.c
 * Autor:   Anthony Gutiérrez
 *
 * Creado el 30 de noviembre de 2020, 08:20 PM
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "funcionesCadenas.h"
#include "funcionesPacientes.h"

#define MAX_SEPARACION 70
#define NO_ENCONTRADO -1

/* Parte 1: Leer el archivo de médicos */

void leerMedicos(struct Medico *medicos, int *numMedicos) {
    FILE *arch = abrirArchivo("Medicos.csv", "r");
    char buffer[100], *palabras[10];
    int numPalabras;
    // Leer línea por linea
    *numMedicos = 0;
    while (1) {
        leerCadena(buffer, 100, arch);
        if (feof(arch)) break;
        // Separar las palabras y asignar los datos en la estructura
        sacaPalabras(buffer, palabras, &numPalabras, ',');
        medicos[*numMedicos].codigo = palabras[0];
        medicos[*numMedicos].nombre = palabras[1];
        medicos[*numMedicos].especialidad = palabras[2];
        medicos[*numMedicos].tarifa = atof(palabras[3]);
        medicos[*numMedicos].numCitas = 0;
        // Actualizar el número de médicos
        (*numMedicos)++;
        // Liberar los espacios innecesarios
        free(palabras[3]);
    }
    fclose(arch);
}

/* Parte 2: Leer el archivo de citas */

void leerPacientes(struct Medico *medicos, int numMedicos,
        struct Paciente *pacientes, int *numPacientes) {
    FILE *arch = abrirArchivo("Citas.csv", "r");
    char buffer[1000], *palabras[100];
    int dd, mm, aa, fecha, numPalabras, codPaciente;
    double porcentaje;
    // Leer línea por línea
    *numPacientes = 0;
    while (1) {
        fscanf(arch, "%d/%d/%d,", &dd, &mm, &aa);
        if (feof(arch)) break;
        fecha = 10000*aa + 100*mm + dd;
        leerCadena(buffer, 600, arch);
        // Separar las palabras y registrar todas las citas
        sacaPalabras(buffer, palabras, &numPalabras, ',');
        for (int i = 0; i < numPalabras; i += 4) {
            codPaciente = atoi(palabras[i]);
            porcentaje = atof(palabras[i+2]);
            agregarPaciente(fecha, medicos, numMedicos, pacientes, numPacientes,
                    codPaciente, palabras[i+1], porcentaje, palabras[i+3]);
            free(palabras[i]);
            free(palabras[i+2]);
        }
    }
    fclose(arch);
}

void agregarPaciente(int fecha, struct Medico *medicos, int numMedicos,
        struct Paciente *pacientes, int *numPacientes, int codPaciente,
        char *nomPaciente, double porcentaje, char *codMedico) {
    // Declaración de variablesS
    int posMedico, posPaciente, posCita;
    // Buscar el médico y agregar la cita
    posMedico = buscarMedico(medicos, numMedicos, codMedico);
    if (posMedico != NO_ENCONTRADO) {
        posCita = medicos[posMedico].numCitas;
        medicos[posMedico].citas[posCita].codigo = codPaciente;
        medicos[posMedico].citas[posCita].fecha = fecha;
        medicos[posMedico].citas[posCita].porcentaje = porcentaje;
        (medicos[posMedico].numCitas)++;
    }
    // Buscar el paciente y agregarlo si es que no existe
    posPaciente = buscarPaciente(pacientes, *numPacientes, codPaciente);
    if (posPaciente == NO_ENCONTRADO) {
        pacientes[*numPacientes].codigo = codPaciente;
        pacientes[*numPacientes].nombre = nomPaciente;
        pacientes[*numPacientes].porcentaje = porcentaje;
        (*numPacientes)++;
    }
}

int buscarMedico(struct Medico *medicos, int numMedicos, char *codMedico) {
    for (int i = 0; i < numMedicos; i++) {
        if (strcmp(medicos[i].codigo, codMedico) == 0) return i;
    }
    return NO_ENCONTRADO;
}

int buscarPaciente(struct Paciente *pacientes, int numPacientes, int codPaciente) {
    for (int i = 0; i < numPacientes; i++) {
        if (pacientes[i].codigo == codPaciente) return i;
    }
    return NO_ENCONTRADO;
}

/* Parte 3: Imprimir el reporte */

void imprimirReporte(struct Medico *medicos, int numMedicos,
        struct Paciente *pacientes, int numPacientes) {
    FILE *arch = abrirArchivo("Reporte.txt", "w");
    // Imprimir lista de médicos
    fprintf(arch, "%44s\n", "CITAS POR MEDICO");
    for (int i = 0; i < numMedicos; i++) {
        // Imprimir datos del médico
        separacion('=', arch);
        fprintf(arch, "Medico: %-46s  Codigo: %6s\n", medicos[i].nombre,
                medicos[i].codigo);
        fprintf(arch, "Especialidad: %-40s  Tarifa: %6.2lf\n",
                medicos[i].especialidad, medicos[i].tarifa);
        // Imprimir cabecera de la lista de citas por médico
        separacion('-', arch);
        fprintf(arch, "Relacion de citas:\n");
        fprintf(arch, "%-4s  %8s  %10s  %4c  %10s\n", "No.", "Fecha",
                "Paciente", '%', "Pago");
        separacion('-', arch);
        // Imprimir datos de la lista de citas por médico
        imprimirCitas(arch, medicos, i);
    }
    fputc('\n', arch);
    // Imprimir lista de pacientes
    fprintf(arch, "%48s\n", "PACIENTES DE LA INSTITUCION");
    separacion('=', arch);
    fprintf(arch, "%-4s  %-6s  %-20s  %5c\n", "No.", "Codigo", "Nombre", '%');
    for (int i = 0; i < numPacientes; i++) {
        fprintf(arch, "%3d)  %6d  %-20s  %8.2lf\n", i+1, pacientes[i].codigo,
                pacientes[i].nombre, pacientes[i].porcentaje);
    }
    // Cierre del archivo
    fclose(arch);
}

void imprimirCitas(FILE *arch, struct Medico *medicos, int i) {
    int dia, mes, anho;
    double pago, totalPago = 0, totalSeguro = 0;
    // Imprimir lista de citas del médico
    for (int j = 0; j < medicos[i].numCitas; j++) {
        dia = medicos[i].citas[j].fecha % 100;
        mes = (medicos[i].citas[j].fecha / 100) % 100;
        anho = medicos[i].citas[j].fecha / 10000;
        pago = medicos[i].tarifa * medicos[i].citas[j].porcentaje / 100;
        // Imprimir los datos en el archivo
        fprintf(arch, "%3d)  %02d/%02d/%04d  %8d  %6.2lf  %8.2lf\n",
                j+1, dia, mes, anho, medicos[i].citas[j].codigo,
                medicos[i].citas[j].porcentaje, pago);
        // Calcular las estadísticas
        totalPago += pago;
        totalSeguro += (medicos[i].tarifa - pago);
    }
    // Imprimir resumen del médico
    separacion('-', arch);
    fprintf(arch, "Total a recibir: %27.2lf\n", totalPago);
    fprintf(arch, "Cantidad a solicitar al seguro: %12.2lf\n", totalSeguro);
}

void liberarEspacios(struct Medico *medicos, int numMedicos,
        struct Paciente *pacientes, int numPacientes) {
    // Liberar los espacios de los médicos
    for (int i = 0; i < numMedicos; i++) {
        free(medicos[i].codigo);
        free(medicos[i].nombre);
        free(medicos[i].especialidad);
    }
    // Liberar los espacios de los pacientes
    for (int i = 0; i < numPacientes; i++) {
        free(pacientes[i].nombre);
    }
}

/* Funciones auxiliares */

void separacion(char c, FILE *arch) {
    for (int i = 0; i < MAX_SEPARACION; i++) {
        fputc(c, arch);
    }
    fputc('\n', arch);
}
