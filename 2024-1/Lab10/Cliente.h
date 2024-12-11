/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * Archivo: Cliente.h
 * Autor:   Anthony Gutiérrez
 * Fecha:   30 de junio de 2024, 08:31 PM
 */

#ifndef CLIENTE_H
#define CLIENTE_H

#define MAX_NOM_CLIENTE 50

struct Cliente {
    int dni;
    char nombre[MAX_NOM_CLIENTE];
};

#endif /* CLIENTE_H */
