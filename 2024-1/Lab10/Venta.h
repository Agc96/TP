/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * Archivo: Venta.h
 * Autor:   Anthony Gutiérrez
 * Fecha:   30 de junio de 2024, 08:32 PM
 */

#ifndef VENTA_H
#define VENTA_H

#include "Fecha.h"
#define MAX_NOM_VENTA 50

struct Venta {
    int dni;
    char nombre[MAX_NOM_VENTA];
    struct Fecha fecha;
    int calificacion;
};

#endif /* VENTA_H */
