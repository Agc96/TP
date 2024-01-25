/* 
 * Archivo:      FuncionesAuxiliares.c
 * Autor:        20130095 Anthony Gutiérrez
 * Fecha y hora: 4 de abril de 2022, 11:20 PM
 */

#include <stdio.h>

void imprimirResultado(double real, double imaginario){
    if (imaginario<0)
        printf("\nResultado: %0.2lf - %0.2lfi\n", real, imaginario*(-1));
    else
        printf("\nResultado: %0.2lf + %0.2lfi\n", real, imaginario);
}
