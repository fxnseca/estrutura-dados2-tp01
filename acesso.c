#include <stdio.h>
#include <time.h>
#include <stdbool.h>
#include "acesso.h"
#include "gerador.h"
#include "tipos.h"

//gerando tabela de indices
int preprocessamento(FILE *arquivo, int tabela[], int quantidade_itens, int *transferencia, double *tempo){

    Item pagina[ITENSPAGINA];
    int posicao = 0, contador = 0;

    //variaveis para medir tempo de execução 
    clock_t fim, inicio = clock();
    double tempo_cpu;

    //leitura dos itens da pagina (feito de 4 em 4)
    while((fread(pagina, ITENSPAGINA * sizeof(Item), 1, arquivo)) == 1){
        contador++;

        if (contador > quantidade_itens) break;

        //insersão do primeiro nro de cada pagina na tabela
        tabela[posicao] = pagina[0].chave;
        posicao++;
    }

    //contando o numero de transferencias entre memoria secundaria e principal
    *transferencia = contador;

    //O clock para e o tempo de execução retorna em double
    fim = clock();
    tempo_cpu = ((double) (fim - inicio)) / CLOCKS_PER_SEC;
    *tempo = tempo_cpu;

// Imprimindo tabela de índices
    // int i;
    // for(i = 0; i < quantidade_itens / ITENSPAGINA; i++) {
    //     printf("\n\n%2d | %-8d", i, tabela[i]);
    // }
    // printf("\n");

    fflush(stdout);
    return posicao;
}

int preprocessamento_decrescente(FILE *arquivo, int tabela[], int quantidade_itens, int *transferencia, double *tempo){

    Item pagina[ITENSPAGINA];
    int posicao = 0, contador = 0;

    //variaveis para medir tempo de execução 
    clock_t fim, inicio = clock();
    double tempo_cpu;

    //leitura dos itens da pagina (feito de 4 em 4)
    while((fread(pagina, ITENSPAGINA * sizeof(Item), 1, arquivo)) == 1){
        contador++;

        if (contador > quantidade_itens) break;

        //insersão do primeiro nro de cada pagina na tabela
        tabela[posicao] = pagina[0].chave;
        posicao++;
    }

    //contando o numero de transferencias entre memoria secundaria e principal
    *transferencia = contador;

    //O clock para e o tempo de execução retorna em double
    fim = clock();
    tempo_cpu = ((double) (fim - inicio)) / CLOCKS_PER_SEC;
    *tempo = tempo_cpu;

// Imprimindo tabela de índices
    // int i;
    // for(i = 0; i < quantidade_itens / ITENSPAGINA; i++) {
    //     printf("\n\n%2d | %-8d", i, tabela[i]);
    // }
    // printf("\n");

    fflush(stdout);
    return posicao;
}

int pesquisa_as(FILE *arquivo, Item* item, int tabela[], int tamanho, int *comparacoes, int *transferencias, double *tempo, bool p){
    Item pagina[ITENSPAGINA];
    int i = 0, quantidade_itens;
    long long int deslocamento;

    *comparacoes = 0;

    //variaveis para medir tempo de execução 
    clock_t fim, inicio = clock();
    double tempo_cpu;

    if(p){ //parametro de print
        while (i < tamanho && tabela[i] <= item->chave){
            printf("\nCOMPARACAO NA TABELA: %d", tabela[i]); 
            i++;

            *comparacoes += 1;
        }
        printf("\n\n");
    }
    else{
        while (i < tamanho && tabela[i] <= item->chave){
            i++;
            *comparacoes += 1;
        }
    }

    if(i == 0) return 0;

    else{ //verifica qnts itens tem dentro da pagina.
        if(i < tamanho) 
            quantidade_itens = ITENSPAGINA;

        else{ //caso entre aqui, calcula a qntd de itens que tem na pag
            fseek(arquivo, 0, SEEK_END); 
            //calcula qntd de itens da ultima pagina
            quantidade_itens = (ftell(arquivo)/sizeof(Item))%ITENSPAGINA;

            if(quantidade_itens == 0) //faz outra verificação, se a ultima pag ta completa
                quantidade_itens = ITENSPAGINA;
        }
        
        //qntd em bytes q preciso pular
        deslocamento = (i-1) * ITENSPAGINA * sizeof(Item);

        //leva o ponteiro pra posição desejada pelo valor do deslocamento
        fseek(arquivo, deslocamento, SEEK_SET); 
        fread(&pagina,sizeof(Item), quantidade_itens, arquivo);

        *transferencias += 1;

        //a pesquisa propriamente dita
        for(i = 0; i < quantidade_itens; i++){
            *comparacoes += 1;

            if(p){
                printf("COMPARACAO NA PAGINA: %d\n", pagina[i].chave);
            }
            if (pagina[i].chave == item->chave){
                *item = pagina[i]; //retorna por referencia ao conteudo da var

               //O clock para e o tempo de execução retorna em double
                fim = clock();
                tempo_cpu = ((double) (fim - inicio)) / CLOCKS_PER_SEC;
                *tempo = tempo_cpu; 
                return 1;
            }
        }

        //O clock para e o tempo de execução retorna em double
        fim = clock();
        tempo_cpu = ((double) (fim - inicio)) / CLOCKS_PER_SEC;
        printf("\ntempo: %.2f",tempo_cpu);
        *tempo = tempo_cpu; 
        return 0;
    }
}

int pesquisa_as_decrescente(FILE *arquivo, Item* item, int tabela[], int tamanho, int *comparacoes, int *transferencias, double *tempo, bool p){
    Item pagina[ITENSPAGINA];
    int i, quantidade_itens;
    long long int deslocamento;

    *comparacoes = 0;

    //variaveis para medir tempo de execução 
    clock_t fim, inicio = clock();
    double tempo_cpu;

    if(p){
        i = 0;
        while (i < tamanho && tabela[i] >= item->chave){
            printf("\nCOMPARACAO NA TABELA: %d", tabela[i]); 
            i++;

            *comparacoes += 1;
        }
        printf("\n\n");
    }
    else{
        i = 0;
        while (i < tamanho && tabela[i] >= item->chave){
            i++;
            *comparacoes += 1;
        }
    }

    if(i == 0) return 0;

    else{
        if(i < tamanho)
            quantidade_itens = ITENSPAGINA;

        else{
            fseek(arquivo, 0, SEEK_END);
            quantidade_itens = (ftell(arquivo)/sizeof(Item))%ITENSPAGINA;

            if(quantidade_itens == 0)
                quantidade_itens = ITENSPAGINA;
        }
        
        deslocamento = (i-1) * ITENSPAGINA * sizeof(Item);

        fseek(arquivo, deslocamento, SEEK_SET);
        fread(&pagina,sizeof(Item), quantidade_itens, arquivo);

        *transferencias += 1;

        for(i = 0; i < quantidade_itens; i++){
            *comparacoes += 1;

            if(p){
                printf("COMPARACAO NA PAGINA: %d\n", pagina[i].chave);
            }
            if (pagina[i].chave == item->chave){
                *item = pagina[i];

               //O clock para e o tempo de execução retorna em double
                fim = clock();
                tempo_cpu = ((double) (fim - inicio)) / CLOCKS_PER_SEC;
                *tempo = tempo_cpu; 
                return 1;
            }
        }

        //O clock para e o tempo de execução retorna em double
        fim = clock();
        tempo_cpu = ((double) (fim - inicio)) / CLOCKS_PER_SEC;
        *tempo = tempo_cpu; 
        
        return 0;
    }
}

void acesso_sequencial(int situacao, int chave, int quantidade, bool parametro){
    FILE *arquivo;
    int tabela[MAXTABELA];
    int posicao, resultado; double tempoC, tempoD;
    int comparacoes = 0, transferencia = 0; 

    Item x; x.chave = chave;

    if (situacao == 1){
        if((arquivo = fopen("crescente.bin", "rb")) == NULL){
            printf("\nERRO AO ABRIR O ARQUIVO.");
            return;
        }
        posicao = preprocessamento(arquivo, tabela, quantidade, &transferencia, &tempoC);
        printf("================== Analise: Memoria externa ==================");    
        printf("\nCOMPARACOES             : %d", comparacoes);
        printf("\nTRANSFERENCIAS          : %d", transferencia);
        printf("\nTEMPO PREPROCESSAMENTO  : %lf", tempoC);
        printf("\nTEMPO EXECUCAO PESQUISA : %lf \n", tempoD);
        comparacoes = 0;
        transferencia = 0;
        resultado = pesquisa_as(arquivo, &x, tabela, posicao, &comparacoes, &transferencia, &tempoC, parametro); 
    }
    else if(situacao == 2){
        if ((arquivo = fopen("decrescente.bin","rb")) == NULL) {
            printf("Erro ao abrir arquivo"); 
            return;
        }
        posicao = preprocessamento_decrescente(arquivo, tabela, quantidade, &transferencia, &tempoD);
        printf("================== Analise: Memoria externa ==================");    
        printf("\nCOMPARACOES             : %d", comparacoes);
        printf("\nTRANSFERENCIAS          : %d", transferencia);
        printf("\nTEMPO PREPROCESSAMENTO  : %lf segundos", tempoC);
        printf("\nTEMPO EXECUCAO PESQUISA : %lf segundos\n", tempoD);
        comparacoes = 0;
        transferencia = 0;
        resultado = pesquisa_as_decrescente(arquivo, &x, tabela, posicao, &comparacoes, &transferencia, &tempoD, parametro); 
    }

    if (resultado){
        printf("\nREGISTRO ENCONTRADO!\n");
        printf("ITEM: %d | %ld %s\n\n", x.chave, x.dado1, x.dado2);
    } else{
        printf("\nREGISTRO NAO ENCONTRADO!\n\n");
    }
    printf("================== Analise: Busca ==================");    
    printf("\nCOMPARACOES             : %d", comparacoes);
    printf("\nTRANSFERENCIAS          : %d", transferencia);
    printf("\nTEMPO PREPROCESSAMENTO  : %lf segundos", tempoC);
    printf("\nTEMPO EXECUCAO PESQUISA : %lf segundos\n", tempoD);
    printf("\n----------------------------------------------------------------------------\n\n");

    fclose(arquivo);
}