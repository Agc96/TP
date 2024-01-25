/* 
 * Archivo:      main.c
 * Autor:        20130095 Anthony Gutiérrez
 * Fecha y hora: 4 de abril de 2022, 11:20 PM
 * 
 * ********************************************************************
 * Programa que permite realizar operaciones aritméticas empleando
 * números complejos de la forma "a + bi".
 * ********************************************************************
 */

#include <stdio.h>
#include <stdlib.h>
#include "NumerosComplejos.h"
#include "FuncionesAuxiliares.h"

int main(int argc, char** argv) {
    /*declaración de variables*/
    char opcion, operador;
    // Debe cambiar las variables no descriptivas: a=comp1Real, b=comp1Imag, c=comp2Real, d=comp2Imag
    double a, b, c, d, real, imaginario;
    double numReal, numImag, denominador;
    int n = 0; // n=potencia
    char i; // Error de sintaxis: Esta declaración debió colocarse antes del scanf, no después
    // puede ser i por "simbolo" por ejemplo
    
    printf("\nIngrese un numero complejo: ");
    scanf("%lf %lf%c", &a, &b, &i); // Error de sintaxis: Faltaba una coma en scanf
    while(1){
        printf("\nIngrese la operacion y el siguiente numero complejo: ");
        scanf("\n%c", &opcion); // Falta el porcentaje
        if((opcion == 'F') || (opcion == 'f')) break; // Debe ser 
        if((opcion == 'P') || (opcion =='p')){
            scanf("%d", &n);
            potenciar(a, b, n, &real, &imaginario);
        }
        else{
            scanf("%lf %lf%c", &c, &d, &i);
            if((opcion == 'S') || (opcion =='s'))
                sumar(a, b, c, d, &real, &imaginario);
            else if((opcion == 'R') || (opcion =='r'))
                restar(a, b, c, d, &real, &imaginario);
            else if((opcion == 'M') || (opcion =='m'))
                multiplicar(a, b, c, d, &real, &imaginario);
            else if((opcion == 'D') || (opcion =='d')){
                dividir(a, b, c, d, &real, &imaginario, &denominador);
            }
        }
        a = real ; b = imaginario; 
        imprimirResultado(real, imaginario);
    }
    return (EXIT_SUCCESS);
}
