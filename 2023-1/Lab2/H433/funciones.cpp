/*
 * Archivo: funciones.cpp
 * Autor:   Anthony Gutiérrez
 * Fecha:   11 de abril de 2023, 05:33 PM
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
    cout << setw(59) << "RELACION DE USUARIO Y LIBROS PRESTADOS" << endl;
    imprimirLinea('=');
}

void procesarUsuarios(int fechaLimDoc, int fechaLimEst, int &codDocDeuda,
        double &multaDocDeuda, int &codEstDeuda, double &multaEstDeuda,
        int &codDocLibros, int &cantDocLibros, int &codEstLibros,
        int &cantEstLibros) {
    int codUsuario, codLibro, cantLibros, fecha;
    char tipo;
    double monto, total;
    while (true) {
        cin >> codUsuario >> tipo;
        if (cin.eof()) break;
        imprimirCabeceraUsuario(codUsuario, tipo);
        cantLibros = 0;
        total = 0;
        while (true) {
            cin >> codLibro;
            fecha = leerFecha();
            cin >> monto;
            procesarLibro(fechaLimDoc, fechaLimEst, tipo, codLibro, fecha,
                    monto, cantLibros, total);
            if (cin.get() == '\n') break;
        }
        if (tipo == 'E') {
            if (total > multaEstDeuda) {
                codEstDeuda = codUsuario;
                multaEstDeuda = total;
            }
            if (cantLibros > cantEstLibros) {
                codEstLibros = codUsuario;
                cantEstLibros = cantLibros;
            }
        } else {
            if (total > multaDocDeuda) {
                codDocDeuda = codUsuario;
                multaDocDeuda = total;
            }
            if (cantLibros > cantDocLibros) {
                codDocLibros = codUsuario;
                cantDocLibros = cantLibros;
            }
        }
        imprimirResumenUsuario(cantLibros, total);
    }
}

void imprimirCabeceraUsuario(int codigo, char tipo) {
    cout << left << setw(10) << "Carne No.:" << setw(10) << codigo
            << setw(10) << "Tipo:";
    if (tipo == 'E') cout << "Estudiante" << endl;
    else cout << "Docente" << endl;
    imprimirLinea('-');
    cout << "Libros en su poder:" << endl;
    cout << right << setw(10) << "Codigo" << setw(20) << "F. de retiro"
            << setw(20) << "Observacion" << endl;
}

void procesarLibro(int fechaLimDoc, int fechaLimEst, char tipo, int codLibro,
        int fecha, double monto, int &cantLibros, double &total) {
    double multa;
    cout << setw(5) << ' ' << setfill('0') << setw(5) << codLibro
            << setfill(' ') << setw(10) << ' ';
    imprimirFecha(fecha);
    if (tipo == 'E') {
        if (fecha < fechaLimEst) {
            cantLibros++;
            multa = 0.01*monto;
            total += multa;
            cout << setw(17) << "EN DEUDA" << setw(20) << "Multa: "
                    << right << setw(5) << multa << endl;
        } else {
            cout << setw(12) << "---" << endl;
        }
    } else {
        if (fecha < fechaLimDoc) {
            cantLibros++;
            multa = 0.0225*monto;
            total += multa;
            cout << setw(17) << "EN DEUDA" << setw(20) << "Multa: "
                    << right << setw(5) << multa << endl;
        } else {
            cout << setw(12) << "---" << endl;
        }
    }
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
        double multaEstDeuda, int codDocLibros, int cantDocLibros,
        int codEstLibros, int cantEstLibros) {
    cout << "Resumen:" << endl;
    cout << setw(4) << ' ' << "Con mayor deuda:" << endl;
    cout << left << setw(8) << ' ' << setw(12) << "Docente: "
            << setw(15) << codDocDeuda << right << "Deuda: S/ "
            << setw(10) << multaDocDeuda << endl;
    cout << left << setw(8) << ' ' << setw(12) << "Estudiante: "
            << setw(15) << codEstDeuda << right << "Deuda: S/ "
            << setw(10) << multaEstDeuda << endl;
    cout << setw(4) << ' ' << "Con mayor cantidad de libros:" << endl;
    cout << left << setw(8) << ' ' << setw(12) << "Docente: "
            << setw(15) << codDocLibros << right << "Cantidad: "
            << setw(3) << cantDocLibros << " libros" << endl;
    cout << left << setw(8) << ' ' << setw(12) << "Estudiante: "
            << setw(15) << codEstLibros << right << "Cantidad: "
            << setw(3) << cantEstLibros << " libros" << endl;
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
