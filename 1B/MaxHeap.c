#include "MaxHeap.h"

#include <stdio.h>
#include <stdlib.h>

MaxHeap inicializarLista() {
    MaxHeap listaVazia;
    listaVazia.tamanho = 0;
    listaVazia.lista = (Aeronave *)malloc(sizeof(Aeronave));
    return listaVazia;
}

MaxHeap inserirAeronave(MaxHeap heap, Aeronave novaAeronave) {
    Aeronave *novaLista = (Aeronave *)realloc(heap.lista, (heap.tamanho + 1) * sizeof(Aeronave));
    heap.lista = novaLista;

    novaAeronave.prioridade = (1000 - novaAeronave.combustivel) + (1440 - novaAeronave.horario) + (500 * novaAeronave.tipo) + (5000 * novaAeronave.emergencia);
    heap.lista[heap.tamanho] = novaAeronave;
    heap.tamanho += 1;

    heap = ordenarLista(heap);

    return heap;
}

MaxHeap carregarLista(MaxHeap heap) {
    FILE *arquivo = fopen("aeronaves.csv", "r");
    if (arquivo == NULL) {
        perror("Nao foi possivel abrir o arquivo");
        return heap;
    }

    char linha[50];
    while (fgets(linha, sizeof(linha), arquivo)) {
        Aeronave nova;

        sscanf(linha, "%[^,],%d,%d,%d,%d",
               nova.identificador,
               &nova.combustivel,
               &nova.horario,
               &nova.tipo,
               &nova.emergencia);

        heap = inserirAeronave(heap, nova);
    }

    fclose(arquivo);
    return heap;
}

MaxHeap ordenarLista(MaxHeap heap) {
    for (int i = (heap.tamanho - 1) / 2; i >= 0; i--) {
        heapify(heap.lista, heap.tamanho, i);
    }
    return heap;
}

MaxHeap removerRaiz(MaxHeap heap) {
    if (heap.tamanho == 0) {
        printf("Heap vazia! Nada a remover.\n");
        return heap;
    }

    heap.lista[0] = heap.lista[heap.tamanho - 1];
    heap.tamanho -= 1;

    Aeronave *novaLista = (Aeronave *)realloc(heap.lista, heap.tamanho * sizeof(Aeronave));
    if (novaLista != NULL) {
        heap.lista = novaLista;
    }

    heapify(heap.lista, heap.tamanho, 0);

    return heap;
}

void heapify(Aeronave *lista, int tamanho, int i) {
    int maior = i;
    int esquerda = 2 * i + 1;
    int direita = 2 * i + 2;

    if (esquerda < tamanho && lista[esquerda].prioridade > lista[maior].prioridade) {
        maior = esquerda;
    }

    if (direita < tamanho && lista[direita].prioridade > lista[maior].prioridade) {
        maior = direita;
    }

    if (maior != i) {
        Aeronave temp = lista[i];
        lista[i] = lista[maior];
        lista[maior] = temp;

        heapify(lista, tamanho, maior);
    }
}