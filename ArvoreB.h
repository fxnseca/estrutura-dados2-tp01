#ifndef ArvoreB_H
#define ArvoreB_H
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include "tipos.h"

#define M 6

typedef struct No No;

typedef struct No Ponteiro;

struct No{
    int n;
    Register r[2 * M];
    Ponteiro* p[2 * M + 1];
};

void ArvoreB_execucao(int chave, const char* name, bool parametro);
void printArvoreB(Ponteiro* arvore);
void Insere_na_arvore(Register reg, Ponteiro** arvore, long long *comp);
bool PesquisaArvoreB(Register* reg, Ponteiro* arvore, long long *comp, bool parametro);
void Insere_na_pagina(Ponteiro** arvore, Register* reg, Ponteiro** p_direito, long long* comp);
void Ins(Register reg, Ponteiro** arvore, bool *Cresceu, Register* RegRetorno, Ponteiro** pr, long long *comp);
#endif
