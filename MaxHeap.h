#ifndef MAX_HEAP_H
#define MAX_HEAP_H

#include "Aeronave.h"

typedef struct MaxHeap
{
    int tamanho;
    Aeronave *lista;
} MaxHeap;

MaxHeap inicializarLista();
MaxHeap inserirAeronave(MaxHeap heap, Aeronave novaAeronave);
MaxHeap carregarLista(MaxHeap heap);
MaxHeap ordenarLista(MaxHeap heap);
MaxHeap removerRaiz(MaxHeap heap);

void heapify(Aeronave *lista, int tamanho, int i);
int verificarIdentificador(MaxHeap heap, char id[10]);
void imprimirEmOrdem(MaxHeap heap);
MaxHeap atualizarAeronave(MaxHeap heap, Aeronave novaAeronave);

#endif