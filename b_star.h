#ifndef BESTRELA
#define BESTRELA
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <stdbool.h>
#include "tipos.h"


#define M 6
#define MM 2*M
#define SIZE 200

// estrutura criada a partir do arquivo binario


typedef enum {
    INTERNAL,
    EXTERNAL
} Status;

typedef struct page* PointerS;

typedef struct page {
    Status st;

    union {
        struct {
            int n_int;
            int key_int[MM];
            PointerS p_int[MM + 1];
        } UI;

        struct {
            int n_ext;
            Register reg_ext[MM];
        } UE;
    } UU;
} Page;

void b_star(int key, const char* file_name, int qtd, bool p);
void insert_general(Register*, PointerS*, long int*, long int*);
void ins_Bstar(Register, PointerS, short*, Register*, PointerS*, long int*, long int*);
void insert_Bstar(PointerS, PointerS*, Register*, Register, short*, long, long int*, long int*);
void insert_on_page(PointerS, Register, PointerS, long int*, long int*);
void searchBStar(Register*, PointerS*, long int*, long int*);
void print(PointerS*, int, long int*, long int*);


#endif