/*
 * Archivo: Funciones.cpp
 * Autor:   Anthony Gutiérrez
 * Fecha:   19 de junio de 2023, 12:09 PM
 */

#include <iostream>
#include <iomanip>
#include <fstream>
#include <cstring>
#include "Libro.h"
#include "Usuario.h"
#include "Solicitud.h"
#include "Funciones.h"
using namespace std;

#define MAX_LINEA 120
#define MAX_PRESTAMOS_ALUMNO 4
#define MAX_PRESTAMOS_DOCENTE 6
#define MAX_PRESTAMOS_VISITANTE 2
#define DESCUENTO 10
#define NO_ENCONTRADO -1

void leerDatos(Libro *libros, int &cantLibros, Usuario *usuarios,
        int &cantUsuarios, Solicitud *solicitudes, int &cantSolicitudes) {
    leerLibros(libros, cantLibros);
    leerUsuarios(usuarios, cantUsuarios);
    leerSolicitudes(solicitudes, cantSolicitudes);
}

void leerLibros(Libro *libros, int &cantLibros) {
    ifstream arch;
    abrirArchivoEntrada(arch, "Libros.csv");
    cantLibros = 0;
    // Leer el archivo línea por línea
    while (true) {
        arch.getline(libros[cantLibros].codigo, MAX_CODIGO_LIBRO, ',');
        if (arch.eof()) break;
        arch.getline(libros[cantLibros].titulo, MAX_TITULO_LIBRO, ',');
        arch.getline(libros[cantLibros].autor, MAX_AUTOR_LIBRO, ',');
        arch >> libros[cantLibros].cantVolumenes;
        arch.get();
        arch >> libros[cantLibros].precio >> ws;
        libros[cantLibros].cantPrestados = 0;
        cantLibros++;
    }
}

void leerUsuarios(Usuario *usuarios, int &cantUsuarios) {
    ifstream arch;
    abrirArchivoEntrada(arch, "Usuarios.csv");
    cantUsuarios = 0;
    // Leer el archivo línea por línea
    while (true) {
        arch >> usuarios[cantUsuarios].dni;
        if (arch.eof()) break;
        arch.get();
        arch.getline(usuarios[cantUsuarios].nombre, MAX_NOMBRE_USUARIO, ',');
        usuarios[cantUsuarios].categoria = arch.get();
        arch.get();
        arch >> usuarios[cantUsuarios].calificacion;
        usuarios[cantUsuarios].cantPrestados = 0;
        usuarios[cantUsuarios].cantNoPrestados = 0;
        cantUsuarios++;
    }
}

void leerSolicitudes(Solicitud *solicitudes, int &cantSolicitudes) {
    ifstream arch;
    abrirArchivoEntrada(arch, "SolicitudesDePrestamo.txt");
    cantSolicitudes = 0;
    // Leer el archivo línea por línea
    while (true) {
        arch >> solicitudes[cantSolicitudes].dniUsuario;
        if (arch.eof()) break;
        arch >> ws;
        arch.getline(solicitudes[cantSolicitudes].codLibro, MAX_CODIGO_LIBRO);
        cantSolicitudes++;
    }
}

void imprimirReporte(Libro *libros, int cantLibros, Usuario *usuarios,
        int cantUsuarios, Solicitud *solicitudes, int cantSolicitudes,
        const char *nomArch) {
    ofstream arch;
    abrirArchivoSalida(arch, nomArch);
    arch << fixed << setprecision(2);
    imprimirLibros(arch, libros, cantLibros);
    arch << endl;
    imprimirUsuarios(arch, usuarios, cantUsuarios);
    arch << endl;
    imprimirSolicitudes(arch, solicitudes, cantSolicitudes);
}

void imprimirLibros(ofstream &arch, Libro *libros, int cantLibros) {
    // Imprimir cabecera
    arch << right << setw(68) << "LISTA DE LIBROS" << endl;
    imprimirLinea(arch, '=');
    arch << left << setw(MAX_CODIGO_LIBRO) << "Codigo"
            << setw(MAX_TITULO_LIBRO) << "Titulo"
            << setw(MAX_AUTOR_LIBRO) << "Autor"
            << setw(18) << "Cant. Volumenes"
            << setw(9) << "Precio" << "Cant. Prestados" << endl;
    // Imprimir listado de libros
    for (int i = 0; i < cantLibros; i++) {
        arch << left << setw(MAX_CODIGO_LIBRO) << libros[i].codigo
                << setw(MAX_TITULO_LIBRO) << libros[i].titulo
                << setw(MAX_AUTOR_LIBRO) << libros[i].autor
                << right << setw(9) << libros[i].cantVolumenes
                << setw(15) << libros[i].precio
                << setw(11) << libros[i].cantPrestados << endl;
    }
}

void imprimirUsuarios(ofstream &arch, Usuario *usuarios, int cantUsuarios) {
    // Imprimir cabecera
    arch << right << setw(69) << "LISTA DE USUARIOS" << endl;
    imprimirLinea(arch, '=');
    arch << left << setw(11) << "DNI" << setw(MAX_NOMBRE_USUARIO) << "Nombre"
            << setw(12) << "Categoria" << setw(15) << "Calificacion"
            << setw(18) << "Cant. Prestados" << "Cant. No Prestados" << endl;
    // Imprimir listado de usuarios
    for (int i = 0; i < cantUsuarios; i++) {
        arch << left << setw(11) << usuarios[i].dni
                << setw(MAX_NOMBRE_USUARIO) << usuarios[i].nombre
                << right << setw(6) << usuarios[i].categoria
                << setw(15) << usuarios[i].calificacion
                << setw(15) << usuarios[i].cantPrestados
                << setw(18) << usuarios[i].cantNoPrestados << endl;
    }
}

void imprimirSolicitudes(ofstream &arch, Solicitud *solicitudes,
        int cantSolicitudes) {
    // Imprimir cabecera
    arch << right << setw(70) << "LISTA DE SOLICITUDES" << endl;
    imprimirLinea(arch, '=');
    arch << left << setw(10) << "DNI" << "Cod. Libro" << endl;
    // Imprimir listado de usuarios
    for (int i = 0; i < cantSolicitudes; i++) {
        arch << left << setw(10) << solicitudes[i].dniUsuario
                << right << setw(10) << solicitudes[i].codLibro << endl;
    }
}

void ordenarUsuarios(Usuario *usuarios, int cantUsuarios) {
    Usuario aux;
    for (int i = 0; i < cantUsuarios - 1; i++) {
        for (int k = i + 1; k < cantUsuarios; k++) {
            if (usuarios[i].categoria > usuarios[k].categoria ||
                    (usuarios[i].categoria == usuarios[k].categoria &&
                    usuarios[i].calificacion < usuarios[k].calificacion)) {
                aux = usuarios[i];
                usuarios[i] = usuarios[k];
                usuarios[k] = aux;
            }
        }
    }
}

void atenderSolicitudes(Libro *libros, int cantLibros, Usuario *usuarios,
        int cantUsuarios, Solicitud *solicitudes, int cantSolicitudes) {
    ofstream archDenegadas;
    int maxPrestamos, posLibro;
    bool primeraVez = true;
    abrirArchivoSalida(archDenegadas, "SolicitudesDenegadas.txt");
    archDenegadas << fixed << setprecision(2);
    // Recorrer los usuarios ordenados por categoría y calificación
    for (int i = 0; i < cantUsuarios; i++) {
        maxPrestamos = obtenerMaxPrestamos(usuarios[i].categoria);
        // Recorrer las solicitudes del usuario
        for (int k = 0; k < cantSolicitudes; k++) {
            if (usuarios[i].dni != solicitudes[k].dniUsuario) continue;
            // Verificar que cumple con los requisitos
            if (usuarios[i].cantPrestados < maxPrestamos) {
                posLibro = buscarLibro(libros, solicitudes[k].codLibro, cantLibros);
                if (posLibro != NO_ENCONTRADO && libros[posLibro].cantVolumenes > 0) {
                    usuarios[i].cantPrestados++;
                    libros[posLibro].cantPrestados++;
                    libros[posLibro].cantVolumenes--;
                } else {
                    agregarSolicitudDenegada(archDenegadas, usuarios[i],
                            solicitudes[k], primeraVez);
                }
            } else {
                agregarSolicitudDenegada(archDenegadas, usuarios[i],
                        solicitudes[k], primeraVez);
                usuarios[i].calificacion *= (1 - DESCUENTO/100.0);
            }
        }
    }
}

int obtenerMaxPrestamos(char categoria) {
    switch (categoria) {
        case 'A':
            return MAX_PRESTAMOS_ALUMNO;
        case 'D':
            return MAX_PRESTAMOS_DOCENTE;
        case 'V':
            return MAX_PRESTAMOS_VISITANTE;
    }
    return 0;
}

int buscarLibro(Libro *libros, const char *codLibro, int cantLibros) {
    for (int i = 0; i < cantLibros; i++) {
        if (strcmp(libros[i].codigo, codLibro) == 0)
            return i;
    }
    return NO_ENCONTRADO;
}

void agregarSolicitudDenegada(ofstream &archDenegadas, Usuario &usuario,
        Solicitud &solicitud, bool &primeraVez) {
    // Imprimir solicitud
    if (primeraVez) {
        archDenegadas << setw(75) << "LISTA DE SOLICITUDES DENEGADAS" << endl;
        imprimirLinea(archDenegadas, '=');
        archDenegadas << left << setw(10) << "DNI" << "Cod. Libro" << endl;
        primeraVez = false;
    }
    archDenegadas << left << setw(10) << solicitud.dniUsuario
            << right << setw(10) << solicitud.codLibro << endl;
    // Actualizar usuario
    usuario.cantNoPrestados++;
}

/* Funciones auxiliares */

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
        cerr << "No se pudo abrir el archivo " << nomArch << endl;
        exit(1);
    }
}

void imprimirLinea(ofstream &arch, char car) {
    for (int i = 0; i < MAX_LINEA; i++)
        arch.put(car);
    arch << endl;
}
