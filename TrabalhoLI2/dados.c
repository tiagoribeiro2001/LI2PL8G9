#include "dados.h"
#include <stdlib.h>

ESTADO *inicializar_estado() {
    ESTADO *novo = (ESTADO *) malloc(sizeof(ESTADO));
    int i, j;
    novo->jogador_atual = 1;
    novo->num_jogadas = 0;
    novo->ultima_jogada.coluna = 4;
    novo->ultima_jogada.linha = 4;
    novo->num_comandos = 1;
    for (i=0; i<8; i++){
        for (j=0; j<8; j++){
            novo->tab[i][j] = VAZIO;
        }
    }
    novo->tab[4][4] = BRANCA;
    novo->tab[0][0] = UM;
    novo->tab[7][7] = DOIS;
    novo->total_jogadas_pos = 0;
    novo->numero_jogador_pos = 1;
    return novo;
}

CASA obter_casa (ESTADO *e, int c, int l){
    CASA casa;
    if (c>=0 && c<8 && l>=0 && l<8) {
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

void alterar_numero_de_jogadas(ESTADO *e, int n){
    e->num_jogadas = n;
}

int obter_jogador_atual(ESTADO *e){
    int j;
    j = e->jogador_atual;
    return j;
}

void alterar_jogador_atual(ESTADO *e, int n){
    e->jogador_atual = n;
}

int obter_numero_comandos(ESTADO *e){
    int n;
    n = e->num_comandos;
    return n;
}

void alterar_numero_comandos(ESTADO *e, int n){
    e->num_comandos = n;
}

int obter_total_jogadas(ESTADO *e){
    int n;
    n = e->total_jogadas_pos;
    return n;
}

void alterar_total_jogadas(ESTADO *e, int n){
    e->total_jogadas_pos = n;
}

int obter_numj_pos(ESTADO *e){
    int n;
    n = e ->numero_jogador_pos;
    return n;
}

void alterar_numero_jogador_pos(ESTADO *e, int n){
    e->numero_jogador_pos = n;
}

int obter_jogadas_jog1_coluna (ESTADO *e, int i){
    int n;
    n = e->jogadas[i].jogador1.coluna;
    return n;
}

int obter_jogadas_jog1_linha (ESTADO *e, int i){
    int n;
    n = e->jogadas[i].jogador1.linha;
    return n;
}

int obter_jogadas_jog2_coluna (ESTADO *e, int i){
    int n;
    n = e->jogadas[i].jogador2.coluna;
    return n;
}

int obter_jogadas_jog2_linha (ESTADO *e, int i){
    int n;
    n = e->jogadas[i].jogador2.linha;
    return n;
}

void alterar_jogadas_jog1 (ESTADO *e, int i, COORDENADA c){
    e->jogadas[i].jogador1 = c;
}

void alterar_jogadas_jog1_coluna (ESTADO *e, int i, int c){
    e->jogadas[i].jogador1.coluna = c;
}

void alterar_jogadas_jog1_linha (ESTADO *e, int i, int l){
    e->jogadas[i].jogador1.linha = l;
}

void alterar_jogadas_jog2 (ESTADO *e, int i, COORDENADA c){
    e->jogadas[i].jogador2 = c;
}

void alterar_jogadas_jog2_coluna (ESTADO *e, int i, int c){
    e->jogadas[i].jogador2.coluna = c;
}

void alterar_jogadas_jog2_linha (ESTADO *e, int i, int l){
    e->jogadas[i].jogador2.linha = l;
}

void alterar_tab (ESTADO *e, int c, int l, CASA casa){
    e->tab[c][l] = casa;
}

void alterar_ultima_jogada_coluna (ESTADO *e, int c){
    e->ultima_jogada.coluna = c;
}

void alterar_ultima_jogada_linha (ESTADO *e, int l){
    e->ultima_jogada.linha = l;
}

int obter_ultima_jogada_coluna (ESTADO *e){
    return e->ultima_jogada.coluna;
}

int obter_ultima_jogada_linha (ESTADO *e){
    return e->ultima_jogada.linha;
}

COORDENADA obter_ultima_jogada (ESTADO *e){
    return e->ultima_jogada;
}

