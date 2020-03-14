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
    novo->tab[3][4] = BRANCA;
    return novo;
}

CASA obter_casa (ESTADO *e, int i, int k){
    CASA c;
    c = e->tab[i][k];
    return c;
}