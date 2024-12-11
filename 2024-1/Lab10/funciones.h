/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * Archivo: funciones.h
 * Autor:   Anthony Gutiérrez
 * Fecha:   30 de junio de 2024, 08:37 PM
 */

#ifndef FUNCIONES_H
#define FUNCIONES_H

void leerClientes(const char *nomArchTxt, const char *nomArchBin);
void leerLibros(const char *nomArchTxt, const char *nomArchBin);
void leerVentas(const char *nomArchVen, const char *nomArchCli, const char *nomArchLib);
int obtenerNumReg(istream &archBin, int tamReg);
int buscarLibro(fstream &archLib, int tamReg, int numReg, char *codigo);
int buscarCliente(ifstream &archCli, int tamReg, int numReg, int dni);
void determinarRanking(const char *nomArchBin);
void ordenarLibros(const char *nomArchBin);
void generarReporte(const char *nomArchBin, const char *nomArchRep);
void imprimirFecha(ofstream &archRep, struct Fecha &fecha);

void abrirArchTxtEntrada(ifstream &archTxt, const char *nomArchTxt);
void abrirArchTxtSalida(ofstream &archTxt, const char *nomArchTxt);
void abrirArchBinEntrada(ifstream &archBin, const char *nomArchBin);
void abrirArchBinEntradaSalida(fstream &archBin, const char *nomArchBin);
void abrirArchBinSalida(ofstream &archBin, const char *nomArchBin);
void imprimirLinea(ofstream &archRep, char car);

#endif /* FUNCIONES_H */

