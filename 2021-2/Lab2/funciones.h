/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   funciones.h
 * Author: Anthony
 *
 * Created on 28 de septiembre de 2021, 07:12 AM
 */

#ifndef FUNCIONES_H
#define FUNCIONES_H

#include <stdio.h>
#include <stdlib.h>

void procesarPacientes();
void procesarNombrePaciente(FILE *, FILE *);
void procesarDistritoPaciente(FILE *, FILE *);
void procesarAtenciones(FILE *, int, double *);
int leerHora(FILE *);
void imprimirAtencion(FILE *, int, int, int, int, double *);
void imprimirFecha(FILE *, int);
void imprimirHora(FILE *, int);
double buscarTarifaMedico(int);

/* Funciones auxiliares */

FILE *abrirArchivo(const char *, const char *);
void separacion(FILE *, char, int, int);

#endif /* FUNCIONES_H */

