/*
 * Archivo: funciones.c
 * Autor:   Anthony Gutiérrez
 *
 * Creado el 28 de septiembre de 2020, 07:05 PM
 */

#include "funciones.h"
#define MAX_LINEA 120
#define MIN_APROBADA 10.5

void generarReporte(FILE* archAlumnos, FILE* archReporte) {
    int codAlumno, anho, codFacultad, numAlumnos = 0, numAluAprob = 0;
    double credAprob, credDesaprob;
    /* Imprimir cabecera del reporte */
    fprintf(archReporte, "%78s\n", "RESULTADOS ACADEMICOS DE LOS ALUMNOS");
    /* Leer línea por línea */
    while (1) {
        fscanf(archAlumnos, "%d %d %d %lf", &codAlumno, &anho, &codFacultad, &credAprob);
        if (feof(archAlumnos)) break;
        /* Ver si se puede leer el número de créditos desaprobados */
        if (getc(archAlumnos) == '\n') {
            credDesaprob = 0;
        } else {
            fscanf(archAlumnos, "%lf", &credDesaprob);
        }
        /* Imprimir los datos principales del alumno */
        imprimirCabeceraAlumno(archReporte, ++numAlumnos, codAlumno, anho,
                codFacultad, credAprob, credDesaprob);
        /* Buscar los cursos del alumno */
        buscarCursos(archReporte, codAlumno, codFacultad, credAprob, credDesaprob, &numAluAprob);
    }
    /* Imprimir resumen del reporte */
    imprimirResumenReporte(archReporte, numAlumnos, numAluAprob);
}

void imprimirCabeceraAlumno(FILE* archReporte, int numAlumnos, int codAlumno,
        int anhoAlumno, int codFacultad, double credAprob, double credDesaprob) {
    /* Imprimir datos principales del alumno */
    separacion(archReporte, '=');
    fprintf(archReporte, "%02d)  Alumno: %4d  A. de ingreso: %4d  Facultad: %07d",
            numAlumnos, codAlumno, anhoAlumno, codFacultad);
    fprintf(archReporte, "  Cred. aprobados: %.1lf  Cred. desaprobados: %.1lf\n",
            credAprob, credDesaprob);
    /* Imprimir cabecera para la lista de cursos */
    separacion(archReporte, '-');
    fprintf(archReporte, "%25s%48s\n", "CURSOS APROBADOS", "CURSOS DESAPROBADOS");
    fprintf(archReporte, "No.  CODIGO  CREDITOS  %-30s", "NOTA");
    fprintf(archReporte, "CODIGO  CREDITOS  NOTA\n");
    separacion(archReporte, '-');
}

void buscarCursos(FILE* archReporte, int codAlumno, int codFacultad,
        double credAprobInicial, double credDesaprobInicial, int* numAluAprob) {
    /* Declaración de variables */
    FILE* archMatricula = abrirArchivo("Matricula.txt", "r");
    double credAprobFac = 0, credDesaprobFac = 0, credAprobOtros = 0,
            credDesaprobOtros = 0, sumaPond = 0;
    int codAluLeido, codCurso, cont = 0, numCurFac = 0, numCurOtros = 0;
    /* Leer línea por línea */
    while (1) {
        fscanf(archMatricula, "%d", &codAluLeido);
        if (feof(archMatricula)) break;
        /* Leer cada curso en la misma línea */
        while (getc(archMatricula) != '\n') {
            fscanf(archMatricula, "%d", &codCurso);
            /* Verificar si es el alumno deseado */
            if (codAluLeido == codAlumno) {
                buscarNotaCurso(archReporte, codAlumno, codFacultad, codCurso, &cont,
                        &numCurFac, &credAprobFac, &credDesaprobFac, &numCurOtros,
                        &credAprobOtros, &credDesaprobOtros, &sumaPond);
            }
        }
    }
    /* Imprimir resumen del alumno */
    imprimirResumenAlumno(archReporte, credAprobInicial, credDesaprobInicial, numCurFac,
            credAprobFac, credDesaprobFac, numCurOtros, credAprobOtros, credDesaprobOtros,
            sumaPond, numAluAprob);
    /* Cierre de archivos */
    fclose(archMatricula);
}

void buscarNotaCurso(FILE* archReporte, int codAlumno, int codFacultad, int codCurso,
        int* contador, int* numCurFac, double* credAprobFac, double* credDesaprobFac,
        int* numCurOtros, double* credAprobOtros, double* credDesaprobOtros,
        double* sumaPond) {
    /* Declaración de variables */
    FILE* archNotas = abrirArchivo("Notas.txt", "r");
    double creditos, nota;
    int codCursoLeido, codFacLeida, codAluLeido;
    /* Leer línea por línea */
    while (1) {
        fscanf(archNotas, "%d %d %lf", &codCursoLeido, &codFacLeida, &creditos);
        if (feof(archNotas)) break;
        /* Leer cada alumno-nota en la misma línea */
        while (getc(archNotas) != '\n') {
            fscanf(archNotas, "%d %lf", &codAluLeido, &nota);
            /* Verificar si es el alumno y curso deseado */
            if (codCursoLeido == codCurso && codAluLeido == codAlumno) {
                ++(*contador);
                if (codFacultad == codFacLeida) {
                    agregarNota(archReporte, codCurso, creditos, nota, *contador,
                            numCurFac, credAprobFac, credDesaprobFac, sumaPond);
                } else {
                    agregarNota(archReporte, codCurso, creditos, nota, *contador,
                            numCurOtros, credAprobOtros, credDesaprobOtros, sumaPond);
                }
            }
        }
    }
    /* Cierre de archivos */
    fclose(archNotas);
}

void agregarNota(FILE* archReporte, int codCurso, double creditos, double nota,
        int contador, int* numCursos, double* credAprob, double* credDesaprob,
        double* sumaPond) {
    /* Imprimir número de cursos */
    fprintf(archReporte, "%03d", contador);
    /* Actualizar contadores */
    (*numCursos)++;
    (*sumaPond) += (creditos * nota);
    if (nota >= MIN_APROBADA) {
        fprintf(archReporte, "%4c", ' ');
        (*credAprob) += creditos;
    } else {
        fprintf(archReporte, "%52c", ' ');
        (*credDesaprob) += creditos;
    }
    /* Imprimir datos del curso */
    fprintf(archReporte, "%3d     %.2lf    %04.1lf\n", codCurso, creditos, nota);
}

void imprimirResumenAlumno(FILE* archReporte, double credAprob, double credDesaprob,
        int numCurFac, double credAprobFac, double credDesaprobFac, int numCurOtros,
        double credAprobOtros, double credDesaprobOtros, double sumaPond, int* numAluAprob) {
    /* Calcular valores intermedios */
    double totalCred = credAprobFac + credAprobOtros + credDesaprob + credDesaprobOtros;
    double promPond = sumaPond / totalCred;
    double credAprobAcum = credAprob + credAprobFac + credAprobOtros;
    double credDesaprobAcum = credDesaprob + credDesaprobFac + credDesaprobOtros;
    /* Imprimir resumen de cursos de la misma facultad */
    separacion(archReporte, '=');
    fprintf(archReporte, "%6c RESUMEN:\n", ' ');
    fprintf(archReporte, "%6c EN SU FACULTAD:\n", ' ');
    imprimirResumenAlumnoFacultad(archReporte, numCurFac, credAprobFac, credDesaprobFac);
    /* Imprimir resumen de cursos de otras facultades */
    separacion(archReporte, '-');
    fprintf(archReporte, "%6c EN OTRA FACULTAD:\n", ' ');
    imprimirResumenAlumnoFacultad(archReporte, numCurOtros, credAprobOtros, credDesaprobOtros);
    separacion(archReporte, '-');
    /* Imprimir promedios */
    fprintf(archReporte, "%6c Promedio ponderado: %20.2lf\n", ' ', promPond);
    fprintf(archReporte, "%6c Creditos aprobados acumulados: %8.1lf\n", ' ', credAprobAcum);
    fprintf(archReporte, "%6c Creditos desaprobados acumulados: %5.1lf\n", ' ', credDesaprobAcum);
    /* Actualizar contador de ponderados aprobados */
    if (promPond >= MIN_APROBADA) {
        (*numAluAprob)++;
    }
}

void imprimirResumenAlumnoFacultad(FILE* archReporte, int numCursos,
        double credAprob, double credDesaprob) {
    /* Calcular valores intermedios */
    double totalCred = credAprob + credDesaprob;
    double porcAprob = credAprob * 100.0 / totalCred;
    /* Imprimir resumen según la facultad */
    fprintf(archReporte, "%6c Cursos matriculados: %2d", ' ', numCursos);
    fprintf(archReporte, "%22c Total de creditos matriculados: %.1lf\n", ' ', totalCred);
    fprintf(archReporte, "%6c Creditos aprobados: %5.1lf", ' ', credAprob);
    fprintf(archReporte, "%20c Creditos desaprobados: %.1lf\n", ' ', credDesaprob);
    fprintf(archReporte, "%6c Creditos aprobados/matriculados: %7.2lf%%\n", ' ',
            porcAprob);
}

void imprimirResumenReporte(FILE* archReporte, int numAlumnos, int numAluAprob) {
    /* Calcular porcentajes */
    double porcAprobado = numAluAprob * 100.0 / numAlumnos;
    double porcDesaprob = 100.0 - porcAprobado;
    /* Imprimir el resumen del reporte */
    separacion(archReporte, '*');
    fprintf(archReporte, "%4c TOTAL DE ALUMNOS MATRICULADOS EN EL CICLO: %d\n", ' ', numAlumnos);
    fprintf(archReporte, "%4c PORCENTAJE DE ALUMNOS CON PROMEDIO PONDERADO APROBADO: %9.2lf%%\n", ' ', porcAprobado);
    fprintf(archReporte, "%4c PORCENTAJE DE ALUMNOS CON PROMEDIO PONDERADO DESAPROBADO: %6.2lf%%\n", ' ', porcDesaprob);
    separacion(archReporte, '*');
}

/* Funciones auxiliares */

FILE* abrirArchivo(const char* nomArch, const char* tipoArch) {
    FILE* arch = fopen(nomArch, tipoArch);
    if (arch == NULL) {
        fprintf(stderr, "No se pudo abrir o guardar el archivo %s.\n", nomArch);
        exit(1);
    }
    return arch;
}

void separacion(FILE* arch, char c) {
    int i;
    for (i = 0; i < MAX_LINEA; i++) {
        putc(c, arch);
    }
    putc('\n', arch);
}
