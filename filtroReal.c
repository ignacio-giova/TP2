#include <stdio.h>
#include <string.h>

#define TAM_PALABRA 5

typedef struct {
    char letra;
    int posiciones[5]; //Una letra en amarillo solo puede ocupar 4 espacios
} Letra;

typedef struct {
    char letrasVerdes[TAM_PALABRA]; // Letras en la posición correcta
    Letra letrasAmarillas[5]; // A lo sumo habra 5 letras amarillas Q PASA CUANDO HAY MENOS?
    int letrasNoIncluidas[26]; // Letras que no están en la palabra
} Filtro;


int verificarPalabra(const char *palabra, Filtro *filtro) {
    printf("Corte 6\n");
    // Verificamos letras Verdes
    for (int i = 0; i < TAM_PALABRA; i++) {
        if (filtro->letrasVerdes[i] != '_' && palabra[i] != filtro->letrasVerdes[i]) {
            return 0;
        }
    }
    
    printf("Corte 1\n");

    // Verificar letras amarillas
     for(int i = 0; i < 5 && filtro->letrasAmarillas[i].letra != '_'; i++){
        int encontro = 0;
        printf("Corte 8\n");
        for (int j= 0; j < TAM_PALABRA && !encontro; j++){
            if (filtro->letrasAmarillas[i].posiciones[j] //Verifica que sea una posicion posible de la letra
            && filtro->letrasAmarillas[i].letra == palabra[j] //Verifica que las letras sean iguales
            && filtro->letrasVerdes[j] == '_') // Verifica que no sea una letra verde
            encontro = 1;
        }
        if (!encontro)
            return 0;
     }

    // Verificamos letras no incluidas
    for (int i = 0; i < TAM_PALABRA; i++) {
        if (filtro->letrasNoIncluidas[palabra[i] - 'a']) { //CAMBIAR FORMA PARA LETRAS REPETIDAS!!!!
            printf("Corte 4\n");
            return 0; // Si alguna letra está en letrasNoIncluidas, la palabra es inválida
        }
    }

    return 1; // Si pasa todas las verificaciones, es válida
}

void inicializarFiltro(Filtro *filtro) {
    // Inicializar letras verdes con '_'
    for (int i = 0; i < TAM_PALABRA; i++) {
        filtro->letrasVerdes[i] = '_';
    }

    // Inicializar letras amarillas
    for (int i = 0; i < TAM_PALABRA; i++) {
        filtro->letrasAmarillas[i].letra = '_';  // Letra amarilla vacía
        for (int j = 0; j < 5; j++) {
            filtro->letrasAmarillas[i].posiciones[j] = 0; // Ninguna posición válida aún
        }
    }

    // Inicializar letras no incluidas
    for (int i = 0; i < 26; i++) {
        filtro->letrasNoIncluidas[i] = 0;  // Ninguna letra excluida inicialmente
    }
}

void actualizarFiltro(Filtro *filtro, const char *palabra, const char *palabraSecreta){
    char aux[5]; //Si hay un '_' significa que ya nos encargamos de esa letra
    strcpy(aux, palabra);

    //Letras Verdes
    for(int i = 0; i < TAM_PALABRA; i++){
        if (aux[i] == palabraSecreta[i]){
            filtro->letrasVerdes[i] = aux[i];
            aux[i] = '_';
        }
    }
    //Letras Amarillas
    for (int i = 0; i < TAM_PALABRA; i++){ //Recorre aux
        for (int j = 0; j < TAM_PALABRA && aux[i] != '_'; j++){ //Recorre Secreta
            if(aux[i] == palabraSecreta[j] && aux[j] != '_'){
                filtro->letrasAmarillas[POSICION].letra = aux[i];
                for (int m = 0; m < TAM_PALABRA; m++){

                }
            }
    }
    }

    //Letras No inlcuidas
    for(int i= 0; i < TAM_PALABRA; i++){
        if(aux[i] != '_')
            filtro->letrasNoIncluidas[aux[i] - 'a'] = 1;
    }
}

int main() {
    Filtro filtro;
    inicializarFiltro(&filtro);

    filtro.letrasAmarillas[0].letra = 'b';
    for(int i = 0; i < 5; i++){
        filtro.letrasAmarillas[0].posiciones[i] = 1;
    }

    filtro.letrasAmarillas[1].letra = 'm';
    for(int i = 4; i < 5; i++){
        filtro.letrasAmarillas[1].posiciones[i] = 1;
    }


    filtro.letrasNoIncluidas['l' - 'a'] = 1;

    // Probar palabra
    char palabra[6];
    printf("Di la palabra a probar: ");
    scanf("%5s", palabra);  // Limitamos el número de caracteres a 5
    printf("Corte 5\n");
    printf("%d\n", verificarPalabra(palabra, &filtro));
    return 0;
}
