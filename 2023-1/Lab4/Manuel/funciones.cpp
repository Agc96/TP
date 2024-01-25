/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/cppFiles/file.cc to edit this template
 */

#include <iostream>
#include <fstream>
#include <iomanip>
using namespace std;

#include "funciones.h"


void leerRangoFechas(int &fechaIni, int &fechaFin){
    int dd,mm,aa;
    char c;
    
    
    while(true){
        cout<<"Ingrese la fecha inicio del rango para considerar en el reporte de ventas: (dd/mm/aa) ";
        cin>>dd>>c>>mm>>c>>aa;
        aa=aa+2000;
        fechaIni=aa*10000+mm*100+dd;
        cout<<"Ingrese la fecha fin del rango para considerar en el reporte de ventas: (dd/mm/aa) ";
        cin>>dd>>c>>mm>>c>>aa;
        aa=aa+2000;
        fechaFin=aa*10000+mm*100+dd;

        if (fechaIni>fechaFin){
            cout<<"El rango de fechas ingresado es inválido."<<endl<<endl;
        }
        else{
            //cout<<fechaIni<<" "<<fechaFin<<endl;
            break;
        } 
    }    
}

void leerDatosLibro(int* arrCodLibro, double* arrPrecioLibro, int &cantLibros){
    ifstream archLibros(ARCHIVO_LIBROS, iostream::in);
    int codLibro;
    double precioLibro; 
    char c;
    
    
    if (not archLibros.is_open()){
        cout<<"No se pudo abrir el archivo "<<ARCHIVO_LIBROS<<endl;
        exit(1);
    }
    
    while(true){
        archLibros>>codLibro;
        
        if (archLibros.eof()){
            break;
        }
        archLibros>>ws;
        //Limpiar nombre
        do{
            c=archLibros.get();
        }while(c!=' ');
        
        archLibros>>precioLibro;
        
        arrCodLibro[cantLibros]=codLibro;
        arrPrecioLibro[cantLibros]=precioLibro;
        cantLibros++;
    }
    
}

void leerRegistrosAutores(int* arrCodAutor, int* arrAutorCodLibro, double *arrRegaliaAutorLibro, int&cantRegAutores){
    ifstream archAutores(ARCHIVO_AUTORES, iostream::in);
    int codAutor, codLibro;
    double porcRegalia;
    
    if (not archAutores.is_open()){
        cout<<"No se pudo abrir el archivo "<<ARCHIVO_AUTORES<<endl;
        exit(1);
    }
    
    while(true){
        archAutores>>codAutor;
        
        if(archAutores.eof()){
            break;
        }
        
        archAutores>>codLibro>>porcRegalia;
        
        arrCodAutor[cantRegAutores]=codAutor;
        arrAutorCodLibro[cantRegAutores]=codLibro;
        arrRegaliaAutorLibro[cantRegAutores]=porcRegalia;
        
        cantRegAutores++;
          
    }
    
}

int buscarEntero(int* arreglo, int cant, int identificador){
    for (int i=0; i<cant; i++){
        if (arreglo[i]==identificador){
            return i;
        }
    }
    return ERROR;
}

void leerVentas(int* arrCodLibro, double* arrPrecioLibro, int *arrCantidadLibro, double *arrRecaudadoLibro,
        int cantLibros, int fechaIni, int fechaFin, double* arrRegaliaAutorLibroRecaudado, double* arrRegaliaAutorLibro, int* arrCodAutor, int* arrAutorcodLibro, int cantAutores){
    int dd, mm, aaaa, pos;
    char c;
    
    int fechaVenta, codLibro, cantVenta;
    
    ifstream archVentas(ARCHIVO_VENTAS, iostream::in);
    
    if (not archVentas.is_open()){
        cout<<"No se pudo abrir el archivo "<<ARCHIVO_VENTAS<<endl;
        exit(1);
    }
    
    while(true){
        archVentas>>dd;
        if (archVentas.eof()){
            break;
        }
        archVentas>>c>>mm>>c>>aaaa;
        
        fechaVenta=aaaa*10000+mm*100+dd;
        if ((fechaVenta>=fechaIni) and (fechaVenta<=fechaFin)){
            while(true){
                archVentas>>codLibro>>cantVenta;
                pos=buscarEntero(arrCodLibro, cantLibros, codLibro);
                if (pos!=ERROR){
                    //Actualizar Libro
                    arrCantidadLibro[pos]+=cantVenta;
                    arrRecaudadoLibro[pos]+=cantVenta*arrPrecioLibro[pos];
                    //Actualizar autores del libro
                    for(int i=0; i<=cantAutores; i++){
                        if (arrAutorcodLibro[i]==codLibro){
                            arrRegaliaAutorLibroRecaudado[i]+=cantVenta*arrPrecioLibro[pos]*arrRegaliaAutorLibro[i]/100;
                        }
                    }

                }
                if(archVentas.get()=='\n') break;
            }
        }
        else{
            //Ignorar linea
            while(archVentas.get()!='\n');
        }
    }
    
}



void imprimirLinea(ofstream &arch, char c){
    for (int i=0;i<CANT_LINEAS;i++){
        arch.put(c);
    }
    arch<<endl;
}

void mostrarReporte(int* arrCodLibro, int* arrCodAutor, int* arrAutorCodLibro, 
        int* arrCantidadLibro, double* arrRegaliaAutorLibro, double* arrRecaudadoLibro,
        double *arrPrecioLibro,
        int cantLibros, int cantRegAutores, int fechaIni, int fechaFin,
        double* arrRegaliaAutorLibroRecaudado){
    
    ofstream archReporte(ARCHIVO_REPORTE, iostream::out);
    
    if (not archReporte.is_open()){
        cout<<"No se pudo abrir el archivo "<<ARCHIVO_REPORTE<<endl;
        exit(1);
    }
    
    archReporte<<setw(50)<<" "<<"LIBRERIA LOS LIBROS_TP"<<endl;
    archReporte<<setw(35)<<" "<<"VENTA DE LIBROS EN EL RANGO ";
    archReporte.fill('0');
    archReporte<<setw(2)<<fechaIni%100<<"/"<<setw(2)<<(fechaIni%10000)/100<<'/'<<fechaIni/10000<<" AL ";
    archReporte<<setw(2)<<fechaFin%100<<"/"<<setw(2)<<(fechaFin%10000)/100<<'/'<<fechaFin/10000<<endl;
    
    for(int i=0; i<cantLibros; i++){
        imprimirLinea(archReporte,'=');
        archReporte<<fixed;
        archReporte.precision(2);
        archReporte.fill('0');
        archReporte<<setw(2)<<i+1;
        archReporte.fill(' ');
        archReporte.put(')');
        archReporte<<setw(5)<<" LIBRO"<<setw(15)<<"CANTIDAD"<<setw(10)<<"PRECIO"<<setw(20)<<"MONTO RECAUDADO"<<endl;
        archReporte<<setw(4)<<" "<<setw(5)<<arrCodLibro[i]<<setw(9)<<arrCantidadLibro[i]<<setw(12)<<arrPrecioLibro[i]<<setw(18)<<arrRecaudadoLibro[i]<<endl;
        archReporte<<endl;
        archReporte<<setw(4)<<" "<<"REGALIAS PARA LOS AUTORES"<<endl;
        archReporte<<setw(4)<<" "<<"AUTOR"<<setw(25)<<"PORCENTAJE A RECIBIR"<<setw(20)<<"MONTO A RECIBIR"<<endl;
        for (int j=0; j<=cantRegAutores; j++){
            if (arrAutorCodLibro[j]==arrCodLibro[i]){
                //Mostrar autor
                archReporte<<setw(4)<<" "<<arrCodAutor[j]<<setw(17)<<arrRegaliaAutorLibro[j]<<"%"<<setw(22)<<arrRegaliaAutorLibroRecaudado[j]<<endl;
            }
        }
    }
    
}