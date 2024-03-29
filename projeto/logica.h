/**
@file logica.h
Parte lógica do programa
*/
#ifndef PROJETO_LOGICA_H
#define PROJETO_LOGICA_H

#include "dados.h"
#include "listas.h"

/**
\brief Altera os parâmetros no estado mediante a jogada
@param e Apontador para o estado
@param c A coordenada da jogada a efetuar
@returns Devolve um se for possível jogar e zero caso não seja possível.
*/
int jogar(ESTADO *e, COORDENADA c);

/**
\brief Verifica se a jogada introduzida é valida
@param e Apontador para o estado
@param c A coordenada da jogada a efetuar
@returns Devolve um se for possível jogar e zero caso não seja possível.
*/
int valida_jogada(ESTADO *e, COORDENADA c);

/**
\brief Verifica se o jogo chegou ao fim
@param e Apontador para o estado
@returns Devolve zero caso o jogo tenha acabado ou um em caso contrário.
*/
int verifica_fim(ESTADO *e);

/**
\brief Verifica se o jogador tem algum sitio aonde jogar
@param e Apontador para o estado
@returns Devolve um caso seja possível jogar e zero caso contrário.
*/
int verifica_pos(ESTADO *e);

/**
\brief Verifica qual jogador venceu o jogo
@param e Apontador para o estado
@returns Devolve um caso o jogador um tenha ganho ou dois caso o jogador dois tenha ganho.
*/
int verifica_vencedor(ESTADO *e);

/**
\brief Altera o estado do jogo para uma jogada anterior
@param e Apontador para o estado
@param i Jogada para qual quere alterar o estado
*/
void pos (ESTADO *e, int i);

/**
\brief Cria uma lista de possíveis jogadas a executar
@param e Apontador para o estado
@returns A lista com as jogadas possíveis
*/
LISTA lista_jogadas_possiveis (ESTADO *e);

/**
\brief Permite ao jogador atual que peça ao computador para jogar por si
@param e Apontador para o estado
@returns A jogada escolhida para ser realizada
*/
COORDENADA jog(ESTADO *e);

/**
\brief Define a melhor jogada possível
@param e  Estado atual do jogo
@param depth Profundidade da escolha da jogada
@returns Retorna o valor da melhor jogada possível
*/
int minimax(ESTADO e, int depth);

/**
\brief Permite ao jogador atual que peça ao computador para jogar por si
@param e  Estado atual do jogo
@returns A melhor jogada escolhida para ser realizada
*/
COORDENADA jog2(ESTADO e);

/**
\brief Calcula a distância entre duas coordenadas
@param c  Coordenada
@param d  Coordenada
@returns A distância entre as duas coordenadas
*/
double dist_2_coordenadas(COORDENADA c, COORDENADA d);

/**
\brief Determina a posição da casa UM
@returns A coordenada da casa UM
*/
COORDENADA casa_1();

/**
\brief Determina a posição da casa DOIS
@returns A coordenada da casa DOIS
*/
COORDENADA casa_2();

#endif //PROJETO_LOGICA_H
