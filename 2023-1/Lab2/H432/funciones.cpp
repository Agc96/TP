/*
 * Archivo: funciones.cpp
 * Autor:   Anthony Gutiérrez
 * Fecha:   11 de abril de 2023, 09:38 PM
 */

#include <iostream>
#include <iomanip>
#include "funciones.h"
using namespace std;

void procesarCabecera(int &fechaLimDoc, int &fechaLimEst) {
    // Leer cabecera
    fechaLimDoc = leerFecha();
    fechaLimEst = leerFecha();
    // Imprimir cabecera
    cout << fixed << setprecision(2);
    cout << setw(58) << "BIBLIOTECA GENERAL DE LA UNIVERSIDAD" << endl;
    imprimirLinea('=');
    cout << setw(4) << ' ' << "Fechas limite de devolucion:" << endl;
    cout << left << setw(10) << ' ' << setw(20) << "Docentes: ";
    imprimirFecha(fechaLimDoc);
    cout << endl;
    cout << left << setw(10) << ' ' << setw(20) << "Estudiantes: ";
    imprimirFecha(fechaLimEst);
    cout << endl;
    imprimirLinea('-');
    cout << setw(62) << "RELACION DE USUARIOS RETRASADOS EN SU ENTREGA" << endl;
    imprimirLinea('=');
}

void procesarUsuarios(int fechaLimDoc, int fechaLimEst, int &codDocDeuda,
        double &multaDocDeuda, int &codEstDeuda, double &multaEstDeuda) {
    int codUsuario, codLibro, cantLibros, fecha;
    char tipo, reincidente;
    double monto, total;
    while (true) {
        cin >> codUsuario >> tipo >> reincidente;
        if (cin.eof()) break;
        cantLibros = 0;
        total = 0;
        imprimirCabeceraUsuario(codUsuario, tipo, reincidente);
        while (true) {
            cin >> codLibro;
            fecha = leerFecha();
            cin >> monto;
            if ((tipo == 'E' && fecha < fechaLimEst) ||
                    (tipo == 'D' && fecha < fechaLimDoc)) {
                procesarLibro(tipo, reincidente, codLibro, fecha, monto,
                        cantLibros, total);
            }
            if (cin.get() == '\n') break;
        }
        imprimirResumenUsuario(cantLibros, total);
        if (tipo == 'E' && reincidente == 'R' && total > multaEstDeuda) {
            codEstDeuda = codUsuario;
            multaEstDeuda = total;
        }
        if (tipo == 'D' && reincidente == 'R' && total > multaDocDeuda) {
            codDocDeuda = codUsuario;
            multaDocDeuda = total;
        }
    }
}

void imprimirCabeceraUsuario(int codigo, char tipo, char reincidente) {
    cout << left << setw(10) << "Carne No.:" << setw(10) << codigo
            << setw(10) << "Tipo:";
    if (tipo == 'E')
        cout << "Estudiante";
    else
        cout << "Docente";
    if (reincidente == 'R')
        cout << " - Reincidente";
    cout << endl;
    imprimirLinea('-');
    cout << "Libros en su poder, retrasados en su entrega:" << endl;
    cout << right << setw(10) << "Codigo" << setw(20) << "F. de retiro"
            << setw(20) << "Multa" << endl;
}

void procesarLibro(char tipo, char reincidente, int codLibro, int fecha,
        double monto, int &cantLibros, double &total) {
    double multa;
    // Calcular la multa
    if (tipo == 'E') {
        if (reincidente == 'R')
            multa = 0.03*monto; // 1% + 2%
        else
            multa = 0.01*monto;
    } else {
        if (reincidente == 'R')
            multa = 0.0725*monto; // 2.25% + 5%
        else
            multa = 0.0225*monto;
    }
    // Imprimir datos del libro
    cout << setw(5) << ' ' << setfill('0') << setw(5) << codLibro
            << setfill(' ') << setw(10) << ' ';
    imprimirFecha(fecha);
    cout << setw(20) << multa << endl;
    // Actualizar contadores
    cantLibros++;
    total += multa;
}

void imprimirResumenUsuario(int cant, double total) {
    imprimirLinea('=');
    cout << left << setw(30) << "Cantidad de libros adeudados: "
            << right << setw(5) << cant << endl;
    cout << left << setw(30) << "Total de deudas por multa: "
            << right << setw(5) << total << endl;
    imprimirLinea('=');
}

void imprimirResumen(int codDocDeuda, double multaDocDeuda, int codEstDeuda,
        double multaEstDeuda) {
    cout << "Resumen:" << endl;
    cout << setw(4) << ' ' << "Reincidente con mayor deuda:" << endl;
    cout << left << setw(8) << ' ' << setw(12) << "Docente: "
            << setw(15) << codDocDeuda << right << "Deuda: S/ "
            << setw(10) << multaDocDeuda << endl;
    cout << left << setw(8) << ' ' << setw(12) << "Estudiante: "
            << setw(15) << codEstDeuda << right << "Deuda: S/ "
            << setw(10) << multaEstDeuda << endl;
}

/* Funciones auxiliares */

int leerFecha() {
    int dd, mm, aaaa;
    char c;
    cin >> dd >> c >> mm >> c >> aaaa;
    return 10000*aaaa + 100*mm + dd;
}

void imprimirFecha(int fecha) {
    int dd = fecha % 100, mm = (fecha/100) % 100, aaaa = fecha / 10000;
    cout << right << setfill('0');
    cout << setw(2) << dd << '/' << setw(2) << mm << '/' << aaaa;
    cout << setfill(' ');
}

void imprimirLinea(char c) {
    for (int i = 0; i < 80; i++) cout.put(c);
    cout << endl;
}
