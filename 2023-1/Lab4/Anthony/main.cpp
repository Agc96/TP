/*
 * Archivo: main.cpp
 * Autor:   Anthony Gutiérrez
 * Fecha:   9 de mayo de 2023, 07:56 PM
 */

#include "funciones.h"

#define MAX_LIBROS 100
#define MAX_AUTORES 400

int main() {
    int arrCodLib[MAX_LIBROS], arrCantLib[MAX_LIBROS]{}, arrCodAut[MAX_AUTORES],
            arrLibAut[MAX_AUTORES]{}, cantLib, cantAut, fechaIni, fechaFin;
    double arrPrecLib[MAX_LIBROS], arrMontoLib[MAX_LIBROS]{},
            arrPorcAut[MAX_AUTORES], arrMontoAut[MAX_AUTORES]{};
    leerLibros(arrCodLib, arrPrecLib, cantLib);
    leerAutores(arrCodAut, arrLibAut, arrPorcAut, cantAut);
    leerFechas(fechaIni, fechaFin);
    procesarVentas(arrCodLib, arrPrecLib, arrCantLib, arrMontoLib, cantLib,
            arrCodAut, arrLibAut, arrPorcAut, arrMontoAut, cantAut, fechaIni,
            fechaFin);
    imprimirReporte(arrCodLib, arrPrecLib, arrCantLib, arrMontoLib, cantLib,
            arrCodAut, arrLibAut, arrPorcAut, arrMontoAut, cantAut, fechaIni,
            fechaFin);
    return 0;
}
