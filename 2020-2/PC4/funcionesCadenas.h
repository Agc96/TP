#ifndef FUNCIONESCADENAS_H
#define FUNCIONESCADENAS_H

#include <stdio.h>

FILE *abrirArchivo(const char *, const char *);
void leerCadena(char *, int, FILE *);
char *leeCadenaExacta(FILE *);
void sacaPalabras(char *, char **, int *, char);

#endif /* FUNCIONESCADENAS_H */
