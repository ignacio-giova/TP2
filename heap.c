#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int* data;
    int capacity;
    int size;
} MaxHeap;

// Función auxiliar para intercambiar dos elementos
void swap(int* a, int* b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

int getMax(MaxHeap* heap) {
    if (heap->size == 0) {
        printf("El heap está vacío.\n");
        return -1;  // O un valor adecuado para indicar error
    }
    return heap->data[0];  // La raíz siempre está en el índice 0
}

void insert(MaxHeap* heap, int value) {
    if (heap->size == heap->capacity) {
        printf("El heap está lleno.\n");
        return;
    }

    // Añadir el nuevo valor al final del heap
    heap->data[heap->size] = value;
    heap->size++;

    // Subir el valor si es necesario
    int i = heap->size - 1;
    while (i > 0 && heap->data[i] > heap->data[(i - 1) / 2]) {
        swap(&heap->data[i], &heap->data[(i - 1) / 2]);
        i = (i - 1) / 2;
    }
}

void heapify(MaxHeap* heap, int i) {
    int left = 2 * i + 1;
    int right = 2 * i + 2;
    int largest = i;

    if (left < heap->size && heap->data[left] > heap->data[largest])
        largest = left;
    if (right < heap->size && heap->data[right] > heap->data[largest])
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

void printBFS(MaxHeap* heap) {
    if (heap->size == 0) {
        printf("El heap está vacío.\n");
        return;
    }

    printf("Heap en orden BFS: ");
    for (int i = 0; i < heap->size; i++) {
        printf("%d ", heap->data[i]);
    }
    printf("\n");
}

int main() {
    MaxHeap heap;
    heap.capacity = 10;
    heap.size = 0;
    heap.data = (int*)malloc(heap.capacity * sizeof(int));

    insert(&heap, 10);
    insert(&heap, 20);
    insert(&heap, 15);
    insert(&heap, 30);
    insert(&heap, 1);
    insert(&heap, 1);

    printf("Máximo: %d\n", getMax(&heap));

    deleteMax(&heap);
    printf("Máximo después de eliminar: %d\n", getMax(&heap));

    printBFS(&heap);

    free(heap.data);
    return 0;
}
