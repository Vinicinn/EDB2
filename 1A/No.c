#include "No.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

No* inicializarArvore() {
    return NULL;
}

No* criarNo(Livro livro) {
    No* novoNo = (No*)malloc(sizeof(No));
    novoNo->livro = livro;
    novoNo->direita = NULL;
    novoNo->esquerda = NULL;
    return novoNo;
}

void inserirLivro(No** raiz, Livro livro) {
    if (*raiz == NULL) {
        *raiz = criarNo(livro);
    } else if (livro.codigo > (*raiz)->livro.codigo) {
        inserirLivro(&(*raiz)->direita, livro);
    } else if (livro.codigo < (*raiz)->livro.codigo) {
        inserirLivro(&(*raiz)->esquerda, livro);
    } else {
        printf("Livro com codigo duplicado nao foi inserido: %d", livro.codigo);
    }
}

void buscar_por_genero(No* raiz, char genero[]) {
    if (raiz != NULL) {
        buscar_por_genero(raiz->esquerda, genero);
        if (strcmp(raiz->livro.genero, genero) == 0) {
            printf("Código: %d, Título: %s, Autor: %s, Gênero: %s, Ano: %d, Editora: %s, Páginas: %d\n",
                   raiz->livro.codigo, raiz->livro.titulo, raiz->livro.autor,
                   raiz->livro.genero, raiz->livro.ano, raiz->livro.editora,
                   raiz->livro.qtdPaginas);
        }
        buscar_por_genero(raiz->direita, genero);
    }
}

No* carregar_livros(char* nomeArquivo, No* raiz) {
    FILE* arquivo = fopen(nomeArquivo, "r");
    if (arquivo == NULL) {
        return raiz;
    }

    Livro livro;
    char linha[100];
    while (fgets(linha, sizeof(linha), arquivo)) {
        sscanf(linha, "%d,%49[^,],%49[^,],%49[^,],%d,%49[^,],%d",
               &livro.codigo, livro.titulo, livro.autor, livro.genero,
               &livro.ano, livro.editora, &livro.qtdPaginas);
        inserirLivro(&raiz, livro);
    }
    return raiz;
}

void exibir_arvore(No* raiz) {
    if (raiz != NULL) {
        exibir_arvore(raiz->esquerda);
        printf("Código: %d, Título: %s, Autor: %s, Gênero: %s, Ano: %d, Editora: %s, Páginas: %d\n",
               raiz->livro.codigo, raiz->livro.titulo, raiz->livro.autor,
               raiz->livro.genero, raiz->livro.ano, raiz->livro.editora,
               raiz->livro.qtdPaginas);
        exibir_arvore(raiz->direita);
    }
}

void liberar_arvore(No* raiz) {
    if (raiz != NULL) {
        liberar_arvore(raiz->esquerda);
        liberar_arvore(raiz->direita);
        free(raiz);
    }
}
