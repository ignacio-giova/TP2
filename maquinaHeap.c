#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char palabra[6];
    int frecuencia;
} Registro;

typedef struct heap {
    Registro dato;
    struct heap *izq, *der;
} Heap;

Registro* transformarArchivo(char* nombreArchivo, int* lineas);

//para probar
void imprimirArr(Registro* a, int lineas);

int main() {
    int lineas = 0; //cantidad de datos
    Registro* base = transformarArchivo("holis.txt", &lineas);
  
    if (base == NULL) {
        printf("No se pudo cargar la base de datos.\n");
        return 1;
    }

    //para probar
    imprimirArr(base, lineas);
    free(base);  
    return 0;
}

Registro* transformarArchivo(char* nombreArchivo, int* lineas) { 
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
    Registro* base = (Registro*)malloc((*lineas) * sizeof(Registro)); 

    // Leer registros
    for (int i = 0; i < (*lineas); i++) { 
        fscanf(fd, "%5[^,],%d\n", base[i].palabra, &base[i].frecuencia);
    }

    fclose(fd);  // Cerrar el archivo
    return base;
}

void imprimirArr(Registro* a, int lineas){
    printf("Base de datos:\n");
    for (int i = 0; i < lineas; i++) {
        printf("Nombre: %s; Frecuencia: %d\n", a[i].palabra, a[i].frecuencia);
    }

}
