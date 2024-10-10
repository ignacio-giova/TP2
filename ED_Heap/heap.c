#include "heap.h"

// Función auxiliar para intercambiar dos elementos
void swap(Registro* a, Registro* b) {
    Registro temp = *a;
    *a = *b;
    *b = temp;
}

Registro getMax(MaxHeap* heap) {
    return heap->data[0];  // La raíz siempre está en el índice 0
}

void insert(MaxHeap* heap, Registro value) {
    if (heap->size >= heap->capacity) {
        printf("El heap está lleno.\n");
        return;   
    }

    // Añadir el nuevo valor al final del heap
    heap->data[heap->size] = value;
    heap->size++;

    // Subir el valor si es necesario
    int i = heap->size - 1;
    while (i > 0 && heap->data[i].frecuencia > heap->data[(i - 1) / 2].frecuencia) {
        swap(&heap->data[i], &heap->data[(i - 1) / 2]);
        i = (i - 1) / 2;
    }
}

void heapify(MaxHeap* heap, int i) {
    int left = 2 * i + 1;
    int right = 2 * i + 2;
    int largest = i;

    if (left < heap->size && heap->data[left].frecuencia > heap->data[largest].frecuencia)
        largest = left;
    if (right < heap->size && heap->data[right].frecuencia > heap->data[largest].frecuencia)
        largest = right;

    if (largest != i) {
        swap(&heap->data[i], &heap->data[largest]);
        heapify(heap, largest);
    }
}

void deleteMax(MaxHeap* heap) {
    if (heap->size == 0) {
        printf("El heap está vacío.\n");
        return;
    }

    // Reemplazar la raíz con el último elemento
    heap->data[0] = heap->data[heap->size - 1];
    heap->size--;

    // Hundir el nuevo valor en la raíz si es necesario
    heapify(heap, 0);
}

int isEmpty(MaxHeap *heap){
    if(heap == NULL || heap->size == 0)
        return 1;
    else
        return 0;
}

void printBFS(MaxHeap* heap) {
    if (heap->size == 0) {
        printf("El heap está vacío.\n");
        return;
    }

    printf("Heap en orden BFS: ");
    for (int i = 0; i < heap->size; i++) {
        printf("\n%s, %i ", heap->data[i].palabra, heap->data[i].frecuencia);
    }
    printf("\n");
}

MaxHeap* createHeap(int capacity) {
    // Reservar memoria para la estructura MaxHeap
    MaxHeap* heap = (MaxHeap*)malloc(sizeof(MaxHeap));
    if (heap == NULL) {
        printf("Error al asignar memoria para el heap.\n");
        return NULL;
    }

    // Reservar memoria para los datos del heap
    heap->data = (Registro*)malloc(capacity * sizeof(Registro));
    if (heap->data == NULL) {
        printf("Error al asignar memoria para los datos del heap.\n");
        free(heap);  // Liberar la estructura del heap si falla la asignación de datos
        return NULL;
    }

    // Inicializar los campos del heap
    heap->capacity = capacity;
    heap->size = 0;

    return heap;
}

void freeHeap(MaxHeap* heap) {
    if (heap == NULL) return;  // Si el heap es NULL, no hay nada que liberar
    free(heap->data);  // Liberar la memoria del arreglo de datos
    free(heap);        // Liberar la estructura MaxHeap
}
