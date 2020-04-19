#include "logica.h"
#include "dados.h"
#include "listas.h"
#include <stdio.h>
#include <math.h>
#include <stdlib.h>

int jogar(ESTADO *e, COORDENADA c) {
    int i = valida_jogada (e,c);
    if (i) {
        e->tab[e->ultima_jogada.coluna][e->ultima_jogada.linha] = PRETA;
        e->tab[c.coluna][c.linha] = BRANCA;
        e->ultima_jogada.coluna = c.coluna;
        e->ultima_jogada.linha = c.linha;
        if (obter_jogador_atual(e) == 1){
            alterar_jogador_atual(e, 2);
            alterar_numero_de_jogadas(e, obter_numero_de_jogadas(e) + 1);
            e->jogadas[obter_numero_de_jogadas(e)-1].jogador1.coluna = c.coluna;
            e->jogadas[obter_numero_de_jogadas(e)-1].jogador1.linha = c.linha;
        }
        else if (obter_jogador_atual(e) == 2){
            e->jogadas[obter_numero_de_jogadas(e)-1].jogador2.coluna = c.coluna;
            e->jogadas[obter_numero_de_jogadas(e)-1].jogador2.linha = c.linha;
            alterar_jogador_atual(e, 1);
        }
        alterar_numero_comandos(e,obter_numero_comandos(e) + 1);
        alterar_total_jogadas(e, obter_numero_de_jogadas(e));
        alterar_numero_jogador_pos(e, obter_jogador_atual(e));
    }
    return i;
}

int valida_jogada(ESTADO *e, COORDENADA c){
    int p=1;
    if (obter_casa(e,c.coluna,c.linha) == PRETA || obter_casa(e,c.coluna,c.linha) == BRANCA || obter_casa(e,c.coluna,c.linha) == ERRO) p = 0;
    if (c.coluna > (e->ultima_jogada.coluna)+1 || c.coluna < (e->ultima_jogada.coluna)-1) p = 0;
    if (c.linha > (e->ultima_jogada.linha)+1 || c.linha < (e->ultima_jogada.linha)-1) p = 0;
    return p;
}

int verifica_fim(ESTADO *e){
    int i=1;
    if (obter_casa(e,0,0) == BRANCA) i = 0;
    if (obter_casa(e,7,7) == BRANCA) i = 0;
    i = (i && verifica_pos(e));
    return i;
}

int verifica_pos(ESTADO *e){
    int i=0, c, l, cm=(e->ultima_jogada.coluna)+1, lm=(e->ultima_jogada.linha)+1;
    for (c=(e->ultima_jogada.coluna)-1; c<=cm; c++){
        for (l=(e->ultima_jogada.linha)-1; l<=lm; l++){
            if (obter_casa(e,c,l) != PRETA && obter_casa(e,c,l) != BRANCA && obter_casa(e,c,l) != ERRO) i = 1;
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
    for (i=0; i<8; i++){
        for (j=0; j<8; j++){
            e->tab[i][j] = VAZIO;
        }
    }
    e->tab[4][4] = BRANCA;
    e->tab[0][0] = UM;
    e->tab[7][7] = DOIS;
    alterar_jogador_atual(e, 1);
    e->ultima_jogada.coluna = 4;
    e->ultima_jogada.linha = 4;
    for (i=0; i<n; i++){
        e->tab[e->ultima_jogada.coluna][e->ultima_jogada.linha] = PRETA;
        e->tab[e->jogadas[i].jogador1.coluna][e->jogadas[i].jogador1.linha] = PRETA;
        e->tab[e->jogadas[i].jogador2.coluna][e->jogadas[i].jogador2.linha] = BRANCA;
        e->ultima_jogada.coluna = e->jogadas[i].jogador2.coluna;
        e->ultima_jogada.linha = e->jogadas[i].jogador2.linha;
    }
    alterar_numero_de_jogadas(e, n);
    alterar_numero_comandos(e, 2*n+1);
}

COORDENADA jog (ESTADO *e){
    COORDENADA ult_coord = e->ultima_jogada;
    int linha = ult_coord.linha, coluna = ult_coord.coluna, c, l;
    LISTA L = criar_lista();
    for (c=coluna-1; c<coluna+2; c++){
        for (l=linha-1; l<linha+2; l++){
            if (obter_casa(e,c,l) != PRETA && obter_casa(e,c,l) != BRANCA && obter_casa(e,c,l) != ERRO) {
                COORDENADA *C = (COORDENADA *) malloc(sizeof(COORDENADA));
                (*C).coluna = c;
                (*C).linha = l;
                L = insere_cabeca(L, C);
                printf("%d %d \n", (*C).coluna, (*C).linha);
            }
        }
    }
    //COORDENADA *coord = (COORDENADA *) devolve_cabeca(L);
    printf("ola");
    COORDENADA *coord = (COORDENADA *) decide_jog(e,L);
    return *coord;
}

COORDENADA *decide_jog (ESTADO *e, LISTA L){
    printf("ola");
    COORDENADA *coordenada = malloc(sizeof(COORDENADA));
    double distm = 100;
    printf("ola");
    for(LISTA T = L; !lista_esta_vazia(T); T = proximo(T)) {
        COORDENADA *coord = (COORDENADA *) devolve_cabeca(T);
        int c = coord->coluna;
        int l = coord->linha;
            if (obter_jogador_atual(e) == 1) {
                double dist = sqrt((c - 0) * (c - 0) + (l - 0) * (l - 0));
                if (dist < distm) {
                    distm = dist;
                    (*coordenada).coluna = c;
                    (*coordenada).linha = l;
                }
            }
            if (obter_jogador_atual(e) == 2) {
                double dist = sqrt((c - 7) * (c - 7) + (l - 7) * (l - 7));
                if (dist < distm) {
                    distm = dist;
                    (*coordenada).coluna = c;
                    (*coordenada).linha = l;
                }
            }
    }
    return coordenada;
}