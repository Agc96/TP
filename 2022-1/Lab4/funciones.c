/*
 * Archivo:      funciones.c
 * Autor:        Anthony Gutiérrez
 * Fecha y hora: 4 de junio de 2022, 03:53 PM
 */

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "funciones.h"

#define MAX_LINEA 130
#define MAX_NOM_ALUMNO 40
#define MAX_NOM_CURSO 40
#define NO_ENCONTRADO -1

void leerCursos(int *arrCodCur, double *arrCredCur, int *cantCur) {
    FILE *arch = abrirArchivo("Cursos.txt", "r");
    *cantCur = 0;
    while (1) {
        fscanf(arch, "%d", &arrCodCur[*cantCur]);
        if (feof(arch)) break;
        while (fgetc(arch) != '}');
        fscanf(arch, "%lf", &arrCredCur[*cantCur]);
        (*cantCur)++;
    }
    fclose(arch);
}

void leerAlumnos(int *arrCodAlu, double *arrCredApAlu, double *arrCredDesAlu,
        double *arrCredFacuAlu, int *cantAlu) {
    FILE *arch = abrirArchivo("Alumnos.txt", "r");
    *cantAlu = 0;
    while (1) {
        fscanf(arch, "%d", &arrCodAlu[*cantAlu]);
        if (feof(arch)) break;
        fscanf(arch, "%*s %lf %lf %lf", &arrCredApAlu[*cantAlu],
                &arrCredDesAlu[*cantAlu], &arrCredFacuAlu[*cantAlu]);
        (*cantAlu)++;
    }
    fclose(arch);
}

void leerNotas(int *arrCodCur, double *arrCredCur, int *arrAluApCur,
        int *arrAluDesCur, int cantCur, int *arrCodAlu, int *arrCurApAlu,
        int *arrCurDesAlu, double *arrSumaNotasAlu, double *arrCredApCiclo,
        double *arrCredDesCiclo, double *arrCredApAlu, double *arrCredDesAlu,
        int cantAlu) {
    FILE *arch = abrirArchivo("Notas.txt", "r");
    int codCur, indCur, codAlu, indAlu, nota;
    while (1) {
        fscanf(arch, "%d", &codCur);
        if (feof(arch)) break;
        // Obtener el índice del curso y validarlo
        indCur = buscar(arrCodCur, cantCur, codCur);
        if (indCur != NO_ENCONTRADO) {
            while (1) {
                fscanf(arch, "%d %d", &codAlu, &nota);
                // Obtener el índice del alumno y validarlo
                indAlu = buscar(arrCodAlu, cantAlu, codAlu);
                if (indAlu != NO_ENCONTRADO) {
                    arrSumaNotasAlu[indAlu] += arrCredCur[indCur]*nota;
                    if (nota > 10) {
                        arrAluApCur[indCur]++;
                        arrCurApAlu[indAlu]++;
                        arrCredApAlu[indAlu] += arrCredCur[indCur];
                        arrCredApCiclo[indAlu] += arrCredCur[indCur];
                    } else {
                        arrAluDesCur[indCur]++;
                        arrCurDesAlu[indAlu]++;
                        arrCredDesAlu[indAlu] += arrCredCur[indCur];
                        arrCredDesCiclo[indAlu] += arrCredCur[indCur];
                    }
                }
                if (fgetc(arch) == '\n') break;
            }
        } else {
            while (fgetc(arch) != '\n');
        }
    }
    fclose(arch);
}

int buscar(int *arr, int num, int cod) {
    for (int i = 0; i < num; i++) {
        if (arr[i] == cod) return i;
    }
    return NO_ENCONTRADO;
}

void ordenarAlumnos(int *arrCodAlu, int *arrCurApAlu, int *arrCurDesAlu,
        double *arrSumaNotasAlu, double *arrCredApCurso, double *arrCredDesCurso,
        double *arrCredApAlu, double *arrCredDesAlu, double *arrCredFacuAlu,
        int cantAlu) {
    double promPondI, promPondJ;
    for (int i = 0; i < cantAlu - 1; i++) {
        for (int j = i; j < cantAlu; j++) {
            promPondI = calcularPromPond(arrSumaNotasAlu[i], arrCredApCurso[i]+arrCredDesCurso[i]);
            promPondJ = calcularPromPond(arrSumaNotasAlu[j], arrCredApCurso[j]+arrCredDesCurso[j]);
            if (arrCurApAlu[i] < arrCurApAlu[j] || (arrCurApAlu[i] == arrCurApAlu[j]
                    && promPondI > promPondJ)) {
                intercambiarInt(arrCodAlu, i, j);
                intercambiarInt(arrCurApAlu, i, j);
                intercambiarInt(arrCurDesAlu, i, j);
                intercambiarDouble(arrSumaNotasAlu, i, j);
                intercambiarDouble(arrCredApCurso, i, j);
                intercambiarDouble(arrCredDesCurso, i, j);
                intercambiarDouble(arrCredApAlu, i, j);
                intercambiarDouble(arrCredDesAlu, i, j);
                intercambiarDouble(arrCredFacuAlu, i, j);
            }
        }
    }
}

double calcularPromPond(double sumaNotas, double sumaCred) {
    return (sumaCred > 0) ? sumaNotas / sumaCred : 0;
}

void intercambiarInt(int *arr, int i, int j) {
    int aux = arr[i];
    arr[i] = arr[j];
    arr[j] = aux;
}

void intercambiarDouble(double *arr, int i, int j) {
    double aux = arr[i];
    arr[i] = arr[j];
    arr[j] = aux;
}

void imprimirReporte(int *arrCodCur, int *arrAluApCur, int *arrAluDesCur,
        int cantCur, int *arrCodAlu, int *arrCurApAlu, int *arrCurDesAlu,
        double *arrSumaNotasAlu, double *arrCredApCurso, double *arrCredDesCurso,
        double *arrCredApAlu, double *arrCredDesAlu, double *arrCredFacuAlu, int cantAlu) {
    FILE *arch = abrirArchivo("ReportedeConsolidadoResultados.txt", "w");
    int cantAluFacu = 0;
    fprintf(arch, "%78s\n", "INSTITUCION EDUCATIVA LIMA");
    fprintf(arch, "%76s\n", "CONSOLIDADO DE ALUMNOS");
    imprimirLinea(arch, '=');
    fprintf(arch, "%10s %8s %30s %9s %14s %9s %9s %21s\n", "CODIGO", "NOMBRE",
            "CURSOS", "CURSOS", "PROMEDIO", "CREDITOS", "CREDITOS", "PASA A FACULTAD");
    fprintf(arch, "%53s %s %s %s %s\n", "APROBADOS", "DESAPROBADOS", "PONDERADO",
            "APROBADOS", "DESAPROBADOS");
    imprimirLinea(arch, '-');
    for (int i = 0; i < cantAlu; i++) {
        imprimirAlumno(arch, arrCodAlu, arrCurApAlu, arrCurDesAlu, arrSumaNotasAlu,
                arrCredApCurso, arrCredDesCurso, arrCredApAlu, arrCredDesAlu, arrCredFacuAlu,
                i, &cantAluFacu);
    }
    imprimirLinea(arch, '-');
    fprintf(arch, "Cantidad de alumnos que pasaran a Facultad: %9d\n", cantAluFacu);
    fprintf(arch, "Cantidad de alumnos que no pasaran a Facultad: %6d\n", cantAlu-cantAluFacu);
    imprimirLinea(arch, '=');
    fprintf(arch, "TOTAL DE ALUMNOS MATRICULADOS EN EL CICLO: %10d\n", cantAlu);
    imprimirLinea(arch, '=');
    fprintf(arch, "\n%48s\n", "RESULTADOS POR CURSO");
    fprintf(arch, "%10s %8s %42s %12s\n", "CODIGO", "NOMBRE", "APROBADOS", "DESAPROBADOS");
    for (int i = 0; i < cantCur; i++) {
        fprintf(arch, "%2d) %-8d ", i+1, arrCodCur[i]);
        imprimirNombreCurso(arch, arrCodCur[i]);
        fprintf(arch, "%6d %11d\n", arrAluApCur[i], arrAluDesCur[i]);
    }
    fclose(arch);
}

void imprimirAlumno(FILE *arch, int *arrCodAlu, int *arrCurApAlu,
        int *arrCurDesAlu, double *arrSumaNotasAlu, double *arrCredApCurso, double *arrCredDesCurso,
        double *arrCredApAlu, double *arrCredDesAlu, double *arrCredFacuAlu,
        int i, int *cantAluFacu) {
    double difCred, promPond;
    fprintf(arch, "%2d) %8d ", i+1, arrCodAlu[i]);
    buscarNombreAlumno(arch, arrCodAlu[i]);
    fprintf(arch, "%10d %12d", arrCurApAlu[i], arrCurDesAlu[i]);
    promPond = calcularPromPond(arrSumaNotasAlu[i], arrCredApCurso[i]+arrCredDesCurso[i]);
    if (promPond > 0) {
        fprintf(arch, " %9.2lf", promPond);
    } else {
        fprintf(arch, " %9s", "--.--");
    }
    fprintf(arch, " %9.2lf %12.2lf", arrCredApAlu[i], arrCredDesAlu[i]);
    difCred = arrCredFacuAlu[i] - arrCredApCurso[i];
    if (difCred <= 0) {
        fprintf(arch, "%3cSI\n", ' ');
        (*cantAluFacu)++;
    } else {
        fprintf(arch, "%3cNo, faltan %.2lf creditos\n", ' ', difCred);
    }
}

void buscarNombreAlumno(FILE *archRep, int codAluBuscado) {
    FILE *archAlu = abrirArchivo("Alumnos.txt", "r");
    int codAluLeido, mayusculas = 1, cantPal = 1, longNomAlu = 0;
    char nomAlu[MAX_NOM_ALUMNO];
    while (1) {
        fscanf(archAlu, "%d", &codAluLeido);
        if (feof(archAlu)) break;
        // Verificar si el código leído es el buscado
        if (codAluLeido == codAluBuscado) {
            fscanf(archAlu, "%s", nomAlu);
            // Formatear nombre del alumno
            for (int i = 0; nomAlu[i]; i++) {
                if (nomAlu[i] == '_') {
                    nomAlu[i] = ' ';
                    mayusculas = 1;
                    cantPal++;
                } else if (mayusculas) {
                    nomAlu[i] = toupper(nomAlu[i]);
                    mayusculas = 0;
                } else {
                    nomAlu[i] = tolower(nomAlu[i]);
                }
            }
            // Imprimir nombre del alumno
            imprimirApellidos(archRep, nomAlu, cantPal, &longNomAlu);
            imprimirNombres(archRep, nomAlu, cantPal, &longNomAlu);
            imprimirEspacios(archRep, MAX_NOM_ALUMNO - longNomAlu - 10);
            break;
        } else {
            while (fgetc(archAlu) != '\n');
        }
    }
    fclose(archAlu);
}

void imprimirApellidos(FILE *arch, char *nomAlu, int cantPalTotal,
        int *longNomAlu) {
    int cantPal = 0, imprimir = 0;
    for (int i = 0; nomAlu[i]; i++) {
        if (nomAlu[i] == ' ') {
            cantPal++;
            if (cantPal == cantPalTotal - 2) imprimir = 1;
            if (cantPal == cantPalTotal - 1) {
                fputc(' ', arch);
                (*longNomAlu)++;
            }
        } else if (imprimir) {
            fputc(nomAlu[i], arch);
            (*longNomAlu)++;
            if (cantPal == cantPalTotal - 1) {
                fprintf(arch, ". ");
                (*longNomAlu) += 2;
                break;
            }
        }
    }
}

void imprimirNombres(FILE *arch, char *nomAlu, int cantPalTotal, int *longNomAlu) {
    int mayusculas = 1, cantPal = 0;
    for (int i = 0; nomAlu[i]; i++) {
        if (nomAlu[i] == ' ') {
            fputc(' ', arch);
            cantPal++;
            (*longNomAlu)++;
            mayusculas = 1;
            if (cantPal == cantPalTotal - 2) break;
        } else if (mayusculas) {
            fputc(nomAlu[i], arch);
            (*longNomAlu)++;
            if (cantPal > 0) {
                fputc('.', arch);
                mayusculas = 0;
                (*longNomAlu)++;
            }
        }
    }
}

void imprimirNombreCurso(FILE *archRep, int codCurBuscado) {
    FILE *archCur = abrirArchivo("Cursos.txt", "r");
    int codCurLeido, continuar = 1, longNomCur = 0;
    char nomCur[MAX_NOM_CURSO];
    while (1) {
        fscanf(archCur, "%d", &codCurLeido);
        if (feof(archCur)) break;
        // Verificar si el código leído es el buscado
        if (codCurBuscado == codCurLeido) {
            while (fgetc(archCur) != '{');
            // Leer el nombre paso por paso
            while (continuar) {
                fscanf(archCur, "%s", nomCur);
                for (int i = 0; nomCur[i]; i++) {
                    longNomCur++;
                    if (nomCur[i] == '}') {
                        nomCur[i] = 0;
                        continuar = 0;
                        break;
                    }
                }
                fprintf(archRep, "%s ", nomCur);
                longNomCur++;
            }
            imprimirEspacios(archRep, MAX_NOM_CURSO - longNomCur);
            break;
        } else {
            while (fgetc(archCur) != '\n');
        }
    }
    fclose(archCur);
}

FILE *abrirArchivo(const char *nomArch, const char *modo) {
    FILE *arch = fopen(nomArch, modo);
    if (arch == NULL) {
        fprintf(stderr, "No se pudo abrir el archivo %s", nomArch);
        exit(1);
    }
    return arch;
}

void imprimirLinea(FILE *arch, char c) {
    for (int i = 0; i < MAX_LINEA; i++) {
        fputc(c, arch);
    }
    fputc('\n', arch);
}

void imprimirEspacios(FILE *arch, int cant) {
    for (int i = 0; i < cant; i++) {
        fputc(' ', arch);
    }
}
