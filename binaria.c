#include "binaria.h"

void pesquisar(int chave, FILE* arquivoSaida, int parametro){
    long long transf = 0;
    long long comp = 0;
    clock_t start = clock();
    if(pesquisarNo(chave, &arquivoSaida, &transf, &comp, parametro)){
        printf("Item encontrado\n");
    }
    else{
        printf("item nao encontrado\n");
    }
    clock_t end = clock();
    double tempo_uso_cpu = ((double) (end-start)) / CLOCKS_PER_SEC;

    printf("================== Analise da Busca==================\n");
        printf("Comparações: %lld\n", comp);
        printf("Transferencias: %lld\n", transf);
        printf("Tempo Total de busca: %lf\n", tempo_uso_cpu);
}

void arvoreBinaria(int chave, const char* nome, int parametro){
    long long comp = 0;
    long long transf = 0;
    FILE* arquivoSaida;
    FILE* arquivoEntrada;

    //caso o arquivo abra com sucesso, executamos:
    if(abrirArquivoBin(&arquivoSaida,"arquivo.bin","w+b") && abrirArquivoBin(&arquivoEntrada, nome, "r+b")){
        inserir(arquivoSaida, arquivoEntrada, transf, comp);
        //quando inserimos já fazemos a exibição da analise para inserção, por isso zeramos denovo transf e comp
        comp=0; transf=0;
        //Volta para o início do arquivo
        rewind(arquivoSaida);
        //realiza a pesquisa
        pesquisar(chave, arquivoSaida, parametro);
    }
    fclose(arquivoSaida);
    fclose(arquivoEntrada);
}

void inserir(FILE *arquivoSaida, FILE *arquivoEntrada, long long *transf, long long *comp){
    clock_t start = clock();        //Função do Time.h
    No a, aux;
    int i = -1;

    (*transf)++;
    while(fread(&a.reg,sizeof(Registro),1,arquivoEntrada)==1){
        i++;
        a=criar_No(a);

        //caso o Arquivo esteja vazio
        if(ftell(arquivoSaida)-1 < 0){
            fwrite(&a, sizeof(No),1,arquivoSaida);
        }
        else{
            int inserido=0;
            int posicao=0;
            //Enquando o Registro não for inserido
            while(inserido==0){
                //Caminha no arquivo de acordo com a posição selecionada
                fseek(arquivoSaida, posicao*sizeof(No), SEEK_SET);
                //Caso seja possivel ler um item, então ele é lido
                (*transf)++;
                if(fread(&aux, sizeof(No), 1, arquivoSaida) == 1){
                    //Caso a chave seja maior do que do item lido, é feita a tentativa de inserção à direita
                    if(a.reg.chave > aux.reg.chave){
                        (*comp)++;
                        inserido = inserirDireitaNo(a, aux, i, &posicao, &arquivoSaida);
                        (*comp)++;
                    }
                    //Caso a chave seja menor do que do item lido, é feita a tentativa de inserção à esquerda
                    else if(a.reg.chave < aux.reg.chave){
                        (*comp)+=2;
                        inserido = inserirEsquerdaNo(a, aux, i, &posicao, &arquivoSaida);
                        (*comp)++;
                    }
                    //Caso o item seja igual, é feita a finalização do laço
                    else{
                        (*comp)+=3;
                        inserido = 1;
                    }
                }
            }
        }
        (*transf)++;
    }
    
    clock_t end = clock();
    double tempo_uso_cpu = ((double) (end-start)) / CLOCKS_PER_SEC;

    printf("================== Analise: Pre-Processamento==================\n");
    printf("Comparações: %lld\n", *comp);
    printf("Transferencias: %lld\n", *transf);
    printf("Tempo Total de pre-processamento: %lf\n", tempo_uso_cpu);
}

No criar_No(No a){
    a.direita = -1;
    a.esquerda = -1;
    return a;
}

int abrirArquivoBin(FILE** arquivo, const char* nome, const char* tipo){
    if((*arquivo = fopen(nome, tipo)) == NULL){
        printf("Erro ao abrir o arquivo");
        return 0;
    }
    return 1;
}

int inserirDireitaNo(No no, No aux, int cont, int* posicao, FILE** arquivo){
    if(aux.esquerda == -1){
        aux.esquerda = cont;
        fseek(*arquivo, (*posicao*sizeof(No)), SEEK_SET);
        fwrite(&aux, sizeof(No),1, *arquivo);
        fseek(*arquivo,(cont*sizeof(No)), SEEK_SET);
        fwrite(&no, sizeof(No),1,*arquivo);
        return 1;
    }
    *posicao = aux.esquerda;
    return 0;
}


int inserirEsquerdaNo(No no, No aux, int cont, int* posicao, FILE** arquivo){
    if(aux.direita == -1){
        aux.direita = cont;
        fseek(*arquivo, (*posicao*sizeof(No)), SEEK_SET);
        fwrite(&aux, sizeof(No),1, SEEK_SET);
        fseek(*arquivo, (cont*sizeof(No)), SEEK_SET);
        fwrite(&no, sizeof(No), 1, *arquivo);
        return 1;
    }
    *posicao = aux.direita;
    return 0;
}

int pesquisarNo(int chave, FILE** arquivo, long long* transf, long long* comp, int parametro){
    No aux;
    int posicao = 0;
    (*transf)++;
    while(fread(&aux, sizeof(No), 1, *arquivo) == 1){
        fseek(*arquivo, posicao*sizeof(No), SEEK_SET);

        if(fread(&aux, sizeof(No), 1, *arquivo) == 1){
            (transf)++;
            if(parametro){
                printf("%d\n", aux.reg.chave);
            }
            else if(chave > aux.reg.chave){
                (*comp)++;
                posicao = aux.esquerda;
            }
            else if(chave < aux.reg.chave){
                (*comp)+=2;
                posicao = aux.direita;
            }
            else{
                (*comp)+=3;
                return 1;
            }
        }
        (*transf)++;
    }

    return 0;
}