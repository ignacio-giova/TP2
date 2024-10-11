#include "../ED_Heap/heap.h"

typedef struct {
    char letra;
    int posiciones[TAM_PALABRA]; //Una letra en amarillo solo puede ocupar 5 espacios
} Letra;

typedef struct {
    char letrasVerdes[TAM_PALABRA]; // Letras en la posición correcta
    Letra letrasAmarillas[TAM_PALABRA]; // A lo sumo habra 5 letras amarillas
    int letrasNoIncluidas[26]; // Letras que no están en la palabra
} Filtro;


MaxHeap* transformarArchivo(char* nombreArchivo);
//transforma la base de datos en un Heap, en el cual su prioridad es la frecuencia

void sugerirPalabra(char *buffer, MaxHeap *heap, Filtro *filtro, char *palabraSecreta);
//retorna la palabra de mayor prioridad

MaxHeap* filtrarHeap (MaxHeap *a, Filtro* filtro);
//verficia si el maximo cumple el filtro

int verificarPalabra(const char *palabra, Filtro *filtro);
//verificia que la palabra cumpla el filtro


Filtro* inicializarFiltro();
//inicializa el filtro


void actualizarFiltro(Filtro *filtro, const char *palabra, const char *palabraSecreta);
//renueva el filtro

void imprimirFiltro(Filtro *filtro);
//imprime el filtro, se utiliza para comprobar el correcto funcionamiento del mismo