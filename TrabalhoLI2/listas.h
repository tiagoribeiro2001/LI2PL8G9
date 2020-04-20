/**
@file listas.h
Módulo das listas ligadas
*/

#ifndef TRABALHOLI2_LISTAS_H
#define TRABALHOLI2_LISTAS_H

#include "dados.h"

/**
\brief Tipo para as listas ligadas
*/
typedef struct nodo {
    COORDENADA *valor;
    struct nodo *proximo;
} NODO, *LISTA;

/**
\brief Cria uma lista vazia
@returns Devolve a lista vazia criada
*/
LISTA criar_lista();

/**
\brief Insere um valor na cabeça da lista
@param L Apontador para a lista
@param v Apontador para a nova cabeça
@returns Devolve a lista com a nova cabeça
*/
LISTA insere_cabeca(LISTA L, COORDENADA *v);

/**
\brief Indica qual é a cabeça da lista
@param L Apontador para a lista
@returns Devolve a cabeça da lista
*/
COORDENADA *devolve_cabeca(LISTA L);
/**
\brief Indica qual é a cauda da lista
@param L Apontador para a lista
@returns Devolve a cauda da lista
*/
LISTA proximo(LISTA L);

/**
\brief Remove a cabeça da lista (libertando o espaço ocupado) e devolve a cauda
@param L Apontador para a lista
@returns Devolve a cauda da lista
*/
LISTA remove_cabeca(LISTA L);

/**
\brief Testa se uma lista é vazia
@param L Apontador para a lista
@returns Devolve verdareiro se a lista é vazia, caso contrário devolve falso
*/
int lista_esta_vazia(LISTA L);

#endif //TRABALHOLI2_LISTAS_H
