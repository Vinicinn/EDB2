#ifndef LIVRO_H
#define LIVRO_H

typedef struct Livro {
    int codigo;
    char titulo[50];
    char autor[50];
    char genero[50];
    int ano;
    char editora[50];
    int qtdPaginas;
} Livro;

#endif