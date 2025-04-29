#include <stdio.h>
#include <string.h>

#define JUGADORES 5
#define PARTIDOS 4

int main() {
    char jugadores[JUGADORES][30];
    int puntos[JUGADORES][PARTIDOS];
    int totalPuntos[JUGADORES] = {0};
    float promedio[JUGADORES];
    int mejorJugador = 0;
    float maxPromedio = 0;

    for (int i = 0; i < JUGADORES; i++) {
        printf("Ingrese el nombre del jugador %d: ", i + 1);
        fgets(jugadores[i], 30, stdin);
        jugadores[i][strcspn(jugadores[i], "\n")] = '\0';
    }

    for (int i = 0; i < JUGADORES; i++) {
        printf("\nIngrese los puntos de %s durante los 4 partidos:\n", jugadores[i]);
        for (int j = 0; j < PARTIDOS; j++) {
            printf("Partido %d: ", j + 1);
            while (scanf("%d", &puntos[i][j]) != 1 || puntos[i][j] < 0) {
                printf("Entrada invalida. Ingrese un valor positivo para el partido %d: ", j + 1);
                while(getchar() != '\n'); 
            }
            totalPuntos[i] += puntos[i][j];
        }
    }

    printf("\nJugador        Partido 1  Partido 2  Partido 3  Partido 4  Promedio\n");

    for (int i = 0; i < JUGADORES; i++) {
        promedio[i] = totalPuntos[i] / (float)PARTIDOS;
        printf("%-14s %-9d %-9d %-9d %-9d %-8.2f\n", jugadores[i], puntos[i][0], puntos[i][1], puntos[i][2], puntos[i][3], promedio[i]);
        if (promedio[i] > maxPromedio) {
            maxPromedio = promedio[i];
            mejorJugador = i;
        }
    }

    printf("\nEl jugador con el mejor promedio es %s con un promedio de %.2f puntos.\n", jugadores[mejorJugador], maxPromedio);

    return 0;
}
