#include <stdio.h>

#include "No.h"

int main() {
    No* raiz = inicializarArvore();
    raiz = carregar_livros("livros.csv", raiz);

    int seletor;
    while (1) {
        printf("\nMenu\n");
        printf("1 - Consultar Livro\n");
        printf("2 - Inserir Livro\n");
        printf("3 - Visualizar Livros\n");
        printf("4 - Sair\n");
        scanf("%d", &seletor);

        if (seletor == 1) {
            char genero[50];
            printf("\nDigite o gênero que deseja consultar:\n");
            scanf(" %[^\n]s", genero);
            printf("\n");
            buscar_por_genero(raiz, genero);

        } else if (seletor == 2) {
            Livro novo;
            printf("\nCódigo do livro: ");
            scanf("%d", &novo.codigo);
            printf("Título do livro: ");
            scanf(" %[^\n]s", novo.titulo);
            printf("Autor do livro: ");
            scanf(" %[^\n]s", novo.autor);
            printf("Gênero do livro: ");
            scanf(" %[^\n]s", novo.genero);
            printf("Ano do livro: ");
            scanf("%d", &novo.ano);
            printf("Editora do livro: ");
            scanf(" %[^\n]s", novo.editora);
            printf("Quantidade de páginas: ");
            scanf("%d", &novo.qtdPaginas);

            inserirLivro(&raiz, novo);
            printf("\nLivro inserido com sucesso!\n");

        } else if (seletor == 3) {
            printf("\nLivros na Árvore (em ordem)\n");
            exibir_arvore(raiz);

        } else if (seletor == 4) {
            break;

        } else {
            printf("\nOpção inválida! Tente novamente.\n");
        }
    }

    liberar_arvore(raiz);
    return 0;
}