#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TAM_PALABRA 6

typedef struct {
    char palabra[TAM_PALABRA];
    int frecuencia;
} Registro;


typedef struct {
    Registro* data;
    int capacity;
    int size;
} MaxHeap;

void swap(Registro* a, Registro* b);
//intercambia dos elementos de tipo Registro

int compareRegistros(Registro* a, Registro* b);

Registro getMax(MaxHeap* heap);
//obtiene el maximo elemento del Heap de tipo Registro

void insert(MaxHeap* heap, Registro value);
//inserta un elemento al Heap

void heapify(MaxHeap* heap, int i);
//reorganiza el Heap en el indice i para que se siga cumpliendo la propiedad

void deleteMax(MaxHeap* heap);
//elimina el maximo elemento del Heap

int isEmpty(MaxHeap *heap);
//verifica si el Heap es vacío

void printBFS(MaxHeap* heap);
//impre el Heap en BFS

MaxHeap* createHeap(int capacity);
//crea un Heap

void freeHeap(MaxHeap* heap);
//libera la memoria del Heap