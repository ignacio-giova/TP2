#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char palabra[6];
    int frecuencia;
} Registro;

Registro* transformarArchivo(char* nombreArchivo, Registro* base, int* lineas);

int main() {
    int lineas = 0; //cant de datos
    Registro* base = transformarArchivo("2.txt", base, &lineas);
  
    if (base == NULL) {
        printf("No se pudo cargar la base de datos.\n");
        return 1;
    }

    // Imprimimos los registros
    printf("Base de datos:\n");
    for (int i = 0; i < lineas; i++) {
        printf("Nombre: %s; Frecuencia: %d\n", base[i].palabra, base[i].frecuencia);
    }

    free(base);  // Liberamos la memoria
    return 0;
}

Registro* transformarArchivo(char* nombreArchivo, Registro* base, int* lineas) { 
    FILE* fd = fopen(nombreArchivo, "r");  // Abrimos el archivo en modo lectura
    if (fd == NULL) {
        printf("No se pudo abrir el archivo.\n");
        return NULL;
    }

    // Contar líneas
    *lineas = 1; //consideramos la primera linea
    char c;
    while ((c = fgetc(fd)) != EOF) {
        if (c == '\n') {
            (*lineas)++;
        }
    }

    // Reiniciar el puntero de archivo
    fseek(fd, 0, SEEK_SET);

    // Reservar memoria para los registros
    base = (Registro*)malloc((*lineas) * sizeof(Registro)); 

    // Leer registros
    for (int i = 0; i < (*lineas); i++) { 
        fscanf(fd, "%5[^,],%d\n", base[i].palabra, &base[i].frecuencia);
    }

    fclose(fd);  // Cerrar el archivo
    return base;
}
