/**
@file logica.h
Parte lógica do programa
*/
#ifndef TRABALHOLI2_LOGICA_H
#define TRABALHOLI2_LOGICA_H

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
\brief Permite ao jogador atual que peça ao computador para jogar por si
@param e Apontador para o estado
@returns A jogada escolhida para ser realizada
*/
COORDENADA jog (ESTADO *e);

/**
\brief Seleciona a melhor jogada
@param e Apontador para o estado
@param L Lista de jogadas possíveis
@returns A jogada escolhida para ser realizada
*/
COORDENADA decide_jog (ESTADO *e, LISTA L);

#endif
