Ignacio Giovannetti, Mateo Giovannetti

# Wordle por Computadora

## Compilación

gcc Maquina/mainMaquina.c Maquina/maquina.c ED_Heap/heap.c -o wordle

## Ejecución

./wordle "palabraSecreta"

Siendo "palabraSecreta" la palabra a adivinar.

# Funcionamiento general

La base de datos es leída e introducida en un Heap en base a su frecuencia. La primera vez que se ejecute, se tomará la raíz de ese Heap. Luego, cada vez que se itere, se tomará la raíz del árbol si esta cumple con las propiedades de un filtro. Al no cumplirlas, se elimina, filtrando el Heap. Cada vez que se dé una palabra, el filtro se hará cada vez más estricto, dando menos palabras para elegir.

## Módulos

|     Jugar   |   Máquina   |   ED_Heap   |
|-------------|-------------|-------------|
| jugador.c   | maquina.c   | heap.c      |
| jugador.h   | maquina.h   | heap.c      |

Esto está ordenado jerárquicamente: **Jugar** depende de las funciones de **Máquina** y esta depende de las funciones de **ED_Heap**.

### Estructura de Datos Heap

Aquí están las implementaciones del Heap, las cuales son:

- **compareRegistros**: Va a determinar que registro tiene mayor prioridad. Primero evalua según frecuencia, si son iguales va a evaluar cual es alfabeticamente mayor.
- **swap**: Intercambia el valor de dos elementos.
- **getMax**: Toma la raíz del heap.
- **insert**: Inserta el elemento en el heap, cumpliendo las propiedades del Heap.
- **heapify**: Verifica si cumple con la propiedad del Heap; de lo contrario, lo acomoda bajándolo.
- **deleteMax**: Elimina la raíz.
- **isEmpty**: Verifica si el árbol es vacío o nulo.
- **printfBFS**: Imprime el Heap en BFS. Sirve para las pruebas.
- **createHeap**: Devuelve un Heap con su respectiva asignación de memoria.
- **freeHeap**: Libera la memoria del Heap.

Las estructuras de datos usadas son:

*Registro*: La cual vincula cada palabra con su frecuencia.

*Heap*: El dato que lleva es de tipo "Registro", tiene una capacidad máxima y un tamaño que se va modificando.

## Juego por Máquina

Este apartado incluye todas las operaciones lógicas para sugerir una palabra. Se transforman las diferentes palabras con sus respectivas frecuencias en un heap. Se elige la de mayor frecuencia (es decir, la raíz del Heap); si cumple con las condiciones del filtro, se mantiene. De lo contrario, se elimina hasta encontrar una palabra que cumpla las propiedades del filtro.

Las funciones usadas son:

- **transformarArchivo**: Lee el archivo y lo transforma en un Heap según la frecuencia de la palabra.
- **sugerirPalabra**: Filtra el Heap según el filtro y cambia el buffer por la nueva palabra. De no poder dar una palabra, devuelve "\0".
- **filtrarHeap**: Filtra el Heap según su raíz. Si esta cumple con el filtro, la mantiene; de lo contrario, la elimina y vuelve a llamar a la función.
- **verificarPalabra**: Dada la palabra y un filtro, dice si lo cumple.
  * Letras Verdes: Se encuentran en la misma posición y son las mismas.
  * Letras Amarillas: Se encuentra la letra amarilla en alguna de las posiciones válidas.
  * Letras No Incluidas: No están esas letras en las letras que no son verdes.
- **actualizarFiltro**: Dado el filtro, la palabra jugada y la palabra secreta, actualiza el filtro con las nuevas propiedades.
  * Letras Verdes: Las letras en las mismas posiciones pasan a ser verdes.
  * Letras Amarillas: Las letras que están presentes en las posiciones que no son verdes se agregan o actualizan. Sus posiciones inválidas son la misma letra y las posiciones de letras verdes.
  * Letras No Incluidas: Las letras que no cumplen ninguna de las características anteriores están excluidas.
- **inicializarFiltro**: Asigna memoria para el filtro. Este empieza con todas las letras en '_', posiciones en 0, y todas las letras incluidas.
- **imprimirFiltro**: Sirve para ver las características del filtro. Este es usado durante las pruebas.

Las estructuras de datos usadas son:

*Filtro*: Tiene las letras verdes; las que no conocemos están señalizadas con un '_'. Letras amarillas, al igual que antes, las que no conocemos están señalizadas con un '_'. Las letras no incluidas están dadas por un mapa de bits, donde cada bit representa un 1 o 0. Si está prendido, significa que la letra no está incluida.

*Letra*: Estructura diseñada únicamente para las letras amarillas. Dada una letra, tiene un arreglo de 5 posiciones de 1 y 0. Si está prendido, significa que es una posición posible para esa letra.

## Jugar

Este apartado conlleva todo lo que es el front-end del programa, teniendo su respectivo **main**. Se toman los argumentos dados al ejecutar y a cada jugada se muestra el tablero (palabras ingresadas en cada ocasión) con su color.

Sus funciones son básicas; aquí su explicación:

- **limpiarTablero**: En cada línea, le copia "-----", para luego imprimir con mayor legibilidad.
- **imprimirTablero**: Imprime las palabras dadas. Luego, solo imprime espacios de las próximas palabras.
- **imprimirColor**: Dada la frase y la palabra secreta, imprime el color asignado a cada letra.
- **jugarPalabra**: Verifica si la palabra que se jugó es la correcta.
