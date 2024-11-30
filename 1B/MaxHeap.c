#include "MaxHeap.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

MaxHeap inicializarLista()
{
    MaxHeap listaVazia;
    listaVazia.tamanho = 0;
    listaVazia.lista = (Aeronave *)malloc(sizeof(Aeronave));
    return listaVazia;
}

MaxHeap inserirAeronave(MaxHeap heap, Aeronave novaAeronave)
{
    if (verificarIdentificador(heap, novaAeronave.identificador))
    {
        printf("\nIdentificador ja em uso\n");
        return heap;
    }

    Aeronave *novaLista = (Aeronave *)realloc(heap.lista, (heap.tamanho + 1) * sizeof(Aeronave));
    heap.lista = novaLista;

    novaAeronave.prioridade = (1000 - novaAeronave.combustivel) + (1440 - novaAeronave.horario) + (500 * novaAeronave.tipo) + (5000 * novaAeronave.emergencia);
    heap.lista[heap.tamanho] = novaAeronave;
    heap.tamanho += 1;

    heap = ordenarLista(heap);

    return heap;
}

MaxHeap carregarLista(MaxHeap heap)
{
    FILE *arquivo = fopen("aeronaves.csv", "r");
    if (arquivo == NULL)
    {
        perror("Nao foi possivel abrir o arquivo");
        return heap;
    }

    char linha[50];
    while (fgets(linha, sizeof(linha), arquivo))
    {
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

MaxHeap ordenarLista(MaxHeap heap)
{
    for (int i = (heap.tamanho - 1) / 2; i >= 0; i--)
    {
        heapify(heap.lista, heap.tamanho, i);
    }
    return heap;
}

MaxHeap removerRaiz(MaxHeap heap)
{
    if (heap.tamanho == 0)
    {
        printf("Heap vazia! Nada a remover.\n");
        return heap;
    }

    heap.lista[0] = heap.lista[heap.tamanho - 1];
    heap.tamanho -= 1;

    Aeronave *novaLista = (Aeronave *)realloc(heap.lista, heap.tamanho * sizeof(Aeronave));
    if (novaLista == NULL && heap.tamanho > 0)
    {
        perror("Falha ao realocar memória");
        exit(EXIT_FAILURE);
    }
    heap.lista = novaLista;

    heapify(heap.lista, heap.tamanho, 0);

    return heap;
}

void heapify(Aeronave *lista, int tamanho, int i)
{
    int maior = i;
    int esquerda = 2 * i + 1;
    int direita = 2 * i + 2;

    if (esquerda < tamanho && lista[esquerda].prioridade > lista[maior].prioridade)
    {
        maior = esquerda;
    }

    if (direita < tamanho && lista[direita].prioridade > lista[maior].prioridade)
    {
        maior = direita;
    }

    if (maior != i)
    {
        Aeronave temp = lista[i];
        lista[i] = lista[maior];
        lista[maior] = temp;

        heapify(lista, tamanho, maior);
    }
}

int verificarIdentificador(MaxHeap heap, char id[10])
{
    for (int i = 0; i < heap.tamanho; i++)
    {
        if (strcmp(heap.lista[i].identificador, id) == 0)
        {
            return 1;
        }
    }
    return 0;
}

void imprimirEmOrdem(MaxHeap heap)
{
    MaxHeap heapTemp;
    heapTemp.tamanho = heap.tamanho;
    heapTemp.lista = (Aeronave *)malloc(heapTemp.tamanho * sizeof(Aeronave));
    if (heapTemp.lista == NULL)
    {
        printf("\nfalha ao alocar memoria.\n");
    }
    else
    {
        for (int i = 0; i < heapTemp.tamanho; i++)
        {
            heapTemp.lista[i] = heap.lista[i];
        }

        printf("\nAeronaves em ordem\n");
        while (heapTemp.tamanho > 0)
        {
            Aeronave maior = heapTemp.lista[0];
            printf("Identificador: %s, Combustível: %d, Horário: %d, Tipo: %d, Emergência: %d, Prioridade: %d\n",
                   maior.identificador, maior.combustivel, maior.horario,
                   maior.tipo, maior.emergencia, maior.prioridade);
            heapTemp = removerRaiz(heapTemp);
        }
    }
}

MaxHeap atualizarAeronave(MaxHeap heap, Aeronave novaAeronave)
{
    novaAeronave.prioridade = (1000 - novaAeronave.combustivel) + (1440 - novaAeronave.horario) + (500 * novaAeronave.tipo) + (5000 * novaAeronave.emergencia);
    for (int i = 0; i < heap.tamanho; i++)
    {
        if (strcmp(heap.lista[i].identificador, novaAeronave.identificador) == 0)
        {
            heap.lista[i] = novaAeronave;
            heap = ordenarLista(heap);
            return heap;
        }
    }
}
