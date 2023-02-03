#ifndef PE_ACESSOSEQUENCIAL_H
#define PE_ACESSOSEQUENCIAL_H
#include <stdio.h>
#include "tipos.h"
#include "gerador.h"
#define ITENSPAGINA 50
#define MAXTABELA 40000

int preprocessamento(FILE *arquivo, int tabela[], int quantidade_itens, int *transferencia, double *tempo);
int pesquisa_as(FILE *arquivo, Item* item, int tabela[], int tamanho, int *comparacoes, int *transferencias, double *tempo, bool p);
int preprocessamento_decrescente(FILE *arquivo, int tabela[], int quantidade_itens, int *transferencia, double *tempo);
int pesquisa_as_decrescente(FILE *arquivo, Item* item, int tabela[], int tamanho, int *comparacoes, int *transferencias, double *tempo, bool p);
void acesso_sequencial(int situacao, int chave, int quantidade, bool parametro);

#endif