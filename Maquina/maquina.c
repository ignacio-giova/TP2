#include "maquina.h"

MaxHeap* transformarArchivo(char* nombreArchivo) { 
    FILE* fd = fopen(nombreArchivo, "r");  // Abrimos el archivo en modo lectura
    if (fd == NULL) {
        printf("No se pudo abrir el archivo.\n");
        return NULL;
    }

    // Contar líneas
    int lineas = 1; //consideramos la primera linea
    char c;
    while ((c = fgetc(fd)) != EOF) {
        if (c == '\n') {
            (lineas)++;
        }
    }

    // Reiniciar el puntero de archivo
    fseek(fd, 0, SEEK_SET);

    // Reservar memoria para los registros
    MaxHeap *heap = createHeap(lineas);

    // Leer registros
    Registro buffer;
    for (int i = 0; i < (lineas); i++) { 
        fscanf(fd, "%5[^,],%d\n", buffer.palabra, &buffer.frecuencia);
        insert(heap, buffer);
    }

    fclose(fd);  // Cerrar el archivo
    return heap;
}

void sugerirPalabra(char *buffer, MaxHeap *heap, Filtro *filtro, char *palabraSecreta){
    heap = filtrarHeap(heap, filtro);
    if(isEmpty(heap)){
        buffer[0] = '\0';
        return;
    }
    Registro aux = getMax(heap);
    deleteMax(heap);
    actualizarFiltro(filtro, aux.palabra, palabraSecreta);
    strcpy(buffer, aux.palabra);
    
    // Actualizar el heap original
}

MaxHeap* filtrarHeap (MaxHeap *a, Filtro* filtro){
    if(isEmpty(a))
        return NULL;

    Registro aux = getMax(a);
    if(verificarPalabra(aux.palabra, filtro))
        return a;
    else{
        deleteMax(a);
        return filtrarHeap(a, filtro);
    }

}


int verificarPalabra(const char *palabra, Filtro *filtro) {
    // Verificamos letras Verdes
    for (int i = 0; i < TAM_PALABRA; i++) {
        if (filtro->letrasVerdes[i] != '_' && palabra[i] != filtro->letrasVerdes[i]) {
            return 0;
        }
    }
    
    // Verificar letras amarillas
    for (int i = 0; i < TAM_PALABRA; i++) {
    if (filtro->letrasAmarillas[i].letra != '_') {  // Solo verificar si hay letra amarilla
        int encontro = 0;
        for (int j = 0; j < TAM_PALABRA && !encontro; j++) {
            if (filtro->letrasAmarillas[i].posiciones[j] 
                && palabra[j] == filtro->letrasAmarillas[i].letra) {
                encontro = 1;
            }
        }
        if (!encontro)
            return 0;  // Si no encuentra una letra amarilla, la palabra no es válida
    }
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
        for (int j = 0; j < TAM_PALABRA; j++) {
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
    char aux[TAM_PALABRA]; // Si hay un '_' significa que ya nos encargamos de esa letra
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
