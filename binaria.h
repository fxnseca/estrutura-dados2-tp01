#ifndef arvore_binaria
#define arvore_binaria

#include "registros.h"
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

typedef struct{
    Registro reg;
    int direita;
    int esquerda;
}No;

No criar_No(No a);
void inserir(FILE* arquivoSaida, FILE* arquivoEntrada, long long* transf, long long* comp);
int inserirDireitaNo(No no, No aux, int cont, int* posicao, FILE** arquivo);
int inserirEsquerdaNo(No no, No aux, int cont, int* posicao, FILE** arquivo);
int abrirArquivoBin(FILE** file, const char* nome, const char* tipo);
int pesquisarNo(int chave, FILE** arquivo, long long* transf, long long* comp, int parametro);
void pesquisar(int chave, FILE* arquivoSaida, int parametro);
void arvoreBinaria(int chave, const char* nome, int parametro);

#endif