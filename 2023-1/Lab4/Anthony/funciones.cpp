/*
 * Archivo: funciones.cpp
 * Autor:   Anthony Gutiérrez
 * Fecha:   9 de mayo de 2023, 07:57 PM
 */

#include <iostream>
#include <iomanip>
#include <fstream>
#include <cstdlib>
#include <cstring>
#include "funciones.h"
using namespace std;

#define MAX_LINEA 80
#define NO_ENCONTRADO -1

void leerLibros(int *arrCodLib, double *arrPrecLib, int &cantLib) {
    ifstream arch("Libros.txt", ios::in);
    if (!arch) {
        cerr << "No se pudo abrir el archivo Libros.txt" << endl;
        exit(1);
    }
    cantLib = 0;
    while (true) {
        arch >> arrCodLib[cantLib];
        if (arch.eof()) break;
        arch >> ws;
        while (arch.get() != ' ');
        arch >> arrPrecLib[cantLib];
        cantLib++;
    }
}

void leerAutores(int *arrCodAut, int *arrLibAut, double *arrPorcAut,
        int &cantAut) {
    ifstream arch("Autores.txt", ios::in);
    if (!arch) {
        cerr << "No se pudo abrir el archivo Autores.txt" << endl;
        exit(1);
    }
    cantAut = 0;
    while (true) {
        arch >> arrCodAut[cantAut];
        if (arch.eof()) break;
        arch >> arrLibAut[cantAut];
        arch >> arrPorcAut[cantAut];
        cantAut++;
    }
}

void leerFechas(int &fechaIni, int &fechaFin) {
    while (true) {
        cout << "Ingrese la fecha inicial en el formato dd/mm/aaaa:" << endl;
        fechaIni = leerFecha(cin);
        cout << "Ingrese la fecha final en el formato dd/mm/aaaa:" << endl;
        fechaFin = leerFecha(cin);
        if (fechaIni < fechaFin) break;
        cout << "Las fechas ingresadas no son correctas, por favor vuelva a intentarlo." << endl;
    }
}

int leerFecha(istream &arch) {
    int dia, mes, anio;
    char car;
    arch >> dia >> car >> mes >> car >> anio;
    return 10000*anio + 100*mes + dia;
}

void procesarVentas(int *arrCodLib, double *arrPrecLib, int *arrCantLib,
        double *arrMontoLib, int cantLib, int *arrCodAut, int *arrLibAut,
        double *arrPorcAut, double *arrMontoAut, int cantAut, int fechaIni,
        int fechaFin) {
    ifstream arch("Ventas.txt", ios::in);
    if (!arch) {
        cerr << "No se pudo abrir el archivo Ventas.txt" << endl;
        exit(1);
    }
    int fecha, codLib, cantVend, posLib;
    // Leer línea por línea
    while (true) {
        fecha = leerFecha(arch);
        if (arch.eof()) break;
        if (fecha >= fechaIni && fecha <= fechaFin) {
            // Leer libros vendidos
            while (true) {
                arch >> codLib >> cantVend;
                // Actualizar montos del libro
                posLib = buscarLibro(arrCodLib, codLib, cantLib);
                if (posLib != NO_ENCONTRADO) {
                    arrCantLib[posLib] += cantVend;
                    arrMontoLib[posLib] += cantVend * arrPrecLib[posLib];
                    // Actualizar montos de los autores
                    for (int i = 0; i < cantAut; i++) {
                        if (arrLibAut[i] != codLib) continue;
                        arrMontoAut[i] = arrPorcAut[i] * arrMontoLib[posLib] / 100;
                    }
                }
                // Verificar si salimos del bucle
                if (arch.get() == '\n') break;
            }
        } else {
            while (arch.get() != '\n');
        }
    }
}

int buscarLibro(int *arrCodLib, int codLib, int cantLib) {
    for (int i = 0; i < cantLib; i++)
        if (arrCodLib[i] == codLib) return i;
    return NO_ENCONTRADO;
}

void imprimirReporte(int *arrCodLib, double *arrPrecLib, int *arrCantLib,
        double *arrMontoLib, int cantLib, int *arrCodAut, int *arrLibAut,
        double *arrPorcAut, double *arrMontoAut, int cantAut, int fechaIni,
        int fechaFin) {
    ofstream arch("Reporte.txt", ios::out);
    if (!arch) {
        cerr << "No se pudo abrir el archivo Reporte.txt" << endl;
        exit(1);
    }
    arch << fixed << setprecision(2);
    // Imprimir cabecera
    arch << "LIBRERIA LOS LIBROS TP" << endl;
    arch << "VENTA DE LIBROS EN EL RANGO ";
    imprimirFecha(arch, fechaIni);
    arch << " AL ";
    imprimirFecha(arch, fechaFin);
    arch << endl;
    // Imprimir libros
    for (int i = 0; i < cantLib; i++) {
        imprimirLinea(arch, '=');
        arch << setfill('0') << setw(2) << (i+1) << ") " << setfill(' ')
                << left << setw(12) << "LIBRO" << setw(12) << "CANTIDAD"
                << setw(10) << "PRECIO" << "MONTO RECAUDADO" << endl;
        arch << setw(4) << ' ' << setw(12) << arrCodLib[i] << right << setw(8)
                << arrCantLib[i] << setw(10) << arrPrecLib[i] << setw(19)
                << arrMontoLib[i] << endl << endl;
        arch << left << setw(4) << ' ' << "REGALIAS PARA LOS AUTORES" << endl;
        arch << setw(4) << ' ' << setw(10) << "AUTOR" << setw(24)
                << "PORCENTAJE A RECIBIR" << "MONTO A RECIBIR" << endl;
        for (int j = 0; j < cantAut; j++) {
            if (arrCodLib[i] != arrLibAut[j]) continue;
            arch << left << setw(4) << ' ' << setw(10) << arrCodAut[j] << right
                    << setw(19) << arrPorcAut[j] << '%' << setw(19)
                    << arrMontoAut[j] << endl;
        }
    }
}

void imprimirFecha(ofstream &arch, int fecha) {
    int anio = fecha/10000, mes = (fecha/100)%100, dia = fecha%100;
    arch << setfill('0') << setw(2) << dia << '/' << setw(2) << mes << '/'
            << setw(4) << anio << setfill(' ');
}

void imprimirLinea(ofstream &arch, char car) {
    for (int i = 0; i < MAX_LINEA; i++) arch.put(car);
    arch << endl;
}
