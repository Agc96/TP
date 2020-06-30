#include <stdio.h>
#define MAX_LINEA 80

void leerDatos(int* distritoReporte, int* anhoReporte, int* mes1, int* mes2, int* mes3) {
    int resultado, dni, dia, mes, anio, fecha, hh, mm, ss, hora, distrito, cantidad;
    double monto;
    /* Leer cabecera del archivo */
    scanf("%d %d %d %d %d", distritoReporte, anhoReporte, mes1, mes2, mes3);
    /* Leer lista de pagos */
    while (1) {
        /* Leer el DNI */
        resultado = scanf("%d", &dni);
        if (resultado < 1) break;
        /* Leer la fecha y hora */
        scanf("%d/%d/%d %d:%d:%d", &dd, &mm, &anho, &hora, &minuto, &segundo);
        fecha = crearFecha(dd, mm, aaaa);
        hora = crearHora(hora, minuto, segundo);
        /* Leer el resto de datos */
        scanf("%d %lf %d", &distrito, &monto, &cantidad);
        /* TODO: BORRAR ESTO */
        printf("[TEST] %d %d %d %d %lf %d\n", dni, fecha, hora, distrito, monto, cantidad);
    }
}

void imprimirDatos(int distrito, int anho, int mes1, int mes2, int mes3) {
    /* Imprimir cabecera */
    printf("PAGOS AL PROVEEDOR DE ENTREGA A DOMICILIO TP2020\n");
    printf("Distrito: %d\n", distrito);
    printf("Año: %d\n", anho);
    repetir('=', MAX_LINEA, 1);
    /* Imprimir datos de cada mes */
    impresionMes(mes1, mes1maniana, mes1tarde);
    impresionMes(mes2, mes2maniana, mes2tarde);
    impresionMes(mes3, mes3maniana, mes3tarde);
    /* Imprimir estadísticas */
    printf("Mes con mayor pago al proveedor: %d - S/ %4.2lf\n", 0, 0.0);
    printf("Mes con menor pago al proveedor: %d - S/ %4.2lf\n", 0, 0.0);
}

void imprimirMes(int mes, double montoManhana, double montoTarde) {
    printf("Mes: %02d\n\n", mes);
    printf("Por la entrega en la mañana: S/ %4.2lf\n", montoManhana);
    printf("Por la entrega por la tarde: S/ %4.2lf\n", montoTarde);
    printf("Total por la entrega: S/ %4.2lf\n", montoManhana + montoTarde);
    repetir('=', MAX_LINEA, 1);
}

int main() {
    /* Declaración de variables */
    int distrito, anho, mes1, mes2, mes3;
    /* Lectura de datos */
    leerDatos(&distrito, &anho, &mes1, &mes1maniana, &mes1tarde, &mes2, &mes3);
    /* Impresión de datos */
    impresionDatos(distrito, anho, mes1, mes2, mes3);
    return 0;
}
