#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "asi.h"

// //definicao de uma entrada da tabela de indice
// typedef struct{
//     int pagina; //pag em questao
//     int chave; //menor chave de uma pag
// }Indice;

// //item do arquivo de dados
// typedef struct{
//     char titulo[31];
//     int codigo;
//     float preco;
// }Item;

// int main(){
//     Indice tabela[MAXTABELA];
//     FILE *arq;
//     Item dado;
//     int posicao, cont;

//     if((arq = fopen("livros.bin", "rb")) == NULL){
//         printf("ERRO NA ABERTURA DO ARQUIVO.\n");
//         exit(1);
//     }

//     //gera a tabela de indice de paginas
//     cont = 0; posicao = 0;

//     while(fread(&dado, sizeof(dado), 1, arq) == 1){
//         cont++; //contagem de acessos
        
//         if(cont%ITENSPAGINA == 1){
//             tabela[posicao].chave = dado.codigo;
//             tabela[posicao].pagina = posicao+1;
//             posicao++;
//         }
//     }
    
//     printf("CODIGO DO LIVRO DESEJADO: %d\n", dado.codigo);
//     return 0;
// }

//gerando tabela de indices
