/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * Archivo: funciones.h
 * Autor:   Anthony Gutiérrez
 * Fecha:   28 de abril de 2024, 04:50 PM
 */

#ifndef FUNCIONES_H
#define FUNCIONES_H

void imprimirCabecera(ofstream &);
void procesarCitas(ifstream &, ofstream &, double &, int &, double &);
int leerFecha(ifstream &);
int leerHora(ifstream &);
double imprimirCita(ofstream &, int, int, int, int, double, int, double);
void imprimirFecha(ofstream &, int);
void imprimirHora(ofstream &, int);
double procesarMedico(ofstream &, int);
void procesarNombre(ifstream &, ofstream &);
void procesarEspecialidad(ifstream &, ofstream &);
void imprimirResumen(ofstream &, double, int, double);

void abrirArchivoEntrada(ifstream &, const char *);
void abrirArchivoSalida(ofstream &, const char *);
void imprimirLinea(ofstream &, char);

#endif /* FUNCIONES_H */

