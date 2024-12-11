/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * Archivo: Alumno.h
 * Autor:   Anthony Gutiérrez
 * Fecha:   15 de junio de 2024, 02:09 PM
 */

#ifndef ALUMNO_H
#define ALUMNO_H

#define MAX_NOM_ALUMNO 40

struct Alumno {
    int codigo;
    char nombre[MAX_NOM_ALUMNO];
    int numCursos;
    double sumaPond;
    double numCreditos;
    double promPond;
    struct Facultad facultad;
};

#endif /* ALUMNO_H */

