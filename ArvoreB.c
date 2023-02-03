#include "ArvoreB.h"

void ArvoreB_execucao(int chave, const char* name, bool parametro){
    FILE* arq;

    //Alocando o ponteiro para a raiz da arvore
    Ponteiro* arvore = (Ponteiro*) malloc(sizeof(No));

    //Setando a raiz da arvore em Nulo no primeiro momento
    arvore = NULL;

    //Criando a variavel auxilar de registro
    Register reg;

    //Criando contadores de transferencias e comparaçoes
    long long transf = 0, comp = 0;

    //Verificando se o arquivo foi aberto com sucesso
    if(arq = fopen(name, "rb")){

        //Lendo os registros do arquivo e inserindo na arvore
        clock_t inicio = clock();
        
        (transf)++;
        while (fread(&reg, sizeof(Register), 1, arq) == 1)
        {
            Insere_na_arvore(reg, &arvore, &comp);
            (transf)++;
        }

        clock_t fim = clock();
        double TempoTotal = ((double) (fim - inicio)) / CLOCKS_PER_SEC;

        printf("================== Analise: Pre-Procesasmento ==================\n");
        printf("COMPARACOES                   : %lld\n", comp);
        printf("TRANSFERENCIAS                : %lld\n", transf);
        printf("TEMPO PREPROCESSAMENTO        : %lf\n", TempoTotal);
       
        reg.key = chave;
        comp = 0;
        inicio = clock();

        if(PesquisaArvoreB(&reg, arvore, &comp, parametro)){
            printf("\nREGISTRO ENCONTRADO! => ");
            printf("ITEM: %d | %ld, %s \n\n", reg.key, reg.data1, reg.data2);
        }
        else{
             printf("\nREGISTRO NAO ENCONTRADO!");
        } 

        fim = clock();
        TempoTotal = ((double) (fim - inicio)) / CLOCKS_PER_SEC;

        printf("================== Analise: Busca ==================\n");
        printf("COMPARACOES             : %lld\n", comp);
        printf("TRANSFERENCIAS          : %lld\n", transf);
        printf("TEMPO EXECUCAO PESQUISA : %lf\n", TempoTotal);
    } 
    //printArvoreB(arvore);
    fclose(arq);          
}

void printArvoreB(Ponteiro* arvore){
    int i = 0;

    if(arvore == NULL){
        return;
    }

    while ( i <= arvore->n){
        printArvoreB(arvore->p[i]);
        if(i != arvore->n){
            printf("%d ", arvore->r[i].key);
        }
        i++;
    }
}

void Insere_na_arvore(Register reg, Ponteiro** arvore, long long *comp){
    //Variável responsavel por verificar se a arvore cresceu
    bool Cresceu;
    //Armazena o registro de retorno
    Register RegRetorno;
    //Armazena filho à direita do registro retornado
    Ponteiro *PontRetorno;
    //Ponteiro de páginas temporários
    Ponteiro *p_temp;
    //Realiza uma busca na arvore para inserir o registro reg
    Ins(reg, arvore, &Cresceu, &RegRetorno, &PontRetorno, comp);
    
    //Criação de um novo nó raiz
     if(Cresceu){
        p_temp  =(Ponteiro*) malloc(sizeof(No));
        p_temp->n = 1;
        p_temp->r[0] = RegRetorno;
        p_temp->p[1] = PontRetorno;
        p_temp->p[0] = (*arvore);
        *arvore = p_temp;
    }
}

bool PesquisaArvoreB(Register* reg, Ponteiro* arvore, long long *comp, bool parametro){
    int i = 1;

    if(arvore == NULL){
        return false;
    }

    //Caminha na página até encontrar o local desejado
    (*comp)++;

    while(i < arvore->n && reg->key > arvore->r[i-1].key){
        if(parametro)
            printf("\n %d ",arvore->r[i - 1].key);
        i++;
        (*comp)++;
     } 

    //Compara o valor, caso seja igual : retorna verdadeiro e a pesquisa se encerra
    (*comp)++;
     if(reg->key == arvore->r[i-1].key){
        if(parametro)
            printf("\n %d ",arvore->r[i - 1].key);
        *reg = arvore->r[i-1];
        return true;
    }
    
    //Caso o valor do registro seja menor que o ultimo registro da pagina: caminhamento à esquerda
    (*comp)++;
    if(reg->key < arvore->r[i-1].key){
        PesquisaArvoreB(reg, arvore->p[i - 1], comp, parametro);
    }
    
    //Caso contrário: caminhamento à direita
    else{ 
        PesquisaArvoreB(reg, arvore->p[i], comp, parametro);
    }  
} 

void Insere_na_pagina(Ponteiro** arvore, Register* reg, Ponteiro** p_direito, long long* comp){
    int k = (*arvore)->n;

    //Caso a página tenha itens, rearanja para inserir na posição correta
    while(k > 0){
       (*comp)++;
        if(reg->key >= (*arvore)->r[k - 1].key){
            break;
        }

        (*arvore)->r[k] = (*arvore)->r[k - 1];
        (*arvore)->p[k + 1] = (*arvore)->p[k];
        k--;

        if( k < 1){
            break;
        }
    }

    (*arvore)->r[k] = *reg;
    (*arvore)->p[k + 1] = *p_direito;
    (*arvore)->n++;
}

void Ins(Register reg, Ponteiro** arvore, bool *Cresceu, Register* RegRetorno, Ponteiro** PontRetorno, long long *comp){
    //Variável que caminha pelas paginas
    long i = 1;
    //Variável responsável por definir local de divisão dos filhos à direita da página
    long j;
    //Ponteiro de páginas temporário
    Ponteiro* p_temp;
    
    //Verifica se arvore está vazia e retorna os valores para a criação da raiz
   (*comp)++;
   if(*arvore == NULL){
        *Cresceu = true;
        *RegRetorno = reg;
        *PontRetorno = NULL;
        return; 
    }  

     //Laço que caminha pela pagina apontada pela raiz da arvore
    (*comp)++;

    while(i < (*arvore)->n && reg.key > (*arvore)->r[i - 1].key){  
        i++;
        (*comp)++;
    };
    
    //Verificação caso o registro já esteja presente na arvore
    
    (*comp)++;
    if(reg.key == (*arvore)->r[i - 1].key){
        printf("ERRO: O REGISTRO JA SE ENCONTRA NA ARVORE");
        *Cresceu = false;
        return;
    }
    
    //A proxima procura será com o filho a esquerda caso a chave seja menor que o ultimo registro
    (*comp)++;
    if(reg.key < (*arvore)->r[i - 1].key) 
        i--;

    //Realiza a pesquisa na subarvore selecionada
    Ins(reg, &((*arvore)->p[i]), Cresceu, RegRetorno, PontRetorno, comp);

    //Verifica se será necessaria a criação de uma nova pagina
    (*comp)++;
    if(!*Cresceu) 
        return;

    //Caso a pagina tenha espaço
    (*comp)++;
    if( (*arvore)->n < (2*M)){
        Insere_na_pagina(arvore, RegRetorno, PontRetorno, comp);
        *Cresceu = false;
        return;
    }

    //Caso a pagina precise ser dividida
    //Aloca ponteiro auxiliar e inicializa
    p_temp = (Ponteiro*) malloc(sizeof(No));
    p_temp->n = 0;
    p_temp->p[0] = NULL;

    (*comp)++;
    if(i < (M + 1)){
        Insere_na_pagina(&p_temp, &(*arvore)->r[2 * M - 1], &(*arvore)->p[2 * M], comp);
        (*arvore)->n--;
        Insere_na_pagina(arvore, RegRetorno, PontRetorno, comp);
    }

    else {
        (*comp)++; 
        Insere_na_pagina(&p_temp, RegRetorno, PontRetorno, comp);
    }

    //Processo de divisão das paginas
    for(j = M + 2; j <= 2 * M; j++){
        Insere_na_pagina(&p_temp, &(*arvore)->r[j - 1], &(*arvore)->p[j], comp);
    }
    
    (*arvore)->n = M;
    p_temp->p[0] = (*arvore)->p[M + 1];
    *RegRetorno = (*arvore)->r[M];
    *PontRetorno = p_temp;
}