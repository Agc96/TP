/*
 * Archivo: main.cpp
 * Autor:   Anthony Gutiérrez
 * Fecha:   11 de abril de 2023, 09:37 PM
 */

#include "funciones.h"

int main() {
    int fechaLimDoc, fechaLimEst, codDocDeuda = 0, codEstDeuda = 0;
    double montoDocDeuda = 0, montoEstDeuda = 0;
    procesarCabecera(fechaLimDoc, fechaLimEst);
    procesarUsuarios(fechaLimDoc, fechaLimEst, codDocDeuda, montoDocDeuda,
            codEstDeuda, montoEstDeuda);
    imprimirResumen(codDocDeuda, montoDocDeuda, codEstDeuda, montoEstDeuda);
    return 0;
}
