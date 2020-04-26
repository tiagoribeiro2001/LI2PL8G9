#include <stdio.h>
#include "logica.h"
#include "dados.h"
#include "listas.h"
#include <math.h>
#include <stdlib.h>
#include "interface.h"


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
    depth++;
    if (depth > 1000){
        printf("erro minimax recursivo:\n");
        exit(1);
    }
    if (verifica_fim(&e) == 0) {
        int x = verifica_vencedor(&e);
        printf("cheguei ao fim:%d\n",x);
        mostrar_tabuleiro(&e);
        if (x == 1) return 1;
        else return -1;
    }
    else {
        LISTA jogadas;
        jogadas = lista_jogadas_possiveis(&e);
        int resultado;
        if (lista_esta_vazia(jogadas)) return 0;
        for(LISTA n = jogadas; n != NULL; n = proximo(n)){
            COORDENADA *coord = (COORDENADA *) n->valor;
            printf(" [%d %d] ", coord->coluna,coord->linha);
            jogar(&e, *coord);
            resultado = minimax(e,depth);
            // Para a jogada na coordenada "*coord", o minimax retornou -1 se o jogador 2 ganhou, 0 se empataram, 1 se o jogador 1 ganhou.
            // Tendo em conta o jogador que está a jogar atualmente, ele escolherá esta jogada se ela lhe for favorável(vitória).
            if ((obter_jogador_atual(&e)) == 2 && (resultado == 1)){
                break;
            }
            else if ((obter_jogador_atual(&e)) == 1 && (resultado == -1)) {
                break;
            }
        }
        for(LISTA n = jogadas;n != NULL; n = proximo(n)){
            remove_cabeca(n);
        }
        return resultado;
    }
}



COORDENADA jog2(ESTADO e){// melhor_jogada
    int i = 0;
    LISTA jogadas;
    jogadas = lista_jogadas_possiveis(&e);
    LISTA n = jogadas;
    COORDENADA *coord;
    int resultado;
    for(;n != NULL; n = proximo(n)){
        coord = (COORDENADA *) n->valor;
        printf("JOG2: [%d, %d]\n", coord->coluna,coord->linha);
        jogar(&e, *coord);
        resultado = minimax(e,i);
        i=0;
        if ((obter_jogador_atual(&e)) == 2 && (resultado == 1)){
            break;
        }
        else if ((obter_jogador_atual(&e)) == 1 && (resultado == -1)) {
            break;
        }
    }
    for(n = jogadas;n != NULL; n = proximo(n)){
        remove_cabeca(n);
    }
    return *coord;
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
    return *coordenada;
}


