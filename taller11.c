#include <stdio.h>
#include <string.h>
#include <ctype.h>
#define MAXLIBROS 10
#define MAXLONGITUD 100
#define MAXLONGITUDAUTOR 50

void buscarCodigo(int id[MAXLIBROS], int *indice, int cantidad, int busca);
int leerEntero(char *mensaje);
int leerEnteroRango(char *mensaje, int min, int max);
int esNombreValido(char *cadena);
void leerDatos(int id[MAXLIBROS], char titulo[MAXLIBROS][MAXLONGITUD], char autor[MAXLIBROS][MAXLONGITUDAUTOR], int año[MAXLIBROS], char estado[MAXLIBROS][MAXLONGITUD], int *cantidad);
int esSoloLetras(const char *cadena);
void mostrarDatos(const int id[MAXLIBROS], const char titulo[MAXLIBROS][MAXLONGITUD], const char autor[MAXLIBROS][MAXLONGITUDAUTOR], const int año[MAXLIBROS], const char estado[MAXLIBROS][MAXLONGITUD], const int cantidad);
void buscarLibro(const int id[MAXLIBROS], const char titulo[MAXLIBROS][MAXLONGITUD], const char autor[MAXLIBROS][MAXLONGITUDAUTOR], const int año[MAXLIBROS], const char estado[MAXLIBROS][MAXLONGITUD], const int cantidad, int buscaId, char buscaTitulo[MAXLONGITUD]);
void actualizarEstado(int id[MAXLIBROS], char estado[MAXLIBROS][MAXLONGITUD], int cantidad, int buscaId);
void borrarLibro(int id[MAXLIBROS], char titulo[MAXLIBROS][MAXLONGITUD], char autor[MAXLIBROS][MAXLONGITUDAUTOR], int año[MAXLIBROS], char estado[MAXLIBROS][MAXLONGITUD], int *cantidad, int buscaId);
/*Eres encargado de diseñar un programa en lenguaje C para una pequeña biblioteca que desea gestionar la información de sus libros y facilitar las consultas de los usuarios.
Requerimientos:
•	Registrar libros en la biblioteca. Cada libro debe incluir:
1.	ID del libro (entero único). 
2.	Título (cadena de hasta 100 caracteres).
3.	Autor (cadena de hasta 50 caracteres).
4.	Año de publicación (entero). Estado (cadena: "Disponible" o "Prestado").
•	Mostrar la lista completa de libros en formato tabla.
•	Buscar un libro por título o ID y mostrar toda su información.
•	Actualizar el estado de un libro (de "Disponible" a "Prestado" o viceversa).
•	Eliminar libro
Restricciones:
•	No se pueden agregar más de 10 libros.
•	El programa debe usar estructuras.
•	El código de producto debe ser único.
•	Validar entradas del usuario.
*/

//GERMÁN CASTELLANOS, DIEGO MONCAYO

int main (int argc, char *argv[]) {
    int id[MAXLIBROS];
    char titulo[MAXLIBROS][MAXLONGITUD];
    char autor[MAXLIBROS][MAXLONGITUDAUTOR];
    int año[MAXLIBROS];
    char estado[MAXLIBROS][MAXLONGITUD];
    int cantidad = 0;
    int buscaId;
    char buscaTitulo[MAXLONGITUD];
    int opcion;

    leerDatos(id, titulo, autor, año, estado, &cantidad);

    do {
        printf("\n--- MENU ---\n");
        printf("1. Mostrar libros\n");
        printf("2. Buscar libro\n");
        printf("3. Actualizar estado de libro\n");
        printf("4. Borrar libro\n");
        printf("0. Salir\n");
        printf("Seleccione una opción: ");
        scanf("%d", &opcion);
        while (getchar() != '\n'); 

        switch (opcion) {
            case 1:
                mostrarDatos(id, titulo, autor, año, estado, cantidad);
                break;
            case 2:
                while (1) {
                    buscarLibro(id, titulo, autor, año, estado, cantidad, buscaId, buscaTitulo);
                    printf("¿Desea buscar otro libro? (1=Si, 0=No): ");
                    int seguir;
                    scanf("%d", &seguir);
                    while (getchar() != '\n');
                    if (!seguir) break;
                }
                break;
            case 3:
                while (1) {
                    actualizarEstado(id, estado, cantidad, buscaId);
                    printf("¿Desea actualizar otro libro? (1=Si, 0=No): ");
                    int seguir;
                    scanf("%d", &seguir);
                    while (getchar() != '\n');
                    if (!seguir) break;
                }
                break;
            case 4:
                while (1) {
                    borrarLibro(id, titulo, autor, año, estado, &cantidad, buscaId);
                    printf("¿Desea borrar otro libro? (1=Si, 0=No): ");
                    int seguir;
                    scanf("%d", &seguir);
                    while (getchar() != '\n');
                    if (!seguir) break;
                }
                break;
            case 0:
                printf("Saliendo...\n");
                break;
            default:
                printf("Opción inválida.\n");
        }
    } while (opcion != 0);

    return 0;
}

void borrarLibro(int id[MAXLIBROS], char titulo[MAXLIBROS][MAXLONGITUD], char autor[MAXLIBROS][MAXLONGITUDAUTOR], int año[MAXLIBROS], char estado[MAXLIBROS][MAXLONGITUD], int *cantidad, int buscaId) {
    int indice;
    buscaId = leerEntero("INGRESE EL ID DEL LIBRO A ELIMINAR");
    buscarCodigo(id, &indice, *cantidad, buscaId);
    if (indice != -1) {
        for (int i = indice; i < *cantidad - 1; i++) {
            id[i] = id[i + 1];
            strcpy(titulo[i], titulo[i + 1]);
            strcpy(autor[i], autor[i + 1]);
            año[i] = año[i + 1];
            strcpy(estado[i], estado[i + 1]);
        }
        (*cantidad)--;
        printf("Libro con ID %d eliminado.\n", buscaId);
    } else {
        printf("Libro con ID %d no encontrado.\n", buscaId);
    }
}

void actualizarEstado(int id[MAXLIBROS], char estado[MAXLIBROS][MAXLONGITUD], int cantidad, int buscaId) {
    int indice;
    buscaId = leerEntero("INGRESE EL ID DEL LIBRO PARA ACTUALIZAR SU ESTADO");
    buscarCodigo(id, &indice, cantidad, buscaId);
    if (indice != -1) {
        if (strcmp(estado[indice], "Disponible") == 0) {
            strcpy(estado[indice], "Prestado");
        } else {
            strcpy(estado[indice], "Disponible");
        }
        printf("Estado del libro con ID %d actualizado a: %s\n", buscaId, estado[indice]);
    } else {
        printf("Libro con ID %d no encontrado.\n", buscaId);
    }
}

void buscarLibro(const int id[MAXLIBROS], const char titulo[MAXLIBROS][MAXLONGITUD], const char autor[MAXLIBROS][MAXLONGITUDAUTOR], const int año[MAXLIBROS], const char estado[MAXLIBROS][MAXLONGITUD], const int cantidad, int buscaId, char buscaTitulo[MAXLONGITUD]) {
    int encontrado = 0;
    printf("INGRESE EL TITULO O ID DEL LIBRO A BUSCAR: ");
    while (getchar() != '\n');
    fgets(buscaTitulo, MAXLONGITUD, stdin);
    buscaTitulo[strcspn(buscaTitulo, "\n")] = 0; // Quita el salto de línea
    if (sscanf(buscaTitulo, "%d", &buscaId) != 1) {
        buscaId = -1; // Si no se pudo convertir a entero, busca por título
    }
    if (buscaId < 0) {
        printf("Buscando por título: %s\n", buscaTitulo);
    } else {
        printf("Buscando por ID: %d\n", buscaId);
    }
    for (int i = 0; i < cantidad; i++) {
        if (id[i] == buscaId || strcmp(titulo[i], buscaTitulo) == 0) {
            printf("Libro encontrado:\n");
            printf("ID: %d\n", id[i]);
            printf("Título: %s\n", titulo[i]);
            printf("Autor: %s\n", autor[i]);
            printf("Año: %d\n", año[i]);
            printf("Estado: %s\n", estado[i]);
            encontrado = 1;
            break;
        }
    }
    if (!encontrado) {
        printf("Libro no encontrado.\n");
    }
}

void mostrarDatos(const int id[MAXLIBROS], const char titulo[MAXLIBROS][MAXLONGITUD], const char autor[MAXLIBROS][MAXLONGITUDAUTOR], const int año[MAXLIBROS], const char estado[MAXLIBROS][MAXLONGITUD], const int cantidad){
    printf("ID\tTITULO\t\tAUTOR\t\tAÑO\tESTADO\n");
    for (int i = 0; i < cantidad; i++)
    {
        printf("%d\t%s\t\t%s\t\t%d\t%s\n",id[i],titulo[i],autor[i],año[i],estado[i]);
    }
    
}

void leerDatos(int id[MAXLIBROS], char titulo[MAXLIBROS][MAXLONGITUD], char autor[MAXLIBROS][MAXLONGITUDAUTOR], int año[MAXLIBROS], char estado[MAXLIBROS][MAXLONGITUD], int *cantidad)
{
    int resp;
    int indice;
    do
    {
        int idIngresado = leerEntero("INGRESE EL ID DEL LIBRO");
        while (getchar() != '\n'); // Limpia el buffer después de scanf
        buscarCodigo(id, &indice, *cantidad, idIngresado);
        if (indice == -1)
        {
            id[*cantidad] = idIngresado;
            do {
                printf("INGRESE EL TITULO DEL LIBRO: ");
                fgets(titulo[*cantidad], MAXLONGITUD, stdin);
                titulo[*cantidad][strcspn(titulo[*cantidad], "\n")] = 0;
                if (!esSoloLetras(titulo[*cantidad])) {
                    printf("TITULO INVALIDO. SOLO SE ACEPTAN LETRAS.\n");
                }
            } while (!esSoloLetras(titulo[*cantidad]));

            do {
                printf("INGRESE EL AUTOR DEL LIBRO: ");
                fgets(autor[*cantidad], MAXLONGITUDAUTOR, stdin);
                autor[*cantidad][strcspn(autor[*cantidad], "\n")] = 0;
                if (!esSoloLetras(autor[*cantidad])) {
                    printf("NOMBRE DEL AUTOR INVALIDO. SOLO SE ACEPTAN LETRAS.\n");
                }
            } while (!esSoloLetras(autor[*cantidad]));

            año[*cantidad] = leerEnteroRango("INGRESE EL AÑO DE PUBLICACION",1700,2025);
            while (getchar() != '\n'); 

            do {
                printf("INGRESE EL ESTADO DEL LIBRO (Disponible/Prestado): ");
                fgets(estado[*cantidad], MAXLONGITUD, stdin);
                estado[*cantidad][strcspn(estado[*cantidad], "\n")] = 0;
                if (strcmp(estado[*cantidad], "Disponible") != 0 && strcmp(estado[*cantidad], "Prestado") != 0) {
                    printf("Estado inválido. Debe ser 'Disponible' o 'Prestado'.\n");
                    continue;
                }
            } while (strcmp(estado[*cantidad], "Disponible") != 0 && strcmp(estado[*cantidad], "Prestado") != 0);

            *cantidad +=1;
        }else{
            printf("El ID INGRESADO YA EXISTE\n");
        }
        resp = leerEnteroRango("0 PARA SALIR, CUALQUIER DIGITO PARA CONTINUAR", 0, 9);
        while (getchar() != '\n'); // Limpia el buffer después de scanf
    } while (*cantidad < MAXLIBROS && resp != 0);
}
void buscarCodigo(int id[MAXLIBROS], int *indice, int cantidad, int busca)
{
    for (int i = 0; i < cantidad; i++)
    {
        if (id[i] == busca)
        {
            *indice = i;
            return;
        }
    }
    *indice = -1;
}

int leerEnteroRango(char *mensaje, int min, int max)
{
    int valor;
    printf("%s ENTRE %d Y %d: ", mensaje, min, max);
    while (scanf("%d", &valor) != 1 || valor < min || valor > max)
    {
        while (getchar() != '\n')
            ;
        printf("Dato incorrecto, vuelva a ingresar: ");
    }
    return valor;
}

int leerEntero(char *mensaje)
{
    int valor;
    printf("%s: ", mensaje);
    while (scanf("%d", &valor) != 1)
    {
        while (getchar() != '\n')
            ;
        printf("Dato incorrecto, vuelva a ingresar: ");
    }
    return valor;
}

int esNombreValido(char *cadena) {
    for (int i = 0; cadena[i] != '\0'; i++) {
        if (!isalpha(cadena[i])) {
            return 0;
        }
    }
    return 1;
}

int esSoloLetras(const char *cadena) {
    for (int i = 0; cadena[i] != '\0'; i++) {
        if (!isalpha(cadena[i]) && cadena[i] != ' ') {
            return 0; // No es solo letras o espacio
        }
    }
    return strlen(cadena) > 0; // Debe tener al menos un carácter
}