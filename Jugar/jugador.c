#include "jugador.h"

int main(int argc, char *argv[]) {
    if (argc != 2 || strlen(argv[1]) != 5){
        printf("Ingrese los argumentos correctamente");
        return 1;
    }

    char palabraSecreta[6];
    strcpy(palabraSecreta, argv[1]);

    system("clear");
    char tablero[6][6];
    limpiarTablero(tablero);
    imprimirTablero (tablero, palabraSecreta);    

    MaxHeap *heap = transformarArchivo("2.txt");
    Filtro *filtro;
    inicializarFiltro(filtro);


    int bandera = 0;
    char *buffer;
    for(int i=0; i <= 6 && !bandera; i++){
        sugerirPalabra(buffer, heap, filtro, palabraSecreta);
        bandera = jugarPalabra (tablero, buffer, palabraSecreta, i);
        system("clear");
        imprimirTablero (tablero, palabraSecreta); 
    }

    if(bandera)
        printf("Has ganado!\n");
    else
        printf("Perdiste! La palabra era: %s\n", palabraSecreta);


    freeHeap(heap);
    return 1;
}
void limpiarTablero (char tablero[6][6]){
    for (int i=0; i <= 6; i++){
        strcpy(tablero[i], "_____");
    }
}

void imprimirTablero (char tablero[6][6], char palabraSecreta[6]){
    for(int i=0; i <=6 ; i++){
        if (tablero[i][0] == '_'){
            printf("%s \n", tablero[i]);
        }
        else{
            imprimirAColor(tablero[i], palabraSecreta);
            printf("\n");
        }
    }
}

void imprimirAColor (char frase[6], char palabraSecreta[6]){
    //Transformar Todas las frases en minusuclas!!
    //Los colores son:
    //0 Gris
    //1 Verde
    //2 Naranja

    char aux[6];
    strcpy(aux, palabraSecreta); 

    int numerosColores[6] = {0, 0, 0, 0, 0, 0};

    for(int i=0; i < 6; i++){
        if (frase[i] == aux[i]){
            numerosColores[i] = 1;
            aux[i] = '_';
        }
    }

    for(int i= 0; i < 6; i++){
        for(int j= 0; j < 6 && numerosColores[i] == 0; j++){
            if (frase[i] == aux[j]){
                numerosColores[i] = 2;
                aux[j] = '_';
            }
        }
    }

    for(int i= 0; i < 6; i++){
        if(numerosColores[i] == 1)
            printf(GREEN "%c" RESET, frase[i]);
        else if (numerosColores[i] == 2)
            printf(ORANGE "%c" RESET, frase[i]);
            else
            printf("%c", frase[i]);
    }


}

int jugarPalabra (char tablero[6][6], char palabra[6], char palabraSecreta[6], int intento){
    strcpy (tablero[intento], palabra);

    return (strcmp(palabra, palabraSecreta) == 0);
}