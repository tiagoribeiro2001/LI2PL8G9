#include "logica.h"
#include "dados.h"
#include "listas.h"
#include <stdio.h>

int jogar(ESTADO *e, COORDENADA c) {
    int i = valida_jogada (e,c);
    if (i) {
        e->tab[e->ultima_jogada.coluna][e->ultima_jogada.linha] = PRETA;
        e->tab[c.coluna][c.linha] = BRANCA;
        e->ultima_jogada.coluna = c.coluna;
        e->ultima_jogada.linha = c.linha;
        if (obter_jogador_atual(e) == 1){
            e->jogador_atual = 2;
            (e->num_jogadas = (obter_numero_de_jogadas(e) + 1));
            e->jogadas[obter_numero_de_jogadas(e)-1].jogador1.coluna = c.coluna;
            e->jogadas[obter_numero_de_jogadas(e)-1].jogador1.linha = c.linha;
        }
        else if (obter_jogador_atual(e) == 2){
            e->jogadas[obter_numero_de_jogadas(e)-1].jogador2.coluna = c.coluna;
            e->jogadas[obter_numero_de_jogadas(e)-1].jogador2.linha = c.linha;
            e->jogador_atual = 1;
        }
        e->num_comandos = (obter_numero_comandos(e) + 1);
        e->total_jogadas = obter_numero_de_jogadas(e);
        e->numj_pos = obter_jogador_atual(e);
    }
    return i;
}

int valida_jogada(ESTADO *e, COORDENADA c){
    int p=1;
    if (obter_casa(e,c.coluna,c.linha) == PRETA || obter_casa(e,c.coluna,c.linha) == BRANCA) p = 0;
    if (c.coluna > (e->ultima_jogada.coluna)+1 || c.coluna < (e->ultima_jogada.coluna)-1) p = 0;
    if (c.linha > (e->ultima_jogada.linha)+1 || c.linha < (e->ultima_jogada.linha)-1) p = 0;
    if (c.coluna < 0 || c.coluna > 7) p = 0;
    if (c.linha < 0 || c.linha > 7) p = 0;
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
    e->jogador_atual = 1;
    e->ultima_jogada.coluna = 4;
    e->ultima_jogada.linha = 4;
    for (i=0; i<n; i++){
        e->tab[e->ultima_jogada.coluna][e->ultima_jogada.linha] = PRETA;
        e->tab[e->jogadas[i].jogador1.coluna][e->jogadas[i].jogador1.linha] = PRETA;
        e->tab[e->jogadas[i].jogador2.coluna][e->jogadas[i].jogador2.linha] = BRANCA;
        e->ultima_jogada.coluna = e->jogadas[i].jogador2.coluna;
        e->ultima_jogada.linha = e->jogadas[i].jogador2.linha;
    }
    e->num_jogadas = n;
    e->num_comandos = 2*n+1;
}

COORDENADA jog (ESTADO *e){
    int c, l, cm=(e->ultima_jogada.coluna)+1, lm=(e->ultima_jogada.linha)+1;
    int a = 0;
    LISTA L;
    L = criar_lista();
    COORDENADA C;
    for (c=(e->ultima_jogada.coluna)-1; c<=cm; c++){
        for (l=(e->ultima_jogada.linha)-1; l<=lm; l++){
            if (obter_casa(e,c,l) != PRETA && obter_casa(e,c,l) != BRANCA && obter_casa(e,c,l) != ERRO){
                C.coluna = c;
                C.linha = l;
                insere_cabeca(L,&C);
                a++;
                printf("%d %d \n", C.coluna , C.linha);
            }
        }
    }
    COORDENADA *x;
    x = devolve_cabeca(L);
    return *x;
}