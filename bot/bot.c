#include "bot.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <math.h>

LISTA criar_lista(){
    return NULL;
}

LISTA insere_cabeca(LISTA L, void *v){
    LISTA n = malloc(sizeof(NODO));
    n->valor = v;
    n->proximo = L;
    return n;
}

LISTA proximo(LISTA L){
    return L->proximo;
}

int lista_esta_vazia(LISTA L){
    return L == NULL;
}

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

void ler_tabuleiro(char *nome, ESTADO *e) {
    FILE *ficheiro = fopen(nome, "r");
    char j;
    int x = 0;
    if (ficheiro == NULL) printf("Ficheiro não existente.\n");
    else {
        for (int l = 7; 0 <= l; l--) {
            for (int c = 0; c <= 7; c++) {
                if (fscanf(ficheiro, "%c", &j) == 1) {};
                // Lê um caracter do ficheiro. Esse caracter contém um ponto ('.'),ou um ('*'), ou um ('#') ou um ('1') ou um ('2').
                // Eu vou agora verificar qual destes carateres é que li e vou preencher a respetiva casa do tabuleiro da variável Estado
                if (j == '.') {
                    alterar_tab(e, c, l, VAZIO);
                } else if (j == '*') {
                    alterar_tab(e, c, l, BRANCA);
                    alterar_ultima_jogada_coluna(e, c);
                    alterar_ultima_jogada_linha(e, l);
                } else if (j == '#') {
                    alterar_tab(e, c, l, PRETA);
                    x++;
                } else if (j == '1') {
                    alterar_tab(e, c, l, UM);
                } else if (j =='2'){
                    alterar_tab(e, c, l, DOIS);
                }
            }
            if (fscanf(ficheiro, "%*c") == 1) {};
        }
        if (x % 2 == 0) {
            alterar_jogador_atual(e, 1);
        } else {
            alterar_jogador_atual(e, 2);
        }
        alterar_numero_comandos(e, x+1);
        alterar_numero_de_jogadas(e, (obter_numero_comandos(e) / 2));
        alterar_total_jogadas(e, obter_numero_de_jogadas(e));
        alterar_numero_jogador_pos(e, obter_jogador_atual(e));
        char col1[2], lin1[2], col2[2], lin2[2];
        if (fscanf(ficheiro, "%*c") == 1) {};
        if (obter_numero_de_jogadas(e) != 0) {
            if (obter_jogador_atual(e) == 1) {
                for (int i = 0; i < obter_numero_de_jogadas(e); i++) {
                    if (fscanf(ficheiro, "%*c%*c%*c%*c") == 4) {};
                    if (fscanf(ficheiro, "%[a-h]%[1-8] %[a-h]%[1-8]", col1, lin1, col2, lin2) == 4) {};
                    COORDENADA coord1 = {*col1 - 'a', (*lin1 - '1')};
                    COORDENADA coord2 = {*col2 - 'a', (*lin2 - '1')};
                    alterar_jogadas_jog1(e, i, coord1);
                    alterar_jogadas_jog2(e, i, coord2);
                    if (fscanf(ficheiro, "%*c") == 1) {};
                }
            } else {
                for (int k = 0; k < obter_numero_de_jogadas(e)-1; k++) {
                    if (fscanf(ficheiro, "%*c%*c%*c%*c") == 4) {};
                    if (fscanf(ficheiro, "%[a-h]%[1-8] %[a-h]%[1-8]", col1, lin1, col2, lin2) == 4) {};
                    COORDENADA coord1 = {*col1 - 'a', (*lin1 - '1')};
                    COORDENADA coord2 = {*col2 - 'a', (*lin2 - '1')};
                    alterar_jogadas_jog1(e, k, coord1);
                    alterar_jogadas_jog2(e, k, coord2);
                    if (fscanf(ficheiro, "%*c") == 1) {};
                }
                if (fscanf(ficheiro, "%*c%*c%*c%*c") == 4) {};
                if (fscanf(ficheiro, "%[a-h]%[1-8]", col1, lin1) == 2) {};
                COORDENADA coord1 = {*col1 - 'a', (*lin1 - '1')};
                alterar_jogadas_jog1(e, obter_numero_de_jogadas(e)-1, coord1);
                if (fscanf(ficheiro, "%*c") == 1){};
            }
        }
    }
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

void alterar_total_jogadas(ESTADO *e, int n){
    e->total_jogadas_pos = n;
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

void guardar_tabuleiro(char *nome, ESTADO *e){
    FILE *ficheiro = fopen(nome,"w");
    //print do tabuleiro
    for (int l = 7; 0 <= l; l--) {
        for (int c = 0; c <= 7; c++) {
            fprintf(ficheiro,(obter_casa(e, c, l) == VAZIO) ? "." : (obter_casa(e, c, l) == BRANCA) ? "*" : (obter_casa(e, c, l) == UM) ? "1" : (obter_casa(e, c, l) == DOIS) ? "2" : "#" );
        }
        fputc('\n',ficheiro);
    }
    fputc('\n',ficheiro);
    //print das jogadas
    int i;
    if (obter_numero_de_jogadas(e) != 0){
        if (obter_jogador_atual(e) == 1) {
            for (i = 0; i < obter_numero_de_jogadas(e); i++) {
                fprintf(ficheiro,"%02d: %c%d %c%d\n", i + 1, obter_jogadas_jog1_coluna(e, i) + 97,
                        obter_jogadas_jog1_linha(e, i) + 1,
                        obter_jogadas_jog2_coluna(e, i) + 97,
                        obter_jogadas_jog2_linha(e, i) + 1);
            }
        } else {
            for (i = 0; i < obter_numero_de_jogadas(e)-1; i++) {
                fprintf(ficheiro,"%02d: %c%d %c%d\n", i + 1, obter_jogadas_jog1_coluna(e, i) + 97,
                        obter_jogadas_jog1_linha(e, i) + 1,
                        obter_jogadas_jog2_coluna(e, i) + 97,
                        obter_jogadas_jog2_linha(e, i) + 1);
            }
            fprintf(ficheiro,"%02d: %c%d\n", i + 1, obter_jogadas_jog1_coluna(e, obter_numero_de_jogadas(e)-1) + 97,
                    obter_jogadas_jog1_linha(e, obter_numero_de_jogadas(e)-1) + 1);
        }
    }
    fclose(ficheiro);
}