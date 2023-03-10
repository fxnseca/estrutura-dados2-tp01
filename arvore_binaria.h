#ifndef arvore_binaria
#define arvore_binaria

#include "tipos.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct{
    Register reg;
    int right;
    int left;
}Node;

Node create_node(Node a);
void insert(FILE* output_file,FILE* input_file, long long*transf ,  long long*comp);
int insert_right_node(Node node, Node aux, int count, int* position, FILE** file);
int insert_left_node( Node node, Node aux, int count, int* position, FILE** file);
int open_binary_file(FILE **file, const char* name, const char* type);
int search_node(int key, FILE** file,  long long*transf , long long*comp, int parametro);
void search(int key, FILE* file, int parametro);
void binary_tree( int key, const char* name, int parametro );

#endif