#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../ED_Heap/heap.h"

#define TAM_PALABRA 5

typedef struct {
    char letra;
    int posiciones[5]; //Una letra en amarillo solo puede ocupar 5 espacios
} Letra;

typedef struct {
    char letrasVerdes[TAM_PALABRA]; // Letras en la posición correcta
    Letra letrasAmarillas[5]; // A lo sumo habra 5 letras amarillas
    int letrasNoIncluidas[26]; // Letras que no están en la palabra
} Filtro;


MaxHeap* transformarArchivo(char* nombreArchivo);
//transforma la base de datos en arreglo de estructura dinamico, para almacenar los datos

char *sugerirPalabra(char *buffer, MaxHeap *heap, Filtro *filtro, char *palabraSecreta);

MaxHeap* filtrarHeap (MaxHeap *a, Filtro* filtro);

int verificarPalabra(const char *palabra, Filtro *filtro);

void inicializarFiltro(Filtro *filtro);

void actualizarFiltro(Filtro *filtro, const char *palabra, const char *palabraSecreta);

void imprimirFiltro(Filtro *filtro);