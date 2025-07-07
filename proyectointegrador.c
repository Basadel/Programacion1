#include <stdio.h>
#include <string.h>
#include <math.h>

#define MAXVAR 3
#define MAXFILAS 8

void mostrarTabla(int numvar, int filas, int tabla[MAXFILAS][MAXVAR], int salida[MAXFILAS]);
void construirSOP(int numvar, int filas, int tabla[MAXFILAS][MAXVAR], int salida[MAXFILAS]);

int main() {
    int numvar;
    do {
        printf("Ingrese el numero de variables booleanas (2 o 3): ");
        scanf("%d", &numvar);
    } while (numvar < 2 || numvar > 3);

    int filas = (int)pow(2, numvar);
    int tabla[MAXFILAS][MAXVAR];
    int salida[MAXFILAS];

    // Generar tabla de verdad
    for (int i = 0; i < filas; i++) {
        for (int j = 0; j < numvar; j++) {
            tabla[i][j] = (i >> (numvar - j - 1)) & 1;
        }
    }

    // Pedir salidas
    printf("Ingrese la salida (0 o 1) para cada fila de la tabla de verdad:\n");
    for (int i = 0; i < filas; i++) {
        printf("Fila %d (", i);
        for (int j = 0; j < numvar; j++) {
            printf("%c=%d ", 'A'+j, tabla[i][j]);
        }
        printf("): ");
        do {
            scanf("%d", &salida[i]);
        } while (salida[i] != 0 && salida[i] != 1);
    }

    // Mostrar tabla
    printf("\nTabla de verdad:\n");
    mostrarTabla(numvar, filas, tabla, salida);

    // Construir y mostrar SOP
    printf("\nExpresion booleana (SOP):\n");
    construirSOP(numvar, filas, tabla, salida);

    return 0;
}

void mostrarTabla(int numvar, int filas, int tabla[MAXFILAS][MAXVAR], int salida[MAXFILAS]) {
    for (int j = 0; j < numvar; j++) {
        printf("%c ", 'A'+j);
    }
    printf("| S\n");
    for (int i = 0; i < filas; i++) {
        for (int j = 0; j < numvar; j++) {
            printf("%d ", tabla[i][j]);
        }
        printf("| %d\n", salida[i]);
    }
}

void construirSOP(int numvar, int filas, int tabla[MAXFILAS][MAXVAR], int salida[MAXFILAS]) {
    int primero = 1;
    for (int i = 0; i < filas; i++) {
        if (salida[i] == 1) {
            if (!primero) printf(" + ");
            primero = 0;
            for (int j = 0; j < numvar; j++) {
                if (tabla[i][j] == 1)
                    printf("%c", 'A'+j);
                else
                    printf("!%c", 'A'+j);
                if (j < numvar-1) printf(" ");
            }
        }
    }
    if (primero) printf("0"); // Si no hay términos
    printf("\n");
}