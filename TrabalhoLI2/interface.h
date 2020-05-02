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
\brief Guarda o jogo num ficheiro
@param nome Apontador para o ficheiro
@param e Apontador para o estado
*/
void guardar_tabuleiro(char *nome, ESTADO *e);

/**
\brief Lê um ficheiro que contêm um jogo
@param nome Apontador para o ficheiro
@param e Apontador para o estado
*/
void ler_tabuleiro(char *nome, ESTADO *e);

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
\brief Imprime a lista de movimentos que foram feitos até ao momento
@param e Apontador para o estado
*/
void movs (ESTADO *e);

/**
\brief Imprime uma linha do comando movs
@param e Apontador para o estado
@param i Número da linha
*/
void printf_movs (ESTADO *e, int i);

/**
\brief Imprime a mensagem que congratula o jogador vencedor
@param e Apontador para o estado
*/
void congratula_jogador (ESTADO *e);

/**
\brief Imprime a mensagem que indica que a jogada introduzida é inválida
*/
void jogada_invalida();

#endif
