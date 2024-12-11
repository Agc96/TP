/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * Archivo: funciones.cpp
 * Autor:   Anthony Gutiérrez
 * Fecha:   28 de abril de 2024, 04:51 PM
 */

#include <iostream>
#include <iomanip>
#include <fstream>
#include <cstdlib>
#include <cstring>
using namespace std;
#include "funciones.h"

#define MAX_LINEA 144
#define MAX_NOMBRE 38
#define MAX_ESPEC 20

void imprimirCabecera(ofstream &archRep) {
    archRep << fixed << setprecision(2);
    archRep << setw(83) << "EMPRESA DE SALUD S. A." << endl;
    imprimirLinea(archRep, '=');
    archRep << setw(85) << "REGISTRO DE CITAS MEDICAS" << endl;
    imprimirLinea(archRep, '=');
    archRep << setw(8) << "Fecha" << setw(12) << "Paciente"
            << setw(9) << "Inicio" << setw(8) << "Fin"
            << setw(13) << "Duracion" << setw(14) << "% por Seguro"
            << setw(8) << "Medico"  << setw(44) << "Especialidad"
            << setw(28) << "Pago (cita+medicinas)" << endl;
    imprimirLinea(archRep, '-');
}

void procesarCitas(ifstream &archCitas, ofstream &archReporte, double &total,
        int &dniMayor, double &montoMayor) {
    int fecha, horaIni, horaFin, dniPac, codMed;
    double desc, montoMed, montoTotal;
    char tieneMed;
    while (true) {
        fecha = leerFecha(archCitas);
        if (archCitas.eof()) break;
        archCitas >> dniPac >> desc;
        horaIni = leerHora(archCitas);
        horaFin = leerHora(archCitas);
        archCitas >> codMed >> tieneMed;
        if (tieneMed == 'S') archCitas >> montoMed;
        else montoMed = 0;
        montoTotal = imprimirCita(archReporte, fecha, dniPac, horaIni, horaFin,
                desc, codMed, montoMed);
        total += montoTotal;
        if (montoTotal > montoMayor) {
            montoMayor = montoTotal;
            dniMayor = dniPac;
        }
    }
}

int leerFecha(ifstream &archCitas) {
    int dia, mes, anio;
    archCitas >> dia;
    archCitas.get();
    archCitas >> mes;
    archCitas.get();
    archCitas >> anio;
    return 10000*anio + 100*mes + dia;
}

int leerHora(ifstream &archCitas) {
    int hora, min, seg;
    archCitas >> hora;
    archCitas.get();
    archCitas >> min;
    archCitas.get();
    archCitas >> seg;
    return 3600*hora + 60*min + seg;
}

double imprimirCita(ofstream &archReporte, int fecha, int dniPac, int horaIni,
        int horaFin, double desc, int codMed, double montoMed) {
    int duracion = horaFin - horaIni;
    double tarifa, montoConsulta, monto;
    imprimirFecha(archReporte, fecha);
    archReporte << setw(10) << dniPac;
    imprimirHora(archReporte, horaIni);
    imprimirHora(archReporte, horaFin);
    imprimirHora(archReporte, duracion);
    archReporte << setw(10) << desc << '%' << setw(5) << ' ';
    tarifa = procesarMedico(archReporte, codMed);
    montoConsulta = tarifa*duracion/3600;
    monto = montoConsulta*(1-desc/100) + montoMed*(1-desc/200);
    archReporte << setw(12) << monto << endl;
    return monto;
}

void imprimirFecha(ofstream &archRep, int fecha) {
    int dia = fecha % 100,
        mes = (fecha / 100) % 100,
        anio = fecha / 10000;
    archRep << right << setfill('0') << setw(2) << dia << '/' << setw(2)
            << mes << '/' << setw(4) << anio << setfill(' ');
}

void imprimirHora(ofstream &archRep, int horaTotal) {
    int hora = horaTotal / 3600,
        min = (horaTotal / 60) % 60,
        seg = horaTotal % 60;
    archRep << setw(2) << ' ' << setfill('0') << setw(2) << hora << ':'
            << setw(2) << min << ':' << setw(2) << seg << setfill(' ');
}

double procesarMedico(ofstream &archReporte, int codMedBuscado) {
    ifstream archMedicos;
    abrirArchivoEntrada(archMedicos, "Medicos.txt");
    int codMed;
    double tarifa = 0.0;
    while (true) {
        archMedicos >> codMed;
        if (archMedicos.eof()) break;
        if (codMed == codMedBuscado) {
            procesarNombre(archMedicos, archReporte);
            procesarEspecialidad(archMedicos, archReporte);
            archMedicos >> tarifa;
            break;
        } else
            while (archMedicos.get() != '\n');
    }
    return tarifa;
}

void procesarNombre(ifstream &archMedicos, ofstream &archReporte) {
    int tamNombre = 0;
    char car;
    bool mayus = true;
    archMedicos >> ws;
    while (true) {
        car = archMedicos.get();
        if (car == ' ') break;
        if (car == '_') {
            car = ' ';
            mayus = true;
        } else if (mayus) {
            mayus = false;
        } else {
            car += 'a' - 'A';
        }
        archReporte.put(car);
        tamNombre++;
    }
    for (int i = tamNombre; i < MAX_NOMBRE; i++) archReporte.put(' ');
}

void procesarEspecialidad(ifstream &archMedicos, ofstream &archReporte) {
    int tamEspec = 0;
    char car;
    archMedicos >> ws;
    while (true) {
        car = archMedicos.get();
        if (car == ' ') break;
        if (car == '_') car = ' ';
        if (car >= 'a' && car <= 'z') car += 'A' - 'a';
        archReporte.put(car);
        tamEspec++;
    }
    for (int i = tamEspec; i < MAX_ESPEC; i++) archReporte.put(' ');
}

void imprimirResumen(ofstream &arch, double total, int dniMayor,
        double montoMayor) {
    imprimirLinea(arch, '=');
    arch << "Total de ingresos: " << total << endl;
    imprimirLinea(arch, '=');
    arch << "Paciente que mas gasto en una cita medica: " << dniMayor << endl;
    arch << "Monto gastado: " << setw(36) << montoMayor << endl;
    imprimirLinea(arch, '=');
}

void abrirArchivoEntrada(ifstream &arch, const char *nomArch) {
    arch.open(nomArch, ios::in);
    if (!arch) {
        cerr << "No se pudo abrir el archivo " << nomArch << endl;
        exit(1);
    }
}
void abrirArchivoSalida(ofstream &arch, const char *nomArch) {
    arch.open(nomArch, ios::out);
    if (!arch) {
        cerr << "No se pudo crear el archivo " << nomArch << endl;
        exit(1);
    }
}

void imprimirLinea(ofstream &arch, char car) {
    for (int i = 0; i < MAX_LINEA; i++) arch.put(car);
    arch << endl;
}
