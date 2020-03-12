#include "dados.h"
#include <stdlib.h>

ESTADO *inicializar_estado() {
    ESTADO *novo = (ESTADO *) malloc(sizeof(ESTADO));
    int i, j;
    novo->jogador_atual = 1;
    novo->num_jogadas = 0;
    novo->ultima_jogada.coluna = 4;
    novo->ultima_jogada.linha = 3;
    for (i=0; i<8; i++){
        for (j=0; j<8; j++){
            novo->tab[i][j] = VAZIO;
        }
    }
    novo->tab[4][3] = BRANCA;
    return novo;
}

