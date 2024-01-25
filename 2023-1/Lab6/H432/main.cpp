/*
 * Archivo: main.cpp
 * Autor:   Anthony Gutiérrez
 * Fecha:   19 de junio de 2023, 11:59 AM
 */

#include <iostream>
#include <cstdlib>
#include "Libro.h"
#include "Usuario.h"
#include "Solicitud.h"
#include "Funciones.h"
using namespace std;

#define MAX_LIBROS 40
#define MAX_USUARIOS 60
#define MAX_SOLICITUDES 300

int main() {
    Libro libros[MAX_LIBROS];
    Usuario usuarios[MAX_USUARIOS];
    Solicitud solicitudes[MAX_SOLICITUDES];
    int cantLibros, cantUsuarios, cantSolicitudes;
    leerDatos(libros, cantLibros, usuarios, cantUsuarios, solicitudes,
            cantSolicitudes);
    imprimirReporte(libros, cantLibros, usuarios, cantUsuarios, solicitudes,
            cantSolicitudes, "ReporteInicial.txt");
    ordenarUsuarios(usuarios, cantUsuarios);
    atenderSolicitudes(libros, cantLibros, usuarios, cantUsuarios, solicitudes,
            cantSolicitudes);
    imprimirReporte(libros, cantLibros, usuarios, cantUsuarios, solicitudes,
            cantSolicitudes, "ReporteFinal.txt");
    return 0;
}
