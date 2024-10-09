#include "heap.h"

int main() {
    MaxHeap *heap = createHeap(10);

    insert(heap, 10);
    insert(heap, 20);
    insert(heap, 15);
    insert(heap, 30);
    insert(heap, 1);
    insert(heap, 1);

    printf("Máximo: %d\n", getMax(heap));

    deleteMax(heap);
    printf("Máximo después de eliminar: %d\n", getMax(heap));

    printBFS(heap);

    freeHeap(heap);


    return 0;
}
