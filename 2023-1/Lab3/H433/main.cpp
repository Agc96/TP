/*
 * Archivo: main.cpp
 * Autor:   Anthony Gutiérrez
 * Fecha:   25 de abril de 2023, 07:08 PM
 */

#include <iostream>
#include <fstream>
#include "funciones.h"
using namespace std;

int main() {
    ifstream archClientes("ClientesCine.txt", ios::in);
    if (!archClientes) {
        cerr << "No se pudo abrir el archivo ClientesCine.txt" << endl;
        exit(1);
    }
    ifstream archCartelera("CarteleraDeCines.txt", ios::in);
    if (!archCartelera) {
        cerr << "No se pudo abrir el archivo CarteleraDeCines.txt" << endl;
        exit(1);
    }
    ofstream archReporte("ListadoPersonas.txt", ios::out);
    if (!archReporte) {
        cerr << "No se pudo crear el archivo ListadoPersonas.txt" << endl;
        exit(1);
    }
    generarReporte(archClientes, archCartelera, archReporte);
    return 0;
}

