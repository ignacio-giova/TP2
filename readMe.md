-- Ignacio Giovannetti, Mateo Giovannetti

# Wordle por Computadora

## Compilacion

> gcc Maquina/mainMaquina.c Maquina/maquina.c ED_Heap/heap.c -o wordle

## Ejecución

> ./worlde "palabraSecreta"

Siendo la palabra secreta la palabra a adivinar.

# Funcionamiento general

La base de datos es leida e introducida en un Heap en base a su frecuencia. La primera vez que se ejecute se tomara la raiz de ese Heap. Luego, cada vez que se itere se tomara la raiz del arbol si esta cumple con las propiedades de un filtro. Al no complirlas, se la elimina, filtrando el heap. Cada vez que demos una palabra el filtro se hara cada vez mas estricto dando menos palabras para elejir.

## Modulos

|     Jugar   |   Maquina   |   ED_Heap   |
|-------------|-------------|-------------|
| jugador.c   | maquina.c   | heap.c      |
| jugador.h   | maquina.h   | heap.c      |

Esto estad ordenado jerarquicamente, **Jugar** depende de las funciones de **Maquina** y este depende de las funciones de **ED_Heap**

### Estructura Datos Heap

Aca estan las implementaciones del Heap, los cuales son:

- **swap**: Intercambia el valor de dos elementos

- **getMax**: Toma la raiz del heap

- **insert**: Inserta el elemento en el heap, cumpliendo propiedades Heap.

- **heapify**: Verifica si cumple propiedad del Heap, de lo contrario lo acomoda bajandolo

- **deleteMax**: Elimina la raiz

- **isEmpty**: Verifica el arbol es vacio o nulo

- **printfBFS**: Imprime el Heap en BFS. Sirve para las pruebas

- **createHeap**: Devuelve un Heap con su respectiva asignacion de memoria

- **freeHeap**: Libera la memoria del Heap

Las Estructuras de datos usadas son:

<u>*Registro*</u>: La cual a cada palabra le vincula su frecuencia

<u>*Heap*</u>: El dato que lleva es de tipo "Registro", tiene una capacidad maxima y un tamaño segun lo vayamos modificando

## Juego por Maquina

Este apartado incluye todas las operacione logicas para sugerir una frase. Se va a transformar las diferentes palabras con sus respectivas frecuencias en un heap. Se va a elegir la de mayor frecuencia (es decir, raiz Heap), si cumple con las condiciones del filtro la palabra. De lo contrario, se la va a eliminar hasta encontrar una palabra que cumpla las propiedades del filtro.

Las funciones usadas son:

- **transformarArhcivo**: Lee el archivo y lo transforma a un Heap segun la frecuencia de la palabra

- **sugerirPalabra**: Va a filtrar el Heap segun el filtro, y va a cambiar el buffer por la nueva palabra. De no poder dar una palabra devuelve "\0"

- **filtrarHeap**: Va a filtrar el Heap segun su Raiz. Si esta cumple con el filtro la deja, por lo contrario la eliminar y vuelve a llamar a la funcion.

- **verificarPalabra**: Dada la palabra y un filtro dice si lo cumple.

  * LetrasVerdes: Se encuentren en la misma posicion y sean las mismas
  * LetrasAmarillas: Se encuentre la letra amarilla en alguna de las posiciones validas
  * LetrasNoIncluidas: No esten esas letras en las letras que no sean verdes.

- **acutalizarFiltro**: Dado el filtro, la palabra jugada y la palabra secreta, actualiza el filtro con las nuevas propiedades

  * LetrasVerdes: Las letras en las mismas posiciones pasan a ser verdes
  * LetrasAmarillas: Las letras que estan presentes en las posiciones que no son verdes. Se agrega o actualiza. Siendo que sus posiciones invalidas son la misma letra, y  posiciones de letras verdes.
  * LetrasNoIncluidas: Las letras que no cumplenm ninguna de las caracteristicas de las letras anteriores estan exlcuidas.

- **inicializarFiltro**: Asigna memoria para el filtro. Este empieza con todas las letras en '_', posiciones en 0, y todas las letras incluidas. 

- **imprimirFiltro**: Sirve para ver las caracteristicas del filtro. Este es usado durante las pruebas

Las Estructuras de datos usadas son:

<u>*Filtro*</u>: Tiene las letras verdes, las que no conocemos son señalizadas con un '_'. Letras amarillas, al igual que antes, las que no conocemos son señalizadas con un '_'. Las letras no incluidas estan dadas por un mapa de bits, el cual cada bit representa un 1 o 0. Si esta prendido significa que la letra no esta incluida.

<u>*Letra*</u>: Estructura diseñada unicamente para las letras amarillas. Dada una letra tiene un arreglo de 5 posiciones de 1 y 0. Si esta prendido signific aque es una posicion posible para esa letra.

## Jugar

Este apartado conlleva todo lo que es el Front-End del programa, teniendo su respectivo **main**. Se toma los argumentos dados al ejecutar y a cada jugada muestra el tablero (palabras ingresadas en cada ocasion) con su color.

Sus funciones son basicas, aca su explicacion: 

- **limpiarTablero**: En cada linea le copia "-----", asi luego imprimir con mayor legibilidad.

- **imprimirTablero**: Imprime las palabras dadas. Luego solo imprime espacios de las proximas palabras

- **imprimirColor**: Dada la frase y la palabra secreta, imprime el color asignado a cada letra

- **jugarPalabra**: Verifica si la palabra que se jugo es la correcta