// David Souza do Nascimento - 19.2.4029
// João Vitor Pedrosa Faria - 19.1.4169
// Lavínia Fonseca Pereira - 19.1.4170
// Taylanne Patricia Mendes - 19.2.4099

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

#include "ArvoreB.h"
#include "arvore_binaria.h"
#include "b_star.h"
#include "acesso.h"
#include "gerador.h"

int main(int argc, char *argv[]){

    int metodo = atoi(argv[1]);
    int qtd = atoi(argv[2]);
    int situacao = atoi(argv[3]);
    int chave = atoi(argv[4]);
    
    bool parametro = false;

    if(argc > 5){
        char *p = argv[5];
        if(strcmp(p, "-P") == 0){
            parametro = true;
        }
        else{
            printf("Parametro invalido\n");
            exit(1);
        }
    }


    switch (metodo){

    case 1:
        if(situacao == 3) {
            return 0;
        } else if (situacao == 1) {
            gerador_crescente(qtd);
            acesso_sequencial(1, chave, qtd, parametro);
        } else if (situacao == 2) {
            gerador_decrescente(qtd);
            acesso_sequencial(2, chave, qtd, parametro);
        }
        break;
    case 2:
        if(situacao == 1 ){
            gerador_crescente(qtd);
            binary_tree(chave, "crescente.bin", parametro);
        }
        else if(situacao == 2 ){
            gerador_decrescente(qtd);
            binary_tree(chave, "decrescente.bin", parametro);
        }
        else{
            gerador_arquivo_aleatorio(qtd);
            binary_tree(chave, "aleatorio.bin", parametro);
        }
        break;
    case 3:
        if(situacao == 1 ){
            gerador_crescente(qtd);
            ArvoreB_execucao(chave, "crescente.bin", parametro);
        }
        else if(situacao == 2 ){
            gerador_decrescente(qtd);
            ArvoreB_execucao(chave, "decrescente.bin", parametro);
        }
        else{
            gerador_arquivo_aleatorio(qtd);
            ArvoreB_execucao(chave, "aleatorio.bin", parametro);
        }
        break;
    
    case 4:
        if(situacao == 1 ){
            gerador_crescente(qtd);
            b_star(chave, "crescente.bin", qtd, parametro);
        }
        else if(situacao == 2 ){
            gerador_decrescente(qtd);
            b_star(chave, "decrescente.bin", qtd, parametro);
        }
        else{
            gerador_arquivo_aleatorio(qtd);
            b_star(chave, "aleatorio.bin", qtd, parametro);
        } 
        break;
    
    default:
        printf("\nMetodo invalido!\n");
        exit(1);
        break;
    }
    return 0;
}