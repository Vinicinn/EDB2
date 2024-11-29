#include <stdio.h>

#include "MaxHeap.h"

int main() {
    MaxHeap heap = inicializarLista();
    heap = carregarLista(heap);

    int seletor;
    while (1) {
        printf("\nMenu\n");
        printf("1 - Inserir aeronave\n");
        printf("2 - Consultar maior prioridade\n");
        printf("3 - Remover maior prioridade\n");
        printf("4 - Atualizar prioridade\n");
        printf("5 - Exibir todas as aeronaves\n");
        printf("6 - Sair\n");
        scanf("%d", &seletor);

        if (seletor == 1) {
            Aeronave nova;
            printf("Identificador da aeronave:\n");
            scanf(" %[^\n]s", nova.identificador);
            printf("Combustivel:\n");
            scanf("%d", &nova.combustivel);
            printf("Horario:\n");
            scanf("%d", &nova.horario);
            printf("Tipo:\n");
            scanf("%d", &nova.tipo);
            printf("Emergencia:\n");
            scanf("%d", &nova.emergencia);

            heap = inserirAeronave(heap, nova);
        } else if (seletor == 2) {
            printf("\nAeronave com maior prioridade:\n");
            printf("Identificador: %s, Combustivel: %d, Horario: %d, Tipo: %d, Emergencia: %d, Prioridade: %d\n", heap.lista[0].identificador, heap.lista[0].combustivel, heap.lista[0].horario, heap.lista[0].tipo, heap.lista[0].emergencia, heap.lista[0].prioridade);
        } else if (seletor == 3) {
            removerRaiz(heap);
        }

        else if (seletor == 5) {
            if (heap.tamanho == 0) {
                printf("Heap vazia.");
            } else {
                for (int i = 0; i < heap.tamanho; i++) {
                    Aeronave a = heap.lista[i];
                    printf("Identificador: %s, Combustível: %d, Horário: %d, Tipo: %d, Emergência: %d, Prioridade: %d\n",
                           a.identificador, a.combustivel, a.horario, a.tipo, a.emergencia, a.prioridade);
                }
            }

        } else if (seletor == 6) {
            break;
        }
    }

    return 0;
}