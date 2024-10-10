#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TAM_PALABRA 5

typedef struct {
    char letra;
    int posiciones[5]; //Una letra en amarillo solo puede ocupar 5 espacios
} Letra;

typedef struct {
    char letrasVerdes[5]; // Letras en la posición correcta
    Letra letrasAmarillas[5]; // A lo sumo habra 5 letras amarillas
    int letrasNoIncluidas[26]; // Letras que no están en la palabra
} Filtro;


int verificarPalabra(const char *palabra, Filtro *filtro) {
    // Verificamos letras Verdes
    for (int i = 0; i < TAM_PALABRA; i++) {
        if (filtro->letrasVerdes[i] != '_' && palabra[i] != filtro->letrasVerdes[i]) {
            return 0;
        }
    }
    
    // Verificar letras amarillas
    for(int i = 0; i < TAM_PALABRA && filtro->letrasAmarillas[i].letra != '_'; i++){
        int encontro = 0;
        for (int j= 0; j < TAM_PALABRA && !encontro; j++){
            if(filtro->letrasAmarillas[i].posiciones[j] 
                && palabra[j] == filtro->letrasAmarillas[i].letra)
                encontro = 1;
        }
        if (encontro)
            return 0;
    }

    // Verificamos letras no incluidas
    for (int i = 0; i < TAM_PALABRA; i++) {
        if (filtro->letrasNoIncluidas[palabra[i] - 'a'] && filtro->letrasVerdes[i] == '_') { //Se fija si no esta incluidas en las q no son verdes
            return 0; // Si alguna letra está en letrasNoIncluidas, la palabra es inválida
        }
    }

    return 1; // Si pasa todas las verificaciones, es válida
}

Filtro* inicializarFiltro() {
    Filtro *filtro = malloc(sizeof(Filtro));
    if (filtro == NULL) {
    // Manejo de error de memoria
    }

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

    return filtro;
}

void actualizarFiltro(Filtro *filtro, const char *palabra, const char *palabraSecreta){
    char aux[5]; // Si hay un '_' significa que ya nos encargamos de esa letra
    strcpy(aux, palabra);

    // Letras Verdes
    for(int i = 0; i < TAM_PALABRA; i++){
        if (aux[i] == palabraSecreta[i]){
            filtro->letrasVerdes[i] = aux[i];
            aux[i] = '_';
        }
    }

    // Letras Amarillas
    for(int i = 0; i < TAM_PALABRA; i++){
        int encontro = 0;
        for(int j= 0; j < TAM_PALABRA && aux[i] != '_' && !encontro; j++){
            if(aux[i]==palabraSecreta[j] && filtro->letrasVerdes[j] == '_'){
                int k = 0, bandera = 0;
                for (k = 0; k < TAM_PALABRA && filtro->letrasAmarillas[k].letra != '_' && !bandera; k++){
                    if (filtro->letrasAmarillas[k].letra == aux[i]){
                    bandera = 1;
                    k--;
                    }
                }
                if(!bandera){
                    filtro->letrasAmarillas[k].letra = aux[i];
                    for(int m = 0; m < TAM_PALABRA; m++)
                        filtro->letrasAmarillas[k].posiciones[m] = 1;
                }
                for (int z = 0; z < TAM_PALABRA; z++){ //ACA
                    if (filtro->letrasVerdes[z] != '_' || i == z)
                        filtro->letrasAmarillas[k]. posiciones[z] = 0;
                }
                aux[i] = '_';
                encontro = 1;
            }
        }
    }

    // Actualización extra: letras amarillas que ahora son verdes
    for(int i = 0; i < TAM_PALABRA; i++){
        if(filtro->letrasVerdes[i] != '_'){
            // Si alguna letra que era amarilla ahora está verde, limpiamos sus posiciones
            for(int j = 0; j < TAM_PALABRA; j++){
                if(filtro->letrasAmarillas[j].letra == filtro->letrasVerdes[i]){
                    for(int z = 0; z < TAM_PALABRA; z++)
                        filtro->letrasAmarillas[j].posiciones[z] = 0; // Limpia todas las posiciones
                    filtro->letrasAmarillas[j].letra = '_'; // Remueve la letra amarilla ya que ahora es verde
                }
            }
        }
    }
 

    // Letras No Incluidas
    for(int i= 0; i < TAM_PALABRA; i++){
        if(aux[i] != '_')
            filtro->letrasNoIncluidas[aux[i] - 'a'] = 1;
    }

}


void imprimirFiltro(Filtro *filtro) {
    printf("Letras Verdes: ");
    for (int i = 0; i < TAM_PALABRA; i++) {
        printf("%c ", filtro->letrasVerdes[i]);
    }
    printf("\n");

    printf("Letras Amarillas:\n");
    for (int i = 0; i < TAM_PALABRA; i++) {
        if (filtro->letrasAmarillas[i].letra != '_') {
            printf("%c: ", filtro->letrasAmarillas[i].letra);
            for (int j = 0; j < TAM_PALABRA; j++) {
                printf("%d ", filtro->letrasAmarillas[i].posiciones[j]);
            }
            printf("\n");
        }
    }

    printf("Letras No Incluidas: ");
    for (int i = 0; i < 26; i++) {
        if (filtro->letrasNoIncluidas[i]) {
            printf("%c ", 'a' + i);
        }
    }
    printf("\n");
}


int main() {
    Filtro* filtro = inicializarFiltro();

    char palabraSecreta[TAM_PALABRA + 1] = "sobar";
    
    actualizarFiltro(filtro, "abasi", palabraSecreta);
    imprimirFiltro(filtro);

    printf("Conoce la palabra: %i\n", verificarPalabra("basal" , filtro));

    actualizarFiltro(filtro, "basal", palabraSecreta);
    imprimirFiltro(filtro);

    printf("Conoce la palabra: %i\n", verificarPalabra("untar" , filtro));

    return 0;

}