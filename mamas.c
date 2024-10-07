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
Heap* crear(Registro dato);
Heap* insertar(Heap* a, Registro dato);
Heap* conversion(Registro* base, Heap* _base, int lineas);
int size(Heap* a);
void liberarHeap(Heap* a);

int main() {
    int lineas = 0; //cantidad de datos
    Registro* base = transformarArchivo("2.txt", &lineas);
  
    if (base == NULL) {
        printf("No se pudo cargar la base de datos.\n");
        return 1;
    }

    // Imprimir los registros
    printf("Base de datos:\n");
    for (int i = 0; i < lineas; i++) {
        printf("Nombre: %s; Frecuencia: %d\n", base[i].palabra, base[i].frecuencia);
    }

    // Crear el heap
    Heap* _base = NULL;
    _base = conversion(base, _base, lineas);

    // Liberar la memoria
    free(base);  
    liberarHeap(_base);  // Liberamos el heap también
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

Heap* crear(Registro dato) {
    Heap* nuevo = (Heap*) malloc(sizeof(Heap));
    nuevo->dato = dato;
    nuevo->izq = NULL;
    nuevo->der = NULL;
    return nuevo;
}

Heap* conversion(Registro* base, Heap* _base, int lineas){
    for(int i = 0; i < lineas; i++){
        _base = insertar(_base, base[i]);
    }
    return _base;
}

Heap* insertar(Heap* a, Registro dato) {
    if (a == NULL) {
        return crear(dato); // Caso base: heap vacío
    }

    if (dato.frecuencia > a->dato.frecuencia) {
        if (size(a->izq) <= size(a->der)) {
            a->izq = insertar(a->izq, a->dato); // Mueve el dato actual hacia abajo
            a->dato = dato; // Coloca el nuevo dato en la raíz
        } else {
            a->der = insertar(a->der, a->dato); 
            a->dato = dato;
        }
    } else {
        if (size(a->izq) <= size(a->der)) {
            a->izq = insertar(a->izq, dato);
        } else {
            a->der = insertar(a->der, dato);
        }
    }
    
    return a;
}

int size(Heap* a){
    if(a == NULL){
        return 0;
    } else {
        return 1 + size(a -> izq) + size(a -> der);
    }
}

void liberarHeap(Heap* a) {
    if (a == NULL) {
        return;
    }
    liberarHeap(a->izq);
    liberarHeap(a->der);
    free(a);
}
