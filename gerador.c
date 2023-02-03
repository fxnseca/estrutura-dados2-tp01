#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "tipos.h"
#include "gerador.h"

void ler_arquivo(char *nome_arquivo){
    FILE *arquivo = fopen(nome_arquivo, "rb");
    Item item;

    //verificação de abertura do arquivo
    if((arquivo = fopen(nome_arquivo, "rb")) == NULL){
        printf("\nERRO AO ABRIR O ARQUIVO\n\n");
        return;
    }
        //leitura do arquivo
    while(fread(&item, sizeof(item), 1, arquivo) == 1){
        printf("chave: %d\n", item.chave);
        printf("Dado 01: %ld\n", item.dado1);
        printf("Dado 02: %s\n\n", item.dado2);
    }

    fclose(arquivo);
}


void gerador_crescente( int tamanho){
    FILE *arquivo = fopen("crescente.bin", "wb");
    Item item;

    // verificando se o arquivo foi criado ou não
    if(arquivo != NULL){
        printf("\nARQUIVO CRIADO COM SUCESSO!\n\n");
    }else{
        printf("\nNAO FOI POSSIVEL ABRIR O ARQUIVO.\n\n");
        exit(0);
    }

    //gravando os dados no arquivo
    for(int i = 0; i <= tamanho; i++){
        item.chave = i;
        item.dado1 = i+1000;
        strcpy(item.dado2, "");

        fwrite(&item, sizeof(item), 1, arquivo);
    }

    fclose(arquivo);

    // ler_arquivo(nome_arquivo);
}

void gerador_decrescente(int tamanho){
    FILE *arquivo = fopen("decrescente.bin", "wb");
    Item item;
    int j = 0;

    // verificando se o arquivo foi criado ou não
    if(arquivo != NULL){
        printf("\nARQUIVO CRIADO COM SUCESSO!\n\n");
    }else{
        printf("\nNAO FOI POSSIVEL ABRIR O ARQUIVO.\n\n");
        exit(0);
    }

    //gravando os dados no arquivo
    for(int i = tamanho; i > 0; i--){
        item.chave = i;
        item.dado1 = i+1000;
        strcpy(item.dado2, "");

        fwrite(&item, sizeof(item), 1, arquivo);
        j++;
    }
 
    fclose(arquivo);

    // ler_arquivo(nome_arquivo);
}

void gerador_arquivo_aleatorio(int quantidade_arquivo){
    FILE *arquivo = fopen("aleatorio.bin", "wb");
    Item item;
    long long int *vetor = (long long int *) malloc (quantidade_arquivo * sizeof(long long int));

    if(arquivo == NULL){
        printf("Erro na abertura do arquivo\n");
        return;
    }
    srand(time(NULL));

    for(long long i=0; i < quantidade_arquivo; i++){
        vetor[i] = 0;
    }

    for(long long int i=0; i < quantidade_arquivo; i++){
        //gera um número aleatório que vai até o tamanho informado, vale ressaltar que o número pode repetir
        long long int aux = rand() % quantidade_arquivo;
        //condição que nos diz que o vetor na posição aux já foi preenchido, isso faz com que não tenhamos que preencher o vetor novamente
        if(vetor[aux] == -1){
            i--;
        }else{
            item.chave = aux+1;
            item.dado1 = aux+1001;
            strcpy(item.dado2, "");

            fwrite(&item, sizeof(item), 1, arquivo);
            //informa que essa unidade do vetor já foi preenchida.
            vetor[aux]=-1;
        }    
    }

    free(vetor);
    fclose(arquivo);

    // ler_arquivo(nome_arquivo);
}