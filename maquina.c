#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char palabra[6];
    int frecuencia;
} Registro;

void transformarArchivo(char* nombreArchivo);

int main() {

    FILE *archivoEntrada = fopen("2.txt", "r+");
      if (archivoEntrada == NULL) {
        printf("No se pudo abrir el archivo");
        return 1;
      }

    Registro *registros = transformarArchivo(FILE *archivoEntrada);



    return 0;
}

void transformarArchivo(char* nombreArchivo) {
    


}
