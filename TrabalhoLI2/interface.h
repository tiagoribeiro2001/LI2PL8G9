/**
@file interface.h
Funções utilizadas na interface do jogo
*/
#ifndef TRABALHOLI2_INTERFACE_H
#define TRABALHOLI2_INTERFACE_H

#include "dados.h"

/**
\brief Imprime o tabuleiro
@param e Apontador para o estado
*/
void mostrar_tabuleiro(ESTADO *e);

/**
\brief Imprime o prompt
@param e Apontador para o estado
*/
void prompt (ESTADO *e);

/**
\brief Lê o que o utilizador escreve no programa
@param e Apontador para o estado
*/
int interpretador(ESTADO *e);

/**
\brief Imprime a mensagem que congratula o jogador vencedor
@param e Apontador para o estado
*/
void congratula_jogador (ESTADO *e);

#endif //TRABALHOLI2_INTERFACE_H
