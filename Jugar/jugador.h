#include "../Maquina/maquina.h"

#define GREEN "\x1b[32m"
#define ORANGE "\x1b[33m" 
#define RESET "\x1b[0m"

void limpiarTablero (char tablero[6][6]);

void imprimirTablero (char tablero[6][6], char palabraSecreta[6]);

void imprimirAColor (char frase[6], char palabraSecreta[6]);

int jugarPalabra (char tablero[6][6], char palabra[6], char palabraSecreta[6], int intento);