#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "registros.h"
#include "gerador.h"


int main(){
    
    // FILE *arquivo = fopen("crescente.bin", "wb");
    // Registro registro;
    // int qntd = 60;

    // if(!arquivo){
    //     printf("ERRO AO CRIAR O ARQUIVO.\n");
    //     exit(1);
    // }

    // for (int i = 0; i < qntd; i++){
    //     registro.chave = i;
    //     registro.dado1 = i+100;
    //     strcpy(registro.dado2, "Desiste nao, vai rolar!\n");

    //     fwrite(&registro, sizeof(registro), 1, arquivo);
    // }
    
    // ler_arquivo("crescente.bin");


FILE *arquivo = fopen("crescente.bin", "rb");
    Registro registro;

    //verifica se o arq foi aberto corretamente
    if (arquivo == NULL){
        printf("\nERRO AO ABRIR O ARQUIVO.\n");
        exit(1);
    }
    
    while(fread(&registro, sizeof(registro), 1, arquivo)){
        printf("chave: %d\n", registro.chave);
        printf("dado 01: %ld\n", registro.dado1);
        printf("dado 02: %s\n", registro.dado2);
    }

    fclose(arquivo);

    return 0;
}