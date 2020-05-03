#include "listas.h"
#include <stdio.h>
#include <stdlib.h>

LISTA criar_lista(){
    return NULL;
}

LISTA insere_cabeca(LISTA L, void *v){
    LISTA n = malloc(sizeof(NODO));
    n->valor = v;
    n->proximo = L;
    return n;
}

void *devolve_cabeca(LISTA L){
    void *cabeca;
    if (L == NULL) cabeca = NULL;
    else cabeca = L->valor;
    return cabeca;
}

LISTA proximo(LISTA L){
    return L->proximo;
}

LISTA remove_cabeca(LISTA L){
    LISTA n;
    n = L;
    L = proximo(L);
    free (n);
    return L;
}

int lista_esta_vazia(LISTA L){
    return L == NULL;
}