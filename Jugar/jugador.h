#include "../Maquina/maquina.h"

#define GREEN "\x1b[32m"
#define ORANGE "\x1b[33m" 
#define RESET "\x1b[0m"

#define INTENTOS 6

void limpiarTablero (char tablero[INTENTOS][TAM_PALABRA]);

void imprimirTablero (char tablero[INTENTOS][TAM_PALABRA], char palabraSecreta[TAM_PALABRA]);

void imprimirAColor (char frase[TAM_PALABRA], char palabraSecreta[TAM_PALABRA]);

int jugarPalabra (char tablero[INTENTOS][TAM_PALABRA], char palabra[TAM_PALABRA], char palabraSecreta[TAM_PALABRA], int intento);