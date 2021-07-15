/* 
 * File:   funciones.c
 * Author:  Código: -----------
 *          Nombre: Silvia Vargas Cáceres
 *          Silvia
 *
 * Created on 21 de mayo de 2021, 09:48 PM
 */
#include <stdio.h>
#include <stdlib.h>
#include "funciones.h"

#define NO_ENCONTRADO -1
#define TAMANHO_LINEA 80

void cargarProductos(int *arrCodProducto,double *arrPreProducto,int *cantProductos){
    FILE *archProductos;
    int codProd;
    double precioProd;
    char c;
    archProductos=fopen("ListaDePrecios.txt","r");
    if (archProductos==NULL){
        printf("No se puede abrir el archivo ListaDePrecios.txt\n");
        exit(1);
    }
    *cantProductos=0;
    while(c=fgetc(archProductos)!='\n');
    while (1){
        fscanf(archProductos,"%d",&codProd);
        if (feof(archProductos)) break;
        while(c=fgetc(archProductos)!=']');
        fscanf(archProductos,"%lf",&precioProd);        
        arrCodProducto[*cantProductos]=codProd;
        arrPreProducto[*cantProductos]=precioProd;
        (*cantProductos)++;
    }
    fclose(archProductos);
}

void cargarProdAlmacenados(int *arrCodProducto,double *arrPreProducto,
        int cantProductos, double *arrCantProdAlm, double *arrSubTotalProd){
    FILE *archProdAlm;
    int codProd,id;
    double cantidad;
    archProdAlm=fopen("productosAlmacenados.txt","r");
    if (archProdAlm==NULL){
        printf("No se puede abrir el archivo productosAlmacenados.txt\n");
        exit(1);
    }
    while(1){
        fscanf(archProdAlm,"%d",&codProd);
        if (feof(archProdAlm)) break;
        fscanf(archProdAlm,"%lf",&cantidad);
        id=buscar(arrCodProducto,cantProductos,codProd);
        if (id!=NO_ENCONTRADO){
            arrCantProdAlm[id]=cantidad;
            arrSubTotalProd[id]=arrCantProdAlm[id]*arrPreProducto[id];
        }
        else
            printf("El codigo %d no se encuentra en listadeprecios.txt\n",codProd);
    }    
}

int buscar(int *arreglo,int cantidad, int codigo){
    for (int i=0;i<cantidad;i++)
        if (arreglo[i]==codigo)
            return i;
    return NO_ENCONTRADO;    
}


void cargarPlatosPreparar(int *arrCodPlato,int *arrCantPlato,int *cantPlatos){
    FILE *archPlatosPreparar;
    int codPlato,cantidad;
    char c;
    archPlatosPreparar=fopen("PlatosAPreparar.txt","r");
    if (archPlatosPreparar==NULL){
        printf("No se puede abrir el archivo PlatosAPreparar.txt\n");
        exit(1);
    }
    *cantPlatos=0;
    while (1){
        fscanf(archPlatosPreparar,"%d",&codPlato);
        if (feof(archPlatosPreparar)) break;
        fscanf(archPlatosPreparar,"%d",&cantidad);        
        arrCodPlato[*cantPlatos]=codPlato;
        arrCantPlato[*cantPlatos]=cantidad;
        (*cantPlatos)++;
    }
    fclose(archPlatosPreparar);
}

void cargarPlatosPrecios(int *arrCodPlato,int *arrCantPlato,int cantPlatos,
        int *arrCodProducto,double *arrPreProducto,int cantProductos,
        double *arrPrePlato){
    FILE *archPlatos;
    int codPlato,idPlato,idProducto,codProd;
    double cantidad;
    char c;
    archPlatos=fopen("Platos.txt","r");
    if (archPlatos==NULL){
        printf("No se puede abrir el archivo Platos.txt\n");
        exit(1);
    }
    while (1){
        fscanf(archPlatos,"%d",&codPlato);
        if (feof(archPlatos)) break;
        idPlato=buscar(arrCodPlato,cantPlatos,codPlato);
        if (idPlato!=NO_ENCONTRADO){
            /*descartar nombre*/
            while(fgetc(archPlatos)!=')');
            while (1){
                fscanf(archPlatos,"%d %lf",&codProd,&cantidad);
                idProducto=buscar(arrCodProducto,cantProductos,codProd);
                if (idProducto!=NO_ENCONTRADO)
                    arrPrePlato[idPlato]+=arrPreProducto[idProducto]*cantidad;
                else
                    printf("El producto %d del plato %d no se encuentra\n",
                            codProd,codPlato);
                if (fgetc(archPlatos)=='\n') break;
            }
        }
        else{
            printf("El plato %d no se encuentra en platosapreparar.txt\n",codPlato);
            /*descartar la linea*/
            while(fgetc(archPlatos)!='\n');
        }
    }
    fclose(archPlatos);
}

void actualizarSubTotalPlatos(int *arrCodPlato,int *arrCantPlato,int cantPlatos,
        double *arrPrePlato,double *arrSubTotalPlato){
    for (int i=0;i<cantPlatos;i++)
        arrSubTotalPlato[i]=arrPrePlato[i]*arrCantPlato[i];
}

void ordenarSubTotalProducto(int *arrCodProducto,double *arrPreProducto,
        double *arrCantProdAlm,double *arrSubTotalProd,int cantProductos){
    for (int i=0;i<cantProductos-1;i++)
        for (int j=i+1;j<cantProductos;j++){
            if (arrSubTotalProd[i]<arrSubTotalProd[j]){
                cambiarInt(arrCodProducto,i,j);
                cambiarDouble(arrPreProducto,i,j);
                cambiarDouble(arrCantProdAlm,i,j);
                cambiarDouble(arrSubTotalProd,i,j);
            }
        }
}

void ordenarSubTotalPlato(int *arrCodPlato,double *arrPrePlato,
        int *arrCantPlato,double *arrSubTotalPlato,int cantPlatos){
    for (int i=0;i<cantPlatos-1;i++)
        for (int j=i+1;j<cantPlatos;j++){
            if (arrCantPlato[i]>arrCantPlato[j]
                ||  (arrCantPlato[i]==arrCantPlato[j] && arrSubTotalPlato[i]<arrSubTotalPlato[j])){
                cambiarInt(arrCodPlato,i,j);
                cambiarInt(arrCantPlato,i,j);
                cambiarDouble(arrPrePlato,i,j);
                cambiarDouble(arrSubTotalPlato,i,j);
            }
        }
}

void cambiarInt(int *arreglo,int i,int j){
    int aux=arreglo[i];
    arreglo[i]=arreglo[j];
    arreglo[j]=aux;
}

void cambiarDouble(double *arreglo,int i,int j){
    double aux=arreglo[i];
    arreglo[i]=arreglo[j];
    arreglo[j]=aux;
}

void generarReporte(int *arrCodProducto,double *arrPreProducto,
        double *arrCantProdAlm,double *arrSubTotalProd,int cantProductos,
        int *arrCodPlato,int *arrCantPlato,double *arrPrePlato,
        double *arrSubTotalPlato,int cantPlatos){
    FILE *archReporte;
    int cont=1;
    double total=0;
    archReporte=fopen("ReportedePerdidas.txt","w");
    if (archReporte==NULL){
        printf("No se puede abrir el archivo ReportedePerdidas.txt\n");
        exit(1);
    }
    imprimirLinea(archReporte,'=',TAMANHO_LINEA);
    fprintf(archReporte,"PRODUCTOS PERDIDOS\n");
    imprimirLinea(archReporte,'-',TAMANHO_LINEA);
    fprintf(archReporte,"%10s %16s %25s %18s\n","Producto","Cantidad", "Precio Unitario(S/.)",
            "Sub-total(S/.)");
    for (int i=0;i<cantProductos;i++){
        if (arrCantProdAlm[i]>0){
            fprintf(archReporte,"%3d) %05d %12.2lf %20.2lf %20.2lf\n",cont,arrCodProducto[i],
                arrCantProdAlm[i],arrPreProducto[i],arrSubTotalProd[i]);
            total+=arrSubTotalProd[i];
            cont++;
        }
    }
    imprimirLinea(archReporte,'-',TAMANHO_LINEA);
    fprintf(archReporte,"Costo total de productos perdidos: S/. %12.2lf\n",total);
    imprimirLinea(archReporte,'=',TAMANHO_LINEA);
    
    imprimirLinea(archReporte,'=',TAMANHO_LINEA);
    fprintf(archReporte,"PLATOS QUE NO SE PODRAN PREPARAR\n");
    imprimirLinea(archReporte,'-',TAMANHO_LINEA);
    fprintf(archReporte,"%10s %16s %25s %18s\n","Plato","Cantidad", "Precio Productos(S/.)",
            "Sub-total(S/.)");
    total=0;
    cont=1;
    for (int i=0;i<cantPlatos;i++){
        fprintf(archReporte,"%3d) %05d %10d %20.2lf %25.2lf\n",cont,arrCodPlato[i],
                arrCantPlato[i],arrPrePlato[i],arrSubTotalPlato[i]);
        total+=arrSubTotalPlato[i];
        cont++;
    }
    imprimirLinea(archReporte,'-',TAMANHO_LINEA);
    fprintf(archReporte,"Costo total de productos perdidos: S/. %12.2lf\n",total);
    imprimirLinea(archReporte,'=',TAMANHO_LINEA);
    fclose(archReporte);
}

void imprimirLinea(FILE *archivo,char simbolo,int cantidad){
    for (int i=0;i<cantidad;i++)
        fputc(simbolo,archivo);
    fputc('\n',archivo);
}