#include "listas.h"
#include <stdio.h>
#include <stdlib.h>

LISTA criar_lista(){
    LISTA L;
    L = malloc(sizeof(struct nodo));
    L->valor = NULL;
    L->proximo = NULL;
    return L;
}

LISTA insere_cabeca(LISTA L, void *v){
    LISTA l1;
    l1 = malloc (sizeof(struct nodo));
    l1->valor = v;
    l1->proximo = L;
    return l1;
}

void *devolve_cabeca(LISTA L){
    return L->valor;
}

LISTA proximo(LISTA L){
    return L->proximo;
}

LISTA remove_cabeca(LISTA L){
    LISTA l1;
    l1 = L->proximo;
    free (L);
    return l1;
}

int lista_esta_vazia(LISTA L){
    int r = 0;
    if (L == NULL) r=1;
    return r;
}