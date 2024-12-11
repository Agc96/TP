/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * Archivo: main.cpp
 * Autor:   Anthony Gutiérrez
 * Fecha:   11 de mayo de 2024, 03:43 PM
 */

#include <iostream>
#include <fstream>
using namespace std;
#include "funciones.h"

#define MAX_MEDICOS 50
#define MAX_MEDICINAS 250

int main(int argc, char** argv) {
    int arrCodMedicos[MAX_MEDICOS], arrPacConMedMedicos[MAX_MEDICOS]{},
            arrPacSinMedMedicos[MAX_MEDICOS]{}, arrCodMedicinas[MAX_MEDICINAS],
            arrUnidMedicinas[MAX_MEDICINAS]{}, numMedicos = 0, numMedicinas = 0;
    double arrTarMedicos[MAX_MEDICOS], arrCitMedicos[MAX_MEDICOS]{},
            arrMedMedicos[MAX_MEDICOS]{}, arrPrecMedicinas[MAX_MEDICINAS],
            arrIngMedicinas[MAX_MEDICINAS]{}, arrDescMedicinas[MAX_MEDICINAS]{},
            promedio;
    leerMedicos(arrCodMedicos, arrTarMedicos, numMedicos);
    leerMedicinas(arrCodMedicinas, arrPrecMedicinas, numMedicinas);
    reportePrueba(arrCodMedicos, arrTarMedicos, numMedicos, arrCodMedicinas,
            arrPrecMedicinas, numMedicinas);
    leerCitas(arrCodMedicos, arrTarMedicos, arrCitMedicos, arrMedMedicos,
            arrPacConMedMedicos, arrPacSinMedMedicos, numMedicos,
            arrCodMedicinas, arrPrecMedicinas, arrUnidMedicinas, 
            arrIngMedicinas, arrDescMedicinas, numMedicinas);
    reporteIngresos(arrCodMedicos, arrTarMedicos, arrCitMedicos, arrMedMedicos,
            arrPacConMedMedicos, arrPacSinMedMedicos, numMedicos,
            arrCodMedicinas, arrPrecMedicinas, arrUnidMedicinas, 
            arrIngMedicinas, arrDescMedicinas, numMedicinas, promedio);
    eliminarMedicos(arrCodMedicos, arrTarMedicos, arrCitMedicos, arrMedMedicos,
            arrPacConMedMedicos, arrPacSinMedMedicos, numMedicos, promedio);
    reporteMejoresMedicos(arrCodMedicos, arrTarMedicos, arrCitMedicos, arrMedMedicos,
            arrPacConMedMedicos, arrPacSinMedMedicos, numMedicos);
    return 0;
}
