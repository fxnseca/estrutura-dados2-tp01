#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

#include "registros.h"
#include "gerador.h"

#include "asi.h"
#include "binaria.h"
#include "arvoreBinaria.h"

int main(int argc, char *argv[])
{
    int metodo = atoi(argv[1]);
    int qntd = atoi(argv[2]);
    int situacao = atoi(argv[3]);
    int chave = atoi(argv[4]);
    bool parametro = false;

    char *nome_arquivo;

    gerador_aleatorio(qntd);
    gerador_crescente(qntd);
    gerador_decrescente(qntd);

    // if (argc > 5)
    // {
    //     char p[20] = argv[5];
    //     if (p == "-P")
    //     {
    //         parametro = true;
    //     }
    //     else
    //     {
    //         printf("Parametro invalido\n");
    //         exit(1);
    //     }
    // }

    // Acesso Sequencial Indexado
    if (metodo == 1){
        if (situacao == 1){
            gerador_crescente(qntd); // metodo sequencial indexado
        }
        if (situacao == 2){
            gerador_decrescente(qntd); // metodo sequencial indexado
        }
        if (situacao == 3){
            return 0;
    // para utilizaro método do acesso sequencial indexado o arquivo não pode estar desordenado
        }
    }

    // Arvore Binaria
    if (metodo == 2){
        if (situacao == 1){
            gerador_crescente(qntd);
            arvoreBinaria(chave, "crescente.bin", parametro);
        }
        if (situacao == 2){
            gerador_decrescente(qntd);
            arvoreBinaria(chave, "decrescente.bin", parametro);
        }
        if (situacao == 3){
            gerador_aleatorio(qntd);
            arvoreBinaria(chave, "aleatorio.bin", parametro);
        }
    }

    // Arvore B
    if (metodo == 3){
        if (situacao == 1){
            gerador_crescente(qntd);
            ArvoreB_execucao(chave, "crescente.bin", parametro);
        }
        if (situacao == 2){
            gerador_decrescente(qntd);
            ArvoreB_execucao(chave, "decrescente.bin", parametro);
        }
        if (situacao == 3){
            gerador_aleatorio(qntd);
            ArvoreB_execucao(chave, "aleatorio.bin", parametro);
        }
    }

    // Arvore B*
    if (metodo == 4){
        if (situacao == 1){
            gerador_crescente(qntd); //Arvore B*
        }
        if (situacao == 2){
            gerador_decrescente(qntd); //Arvore B*
        }
        if (situacao == 3){
            gerador_aleatorio(qntd); //Arvore B*
        }
    }
    return 0;
}