#ifndef TRABALHOLI2_INTERFACE_H
#define TRABALHOLI2_INTERFACE_H

#include "dados.h"

void mostrar_tabuleiro(ESTADO *e);

void prompt (ESTADO *e);

int interpretador(ESTADO *e);

void congratula_jogador (ESTADO *e);

void jogada_invalida ();

#endif //TRABALHOLI2_INTERFACE_H
