/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * Archivo: funciones.cpp
 * Autor:   Anthony Gutiérrez
 * Fecha:   30 de junio de 2024, 08:37 PM
 */

#include <iostream>
#include <iomanip>
#include <fstream>
#include <cstdlib>
#include <cstring>
using namespace std;
#include "Cliente.h"
#include "Libro.h"
#include "funciones.h"

#define MAX_LINEA 135
#define NO_ENCONTRADO -1

void leerClientes(const char *nomArchTxt, const char *nomArchBin) {
    ifstream archTxt;
    ofstream archBin;
    abrirArchTxtEntrada(archTxt, nomArchTxt);
    abrirArchBinSalida(archBin, nomArchBin);
    struct Cliente cliente;
    while (true) {
        archTxt >> cliente.dni;
        if (archTxt.eof()) break;
        archTxt.get();
        archTxt.getline(cliente.nombre, MAX_NOM_CLIENTE);
        // Escribir en el archivo binario
        archBin.write(reinterpret_cast<const char *>(&cliente), sizeof(struct Cliente));
    }
}

void leerLibros(const char *nomArchTxt, const char *nomArchBin) {
    ifstream archTxt;
    ofstream archBin;
    abrirArchTxtEntrada(archTxt, nomArchTxt);
    abrirArchBinSalida(archBin, nomArchBin);
    struct Libro libro;
    while (true) {
        archTxt.getline(libro.codigo, MAX_COD_LIBRO, ',');
        if (archTxt.eof()) break;
        archTxt.getline(libro.titulo, MAX_TIT_LIBRO, ',');
        archTxt.getline(libro.autor, MAX_AUT_LIBRO, ',');
        archTxt >> libro.precio >> ws;
        libro.sumaDeCalificaciones = 0;
        libro.librosVendidos = 0;
        libro.fechaMasReciente.fecha = 0;
        libro.ranking = 0;
        // Escribir en el archivo binario
        archBin.write(reinterpret_cast<const char *>(&libro), sizeof(struct Libro));
    }
}

void leerVentas(const char *nomArchVen, const char *nomArchCli, const char *nomArchLib) {
    ifstream archVen, archCli;
    fstream archLib;
    abrirArchTxtEntrada(archVen, nomArchVen);
    abrirArchBinEntrada(archCli, nomArchCli);
    abrirArchBinEntradaSalida(archLib, nomArchLib);
    struct Libro libro;
    struct Cliente cliente;
    struct Venta venta;
    char codLibro[MAX_COD_LIBRO], car;
    int tamRegLib = sizeof(struct Libro), tamRegCli = sizeof(struct Cliente),
            numRegLib, numRegCli, posLibro, posCliente;
    numRegLib = obtenerNumReg(archLib, tamRegLib);
    numRegCli = obtenerNumReg(archCli, tamRegCli);
    while (true) {
        archVen.getline(codLibro, MAX_COD_LIBRO, ',');
        if (archVen.eof()) break;
        archVen >> venta.dni >> car >> venta.fecha.dd >> car >> venta.fecha.mm
                >> car >> venta.fecha.aa >> car >> venta.calificacion >> ws;
        venta.fecha.fecha = 10000 * venta.fecha.aa + 100*venta.fecha.mm + venta.fecha.dd;
        // Buscar posición del libro
        posLibro = buscarLibro(archLib, tamRegLib, numRegLib, codLibro);
        posCliente = buscarCliente(archCli, tamRegCli, numRegCli, venta.dni);
        if (posLibro != NO_ENCONTRADO && posCliente != NO_ENCONTRADO) {
            // Leer datos del archivo binario
            archLib.seekg(posLibro * tamRegLib, ios::beg);
            archLib.read(reinterpret_cast<char *>(&libro), tamRegLib);
            archCli.seekg(posCliente * tamRegCli, ios::beg);
            archCli.read(reinterpret_cast<char *>(&cliente), tamRegCli);
            // Actualizar libro
            strcpy(venta.nombre, cliente.nombre);
            libro.ventas[libro.librosVendidos] = venta;
            libro.sumaDeCalificaciones += venta.calificacion;
            libro.librosVendidos++;
            if (venta.fecha.fecha > libro.fechaMasReciente.fecha) {
                libro.fechaMasReciente = venta.fecha;
            }
            // Actualizar el archivo binario
            archLib.seekg(posLibro * tamRegLib, ios::beg);
            archLib.write(reinterpret_cast<const char *>(&libro), tamRegLib);
            archLib.flush();
        }
    }
}

int obtenerNumReg(istream &archBin, int tamReg) {
    int tamArch;
    archBin.seekg(0, ios::end);
    tamArch = archBin.tellg();
    archBin.seekg(0, ios::beg);
    return tamArch / tamReg;
}

int buscarLibro(fstream &archLib, int tamReg, int numReg, char *codigo) {
    struct Libro libro;
    archLib.seekg(0, ios::beg);
    for (int i = 0; i < numReg; i++) {
        archLib.read(reinterpret_cast<char *>(&libro), tamReg);
        if (strcmp(libro.codigo, codigo) == 0)
            return i;
    }
    return NO_ENCONTRADO;
}

int buscarCliente(ifstream &archCli, int tamReg, int numReg, int dni) {
    struct Cliente cliente;
    archCli.seekg(0, ios::beg);
    for (int i = 0; i < numReg; i++) {
        archCli.read(reinterpret_cast<char *>(&cliente), tamReg);
        if (cliente.dni == dni)
            return i;
    }
    return NO_ENCONTRADO;
}

void determinarRanking(const char *nomArchBin) {
    fstream archBin;
    abrirArchBinEntradaSalida(archBin, nomArchBin);
    struct Libro libro;
    int tamReg = sizeof(struct Libro), numReg, promedio;
    numReg = obtenerNumReg(archBin, tamReg);
    for (int i = 0; i < numReg; i++) {
        // Leer libro del archivo binario
        archBin.seekg(i * tamReg, ios::beg);
        archBin.read(reinterpret_cast<char *>(&libro), tamReg);
        // Calcular ranking del libro
        if (libro.librosVendidos > 0) {
            promedio = libro.sumaDeCalificaciones / libro.librosVendidos;
            libro.ranking = promedio / 25 + 1;
        } else {
            libro.ranking = 0;
        }
        // Actualizar el archivo binario
        archBin.seekg(i * tamReg, ios::beg);
        archBin.write(reinterpret_cast<const char *>(&libro), tamReg);
        archBin.flush();
    }
}

void ordenarLibros(const char *nomArchBin) {
    fstream archBin;
    abrirArchBinEntradaSalida(archBin, nomArchBin);
    struct Libro libroI, libroJ;
    int tamReg = sizeof(struct Libro), numReg = obtenerNumReg(archBin, tamReg);
    for (int i = 0; i < numReg-1; i++) {
        for (int j = i+1; j < numReg; j++) {
            // Leer libros del archivo binario
            archBin.seekg(i * tamReg, ios::beg);
            archBin.read(reinterpret_cast<char *>(&libroI), tamReg);
            archBin.seekg(j * tamReg, ios::beg);
            archBin.read(reinterpret_cast<char *>(&libroJ), tamReg);
            // Comparar e intercambiar cuando sea necesario
            if (libroI.ranking < libroJ.ranking || (libroI.ranking == libroJ.ranking
                    && libroI.fechaMasReciente.fecha > libroJ.fechaMasReciente.fecha)) {
                archBin.seekg(i * tamReg, ios::beg);
                archBin.write(reinterpret_cast<const char *>(&libroJ), tamReg);
                archBin.seekg(j * tamReg, ios::beg);
                archBin.write(reinterpret_cast<const char *>(&libroI), tamReg);
                archBin.flush();
            }
        }
    }
}

void generarReporte(const char *nomArchBin, const char *nomArchRep) {
    ifstream archBin;
    ofstream archRep;
    abrirArchBinEntrada(archBin, nomArchBin);
    abrirArchTxtSalida(archRep, nomArchRep);
    struct Libro libro;
    int tamReg = sizeof(struct Libro), numReg = obtenerNumReg(archBin, tamReg);
    // Imprimir cabecera
    archRep << fixed << setprecision(2);
    archRep << "LIBRERIA PUCP-TP" << endl;
    archRep << "RESULTADO DE LAS VENTAS REALIZADAS" << endl;
    for (int i = 0; i < numReg; i++) {
        imprimirLinea(archRep, '=');
        archRep << "LIBRO NO. " << setfill('0') << setw(3) << i+1 << setfill(' ') << endl;
        archRep << left << setw(MAX_COD_LIBRO) << "CODIGO" << setw(MAX_TIT_LIBRO) << "TITULO"
                << setw(MAX_AUT_LIBRO) << "AUTOR" << setw(9) << "PRECIO"
                << setw(18) << "LIBROS VENDIDOS" << "RANKINGS" << endl;
        archBin.seekg(i * tamReg, ios::beg);
        archBin.read(reinterpret_cast<char *>(&libro), tamReg);
        archRep << setw(MAX_COD_LIBRO) << libro.codigo << setw(MAX_TIT_LIBRO) << libro.titulo
                << setw(MAX_AUT_LIBRO) << libro.autor << right << setw(6) << libro.precio
                << setw(11) << libro.librosVendidos << setw(15) << libro.ranking << endl;
        imprimirLinea(archRep, '-');
        archRep << "VENTAS REALIZADAS:" << endl;
        if (libro.librosVendidos > 0) {
            archRep << left << setw(5) << "No." << setw(11) << "DNI"
                    << setw(MAX_NOM_CLIENTE) << "NOMBRE"
                    << setw(18) << "CALIFICACION" << "FECHA" << endl;
            for (int j = 0; j < libro.librosVendidos; j++) {
                archRep << right << setfill('0') << setw(2) << (j+1) << setfill(' ')
                        << setw(11) << libro.ventas[j].dni << setw(3) << ' '
                        << left << setw(MAX_NOM_CLIENTE) << libro.ventas[j].nombre
                        << right << setw(7) << libro.ventas[j].calificacion << setw(8) << ' ';
                imprimirFecha(archRep, libro.ventas[j].fecha);
                archRep << endl;
            }
            imprimirLinea(archRep, '-');
            archRep << "FECHA MAS RECIENTE DE COMPRA: ";
            imprimirFecha(archRep, libro.fechaMasReciente);
            archRep << endl;
        } else {
            archRep << "NO SE VENDIO ESTE LIBRO" << endl;
        }
    }
}

void imprimirFecha(ofstream &archRep, struct Fecha &fecha) {
    archRep << setfill('0') << setw(2) << fecha.dd << '/' << setw(2)
            << fecha.mm << '/' << setw(4) << fecha.aa << setfill(' ');
}

/* Funciones auxiliares */

void abrirArchTxtEntrada(ifstream &archTxt, const char *nomArchTxt) {
    archTxt.open(nomArchTxt, ios::in);
    if (!archTxt) {
        cerr << "No se pudo encontrar el archivo " << nomArchTxt << endl;
        exit(1);
    }
}

void abrirArchTxtSalida(ofstream &archTxt, const char *nomArchTxt) {
    archTxt.open(nomArchTxt, ios::out);
    if (!archTxt) {
        cerr << "No se pudo encontrar el archivo " << nomArchTxt << endl;
        exit(1);
    }
}

void abrirArchBinEntrada(ifstream &archBin, const char *nomArchBin) {
    archBin.open(nomArchBin, ios::in | ios::binary);
    if (!archBin) {
        cerr << "No se pudo encontrar el archivo " << nomArchBin << endl;
        exit(1);
    }
}

void abrirArchBinEntradaSalida(fstream &archBin, const char *nomArchBin) {
    archBin.open(nomArchBin, ios::in | ios::out | ios::binary);
    if (!archBin) {
        cerr << "No se pudo encontrar el archivo " << nomArchBin << endl;
        exit(1);
    }
}

void abrirArchBinSalida(ofstream &archBin, const char *nomArchBin) {
    archBin.open(nomArchBin, ios::out | ios::binary);
    if (!archBin) {
        cerr << "No se pudo encontrar el archivo " << nomArchBin << endl;
        exit(1);
    }
}

void imprimirLinea(ofstream &archRep, char car) {
    for (int i = 0; i < MAX_LINEA; i++)
        archRep.put(car);
    archRep << endl;
}
