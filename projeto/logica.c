#include <stdio.h>
#include "logica.h"
#include "dados.h"
#include "listas.h"
#include <math.h>
#include <stdlib.h>

int jogar(ESTADO *e, COORDENADA c) {
    int i = valida_jogada (e, c);
    if (i) {
        alterar_tab(e, obter_ultima_jogada_coluna(e), obter_ultima_jogada_linha(e), PRETA);
        alterar_tab(e, c.coluna, c.linha, BRANCA);
        alterar_ultima_jogada_coluna(e, c.coluna);
        alterar_ultima_jogada_linha(e, c.linha);
        if (obter_jogador_atual(e) == 1){
            alterar_jogador_atual(e, 2);
            alterar_numero_de_jogadas(e, obter_numero_de_jogadas(e) + 1);
            alterar_jogadas_jog1_coluna(e, obter_numero_de_jogadas(e)-1, c.coluna);
            alterar_jogadas_jog1_linha(e, obter_numero_de_jogadas(e)-1, c.linha);
        }
        else if (obter_jogador_atual(e) == 2){
            alterar_jogadas_jog2_coluna(e, obter_numero_de_jogadas(e)-1, c.coluna);
            alterar_jogadas_jog2_linha(e, obter_numero_de_jogadas(e)-1, c.linha);
            alterar_jogador_atual(e, 1);
        }
        alterar_numero_comandos(e,obter_numero_comandos(e) + 1);
        alterar_total_jogadas(e, obter_numero_de_jogadas(e));
        alterar_numero_jogador_pos(e, obter_jogador_atual(e));
    }
    return i;
}

int valida_jogada(ESTADO *e, COORDENADA c){
    int p = 1;
    if (obter_casa(e, c.coluna, c.linha) == PRETA || obter_casa(e, c.coluna, c.linha) == BRANCA || obter_casa(e, c.coluna, c.linha) == ERRO) p = 0;
    if (c.coluna > obter_ultima_jogada_coluna(e) + 1 || c.coluna < obter_ultima_jogada_coluna(e) - 1) p = 0;
    if (c.linha > obter_ultima_jogada_linha(e) + 1 || c.linha < obter_ultima_jogada_linha(e) - 1) p = 0;
    return p;
}

int verifica_fim(ESTADO *e){
    int i = 1;
    if (obter_casa(e,0,0) == BRANCA) i = 0;
    if (obter_casa(e,7,7) == BRANCA) i = 0;
    i = (i && verifica_pos(e));
    return i;
}

int verifica_pos(ESTADO *e){
    int i = 0, c, l, coluna = obter_ultima_jogada_coluna(e), linha = obter_ultima_jogada_linha(e);
    for (c = coluna - 1; c < coluna + 2; c++){
        for (l = linha - 1; l< linha + 2; l++){
            if (obter_casa(e, c ,l) != PRETA && obter_casa(e, c, l) != BRANCA && obter_casa(e, c, l) != ERRO) i = 1;
        }
    }
    return i;
}

int verifica_vencedor(ESTADO *e){
    int i=0;
    if (obter_jogador_atual(e) == 1) i = 2;
    if (obter_jogador_atual(e) == 2) i = 1;
    if (obter_casa(e,0,0) == BRANCA) i = 1;
    if (obter_casa(e,7,7) == BRANCA) i = 2;
    return i;
}

void pos (ESTADO *e, int n){
    int i, j;
    for (i = 0; i < 8; i++){
        for (j = 0; j < 8; j++){
            alterar_tab(e, i, j, VAZIO);
        }
    }
    alterar_tab(e, 4, 4, BRANCA);
    alterar_tab(e, 0, 0, UM);
    alterar_tab(e, 7, 7, DOIS);
    alterar_jogador_atual(e, 1);
    alterar_ultima_jogada_coluna(e, 4);
    alterar_ultima_jogada_linha(e, 4);
    for (i = 0; i < n; i++){
        alterar_tab(e, obter_ultima_jogada_coluna(e), obter_ultima_jogada_linha(e), PRETA);
        alterar_tab(e, obter_jogadas_jog1_coluna(e, i), obter_jogadas_jog1_linha(e, i), PRETA);
        alterar_tab(e, obter_jogadas_jog2_coluna(e, i), obter_jogadas_jog2_linha(e, i), BRANCA);
        alterar_ultima_jogada_coluna(e, obter_jogadas_jog2_coluna(e, i));
        alterar_ultima_jogada_linha(e, obter_jogadas_jog2_linha(e, i));
    }
    alterar_numero_de_jogadas(e, n);
    alterar_numero_comandos(e, 2*n+1);
}

LISTA lista_jogadas_possiveis (ESTADO *e) {
    COORDENADA ult_coord = obter_ultima_jogada(e);
    int linha = ult_coord.linha, coluna = ult_coord.coluna, c, l;
    LISTA L = criar_lista();
    for (c = coluna - 1; c < coluna + 2; c++) {
        for (l = linha - 1; l < linha + 2; l++) {
            if (obter_casa(e, c, l) != PRETA && obter_casa(e, c, l) != BRANCA && obter_casa(e, c, l) != ERRO) {
                COORDENADA *C = (COORDENADA *) malloc(sizeof(COORDENADA));
                C->coluna = c;
                C->linha = l;
                L = insere_cabeca(L, C);
            }
        }
    }
    return L;
}

int minimax(ESTADO e, int depth){
    depth--;
    if (depth < 1){
        return 0;
    }
    if (verifica_fim(&e) == 0) {
        int x = verifica_vencedor(&e);
        if (x == 1) {
            return depth;
        }
        else return -depth;
    }
    else {
        LISTA jogadas;
        jogadas = lista_jogadas_possiveis(&e);
        int resultado;
        int min = 999, max = -999;
        if (lista_esta_vazia(jogadas)){
            return 0;
        }
        for(LISTA n = jogadas; n != NULL; n = proximo(n)){
            ESTADO tmp = e;
            COORDENADA *coord = (COORDENADA *) n->valor;
            jogar(&tmp, *coord);
            resultado = minimax(tmp,depth);
            if(resultado < min){
                min = resultado;
            }
            if(resultado > max){
                max = resultado;
            }
        }
        if (obter_jogador_atual(&e) == 1){
            return max;
        }
        else {
            return min;
        }
    }
}

#define PROFUNDIDADE 10
#define JOGADAS_EM_DISTANCIA 2

COORDENADA jog2(ESTADO e){// melhor_jogada
    LISTA jogadas;
    jogadas = lista_jogadas_possiveis(&e);
    LISTA n = jogadas;
    COORDENADA *coord;
    COORDENADA min_coord, max_coord, coord_mais_perto;
    int resultado;
    int min = 999, max = -999;
    double minimo = 100;
    for(;n != NULL; n = proximo(n)) {
        ESTADO tmp = e;
        coord = (COORDENADA *) n->valor;
        if (obter_numero_de_jogadas(&e) < JOGADAS_EM_DISTANCIA) {
            if (obter_jogador_atual(&e) == 1) {
                double dist = dist_2_coordenadas(*coord, casa_1());
                if (dist < minimo) {
                    minimo = dist;
                    coord_mais_perto = *coord;
                }
            }
            else {
                double dist = dist_2_coordenadas(*coord, casa_2());
                if (dist < minimo) {
                    minimo = dist;
                    coord_mais_perto = *coord;
                }
            }
        }
        else {
            jogar(&tmp, *coord);
            resultado = minimax(tmp, PROFUNDIDADE);
            if (resultado < min) {
                min = resultado;
                min_coord = *coord;
            }
            if (resultado > max) {
                max = resultado;
                max_coord = *coord;
            }
        }
    }
    free(jogadas);
    if (obter_numero_de_jogadas(&e) < JOGADAS_EM_DISTANCIA){
        return coord_mais_perto;
    }
    else {
        if (obter_jogador_atual(&e) == 1){
            return max_coord;
        }
        else {
            return min_coord;
        }
    }
}

double dist_2_coordenadas(COORDENADA c, COORDENADA d){
    double x;
    x = sqrt(pow((c.linha - d.linha),2) + pow((c.coluna-d.coluna),2));
    return x;
}

COORDENADA casa_1(){
    COORDENADA c;
    c.coluna = 0;
    c.linha = 0;
    return c;
}

COORDENADA casa_2(){
    COORDENADA c;
    c.coluna = 7;
    c.linha = 7;
    return c;
}

COORDENADA jog(ESTADO *e) {
    LISTA L = lista_jogadas_possiveis(e);
    COORDENADA *coordenada = (COORDENADA*) malloc(sizeof(COORDENADA));
    COORDENADA *coord = (COORDENADA*) malloc(sizeof(COORDENADA));
    *coordenada = *(COORDENADA*) devolve_cabeca(L);
    double melhor_dist;
    if (obter_jogador_atual(e) == 1)
        melhor_dist = sqrt(((coordenada->coluna) - 0) * ((coordenada->coluna) - 0) + ((coordenada->linha) - 0) * ((coordenada->linha) - 0));
    else
        melhor_dist = sqrt(((coordenada->coluna) - 7) * ((coordenada->coluna) - 7) + ((coordenada->linha) - 7) * ((coordenada->linha) - 7));
    for (LISTA T = proximo(L); !lista_esta_vazia(T); T = proximo(T)) {
        *coord = *(COORDENADA *) devolve_cabeca(T);
        int c = (*coord).coluna;
        int l = (*coord).linha;
        if (obter_jogador_atual(e) == 1) {
            double dist = sqrt((c - 0) * (c - 0) + (l - 0) * (l - 0));
            if (dist < melhor_dist) {
                melhor_dist = dist;
                (*coordenada).coluna = c;
                (*coordenada).linha = l;
            }
        }
        else if (obter_jogador_atual(e) == 2) {
            double dist = sqrt((c - 7) * (c - 7) + (l - 7) * (l - 7));
            if (dist < melhor_dist) {
                melhor_dist = dist;
                (*coordenada).coluna = c;
                (*coordenada).linha = l;
            }
        }
    }
    free(L);
    free(coord);
    return *coordenada;
}