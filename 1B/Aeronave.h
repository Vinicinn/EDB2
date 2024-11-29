#ifndef AERONAVE_H
#define AERONAVE_H

typedef struct Aeronave {
    char identificador[10];
    int combustivel;
    int horario;
    int tipo;
    int emergencia;
    int prioridade;
} Aeronave;

#endif