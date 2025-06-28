//Una tienda de repuestos automotrices tiene problemas para poder obtener estadísticas de sus ventas como por 
//ejemplo los productos mas vendidos, las ventas que tiene, los clientes, se debe plantear una propuesta de solución

#include <stdio.h>
#include <string.h>
#define MAX_PRODUCTOS 100
#define MAX_CLIENTES 100
#define MAX_VENTAS 200

// Estructuras

typedef struct {
    int id;
    char nombre[50];
    float precio;
    int stock;
    int vendidos;
} Producto;

typedef struct {
    int id;
    char nombre[31]; // Hasta 30 caracteres + null
    char cedula[16]; // Cedula hasta 15 caracteres
    char telefono[15];
} Cliente;

typedef struct {
    int idVenta;
    int idProducto;
    int idCliente;
    int cantidad;
    float total;
} Venta;

// Funciones principales
void registrarVenta(Venta ventas[], int *numVentas, Producto productos[], int numProductos, Cliente clientes[], int *numClientes);
void mostrarProductosMasVendidos(Producto productos[], int numProductos);
void mostrarVentas(Venta ventas[], int numVentas);
void mostrarClientes(Cliente clientes[], int numClientes);
void buscarProductoPorNombre(Producto productos[], int numProductos, const char* nombre);
void buscarProductoPorID(Producto productos[], int numProductos, int id);
void mostrarClienteQueMasCompro(Venta ventas[], int numVentas, Cliente clientes[], int numClientes);
void mostrarTotalIngresos(Venta ventas[], int numVentas);
void mostrarProductosBajoStock(Producto productos[], int numProductos, int umbral);
void mostrarNumeroTotalVentas(int numVentas);
void mostrarEstadisticas(Producto productos[], int numProductos, Venta ventas[], int numVentas, Cliente clientes[], int numClientes);
void reabastecerStock(Producto productos[], int numProductos);
void guardarProductos(Producto productos[], int numProductos);
void cargarProductos(Producto productos[], int *numProductos);
void guardarClientes(Cliente clientes[], int numClientes);
void cargarClientes(Cliente clientes[], int *numClientes);
void guardarVentas(Venta ventas[], int numVentas);
void cargarVentas(Venta ventas[], int *numVentas);
void guardarProductosTxt(Producto productos[], int numProductos);
void guardarClientesTxt(Cliente clientes[], int numClientes);
void guardarVentasTxt(Venta ventas[], int numVentas);

// Lista fija de productos
Producto productos[MAX_PRODUCTOS] = {
    {1, "Filtro_de_aceite", 25.0, 20, 0},
    {2, "Pastillas_de_freno", 40.0, 15, 0},
    {3, "Bujias", 10.0, 30, 0},
    {4, "Amortiguadores", 80.0, 10, 0},
    {5, "Radiadores", 120.0, 8, 0},
    {6, "Baterias", 150.0, 12, 0},
    {7, "Refrigerante", 18.0, 25, 0}
};
int numProductos = 7;

int esNumeroValido(const char* str, int longitud) {
    if (strlen(str) != longitud) return 0;
    for (int i = 0; i < longitud; i++) {
        if (str[i] < '0' || str[i] > '9') return 0;
    }
    return 1;
}

void reabastecerStock(Producto productos[], int numProductos) {
    int idProducto, cantidad;
    printf("\nLista de productos:\n");
    for (int i = 0; i < numProductos; i++) {
        printf("%d. %s | Stock actual: %d\n", productos[i].id, productos[i].nombre, productos[i].stock);
    }
    printf("Ingrese ID del producto a reabastecer: ");
    scanf("%d", &idProducto);
    if (idProducto > 0 && idProducto <= numProductos) {
        printf("Ingrese cantidad a agregar: ");
        scanf("%d", &cantidad);
        if (cantidad > 0) {
            productos[idProducto-1].stock += cantidad;
            printf("Stock actualizado! Nuevo stock de %s: %d\n", productos[idProducto-1].nombre, productos[idProducto-1].stock);
        } else {
            printf("Cantidad invalida.\n");
        }
    } else {
        printf("ID de producto invalido.\n");
    }
}

void registrarVenta(Venta ventas[], int *numVentas, Producto productos[], int numProductos, Cliente clientes[], int *numClientes) {
    int idProducto, cantidad;
    char cedula[16], telefono[15];
    printf("\nLista de productos disponibles:\n");
    for (int i = 0; i < numProductos; i++) {
        printf("%d. %s | Precio: %.2f | Stock: %d\n", productos[i].id, productos[i].nombre, productos[i].precio, productos[i].stock);
    }
    do {
        printf("Ingrese ID del producto a comprar: ");
        scanf("%d", &idProducto);
        if (idProducto < 1 || idProducto > numProductos) {
            printf("ID de producto invalido.\n");
        }
    } while (idProducto < 1 || idProducto > numProductos);
    printf("Ingrese cantidad: ");
    scanf("%d", &cantidad);
    if (cantidad <= productos[idProducto-1].stock) {
        // Registrar datos del cliente SOLO si la venta es valida
        Cliente nuevoCliente;
        printf("Ingrese nombre del cliente: ");
        getchar();
        fgets(nuevoCliente.nombre, 31, stdin);
        nuevoCliente.nombre[strcspn(nuevoCliente.nombre, "\n")] = 0;
        do {
            printf("Ingrese cedula del cliente (10 digitos): ");
            fgets(cedula, 16, stdin);
            cedula[strcspn(cedula, "\n")] = 0;
            if (!esNumeroValido(cedula, 10)) printf("Cedula invalida.\n");
        } while (!esNumeroValido(cedula, 10));
        strcpy(nuevoCliente.cedula, cedula);
        do {
            printf("Ingrese telefono del cliente (10 digitos): ");
            fgets(telefono, 15, stdin);
            telefono[strcspn(telefono, "\n")] = 0;
            if (!esNumeroValido(telefono, 10)) printf("Telefono invalido.\n");
        } while (!esNumeroValido(telefono, 10));
        strcpy(nuevoCliente.telefono, telefono);
        nuevoCliente.id = *numClientes + 1;
        clientes[*numClientes] = nuevoCliente;
        (*numClientes)++;
        guardarClientes(clientes, *numClientes);
        // Registrar venta
        ventas[*numVentas].idVenta = *numVentas + 1;
        ventas[*numVentas].idProducto = idProducto;
        ventas[*numVentas].idCliente = nuevoCliente.id;
        ventas[*numVentas].cantidad = cantidad;
        ventas[*numVentas].total = productos[idProducto-1].precio * cantidad;
        productos[idProducto-1].stock -= cantidad;
        productos[idProducto-1].vendidos += cantidad;
        (*numVentas)++;
        guardarVentas(ventas, *numVentas);
        guardarProductos(productos, numProductos);
        guardarProductosTxt(productos, numProductos);
        printf("Venta registrada y cliente registrado!\n");
    } else {
        printf("Datos incorrectos o stock insuficiente.\n");
    }
}

void mostrarProductosMasVendidos(Producto productos[], int numProductos) {
    printf("\n--- Productos mas vendidos ---\n");
    for (int i = 0; i < numProductos; i++) {
        printf("ID: %d | %s | Vendidos: %d\n", productos[i].id, productos[i].nombre, productos[i].vendidos);
    }
}

void mostrarVentas(Venta ventas[], int numVentas) {
    printf("\n--- Ventas realizadas ---\n");
    for (int i = 0; i < numVentas; i++) {
        printf("Venta ID: %d | Producto ID: %d | Cliente ID: %d | Cantidad: %d | Total: %.2f\n",
            ventas[i].idVenta, ventas[i].idProducto, ventas[i].idCliente, ventas[i].cantidad, ventas[i].total);
    }
}

// NOTA: Se corrigieron las funciones para que siempre carguen los datos actualizados desde los archivos binarios antes de mostrar, buscar o calcular estadísticas.

void mostrarClientes(Cliente clientes[], int numClientes) {
    cargarClientes(clientes, &numClientes);
    printf("\n--- Clientes registrados ---\n");
    for (int i = 0; i < numClientes; i++) {
        printf("ID: %d | %s | Cedula: %s | Telefono: %s\n", clientes[i].id, clientes[i].nombre, clientes[i].cedula, clientes[i].telefono);
    }
}

void buscarProductoPorNombre(Producto productos[], int numProductos, const char* nombre) {
    cargarProductos(productos, &numProductos);
    int encontrado = 0;
    for (int i = 0; i < numProductos; i++) {
        if (strcmp(productos[i].nombre, nombre) == 0) {
            printf("ID: %d | %s | Precio: %.2f | Stock: %d\n", productos[i].id, productos[i].nombre, productos[i].precio, productos[i].stock);
            encontrado = 1;
        }
    }
    if (!encontrado) printf("Producto no encontrado.\n");
}

void buscarProductoPorID(Producto productos[], int numProductos, int id) {
    cargarProductos(productos, &numProductos);
    for (int i = 0; i < numProductos; i++) {
        if (productos[i].id == id) {
            printf("ID: %d | %s | Precio: %.2f | Stock: %d\n", productos[i].id, productos[i].nombre, productos[i].precio, productos[i].stock);
            return;
        }
    }
    printf("Producto no encontrado.\n");
}

void mostrarClienteQueMasCompro(Venta ventas[], int numVentas, Cliente clientes[], int numClientes) {
    cargarVentas(ventas, &numVentas);
    cargarClientes(clientes, &numClientes);
    int compras[MAX_CLIENTES] = {0};
    for (int i = 0; i < numVentas; i++) {
        compras[ventas[i].idCliente - 1] += ventas[i].cantidad;
    }
    int max = 0, idx = -1;
    for (int i = 0; i < numClientes; i++) {
        if (compras[i] > max) {
            max = compras[i];
            idx = i;
        }
    }
    if (idx != -1) {
        printf("Cliente que mas compro: %s (ID: %d, Telefono: %s) con %d productos.\n", clientes[idx].nombre, clientes[idx].id, clientes[idx].telefono, max);
    } else {
        printf("No hay ventas registradas.\n");
    }
}

void mostrarTotalIngresos(Venta ventas[], int numVentas) {
    float total = 0;
    for (int i = 0; i < numVentas; i++) {
        total += ventas[i].total;
    }
    printf("Total de ingresos: %.2f\n", total);
}

void mostrarProductosBajoStock(Producto productos[], int numProductos, int umbral) {
    printf("Productos con stock menor o igual a %d:\n", umbral);
    for (int i = 0; i < numProductos; i++) {
        if (productos[i].stock <= umbral) {
            printf("ID: %d | %s | Stock: %d\n", productos[i].id, productos[i].nombre, productos[i].stock);
        }
    }
}

void mostrarNumeroTotalVentas(int numVentas) {
    printf("Numero total de ventas realizadas: %d\n", numVentas);
}

void mostrarEstadisticas(Producto productos[], int numProductos, Venta ventas[], int numVentas, Cliente clientes[], int numClientes) {
    float totalIngresos = 0;
    int totalProductosVendidos = 0;
    int productoMasVendido = 0, maxVendidos = 0;
    int clienteMasComprador = 0, maxCompras = 0;
    int comprasPorCliente[MAX_CLIENTES] = {0};

    // Calcular ingresos y productos vendidos
    for (int i = 0; i < numVentas; i++) {
        totalIngresos += ventas[i].total;
        totalProductosVendidos += ventas[i].cantidad;
        comprasPorCliente[ventas[i].idCliente - 1] += ventas[i].cantidad;
    }
    // Producto mas vendido
    for (int i = 0; i < numProductos; i++) {
        if (productos[i].vendidos > maxVendidos) {
            maxVendidos = productos[i].vendidos;
            productoMasVendido = i;
        }
    }
    // Cliente que mas compro
    for (int i = 0; i < numClientes; i++) {
        if (comprasPorCliente[i] > maxCompras) {
            maxCompras = comprasPorCliente[i];
            clienteMasComprador = i;
        }
    }
    printf("\n--- Estadisticas de Ventas ---\n");
    printf("Total de ingresos: %.2f\n", totalIngresos);
    printf("Total de productos vendidos: %d\n", totalProductosVendidos);
    printf("Producto mas vendido: %s (%d unidades)\n", productos[productoMasVendido].nombre, productos[productoMasVendido].vendidos);
    if (numClientes > 0 && maxCompras > 0) {
        printf("Cliente que mas compro: %s (Cedula: %s, %d productos)\n", clientes[clienteMasComprador].nombre, clientes[clienteMasComprador].cedula, maxCompras);
    } else {
        printf("No hay clientes con compras registradas.\n");
    }
    printf("\n--- Productos vendidos por tipo ---\n");
    for (int i = 0; i < numProductos; i++) {
        printf("%s: %d unidades\n", productos[i].nombre, productos[i].vendidos);
    }
}

void guardarProductos(Producto productos[], int numProductos) {
    FILE *f = fopen("productos.dat", "wb");
    if (f) {
        fwrite(&numProductos, sizeof(int), 1, f);
        fwrite(productos, sizeof(Producto), numProductos, f);
        fclose(f);
    }
}

void cargarProductos(Producto productos[], int *numProductos) {
    FILE *f = fopen("productos.dat", "rb");
    if (f) {
        fread(numProductos, sizeof(int), 1, f);
        fread(productos, sizeof(Producto), *numProductos, f);
        fclose(f);
    }
}

void guardarClientes(Cliente clientes[], int numClientes) {
    FILE *f = fopen("clientes.dat", "wb");
    if (f) {
        fwrite(&numClientes, sizeof(int), 1, f);
        fwrite(clientes, sizeof(Cliente), numClientes, f);
        fclose(f);
    }
}

void cargarClientes(Cliente clientes[], int *numClientes) {
    FILE *f = fopen("clientes.dat", "rb");
    if (f) {
        fread(numClientes, sizeof(int), 1, f);
        fread(clientes, sizeof(Cliente), *numClientes, f);
        fclose(f);
    }
}

void guardarVentas(Venta ventas[], int numVentas) {
    FILE *f = fopen("ventas.dat", "wb");
    if (f) {
        fwrite(&numVentas, sizeof(int), 1, f);
        fwrite(ventas, sizeof(Venta), numVentas, f);
        fclose(f);
    }
}

void cargarVentas(Venta ventas[], int *numVentas) {
    FILE *f = fopen("ventas.dat", "rb");
    if (f) {
        fread(numVentas, sizeof(int), 1, f);
        fread(ventas, sizeof(Venta), *numVentas, f);
        fclose(f);
    }
}

void guardarProductosTxt(Producto productos[], int numProductos) {
    FILE *f = fopen("productos.txt", "w");
    if (f) {
        fprintf(f, "ID,Nombre,Precio,Stock,Vendidos\n");
        for (int i = 0; i < numProductos; i++) {
            fprintf(f, "%d,%s,%.2f,%d,%d\n", productos[i].id, productos[i].nombre, productos[i].precio, productos[i].stock, productos[i].vendidos);
        }
        fclose(f);
    }
}

void guardarClientesTxt(Cliente clientes[], int numClientes) {
    FILE *f = fopen("clientes.txt", "w");
    if (f) {
        fprintf(f, "ID,Nombre,Cedula,Telefono\n");
        for (int i = 0; i < numClientes; i++) {
            fprintf(f, "%d,%s,%s,%s\n", clientes[i].id, clientes[i].nombre, clientes[i].cedula, clientes[i].telefono);
        }
        fclose(f);
    }
}

void guardarVentasTxt(Venta ventas[], int numVentas) {
    FILE *f = fopen("ventas.txt", "w");
    if (f) {
        fprintf(f, "ID_Venta,ID_Producto,ID_Cliente,Cantidad,Total\n");
        for (int i = 0; i < numVentas; i++) {
            fprintf(f, "%d,%d,%d,%d,%.2f\n", ventas[i].idVenta, ventas[i].idProducto, ventas[i].idCliente, ventas[i].cantidad, ventas[i].total);
        }
        fclose(f);
    }
}

