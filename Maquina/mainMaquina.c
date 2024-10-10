#include "maquina.h"

int main() {
    Filtro* filtro = inicializarFiltro();

    char palabraSecreta[TAM_PALABRA + 1] = "sobar";

    imprimirFiltro(filtro);
    actualizarFiltro(filtro, "abasi", palabraSecreta);
    imprimirFiltro(filtro);
    

    return 1;

}