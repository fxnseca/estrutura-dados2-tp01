#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

#include "registros.h"
#include "gerador.h"

int main(){
    int qntd = 60; 
    char *nome_arquivo;
    
    gerador_aleatorio(qntd);
    gerador_crescente(qntd);
    gerador_decrescente(qntd);

    ler_arquivo("crescente.bin");

    return 0;
}