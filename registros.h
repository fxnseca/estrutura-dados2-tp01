#ifndef registros_h
#define registros_h
#define ITENSPAGINA 4
#define MAXTABELA 250

typedef struct{
    int indice; //menor valor que identifica a pagina
}Pagina;

typedef struct{
    int chave;
    long int dado1;
    char dado2[5000];
}Item;

typedef struct{
    int chave;
    long int dado1;
    char dado2[5000];
}Registro;

#endif