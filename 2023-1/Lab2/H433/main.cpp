/*
 * Archivo: main.cpp
 * Autor:   Anthony Gutiérrez
 * Fecha:   11 de abril de 2023, 05:30 PM
 */

#include "funciones.h"
using namespace std;

int main() {
    int fechaLimDoc, fechaLimEst, codDocDeuda, codEstDeuda, codDocLibros,
            cantDocLibros = 0, codEstLibros, cantEstLibros = 0;
    double montoDocDeuda = 0, montoEstDeuda = 0;
    procesarCabecera(fechaLimDoc, fechaLimEst);
    procesarUsuarios(fechaLimDoc, fechaLimEst, codDocDeuda, montoDocDeuda,
            codEstDeuda, montoEstDeuda, codDocLibros, cantDocLibros,
            codEstLibros, cantEstLibros);
    imprimirResumen(codDocDeuda, montoDocDeuda, codEstDeuda, montoEstDeuda,
            codDocLibros, cantDocLibros, codEstLibros, cantEstLibros);
    return 0;
}
