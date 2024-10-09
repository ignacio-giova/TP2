#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char palabra[6];
    int frecuencia;
} Registro;

typedef struct {
    Registro* datos;  // Arreglo dinámico que representa el heap
    int tam;          // Tamaño actual del heap
    int capacidad;    // Capacidad máxima del heap
} Heap;

Heap* crearHeap(int capacidad);
void insertarHeap(Heap* heap, Registro dato);
Registro getMax(Heap* heap);
void deleteMax(Heap* heap);
void destruirHeap(Heap* heap);
Heap* transformarArchivoEnHeap(char* nombreArchivo);
void imprimirHeap(Heap* heap);

int main() {
    Heap* base = transformarArchivoEnHeap("holis.txt");
  
    if (base == NULL) {
        printf("No se pudo cargar la base de datos.\n");
        return 1;
    }

    //para probar
    imprimirHeap(base);

    // Liberar la memoria del heap
    destruirHeap(base);  
    return 0;
}

// Función para crear un heap con capacidad dada
Heap* crearHeap(int capacidad) {
    Heap* heap = (Heap*)malloc(sizeof(Heap));
    heap->datos = (Registro*)malloc((capacidad + 1) * sizeof(Registro));  // +1 porque empezamos en el índice 1
    heap->tam = 0;
    heap->capacidad = capacidad;
    return heap;
}

// Función para insertar un nuevo registro en el heap
void insertarHeap(Heap* heap, Registro dato) {
    if (heap->tam >= heap->capacidad) {
        printf("Heap está lleno, no se puede insertar más elementos.\n");
        return;
    }

    heap->tam++;
    heap->datos[heap->tam] = dato;  // Insertar al final del heap

    // "Trepar" el elemento si es necesario
    int i = heap->tam;
    while (i > 1 && heap->datos[i].frecuencia > heap->datos[i / 2].frecuencia) {
        // Intercambiar con el padre
        Registro temp = heap->datos[i];
        heap->datos[i] = heap->datos[i / 2];
        heap->datos[i / 2] = temp;
        i = i / 2;
    }
}

// Función para obtener el máximo (la raíz del heap)
Registro getMax(Heap* heap) {
    if (heap->tam == 0) {
        printf("El heap está vacío.\n");
        Registro vacio = {"", -1};
        return vacio;
    }
    return heap->datos[1];  // El máximo está en la raíz
}

// Función para eliminar el máximo (la raíz del heap)
void deleteMax(Heap* heap) {
    if (heap->tam == 0) {
        printf("El heap está vacío, no se puede eliminar.\n");
        return;
    }

    // Reemplazar la raíz con el último elemento
    heap->datos[1] = heap->datos[heap->tam];
    heap->tam--;

    // "Hundir" el nuevo valor en la raíz
    int i = 1;
    while (i * 2 <= heap->tam) {
        int hijo = i * 2;
        // Seleccionar el hijo mayor
        if (hijo < heap->tam && heap->datos[hijo].frecuencia < heap->datos[hijo + 1].frecuencia) {
            hijo++;
        }
        // Si el padre es mayor que el hijo mayor, detener
        if (heap->datos[i].frecuencia >= heap->datos[hijo].frecuencia) {
            break;
        }
        // Intercambiar con el hijo mayor
        Registro temp = heap->datos[i];
        heap->datos[i] = heap->datos[hijo];
        heap->datos[hijo] = temp;
        i = hijo;
    }
}

// Función para transformar el archivo en un heap
Heap* transformarArchivoEnHeap(char* nombreArchivo) { 
    FILE* fd = fopen(nombreArchivo, "r");  // Abrimos el archivo en modo lectura
    if (fd == NULL) {
        printf("No se pudo abrir el archivo.\n");
        return NULL;
    }

    int lineas = 0;
    char c;
    // Contar líneas
    while ((c = fgetc(fd)) != EOF) {
        if (c == '\n') {
            lineas++;
        }
    }
    fseek(fd, 0, SEEK_SET);  // Reiniciar el puntero del archivo

    Heap* heap = crearHeap(lineas);  // Crear heap con la cantidad de líneas
    Registro temp;

    // Leer registros y añadirlos al heap
    while (fscanf(fd, "%5[^,],%d\n", temp.palabra, &temp.frecuencia) != EOF) {
        insertarHeap(heap, temp);
    }

    fclose(fd);  // Cerrar el archivo
    return heap;
}

// Función para imprimir el heap
void imprimirHeap(Heap* heap) {
    printf("Heap de registros:\n");
    for (int i = 1; i <= heap->tam; i++) {
        printf("Nombre: %s; Frecuencia: %d\n", heap->datos[i].palabra, heap->datos[i].frecuencia);
    }
}

// Función para liberar la memoria del heap
void destruirHeap(Heap* heap) {
    free(heap->datos);
    free(heap);
}
