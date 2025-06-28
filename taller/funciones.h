// Estructuras y prototipos para la gestión de la tienda
#ifndef FUNCIONES_H
#define FUNCIONES_H

#define MAX_PRODUCTOS 100
#define MAX_CLIENTES 100
#define MAX_VENTAS 200

typedef struct {
    int id;
    char nombre[50];
    float precio;
    int stock;
    int vendidos;
} Producto;

typedef struct {
    int id;
    char nombre[31];
    char cedula[16];
    char telefono[15];
} Cliente;

typedef struct {
    int idVenta;
    int idProducto;
    int idCliente;
    int cantidad;
    float total;
} Venta;

void registrarVenta(Venta ventas[], int *numVentas, Producto productos[], int numProductos, Cliente clientes[], int *numClientes);
void mostrarProductosMasVendidos(Producto productos[], int numProductos);
void mostrarVentas(Venta ventas[], int numVentas);
void mostrarClientes(Cliente clientes[], int numClientes);

// Nuevos prototipos
void buscarProductoPorNombre(Producto productos[], int numProductos, const char* nombre);
void buscarProductoPorID(Producto productos[], int numProductos, int id);
void mostrarClienteQueMasCompro(Venta ventas[], int numVentas, Cliente clientes[], int numClientes);
void mostrarTotalIngresos(Venta ventas[], int numVentas);
void mostrarProductosBajoStock(Producto productos[], int numProductos, int umbral);
void mostrarNumeroTotalVentas(int numVentas);
void mostrarEstadisticas(Producto productos[], int numProductos, Venta ventas[], int numVentas, Cliente clientes[], int numClientes);
// Prototipo de validación de número
int esNumeroValido(const char* str, int longitud);
void reabastecerStock(Producto productos[], int numProductos);

// Prototipos para archivos binarios
void guardarProductos(Producto productos[], int numProductos);
void cargarProductos(Producto productos[], int *numProductos);
void guardarClientes(Cliente clientes[], int numClientes);
void cargarClientes(Cliente clientes[], int *numClientes);
void guardarVentas(Venta ventas[], int numVentas);
void cargarVentas(Venta ventas[], int *numVentas);

// Prototipos para guardar datos en archivos de texto plano
void guardarProductosTxt(Producto productos[], int numProductos);
void guardarClientesTxt(Cliente clientes[], int numClientes);
void guardarVentasTxt(Venta ventas[], int numVentas);
#endif
