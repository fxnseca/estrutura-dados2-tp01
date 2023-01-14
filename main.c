#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

#include "registros.h"
#include "gerador.h"

int main(){
    int qntd = 60; 
    
    gerador_aleatorio(qntd);
    ler_arquivo();

    return 0;
}