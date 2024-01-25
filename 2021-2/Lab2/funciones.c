/* 
 * File:   main.c
 * Author: Anthony
 *
 * Created on 28 de septiembre de 2021, 07:12 AM
 */

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "funciones.h"

#define MAX_LINEA 100
#define MAX_NOMBRE 40

void procesarPacientes() {
    FILE *archPacientes = abrirArchivo("Pacientes.txt", "r");
    FILE *archReporte = abrirArchivo("ReporteDePagos.txt", "w");
    double totalPagos = 0;
    int codPaciente;
    // Imprimir cabecera del reporte
    fprintf(archReporte, "%63s\n", "EMPRESA PRESTADORA DE SALUD");
    fprintf(archReporte, "%67s\n", "LISTADOS DE PAGOS DE LOS PACIENTES");
    separacion(archReporte, '=', MAX_LINEA, 1);
    // Leer lista de pacientes
    while (1) {
        fscanf(archPacientes, "%d", &codPaciente);
        if (feof(archPacientes)) break;
        // Imprimir la cabecera del paciente
        procesarNombrePaciente(archReporte, archPacientes);
        fprintf(archReporte, "Codigo: %d\n", codPaciente);
        procesarDistritoPaciente(archReporte, archPacientes);
        separacion(archReporte, '-', MAX_LINEA, 1);
        // Imprimir las atenciones médicas
        procesarAtenciones(archReporte, codPaciente, &totalPagos);
        separacion(archReporte, '=', MAX_LINEA, 1);
    }
    // Imprimir resumen del reporte
    fprintf(archReporte, "TOTAL DE PAGOS DE LOS PACIENTES: S/ %10.2lf\n", totalPagos);
    separacion(archReporte, '=', MAX_LINEA, 1);
    // Cerrar los archivos
    fclose(archPacientes);
    fclose(archReporte);
}

void procesarNombrePaciente(FILE *archReporte, FILE *archPacientes) {
    int mayuscula = 1, tamNombre = 0;
    char car;
    // Ignorar los caracteres antes de abrir el corchete
    while (fgetc(archPacientes) != '[');
    // Colocar los caracteres hasta cerrar el corchete
    fprintf(archReporte, "%5cNombre:%5c", ' ', ' ');
    while (1) {
        car = fgetc(archPacientes);
        if (car == ']') break;
        // Convertir de mayúsculas a minúsculas según corresponda
        if (car == ' ') mayuscula = 1;
        else if (mayuscula /* == 1 */) mayuscula = 0;
        else car = tolower(car);
        // Colocar el caracter en el reporte
        fputc(car, archReporte);
        tamNombre++;
    }
    separacion(archReporte, ' ', MAX_NOMBRE - tamNombre, 0);
}

void procesarDistritoPaciente(FILE *archReporte, FILE *archPacientes) {
    char car;
    // Ignorar los espacios
    while (1) {
        car = fgetc(archPacientes);
        if (car != ' ') break;
    }
    // Colocar los caracteres hasta el fin de línea
    fprintf(archReporte, "%5cDistrito:%3c", ' ', ' ');
    while (1) {
        // Convertir a mayúsculas o guión bajo según corresponda
        if (car == ' ') car = '_';
        else car = toupper(car);
        // Colocar el caracter en el reporte
        fputc(car, archReporte);
        car = fgetc(archPacientes);
        if (car == '\n') break;
    }
    fputc('\n', archReporte);
}

void procesarAtenciones(FILE *archReporte, int codPaciente, double *totalPagos) {
    FILE *archAtenciones = abrirArchivo("AtencionesMedicas.txt", "r");
    double pagos = 0;
    int codMedico, codPacAtendido, dia, mes, anho, fecha, horaIni, horaFin;
    // Imprimir cabecera de las atenciones
    fprintf(archReporte, "%65s\n", "RELACION DE CONSULTAS REALIZADAS");
    fprintf(archReporte, "%13s%15s%12s%12s%9s%10s%15s\n", "FECHA", "INGRESO",
            "SALIDA", "DURACION", "MEDICO", "TARIFA", "MONTO PAGADO");
    separacion(archReporte, '-', MAX_LINEA, 1);
    // Leer lista de atenciones
    while (1) {
        fscanf(archAtenciones, "%d", &codMedico);
        if (feof(archAtenciones)) break;
        fscanf(archAtenciones, "%d/%d/%d", &dia, &mes, &anho);
        fecha = 10000*anho + 100*mes + dia;
        // Leer datos del paciente
        while (1) {
            fscanf(archAtenciones, "%d", &codPacAtendido);
            horaIni = leerHora(archAtenciones);
            horaFin = leerHora(archAtenciones);
            // Si los códigos coinciden, imprimir los datos de la atención
            if (codPaciente == codPacAtendido) {
                imprimirAtencion(archReporte, fecha, horaIni, horaFin, codMedico, &pagos);
            }
            if (fgetc(archAtenciones) == '\n') break;
        }
    }
    // Imprimir resumen de las atenciones
    separacion(archReporte, '-', MAX_LINEA, 1);
    fprintf(archReporte, "PAGO TOTAL REALIZADO: S/ %6.2lf\n", pagos);
    (*totalPagos) += pagos;
    fclose(archAtenciones);
}

int leerHora(FILE *archAtenciones) {
    int hora, min, seg;
    // Leer hora, minuto y segundo
    int cantLeidos = fscanf(archAtenciones, "%d:%d:%d", &hora, &min, &seg);
    if (cantLeidos < 3) seg = 0;
    if (cantLeidos < 2) min = 0;
    // Convertir todo a segundos
    return 3600*hora + 60*min + seg;
}

void imprimirAtencion(FILE *archReporte, int fecha, int horaIni, int horaFin,
        int codMedico, double *pagos) {
    int totalDur, minDur, segDur;
    double tarifa, monto;
    // Imprimir las fechas y horas
    imprimirFecha(archReporte, fecha);
    imprimirHora(archReporte, horaIni);
    imprimirHora(archReporte, horaFin);
    // Imprimir la duración
    totalDur = horaFin - horaIni;
    minDur = totalDur / 60;
    segDur = totalDur % 60;
    fprintf(archReporte, "%5c%02d:%02d", ' ', minDur, segDur);
    // Imprimir el código del médico
    fprintf(archReporte, "%5c%d", ' ', codMedico);
    // Buscar e imprimir la tarifa
    tarifa = buscarTarifaMedico(codMedico);
    fprintf(archReporte, "%5c%5.2lf", ' ', tarifa);
    // Calcular e imprimir el monto de pago
    monto = minDur * tarifa;
    if (segDur > 0) monto += tarifa;
    fprintf(archReporte, "%5c%7.2lf\n", ' ', monto);
    (*pagos) += monto;
}

void imprimirFecha(FILE *archReporte, int fecha) {
    int anho = fecha / 10000;
    fecha = fecha % 10000;
    int mes = fecha / 100;
    int dia = fecha % 100;
    fprintf(archReporte, "%5c%02d/%02d/%04d", ' ', dia, mes, anho);
}

void imprimirHora(FILE *archReporte, int horaTotal) {
    int hora = horaTotal / 3600;
    horaTotal = horaTotal % 3600;
    int min = horaTotal / 60;
    int seg = horaTotal % 60;
    fprintf(archReporte, "%5c%02d:%02d:%02d", ' ', hora, min, seg);
}

double buscarTarifaMedico(int codMedico) {
    FILE *archMedicos = abrirArchivo("Medicos.txt", "r");
    int codMedLeido;
    double tarifa = 0;
    // Leer la lista de médicos
    while (1) {
        fscanf(archMedicos, "%d", &codMedLeido);
        if (feof(archMedicos)) break;
        // Ignorar el nombre del médico
        while (fgetc(archMedicos) == ' ');
        while (fgetc(archMedicos) != ' ');
        // Obtener la tarifa del médico
        fscanf(archMedicos, "%lf", &tarifa);
        // Ignorar hasta el fin de línea
        while (fgetc(archMedicos) != '\n');
        // El bucle termina cuando encontramos al médico que queremos
        if (codMedico == codMedLeido) break;
    }
    fclose(archMedicos);
    return tarifa;
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

void separacion(FILE *arch, char car, int num, int cambioLinea) {
    for (int i = 0; i < num; i++) {
        fputc(car, arch);
    }
    if (cambioLinea) fputc('\n', arch);
}
