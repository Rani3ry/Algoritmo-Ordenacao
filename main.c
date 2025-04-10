#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

void gerarNumerosAleatorios(int *array, int tamanho) {
    for (int i = 0; i < tamanho; i++) {
        array[i] = rand() % 100; // Altere o intervalo conforme necessário
    }
}

void mostrarNumeros(int *array, int tamanho) {
    for (int i = 0; i < tamanho; i++) {
        printf("%d ", array[i]);
    }
    printf("\n");
}

int passagens_bubble = 0;
int passagens_quick = 0;
int passagens_heap = 0;

void bubbleSort(int *array, int tamanho) {
    int i, j;
    
    for (i = 0; i < tamanho-1; i++) {
        for (j = 0; j < tamanho-i-1; j++) {
            if (array[j] > array[j+1]) {
                int temp = array[j];
                array[j] = array[j+1];
                array[j+1] = temp;
                passagens_bubble++;
            }
        }
    }
}

int partition(int *array, int inicio, int fim) {
    int pivo = array[fim];
    int i = (inicio - 1);

    for (int j = inicio; j <= fim - 1; j++) {
        if (array[j] <= pivo) {
            i++;
            int temp = array[i];
            array[i] = array[j];
            array[j] = temp;
            passagens_quick++;
        }
    }

    int temp = array[i + 1];
    array[i + 1] = array[fim];
    array[fim] = temp;

    return (i + 1);
}

void quickSort(int *array, int inicio, int fim) {
    if (inicio < fim) {
        int pi = partition(array, inicio, fim);
        quickSort(array, inicio, pi - 1);
        quickSort(array, pi + 1, fim);
    }
}

void heapify(int *array, int tamanho, int indice) {
    int maior = indice; 
    int filho_esq = 2 * indice + 1; 
    int filho_dir = 2 * indice + 2; 

    if (filho_esq < tamanho && array[filho_esq] > array[maior])
        maior = filho_esq;

    if (filho_dir < tamanho && array[filho_dir] > array[maior])
        maior = filho_dir;

    if (maior != indice) {
        int temp = array[indice];
        array[indice] = array[maior];
        array[maior] = temp;
        passagens_heap++;

        heapify(array, tamanho, maior);
    }
}

void heapSort(int *array, int tamanho) {
    for (int i = tamanho / 2 - 1; i >= 0; i--)
        heapify(array, tamanho, i);

    for (int i = tamanho - 1; i > 0; i--) {
        int temp = array[0];
        array[0] = array[i];
        array[i] = temp;

        heapify(array, i, 0);
    }
}


int main() {
    srand(time(NULL));

    int tamanho;
    printf("Digite a quantidade de números: ");
    scanf("%d", &tamanho);

    int *numeros = (int *)malloc(tamanho * sizeof(int));
    gerarNumerosAleatorios(numeros, tamanho);

    printf("Números gerados: ");
    mostrarNumeros(numeros, tamanho);

    // Bubble Sort
    int *copiaBubble = (int *)malloc(tamanho * sizeof(int));
    memcpy(copiaBubble, numeros, tamanho * sizeof(int));

    clock_t inicioBubble = clock();
    bubbleSort(copiaBubble, tamanho);
    clock_t fimBubble = clock();

    double tempoBubble = ((double)(fimBubble - inicioBubble)) / CLOCKS_PER_SEC;
    printf("\nNúmeros ordenados (Bubble Sort): ");
    mostrarNumeros(copiaBubble, tamanho);
    printf("Tempo do Bubble Sort: %f segundos\n", tempoBubble);
    printf("Passagens do Bubble Sort: %d\n", passagens_bubble);

    // Quick Sort
    int *copiaQuick = (int *)malloc(tamanho * sizeof(int));
    memcpy(copiaQuick, numeros, tamanho * sizeof(int));

    clock_t inicioQuick = clock();
    quickSort(copiaQuick, 0, tamanho - 1);
    clock_t fimQuick = clock();

    double tempoQuick = ((double)(fimQuick - inicioQuick)) / CLOCKS_PER_SEC;
    printf("\nNúmeros ordenados (Quick Sort): ");
    mostrarNumeros(copiaQuick, tamanho);
    printf("Tempo do Quick Sort: %f segundos\n", tempoQuick);
    printf("Passagens do Quick Sort: %d\n", passagens_quick);

    // Heap Sort
    int *copiaHeap = (int *)malloc(tamanho * sizeof(int));
    memcpy(copiaHeap, numeros, tamanho * sizeof(int));

    clock_t inicioHeap = clock();
    heapSort(copiaHeap, tamanho);
    clock_t fimHeap = clock();

    double tempoHeap = ((double)(fimHeap - inicioHeap)) / CLOCKS_PER_SEC;
    printf("\nNúmeros ordenados (Heap Sort): ");
    mostrarNumeros(copiaHeap, tamanho);
    printf("Tempo do Heap Sort: %f segundos\n", tempoHeap);
    printf("Passagens do Heap Sort: %d\n", passagens_heap);

    // Libera a memória alocada
    free(numeros);
    free(copiaBubble);
    free(copiaQuick);
    free(copiaHeap);

    printf("\nPressione Enter para sair...");
    getchar();
    getchar();

    return 0;
}


