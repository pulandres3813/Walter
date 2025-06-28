#include "funciones.h"
#include <stdio.h>

int main() {
    Cliente clientes[MAX_CLIENTES];
    Venta ventas[MAX_VENTAS];
    int numClientes = 0, numVentas = 0;
    extern Producto productos[];
    extern int numProductos;
    int opcion;
    // Cargar datos binarios
    cargarProductos(productos, &numProductos);
    cargarClientes(clientes, &numClientes);
    cargarVentas(ventas, &numVentas);
    do {
        printf("\n--- Menu Tienda de Repuestos ---\n");
        printf("1. Registrar venta\n");
        printf("2. Mostrar productos mas vendidos\n");
        printf("3. Mostrar ventas\n");
        printf("4. Mostrar clientes\n");
        printf("5. Mostrar estadisticas\n");
        printf("6. Reabastecer stock\n");
        printf("0. Salir\n");
        printf("Seleccione una opcion: ");
        scanf("%d", &opcion);
        if (opcion != 1 && opcion != 6 && opcion != 0 && numVentas == 0) {
            printf("Primero se debe registrar una venta.\n");
            continue;
        }
        switch(opcion) {
            case 1:
                registrarVenta(ventas, &numVentas, productos, numProductos, clientes, &numClientes);
                guardarVentas(ventas, numVentas);
                guardarVentasTxt(ventas, numVentas);
                guardarClientes(clientes, numClientes);
                guardarClientesTxt(clientes, numClientes);
                guardarProductos(productos, numProductos);
                guardarProductosTxt(productos, numProductos);
                break;
            case 2:
                mostrarProductosMasVendidos(productos, numProductos);
                break;
            case 3:
                mostrarVentas(ventas, numVentas);
                break;
            case 4:
                mostrarClientes(clientes, numClientes);
                break;
            case 5:
                mostrarEstadisticas(productos, numProductos, ventas, numVentas, clientes, numClientes);
                break;
            case 6:
                reabastecerStock(productos, numProductos);
                guardarProductos(productos, numProductos);
                guardarProductosTxt(productos, numProductos);
                break;
            case 0:
                printf("Saliendo...\n");
                break;
            default:
                printf("Opcion invalida.\n");
        }
    } while(opcion != 0);
    return 0;
}