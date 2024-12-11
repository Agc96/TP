/*
 * Archivo: funciones.cpp
 * Autor:   Anthony Gutiérrez
 * Fecha:   11 de mayo de 2024, 03:43 PM
 */

#include <iostream>
#include <iomanip>
#include <fstream>
using namespace std;
#include "funciones.h"

#define LIN_REP_PRUEBA 20
#define LIN_REP_MEDICOS 120
#define NO_ENCONTRADO -1

void leerMedicos(int arrCodMedicos[], double arrTarMedicos[], int &numMedicos) {
    ifstream arch;
    abrirArchivoEntrada(arch, "Medicos.txt");
    char c;
    while (true) {
        // Guardar código del médico
        arch >> arrCodMedicos[numMedicos];
        if (arch.eof()) break;
        // Ignorar nombre del médico
        arch >> c; // lee un '/'
        while (arch.get() != '/');
        // Ignorar especialidad del médico
        arch >> ws;
        while (arch.get() != ' ');
        // Guardar tarifa del médico
        arch >> arrTarMedicos[numMedicos];
        numMedicos++;
    }
}

void leerMedicinas(int arrCodMedicinas[], double arrPrecMedicinas[], int &numMedicinas) {
    ifstream arch;
    abrirArchivoEntrada(arch, "Medicinas.txt");
    while (true) {
        // Guardar código de la medicina
        arch >> arrCodMedicinas[numMedicinas];
        if (arch.eof()) break;
        // Ignorar descripción de la medicina
        arch >> ws;
        while (arch.get() != ' ');
        // Guardar precio de la medicina
        arch >> arrPrecMedicinas[numMedicinas];
        numMedicinas++;
    }
}

void reportePrueba(int arrCodMedicos[], double arrTarMedicos[], int numMedicos,
        int arrCodMedicinas[], double arrPrecMedicinas[], int numMedicinas) {
    ofstream arch;
    abrirArchivoSalida(arch, "ReportePrueba.txt");
    arch << fixed << setprecision(2);
    // Imprimir reporte de médicos
    arch << "REPORTE DE MEDICOS" << endl;
    imprimirLinea(arch, '=', LIN_REP_PRUEBA);
    arch << left << setw(10) << "Codigo" << "Tarifa" << endl;
    for (int i = 0; i < numMedicos; i++) {
        arch << right << setw(6) << arrCodMedicos[i] << setw(10) << arrTarMedicos[i] << endl;
    }
    arch << endl;
    // Imprimir reporte de medicinas
    arch << "REPORTE DE MEDICINAS" << endl;
    imprimirLinea(arch, '=', LIN_REP_PRUEBA);
    arch << left << setw(10) << "Codigo" << "Precio" << endl;
    for (int i = 0; i < numMedicinas; i++) {
        arch << right << setw(6) << arrCodMedicinas[i] << setw(10) << arrPrecMedicinas[i] << endl;
    }
}

void leerCitas(int arrCodMedicos[], double arrTarMedicos[], double arrCitMedicos[],
        double arrMedMedicos[], int arrPacConMedMedicos[], int arrPacSinMedMedicos[],
        int numMedicos, int arrCodMedicinas[], double arrPrecMedicinas[],
        int arrUnidMedicinas[], double arrIngMedicinas[], double arrDescMedicinas[],
        int numMedicinas) {
    ifstream arch;
    abrirArchivoEntrada(arch, "CitasMedicas.txt");
    int codMedico, codMedicina, cantMedicina, posMedico, posMedicina;
    double desc, duracion, pagoCita, monto, pagoMedicinas, descCita, descMedicinas;
    while (true) {
        leerPaciente(arch, desc, duracion, codMedico);
        if (arch.eof()) break;
        posMedico = buscar(arrCodMedicos, numMedicos, codMedico);
        if (posMedico != NO_ENCONTRADO) {
            pagoMedicinas = descMedicinas = 0;
            // Leer listado de medicamentos
            if (arch.get() != '\n') {
                arrPacConMedMedicos[posMedico]++;
                while (true) {
                    arch >> codMedicina >> cantMedicina;
                    posMedicina = buscar(arrCodMedicinas, numMedicinas, codMedicina);
                    if (posMedicina != NO_ENCONTRADO) {
                        monto = arrPrecMedicinas[posMedicina] * cantMedicina;
                        pagoMedicinas += monto;
                        cout << "2:" << codMedicina << ',' << cantMedicina << ',' << monto << endl;
                        arrUnidMedicinas[posMedicina] += cantMedicina;
                    }
                    if (arch.get() == '\n') break;
                }
            } else arrPacSinMedMedicos[posMedico]++;
            // Actualizar datos del médico
            pagoCita = arrTarMedicos[posMedico] * duracion;
            descCita = pagoCita * desc / 100;
            descMedicinas = pagoMedicinas * desc / 200;
            cout << "3:" << pagoCita << ',' << descCita << ',' << pagoMedicinas << ',' << descMedicinas << endl;
            arrCitMedicos[posMedico] += pagoCita - descCita;
            arrMedMedicos[posMedico] += pagoMedicinas - descMedicinas;
            arrIngMedicinas[posMedicina] += pagoCita + pagoMedicinas;
            arrDescMedicinas[posMedicina] += descCita + descMedicinas;
        } else while (arch.get() != '\n');
    }
}

void leerPaciente(ifstream &arch, double &desc, double &duracion, int &codMedico) {
    int num, dniPac, horaIni, horaFin;
    // Leer fecha
    arch >> num;
    if (arch.eof()) return;
    while (arch.get() != ' ');
    // Leer datos del paciente
    arch >> dniPac >> desc;
    horaIni = leerHora(arch);
    horaFin = leerHora(arch);
    duracion = (horaFin - horaIni) / 3600.0;
    cout << "1:" << dniPac << ',' << desc << ',' << duracion << endl;
    arch >> codMedico;
}

int leerHora(ifstream &arch) {
    int hora, min, seg;
    arch >> hora;
    arch.get();
    arch >> min;
    arch.get();
    arch >> seg;
    return 3600*hora + 60*min + seg;
}

void reporteIngresos(int arrCodMedicos[], double arrTarMedicos[], double arrCitMedicos[],
        double arrMedMedicos[], int arrPacConMedMedicos[], int arrPacSinMedMedicos[],
        int numMedicos, int arrCodMedicinas[], double arrPrecMedicinas[],
        int arrUnidMedicinas[], double arrIngMedicinas[], double arrDescMedicinas[],
        int numMedicinas, double &promedio) {
    ofstream arch;
    abrirArchivoSalida(arch, "ReporteDeIngresos.txt");
    arch << fixed << setprecision(2);
    promedio = imprimirMedicos(arch, arrCodMedicos, arrTarMedicos, arrCitMedicos,
            arrMedMedicos, arrPacConMedMedicos, arrPacSinMedMedicos, numMedicos);
    arch << endl;
    imprimirMedicinas(arch, arrCodMedicinas, arrPrecMedicinas, arrUnidMedicinas,
            arrIngMedicinas, arrDescMedicinas, numMedicinas);
}

double imprimirMedicos(ofstream &arch, int arrCodMedicos[], double arrTarMedicos[],
        double arrCitMedicos[], double arrMedMedicos[], int arrPacConMedMedicos[],
        int arrPacSinMedMedicos[], int numMedicos) {
    double totalIng, sumaCitas = 0, sumaMedicamentos = 0, sumaTotal = 0;
    int totalPac, sumaPacConMed = 0, sumaPacSinMed = 0, sumaTotalPac = 0;
    // Imprimir cabecera
    imprimirLinea(arch, '=', LIN_REP_MEDICOS);
    arch << setw(71) << "EMPRESA DE SALUD S. A." << endl;
    arch << setw(75) << "REGISTRO DE INGRESOS POR MEDICO" << endl;
    imprimirLinea(arch, '=', LIN_REP_MEDICOS);
    arch << left << setw(5) << "No." << setw(12) << "Codigo del"
            << setw(8) << "Tarifa" << setw(14) << "Ingresos por"
            << setw(16) << "Ingresos por" << setw(9) << "Total"
            << setw(21) << "Pacientes atendidos"
            << setw(21) << "Pacientes atendidos" << "Total de" << endl;
    arch << setw(7) << ' ' << setw(20) << "Medico" << setw(12) << "las citas"
            << setw(14) << "medicamentos" << setw(14) << "ingresado"
            << setw(21) << "con medicinas" << setw(18) << "sin medicinas"
            << "pacientes" << endl;
    imprimirLinea(arch, '-', LIN_REP_MEDICOS);
    // Imprimir listado de médicos
    for (int i = 0; i < numMedicos; i++) {
        totalIng = arrCitMedicos[i] + arrMedMedicos[i];
        totalPac = arrPacConMedMedicos[i] + arrPacSinMedMedicos[i];
        arch << right << setfill('0') << setw(3) << (i+1) << setfill(' ')
                << setw(9) << arrCodMedicos[i] << setw(11) << arrTarMedicos[i]
                << setw(12) << arrCitMedicos[i] << setw(14) << arrMedMedicos[i]
                << setw(13) << totalIng << setw(13) << arrPacConMedMedicos[i]
                << setw(19) << arrPacSinMedMedicos[i] << setw(17) << totalPac << endl;
        // Agregar sumatorias
        sumaCitas += arrCitMedicos[i];
        sumaMedicamentos += arrMedMedicos[i];
        sumaTotal += totalIng;
        sumaPacConMed += arrPacConMedMedicos[i];
        sumaPacSinMed += arrPacSinMedMedicos[i];
        sumaTotalPac += totalPac;
    }
    // Imprimir resumen
    imprimirLinea(arch, '-', LIN_REP_MEDICOS);
    arch << "Totales:" << setw(27) << sumaCitas << setw(14) << sumaMedicamentos
            << setw(13) << sumaTotal << setw(13) << sumaPacConMed
            << setw(19) << sumaPacSinMed << setw(17) << sumaTotalPac << endl;
    imprimirLinea(arch, '=', LIN_REP_MEDICOS);
    // Calcular promedio
    return sumaTotal / numMedicos;
}

void imprimirMedicinas(ofstream &arch, int arrCodMedicinas[], double arrPrecMedicinas[],
        int arrUnidMedicinas[], double arrIngMedicinas[], double arrDescMedicinas[],
        int numMedicinas) {
    double totalIngresado, sumaIngresos = 0, sumaDescuentos = 0, sumaTotal = 0;
    int sumaUnidades = 0;
    // Imprimir cabecera
    imprimirLinea(arch, '=', LIN_REP_MEDICOS);
    arch << setw(71) << "EMPRESA DE SALUD S. A." << endl;
    arch << setw(78) << "REGISTRO DE INGRESOS POR MEDICAMENTO" << endl;
    imprimirLinea(arch, '=', LIN_REP_MEDICOS);
    arch << left << setw(5) << "No." << setw(13) << "Codigo del"
            << setw(8) << "Precio" << setw(22) << "Cantidad de unidades"
            << setw(14) << "Ingresos sin" << setw(18) << "Descuentos por" << "Total" << endl;
    arch << setw(5) << ' ' << setw(27) << "Medicamento" << setw(17) << "vendidas"
            << setw(14) << "descuentos" << setw(15) << "los seguros" << "ingresado" << endl;
    imprimirLinea(arch, '-', LIN_REP_MEDICOS);
    // Imprimir listado de médicos
    for (int i = 0; i < numMedicinas; i++) {
        totalIngresado = arrIngMedicinas[i] - arrDescMedicinas[i];
        arch << right << setfill('0') << setw(3) << (i+1) << setfill(' ')
                << setw(9) << arrCodMedicinas[i] << setw(12) << arrPrecMedicinas[i]
                << setw(13) << arrUnidMedicinas[i] << setw(21) << arrIngMedicinas[i]
                << setw(15) << arrDescMedicinas[i] << setw(13) << totalIngresado << endl;
        // Agregar sumatorias
        sumaUnidades += arrUnidMedicinas[i];
        sumaIngresos += arrIngMedicinas[i];
        sumaDescuentos += arrDescMedicinas[i];
        sumaTotal += totalIngresado;
    }
    // Imprimir resumen
    imprimirLinea(arch, '-', LIN_REP_MEDICOS);
    arch << "Totales:" << setw(29) << sumaUnidades << setw(21) << sumaIngresos
            << setw(15) << sumaDescuentos << setw(13) << sumaTotal << endl;
    imprimirLinea(arch, '=', LIN_REP_MEDICOS);
}

void eliminarMedicos(int arrCodMedicos[], double arrTarMedicos[], double arrCitMedicos[],
        double arrMedMedicos[], int arrPacConMedMedicos[], int arrPacSinMedMedicos[],
        int &numMedicos, double promedio) {
    for (int i = numMedicos - 1; i >= 0; i--) {
        if ((arrCitMedicos[i] + arrMedMedicos[i]) < promedio) {
            for (int j = i; j < numMedicos - 1; j++) {
                arrCodMedicos[j] = arrCodMedicos[j+1];
                arrTarMedicos[j] = arrTarMedicos[j+1];
                arrCitMedicos[j] = arrCitMedicos[j+1];
                arrMedMedicos[j] = arrMedMedicos[j+1];
                arrPacConMedMedicos[j] = arrPacConMedMedicos[j+1];
                arrPacSinMedMedicos[j] = arrPacSinMedMedicos[j+1];
            }
            numMedicos--;
            // i--; // Esto en caso vayan desde 0 hasta n-1.
        }
    }
}

void reporteMejoresMedicos(int arrCodMedicos[], double arrTarMedicos[],
        double arrCitMedicos[], double arrMedMedicos[], int arrPacConMedMedicos[],
        int arrPacSinMedMedicos[], int numMedicos) {
    ofstream arch;
    abrirArchivoSalida(arch, "ReporteDeMejoresMedicos.txt");
    arch << fixed << setprecision(2);
    imprimirMedicos(arch, arrCodMedicos, arrTarMedicos, arrCitMedicos, arrMedMedicos,
            arrPacConMedMedicos, arrPacSinMedMedicos, numMedicos);
}

/* Funciones auxiliares */

void abrirArchivoEntrada(ifstream &arch, const char *nomArch) {
    arch.open(nomArch, ios::in);
    if (!arch) {
        cerr << "No se pudo abrir el archivo " << nomArch << endl;
        exit(1);
    }
}

void abrirArchivoSalida(ofstream &arch, const char *nomArch) {
    arch.open(nomArch, ios::out);
    if (!arch) {
        cerr << "No se pudo crear el archivo " << nomArch << endl;
        exit(1);
    }
}

void imprimirLinea(ofstream &arch, char car, int cant) {
    for (int i = 0; i < cant; i++)
        arch.put(car);
    arch << endl;
}

int buscar(int arreglo[], int numDatos, int codigo) {
    for (int i = 0; i < numDatos; i++) {
        if (arreglo[i] == codigo)
            return i;
    }
    return NO_ENCONTRADO;
}
