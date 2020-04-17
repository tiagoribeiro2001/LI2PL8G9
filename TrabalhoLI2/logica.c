#include "logica.h"
#include "dados.h"

int jogar(ESTADO *e, COORDENADA c) {
    int i = valida_jogada (e,c);
    if (i) {
        e->tab[e->ultima_jogada.coluna][e->ultima_jogada.linha] = PRETA;
        e->tab[c.coluna][c.linha] = BRANCA;
        e->ultima_jogada.coluna = c.coluna;
        e->ultima_jogada.linha = c.linha;
        if (e->jogador_atual == 1){
            e->jogador_atual = 2;
            (e->num_jogadas = (e->num_jogadas + 1));
            e->jogadas[(e->num_jogadas)-1].jogador1.coluna = c.coluna;
            e->jogadas[(e->num_jogadas)-1].jogador1.linha = c.linha;
        }
        else if (e->jogador_atual == 2){
            e->jogadas[(e->num_jogadas)-1].jogador2.coluna = c.coluna;
            e->jogadas[(e->num_jogadas)-1].jogador2.linha = c.linha;
            e->jogador_atual = 1;
        }
        e->num_comandos = (e->num_comandos + 1);
        e->total_jogadas = e->num_jogadas;
        e->numj_pos = e->jogador_atual;
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
    if (obter_casa(e,0,7) == BRANCA) i = 0;
    if (obter_casa(e,7,0) == BRANCA) i = 0;
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
    if (e->jogador_atual == 1) i = 2;
    if (e->jogador_atual == 2) i = 1;
    if (obter_casa(e,0,7) == BRANCA) i = 1;
    if (obter_casa(e,7,0) == BRANCA) i = 2;
    return i;
}