/*
 * Archivo: funciones.cpp
 * Autor:   Anthony Gutiérrez
 * Fecha:   25 de abril de 2023, 07:21 PM
 */

#include <iostream>
#include <iomanip>
#include <fstream>
#include "funciones.h"
using namespace std;

#define MAX_LINEA 90

void generarReporte(ifstream &archClientes, ifstream &archCartelera, ofstream &archRep) {
    int dist1, dist2, horaCli, durCli, dni, indice = 1, totalPeli;
    char alimCli;
    // Imprimir cabecera
    archRep << fixed << setprecision(2);
    archRep << setw(71) << "LISTADO DE PELICULAS A LAS QUE PODRIAN ASISTIR LOS SOLICITANTES" << endl;
    imprimirLinea(archRep, '=');
    // Leer línea por línea
    while (true) {
        archClientes >> dist1 >> dist2;
        if (archClientes.eof()) break;
        horaCli = leerHora(archClientes);
        durCli = leerHora(archClientes);
        archClientes >> alimCli >> dni >> ws;
        // Imprimir cabecera del cliente
        archRep << setw(2) << indice << ") " << dni << " - ";
        procesarNombre(archClientes, archRep);
        archRep << endl;
        // Procesar distritos
        totalPeli = procesarDistrito(archCartelera, archRep, dist1, alimCli, horaCli, durCli);
        imprimirLinea(archRep, '-');
        totalPeli += procesarDistrito(archCartelera, archRep, dist2, alimCli, horaCli, durCli);
        imprimirLinea(archRep, '=');
        // Imprimir resumen del cliente
        archRep << "Tiene " << totalPeli << " opciones de peliculas con los datos que ha ingresado" << endl;
        imprimirLinea(archRep, '=');
        indice++;
    }
}

int procesarDistrito(ifstream &archCartelera, ofstream &archRep,
        int distBuscado, char alimCli, int horaCli, int durCli) {
    int distLeido, cantPeli;
    // Rebobinar el archivo
    archCartelera.clear();
    archCartelera.seekg(0, ios::beg);
    // Leer línea por línea
    while (true) {
        archCartelera >> distLeido >> ws;
        if (archCartelera.eof()) break;
        if (distBuscado == distLeido) {
            // Imprimir cabecera del distrito
            archRep << setw(4) << ' ' << "DISTRITO: " << distBuscado << " - ";
            procesarNombre(archCartelera, archRep);
            archRep << endl;
            imprimirLinea(archRep, '-');
            archRep << left << setw(4) << ' ' << setw(6) << "SALA" << setw(45)
                    << "PELICULA" << setw(7) << "COSTO" << setw(10) << "INICIA"
                    << setw(10) << "TERMINA" << "DURACION" << endl;
            cantPeli = procesarPeliculas(archCartelera, archRep, alimCli,
                    horaCli, durCli);
            break; // No vale la pena seguir leyendo el archivo si ya encontramos al distrito
        } else {
            while (archCartelera.get() != '\n');
        }
    }
    // Imprimir resumen del distrito
    imprimirLinea(archRep, '-');
    if (cantPeli == 0) {
        archRep << setw(4) << ' ' << "NO HAY PELICULAS PARA ESAS CONDICIONES." << endl;
    } else {
        archRep << setw(4) << ' ' << "CANTIDAD DE PELICULAS: " << cantPeli << endl;
    }
    return cantPeli;
}

int procesarPeliculas(ifstream &archCartelera, ofstream &archRep,
        char alimCli, int horaCli, int durCli) {
    int sala, horaIniPeli, horaFinPeli, durPeli, cantPeli = 0, tamNombre;
    char alimPeli, car;
    double costo;
    // Leer películas línea por línea
    while (true) {
        archCartelera >> sala >> costo >> alimPeli;
        horaIniPeli = leerHora(archCartelera);
        horaFinPeli = leerHora(archCartelera);
        archCartelera >> ws;
        durPeli = horaFinPeli - horaIniPeli;
        if (horaIniPeli >= horaCli && durPeli <= durCli && !(alimCli == 'S' && alimPeli == 'N')) {
            archRep << left << setw(4) << ' ' << setw(6) << sala;
            procesarNombrePelicula(archCartelera, archRep, car, tamNombre);
            archRep << right << setw(45-tamNombre) << ' ' << setw(5) << costo << "  ";
            imprimirHora(archRep, horaIniPeli);
            archRep << "  ";
            imprimirHora(archRep, horaFinPeli);
            archRep << "  ";
            imprimirHora(archRep, durPeli);
            archRep << endl;
            cantPeli++;
        } else { // Ignorar el nombre
            car = ignorarNombrePelicula(archCartelera);
        }
        if (car == '\n') break;
    }
    return cantPeli;
}

void procesarNombrePelicula(ifstream &archEnt, ofstream &archRep, char &car,
        int &tamNombre) {
    tamNombre = 0;
    while (true) {
        car = archEnt.get();
        if (car == ' ' || car == '\n') break;
        if (car == '_') archRep.put(' ');
        else archRep.put(car);
        tamNombre++;
    }
}

char ignorarNombrePelicula(ifstream &arch) {
    char car;
    while (true) {
        car = arch.get();
        if (car == ' ' || car == '\n') return car;
    }
}

/* Funciones auxiliares */

void imprimirLinea(ofstream &archRep, char car) {
    for (int i = 0; i < MAX_LINEA; i++) archRep.put(car);
    archRep << endl;
}

int leerHora(ifstream &arch) {
    int hora, min, seg;
    char car;
    arch >> hora >> car >> min >> car >> seg;
    return 3600*hora + 60*min + seg;
}

void imprimirHora(ofstream &archRep, int horaTotal) {
    int hora = horaTotal/3600, min = (horaTotal%3600)/60, seg = horaTotal%60;
    archRep << right << setfill('0') << setw(2) << hora << ':' << setw(2)
            << min << ':' << setw(2) << seg << setfill(' ');
}

char procesarNombre(ifstream &archEnt, ofstream &archRep) {
    char car;
    while (true) {
        car = archEnt.get();
        if (car == ' ' || car == '\n') return car;
        if (car == '_') archRep.put(' ');
        else archRep.put(car);
    }
}
