#include <stdio.h>

//PAUL CABRERA, ALEJANDRO HOLGUIN Y DAVID SOASTI

int main() {
    int id = -1, stock = 0, cantidad, opcion, valido = 0, ventas_realizadas = 0, producto_ingresado = 0;
    float precio = 0, total_ganancias = 0, temp_stock;
    char nombre[30];

    do {
        printf("\nMenú de Opciones:\n");
        printf("0. Ingresar nuevo producto\n");
        printf("1. Vender producto\n");
        printf("2. Reabastecer producto\n");
        printf("3. Mostrar información del producto\n");
        printf("4. Mostrar total de ganancias\n");
        printf("5. Salir\n");
        printf("\nSeleccione una opción: ");
        scanf("%d", &opcion);
        while (getchar() != '\n'); 

        switch (opcion) {
        case 0:
            while (!valido)
            {
                printf("Ingrese el ID del producto: ");
                if (scanf("%d", &id) == 1 && id > 0)
                {
                    char siguiente = getchar();
                    if (siguiente != '\n')
                    {
                        printf("El ID no puede contener letras. El ID guardado es: %d\n", id);
                        while (getchar() != '\n');
                    }
                    valido = 1;
                }
                else
                {
                    printf("ID inválido. Ingrese solo números enteros positivos.\n");
                    while (getchar() != '\n');
                }
            }


            printf("Ingrese el nombre del producto: ");
            fgets(nombre, 30, stdin);

            valido = 0;
            while (!valido)
            {
                printf("Ingrese la cantidad inicial en stock (entero): ");
                if (scanf("%f", &temp_stock) == 1 && temp_stock > 0)
                {
                    stock = (int)temp_stock;
                    valido = 1;
                }
                else
                {
                    printf("Entrada inválida o negativa. Intente nuevamente.\n");
                    while (getchar() != '\n');
                }
            }

            valido = 0;
            while (!valido)
            {
                printf("Ingrese el precio unitario del producto: ");
                if (scanf("%f", &precio) == 1 && precio > 0)
                {
                    valido = 1;
                }
                else
                {
                    printf("Entrada inválida. Intente nuevamente.\n");
                    while (getchar() != '\n');
                }
            }

            ventas_realizadas = 0;
            total_ganancias = 0;
            producto_ingresado = 1;
            printf("Producto ingresado correctamente.\n");
            break;

        case 1:
            if (!producto_ingresado)
            {
                printf("Primero debe ingresar un producto usando la opción 0.\n");
                break;
            }

            do
            {
                printf("Ingrese la cantidad a vender: ");
                scanf("%d", &cantidad);
                if (cantidad < 0)
                {
                    printf("La cantidad no puede ser negativa. Intente nuevamente.\n");
                }
            } while (cantidad < 0);

            if (cantidad <= stock)
            {
                float descuento = 0;
                do
                {
                    printf("Ingrese porcentaje de descuento (0 si no desea): ");
                    scanf("%f", &descuento);
                    if (descuento < 0 || descuento > 100)
                    {
                        printf("Descuento inválido. Debe estar entre 0 y 100.\n");
                    }
                } while (descuento < 0 || descuento > 100);

                float precio_final = precio - (precio * descuento / 100);
                float ganancia = cantidad * precio_final;

                stock -= cantidad;
                total_ganancias += ganancia;
                ventas_realizadas++;

                printf("Venta realizada con éxito.\n");
                printf("Precio final aplicado por unidad: %.2f\n", precio_final);
                printf("Ganancia de esta venta: %.2f\n", ganancia);
            }
            else
            {
                printf("No hay suficiente stock disponible. Stock actual: %d\n", stock);
            }
            break;

        case 2:
            if (!producto_ingresado)
            {
                printf("Primero debe ingresar un producto usando la opción 0.\n");
                break;
            }

            do
            {
                printf("Ingrese la cantidad a agregar al stock: ");
                scanf("%d", &cantidad);
                if (cantidad < 0)
                {
                    printf("La cantidad no puede ser negativa. Intente nuevamente.\n");
                }
            } while (cantidad < 0);

            stock += cantidad;
            printf("Stock actualizado correctamente.\n");
            break;

        case 3:
            if (!producto_ingresado)
            {
                printf("Primero debe ingresar un producto usando la opción 0.\n");
                break;
            }

            printf("------------------------------------------");
            printf("\nInformación del producto:\n");
            printf("ID:\t\t\t%d\n", id);
            printf("Nombre:\t\t\t%s", nombre);
            printf("Stock disponible:\t%d\n", stock);
            printf("Precio unitario:\t%.2f\n", precio);
            printf("------------------------------------------\n");
            break;

        case 4:
            if (!producto_ingresado)
            {
                printf("Primero debe ingresar un producto usando la opción 0.\n");
                break;
            }

            printf("Total de ganancias: $%.2f\n", total_ganancias);
            printf("Total de ventas realizadas: %d\n", ventas_realizadas);
            break;

        case 5:
            printf("Saliendo del programa...\n");
            break;

        default:
            printf("Opción inválida. Intente nuevamente.\n");
        }

    } while (opcion != 5);

    return 0;
}
