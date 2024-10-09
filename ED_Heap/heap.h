#include <stdio.h>
#include <stdlib.h>

typedef struct {
    char palabra[6];
    int frecuencia;
} Registro;


typedef struct {
    Registro* data;
    int capacity;
    int size;
} MaxHeap;

void swap(Registro* a, Registro* b);

Registro getMax(MaxHeap* heap);

void insert(MaxHeap* heap, Registro value);

void heapify(MaxHeap* heap, int i);

void deleteMax(MaxHeap* heap);

int isEmpty(MaxHeap *heap);

void printBFS(MaxHeap* heap);

MaxHeap* createHeap(int capacity);

void freeHeap(MaxHeap* heap);