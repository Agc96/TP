/*
 * Archivo: funciones.h
 * Autor:   Anthony Gutiérrez
 * Fecha:   11 de mayo de 2024, 03:43 PM
 */

#ifndef FUNCIONES_H
#define FUNCIONES_H

void leerMedicos(int [], double [], int &);
void leerMedicinas(int [], double [], int &);
void reportePrueba(int [], double [], int, int [], double [], int);
void leerCitas(int [], double [], double [], double [], int [], int [], int,
        int [], double [], int [], double [], double [], int);
void leerPaciente(ifstream &, double &, double &, int &);
int leerHora(ifstream &);
void reporteIngresos(int [], double [], double [], double [], int [], int [],
        int, int [], double [], int [], double [], double [], int, double &);
double imprimirMedicos(ofstream &, int [], double [], double [], double [],
        int [], int [], int);
void imprimirMedicinas(ofstream &, int [], double [], int [], double [],
        double [], int);
void eliminarMedicos(int [], double [], double [], double [], int [], int [],
        int &, double);
void reporteMejoresMedicos(int [], double [], double [], double [], int [],
        int [], int);

void abrirArchivoEntrada(ifstream &, const char *);
void abrirArchivoSalida(ofstream &, const char *);
void imprimirLinea(ofstream &, char, int);
int buscar(int [], int, int);

#endif /* FUNCIONES_H */
