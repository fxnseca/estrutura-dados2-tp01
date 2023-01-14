#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "registros.h"
#include "gerador.h"

void ler_arquivo(){
    FILE *arquivo = fopen("registro_gerado.bin", "rb");
    Registro registro;

    //verifica se o arq foi aberto corretamente
    if (arquivo == NULL){
        printf("\nERRO AO ABRIR O ARQUIVO.\n");
        exit(1);
    }
    
    while(fread(&registro, sizeof(registro), 1, arquivo)){
        printf("\nchave: %d\n", registro.chave);
        printf("dado 01: %ld\n", registro.dado1);
        printf("dado 02: %s\n", registro.dado2);
    }

    fclose(arquivo);    
}

void gerador_crescente(int qntd){
    FILE *arquivo = fopen("registro_gerado.bin", "wb");
    Registro registro;

    if(!arquivo){
        printf("ERRO AO CRIAR O ARQUIVO.\n");
        exit(1);
    }

    for (int i = 0; i < qntd; i++){
        registro.chave = i;
        registro.dado1 = i+100;
        strcpy(registro.dado2, "Arquivo crescente.");

        fwrite(&registro, sizeof(registro), 1, arquivo);
    }
    
    fclose(arquivo);
}

void gerador_decrescente(int qntd){
    FILE *arquivo = fopen("registro_gerado.bin", "wb");
    Registro registro;

    if(!arquivo){
        printf("ERRO AO CRIAR O ARQUIVO.\n");
        exit(1);
    }

    for(int i = qntd; i > 0; i--){
        registro.chave = i;
        registro.dado1 = i+200;
        strcpy(registro.dado2, "Arquivo decrescente.");
    
        fwrite(&registro, sizeof(registro), 1, arquivo);
    }

    fclose(arquivo);
}

void gerador_aleatorio(int qntd){
    FILE *arquivo = fopen("registro_gerado.bin", "wb");
    Registro registro;

    if(!arquivo){
        printf("ERRO AO CRIAR O ARQUIVO.\n");
        exit(1);
    }

    for (int i = 0; i < qntd; i++){
        int aux = rand() % qntd;

        registro.chave = aux;
        registro.dado1 = aux+100;
        strcpy(registro.dado2, "Arquivo aleatorio.");

        fwrite(&registro, sizeof(registro), 1, arquivo);
    }
    
    fclose(arquivo);
}