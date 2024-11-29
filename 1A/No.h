#ifndef NO_H
#define NO_H

#include "Livro.h"

typedef struct No No;

struct No {
    Livro livro;
    No* direita;
    No* esquerda;
};

No* inicializarArvore();
No* criarNo(Livro livro);
void inserirLivro(No** raiz, Livro livro);
void buscar_por_genero(No* raiz, char genero[]);
No* carregar_livros(char* nomeArquivo, No* raiz);
void exibir_arvore(No* raiz);
void liberar_arvore(No* raiz);

#endif