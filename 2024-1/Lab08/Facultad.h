/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * Archivo: Facultad.h
 * Autor:   Anthony Gutiérrez
 * Fecha:   15 de junio de 2024, 02:08 PM
 */

#ifndef FACULTAD_H
#define FACULTAD_H

#define MAX_COD_FACULTAD 20
#define MAX_NOM_FACULTAD 40

struct Facultad {
    char codigo[MAX_COD_FACULTAD];
    char nombre[MAX_NOM_FACULTAD];
};

#endif /* FACULTAD_H */

