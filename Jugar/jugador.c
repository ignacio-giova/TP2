#include "jugador.h"

int main(int argc, char *argv[]) {
    if (argc != 2 || strlen(argv[1]) != (TAM_PALABRA - 1)){
        printf("Ingrese los argumentos correctamente");
        return 1;
    }

    char palabraSecreta[TAM_PALABRA];
    strcpy(palabraSecreta, argv[1]);

    system("clear");
    char tablero[INTENTOS][TAM_PALABRA];
    limpiarTablero(tablero);
    imprimirTablero (tablero, palabraSecreta);    

    MaxHeap *heap = transformarArchivo("3.txt");
    Filtro *filtro = inicializarFiltro();


    int bandera = 0;
    char buffer[TAM_PALABRA];
    for(int i=0; i < INTENTOS && !bandera; i++){
        sugerirPalabra(buffer, heap, filtro, palabraSecreta);
        if (strlen(buffer) == 0) {
            bandera = 2;
        }
        else{
        bandera = jugarPalabra (tablero, buffer, palabraSecreta, i);
        system("clear");
        imprimirTablero (tablero, palabraSecreta); 
        }
    }

    if(bandera == 1)
        printf("Has ganado!\n");
    else if (bandera == 2)
        printf("No se conoce la palabra\n");
        else
        printf("Perdiste! La palabra era: %s\n", palabraSecreta);


    freeHeap(heap);
    free(filtro);
    return 1;
}
void limpiarTablero (char tablero[INTENTOS][TAM_PALABRA]){
    for (int i=0; i < INTENTOS; i++){
        strcpy(tablero[i], "_____");
    }
}

void imprimirTablero (char tablero[INTENTOS][TAM_PALABRA], char palabraSecreta[TAM_PALABRA]){
    for(int i=0; i <INTENTOS ; i++){
        if (tablero[i][0] == '_'){
            printf("%s \n", tablero[i]);
        }
        else{
            imprimirAColor(tablero[i], palabraSecreta);
            printf("\n");
        }
    }
}

void imprimirAColor (char frase[TAM_PALABRA], char palabraSecreta[TAM_PALABRA]){
    //Transformar Todas las frases en minusuclas!!
    //Los colores son:
    //0 Gris
    //1 Verde
    //2 Naranja

    char aux[TAM_PALABRA];
    strcpy(aux, palabraSecreta); 

    int numerosColores[TAM_PALABRA] = {0, 0, 0, 0, 0};

    for(int i=0; i < TAM_PALABRA; i++){
        if (frase[i] == aux[i]){
            numerosColores[i] = 1;
            aux[i] = '_';
        }
    }

    for(int i= 0; i < TAM_PALABRA; i++){
        for(int j= 0; j < TAM_PALABRA && numerosColores[i] == 0; j++){
            if (frase[i] == aux[j]){
                numerosColores[i] = 2;
                aux[j] = '_';
            }
        }
    }

    for(int i= 0; i < TAM_PALABRA; i++){
        if(numerosColores[i] == 1)
            printf(GREEN "%c" RESET, frase[i]);
        else if (numerosColores[i] == 2)
            printf(ORANGE "%c" RESET, frase[i]);
            else
            printf("%c", frase[i]);
    }


}

int jugarPalabra (char tablero[INTENTOS][TAM_PALABRA], char palabra[TAM_PALABRA], char palabraSecreta[TAM_PALABRA], int intento){
    strcpy (tablero[intento], palabra);

    return (strcmp(palabra, palabraSecreta) == 0);
}