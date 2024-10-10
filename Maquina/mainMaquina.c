#include "maquina.h"

int main() {
    Filtro* filtro = inicializarFiltro();

    char palabraSecreta[TAM_PALABRA + 1] = "sobar";

    actualizarFiltro(filtro, "abasi", palabraSecreta);
    imprimirFiltro(filtro);

    actualizarFiltro(filtro, "basal", palabraSecreta);
    imprimirFiltro(filtro);
    

    return 1;

}