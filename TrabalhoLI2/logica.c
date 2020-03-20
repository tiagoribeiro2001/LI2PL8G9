#include "logica.h"
#include "dados.h"


int jogar(ESTADO *e, COORDENADA c) {
    int i = valida_jogada (e,c);
    if (i) {
        e->tab[e->ultima_jogada.coluna][e->ultima_jogada.linha] = PRETA;
        e->tab[c.coluna][c.linha] = BRANCA;
        if (e->jogador_atual == 1) e->jogador_atual = 2;
        if (e->jogador_atual == 2) e->jogador_atual = 1;
        e->ultima_jogada.coluna = c.coluna;
        e->ultima_jogada.linha = c.linha;
        //falta alterar o array jogadas (adicionar a jogada atual)
        e->num_jogadas = obter_numero_de_jogadas(e) + 1;
    }
    return i;
}

int valida_jogada(ESTADO *e, COORDENADA c){
    int p=1;
    if (obter_casa(e,c.coluna,c.linha) == PRETA || obter_casa(e,c.coluna,c.linha) == BRANCA) p = 0;
    if (c.coluna > (e->ultima_jogada.coluna)+1 || c.coluna < (e->ultima_jogada.coluna)-1) p = 0;
    if (c.linha > (e->ultima_jogada.linha)+1 || c.linha < (e->ultima_jogada.linha)-1) p = 0;
    return p;
}