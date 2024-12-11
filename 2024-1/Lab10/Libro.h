/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * Archivo: Libro.h
 * Autor:   Anthony Gutiérrez
 * Fecha:   30 de junio de 2024, 08:34 PM
 */

#ifndef LIBRO_H
#define LIBRO_H

#include "Fecha.h"
#include "Venta.h"
#define MAX_COD_LIBRO 10
#define MAX_TIT_LIBRO 60
#define MAX_AUT_LIBRO 30
#define MAX_VENTAS_LIBRO 10

struct Libro {
    char codigo[MAX_COD_LIBRO];
    char titulo[MAX_TIT_LIBRO];
    char autor[MAX_AUT_LIBRO];
    double precio;
    struct Venta ventas[MAX_VENTAS_LIBRO];
    int librosVendidos;
    struct Fecha fechaMasReciente;
    int sumaDeCalificaciones;
    int ranking;
};

#endif /* LIBRO_H */
