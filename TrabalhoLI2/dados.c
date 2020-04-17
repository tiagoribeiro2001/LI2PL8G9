#include "dados.h"
#include <stdlib.h>

ESTADO *inicializar_estado() {
    ESTADO *novo = (ESTADO *) malloc(sizeof(ESTADO));
    int i, j;
    novo->jogador_atual = 1;
    novo->num_jogadas = 0;
    novo->ultima_jogada.coluna = 4;
    novo->ultima_jogada.linha = 3;
    novo->num_comandos = 1;
    for (i=0; i<8; i++){
        for (j=0; j<8; j++){
            novo->tab[i][j] = VAZIO;
        }
    }
    novo->tab[4][3] = BRANCA;
    novo->tab[0][7] = UM;
    novo->tab[7][0] = DOIS;
    novo->total_jogadas = 0;
    novo->numj_pos = 1;
    return novo;
}

CASA obter_casa (ESTADO *e, int c, int l){
    CASA casa;
    if (c>=0 && c<=8 && l>=0 && l<=8) {
        casa = e->tab[c][l];
        return casa;
    }
    else return ERRO;
}

int obter_numero_de_jogadas(ESTADO *e){
    int n;
    n = e->num_jogadas;
    return n;
}

int obter_jogador_atual(ESTADO *e){
    int j;
    j = e->jogador_atual;
    return j;
}

int obter_numero_comandos(ESTADO *e){
    int n;
    n = e->num_comandos;
    return n;
}