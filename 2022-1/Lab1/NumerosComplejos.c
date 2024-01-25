/* 
 * Archivo:      NumerosComplejos.c
 * Autor:        20130095 Anthony Gutiérrez
 * Fecha y hora: 4 de abril de 2022, 11:27 PM
 */

#include <stdio.h>

void sumar(double a, double b, double c, double d, double * real, 
        double * imaginario){
    *real = a + c; 
    *imaginario = b + d; 
}

void restar(double a, double b, double c, double d, double * real, 
        double * imaginario){
    *real = a - c; 
    *imaginario = b - d;
}

void multiplicar(double a, double b, double c, double d, double * real, 
        double * imaginario){
    *real = a * c - b * d; 
    *imaginario = a * d + b * c;
}

void dividir(double a, double b, double c, double d, double * numReal, 
        double * numImg, double * denominador){
    *denominador = c * c + d * d; // Esta línea debe ir primero
    *numReal = (a * c + b * d) / (*denominador); // Dividir numReal y numImg por *denominador.
    *numImg = (b * c - a * d) / (*denominador);
}

void potenciar(double a, double b, int n, double * real, double * imaginario){
    double resA = 0.0, resB = 0.0, c, d;
    int cont = n;
    c = a; 
    d = b;
    while (cont>1){
        multiplicar( a, b, c, d, &resA, &resB);
        c = resA;
        d = resB;
        cont--;
    } 
    if (cont > 0){
        *real = resA; 
        *imaginario = resB;
    }
    if (n == 1){
        *real = a; 
        *imaginario = b;
    }
    if (n == 0){
        *real = 1; 
        *imaginario = 0;
    }
}
