/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
#include <stdio.h>
#include <stdlib.h>

void linea(FILE * reporte, char c, int cant){
    
    for (int i=0; i<cant; i++){
        fprintf(reporte, "%c", c);
    }
    fprintf(reporte,"\n");
}

void guardarProductos(int * codigosProd, double * precios, int * cantProductos){
    FILE * archProductos;
  
    archProductos = fopen("productos.txt", "r");
    if(archProductos == NULL){
        printf("Archivo de Productos vacio");
        exit(1);
    }
    int i=0;
    char c;
    while(1){
        fscanf(archProductos,"%d", &codigosProd[i]);
        if (feof(archProductos)) break;
        while(1){
            c = fgetc(archProductos);
            if(c!=' ') break;
        }
        while(1){
            c = fgetc(archProductos);
            if(c==' ') break;
        }
        fscanf(archProductos,"%lf", &precios[i]);
        i++;
    }
    *cantProductos = i;
    fclose(archProductos);
}

void guardarTiendas(int * codTienda, int * codPostal, int *cantTiendas){
     FILE * archTiendas;
  
    archTiendas = fopen("Tiendas.txt", "r");
    if(archTiendas == NULL){
        printf("Archivo de tiendas vacio");
        exit(1);
    }
    int i=0;
    char c;
    while(1){
        fscanf(archTiendas,"%d", &codTienda[i]);
        if (feof(archTiendas)) break;
        while(1){
            c = fgetc(archTiendas);
            if(c!=' ') break;
        }
        while(1){
            c = fgetc(archTiendas);
            if(c==' ') break;
        }
        fscanf(archTiendas,"%d", &codPostal[i]);
        i++;
    }
    *cantTiendas = i;
    fclose(archTiendas);
 }

void cambiar(int * arreglo, int i, int j){
    
    int aux;
    aux = arreglo[i];
    arreglo[i] = arreglo[j];
    arreglo[j] = aux;
}

void  ordenarTiendas(int * codTienda, int * codPostal, int cantTiendas){
    
    for(int i = 0; i<cantTiendas-1; i++)
        for(int j = i+1; j< cantTiendas ; j++){
            if(codTienda[i]>codTienda[j]){
                cambiar(codTienda, i, j);
                cambiar(codPostal, i, j);           
        }
    }
}

int BuscarPrecio(int codProd, int * codigosProd, int cantProductos){
    int indice = -1;
    for (int i = 0; i<cantProductos; i++){
        if (codProd == codigosProd[i]){
            indice = i;
            break;
        }
    }  
    return indice;
}


void leerArchivoCompras(FILE * archCompras, FILE * reporte, int codigoTienda, 
                        int codigoPostal, int * codigosProd, double * precios, 
                        int cantProductos, int * cantidadProd, double * totalProd){
    
    char c;
    int codParte1, codParte2, dni, codTienda, dia, mes, anno;
    int contadorProductos = 0;
    int codProd, cantidad, indice, primero;
    double precioU, subTotal, total = 0;
    //Voy al inicio del archivo, se va leer por cada tienda
    primero = 0;
    rewind(archCompras);
    while(1){
        fscanf(archCompras,"%d-%d", &codParte1, &codParte2);
        if (feof(archCompras)) break;
        fscanf(archCompras,"%d %c", &dni, &c);
        /*con el dato de c evaluo que caracter leyo*/
        /*si leo D debo continuar hasta el siguiente o el cambio de línea*/
        if(c=='D'){
            while(1){
                c = fgetc(archCompras);
                if(c=='\n') break;
            }
        }
        /*si leo T debo comparar las tiendas*/
        if(c=='T'){
            fscanf(archCompras,"-%d %d/%d/%d", &codTienda, &dia, &mes, &anno);
            /*si las tiendas son iguales debo leer los códigos y cantidad*/
            if (codigoTienda == codTienda){
                while(1){
                    fscanf(archCompras,"%d/%d", &codProd, &cantidad);
                     /*realizo una busqueda en los arreglos y devuelvo el indice*/
                    indice = BuscarPrecio(codProd, codigosProd, cantProductos);
                    if (indice == -1)
                        printf("No encontro nada"); /*no lo encontro*/
                    else{
                        primero++;
                        if (primero == 1){
                            linea(reporte, '=', 80);
                            fprintf(reporte, "\nDestino: Tienda %d ", codigoTienda);
                            fprintf(reporte, " Codigo Postal: %d\n", codigoPostal);
                            fprintf(reporte, " %s %15s %15s %15s %15s %13s\n", "FECHA", "PRODUCTO", 
                                    "CANTIDAD", "PRECIO UNITARIO", "SUB TOTAL", "CLIENTE");
                        }
                        /*en este caso, calculo y muestro los resultados*/
                        contadorProductos++;
                        precioU = precios[indice];
                        subTotal = cantidad * precioU;
                        fprintf(reporte, "%02d/%02d/%d %10d  %10d %15.3lf "
                                "%19.3lf %15.08d\n", dia, mes, anno, codProd, 
                                cantidad, precioU, subTotal, dni);
                        /*sub totales*/
                        total = total + subTotal;
                        cantidadProd[indice] += cantidad;
                        totalProd[indice] += subTotal;
                    }
                    fscanf(archCompras,"%c", &c);
                        if(c=='\n') break; 
                }

            }
            else{
                while(1){
                    c = fgetc(archCompras);
                    if(c=='\n') break;
                }
            }
        }    
    }
    /*Resumen de tienda*/
    if(primero>0){
        linea(reporte, '-', 80);
        fprintf(reporte, "\nRESUMEN DE TIENDA\n");
        fprintf(reporte, "CANTIDAD DE PRODCUTOS A ENTREGAR: %d\n", contadorProductos);
        fprintf(reporte, "MONTO DE RPODUCTOS A ENTREGAR: S/. %.3lf\n", total);
        
    }
    
}

void generarReporte(FILE * reporte, FILE * archCompras, int * codTienda, 
                    int * codPostal, int * codProd, double * precio, 
                    int cantProductos, int cantTiendas, int * cantidad,
                    double * total){
     
    char c;
    int i;
    fprintf(reporte, "%30s","\nENTREGA DE PRODUCTOS\n");
    for (i = 0; i< cantTiendas; i++){
          
        leerArchivoCompras(archCompras, reporte, codTienda[i], codPostal[i],
                           codProd, precio, cantProductos, cantidad, total);
    }
 }

