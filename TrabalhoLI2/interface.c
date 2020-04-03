#include "interface.h"
#include "dados.h"
#include <stdio.h>
#include <string.h>
#include "logica.h"
#include <stdlib.h>

#define BUF_SIZE 1024

void mostrar_tabuleiro(ESTADO *e) {
    for (int l = 0; l < 8; l++) {
        printf ("%i ",8-l);
        for (int c = 0; c < 8; c++) {
            printf((obter_casa(e, c, l) == VAZIO) ? "." : (obter_casa(e, c, l) == BRANCA) ? "*" : (obter_casa(e, c, l) == UM) ? "1" : (obter_casa(e, c, l) == DOIS) ? "2" : "#" );
        }
        putchar('\n');
    }
    printf ("  abcdefgh\n");
}

void guardar_tabuleiro(char *nome, ESTADO *e){
    FILE *ficheiro = fopen(nome,"w");
    //print do tabuleiro
    for (int l = 0; l < 8; l++) {
        for (int c = 0; c < 8; c++) {
            fprintf(ficheiro,(obter_casa(e, c, l) == VAZIO) ? "." : (obter_casa(e, c, l) == BRANCA) ? "*" : (obter_casa(e, c, l) == UM) ? "1" : (obter_casa(e, c, l) == DOIS) ? "2" : "#" );
        }
        fputc('\n',ficheiro);
    }
    fputc('\n',ficheiro);
    //print das jogadas
    int i;
    if (e->num_jogadas != 0){
        if (e->jogador_atual == 1) {
            for (i = 0; i < e->num_jogadas; i++) {
                fprintf(ficheiro,"%02d: %c%d %c%d\n", i + 1, (e->jogadas[i].jogador1.coluna + 97),
                       8 - (e->jogadas[i].jogador1.linha),
                       (e->jogadas[i].jogador2.coluna + 97),
                       8 - (e->jogadas[i].jogador2.linha));
            }
        } else {
            for (i = 0; i < (e->num_jogadas)-1; i++) {
                fprintf(ficheiro,"%02d: %c%d %c%d\n", i + 1, (e->jogadas[i].jogador1.coluna + 97),
                       8 - (e->jogadas[i].jogador1.linha),
                       (e->jogadas[i].jogador2.coluna + 97),
                       8 - (e->jogadas[i].jogador2.linha));
            }
            fprintf(ficheiro,"%02d: %c%d\n", i + 1, (e->jogadas[(e->num_jogadas)-1].jogador1.coluna + 97),
                   8 - (e->jogadas[(e->num_jogadas)-1].jogador1.linha));
        }
    }
    fclose(ficheiro);
}

void ler_tabuleiro(char *nome, ESTADO *e) {
    FILE *ficheiro = fopen(nome, "r");
    char j, h;
    int x = 0;
    if (ficheiro == NULL) printf("Ficheiro não existente.\n");
    else {
        printf("Tabuleiro inserido: \n");
        for (int l = 0; l < 8; l++) {
            for (int c = 0; c < 8; c++) {
                fscanf(ficheiro, "%c", &j);
                // Lê um caracter do ficheiro. Esse caracter contém um ponto ('.'),ou um ('*'), ou um ('#') ou um ('1') ou um ('2').
                // Eu vou agora verificar qual destes carateres é que li e vou preencher a respetiva casa do tabuleiro da variável Estado
                if (j == '.') {
                    e->tab[c][l] = VAZIO;
                } else if (j == '*') {
                    e->tab[c][l] = BRANCA;
                    e->ultima_jogada.coluna=c;
                    e->ultima_jogada.linha=l;
                } else if (j == '#') {
                    e->tab[c][l] = PRETA;
                    x++;
                } else if (j == '1') {
                    e->tab[c][l] = UM;
                } else if (j =='2'){
                    e->tab[c][l] = DOIS;
                }
            }
            fscanf(ficheiro, "%c", &h);
        }
        if (x % 2 == 0) {
            e->jogador_atual = 1;
        } else {
            e->jogador_atual = 2;
        }
        e->num_comandos = x + 1;
        e->num_jogadas = (e->num_comandos / 2);
        char col1[2], lin1[2], col2[2], lin2[2];
        fscanf(ficheiro, "%c", &h);
        if (e->num_jogadas != 0) {
            if (e->jogador_atual == 1) {
                for (int i = 0; i < e->num_jogadas; i++) {
                    fscanf(ficheiro, "%c%c%c%c", &h,&h,&h,&h);
                    fscanf(ficheiro, "%[a-h]%[1-8] %[a-h]%[1-8]", col1, lin1, col2, lin2);
                    COORDENADA coord1 = {*col1 - 'a', 7 - (*lin1 - '1')};
                    COORDENADA coord2 = {*col2 - 'a', 7 - (*lin2 - '1')};
                    e->jogadas[i].jogador1 = coord1;
                    e->jogadas[i].jogador2 = coord2;
                    fscanf(ficheiro, "%c", &h);
                }
            } else {
                for (int k = 0; k < (e->num_jogadas)-1; k++) {
                    fscanf(ficheiro, "%c%c%c%c", &h,&h,&h,&h);
                    fscanf(ficheiro, "%[a-h]%[1-8] %[a-h]%[1-8]", col1, lin1, col2, lin2);
                    COORDENADA coord1 = {*col1 - 'a', 7 - (*lin1 - '1')};
                    COORDENADA coord2 = {*col2 - 'a', 7 - (*lin2 - '1')};
                    e->jogadas[k].jogador1 = coord1;
                    e->jogadas[k].jogador2 = coord2;
                    fscanf(ficheiro, "%c", &h);
                }
                fscanf(ficheiro, "%c%c%c%c", &h, &h,&h,&h);
                fscanf(ficheiro, "%[a-h]%[1-8]", col1, lin1);
                COORDENADA coord1 = {*col1 - 'a', 7 - (*lin1 - '1')};
                e->jogadas[(e->num_jogadas)-1].jogador1 = coord1;
                fscanf(ficheiro, "%c", &h);
            }
        }
    }
}

void prompt (ESTADO *e){
    printf ("# %i PL%i (%i)> ", obter_numero_comandos(e), obter_jogador_atual(e), obter_numero_de_jogadas(e));
}

int interpretador(ESTADO *e) {
    char linha[BUF_SIZE];
    char *token;
    char col[2], lin[2];
    int x;
    if(fgets(linha, BUF_SIZE, stdin) == NULL)
        return 0;
    printf("Jogador: %s\n",linha);
    token = strtok(linha," ");
    if (strcmp(token, "Q\n") == 0 || strcmp(token, "q\n") == 0) {
        printf("A sair do programa.\n");
        exit(0);
    }
    else if (strcmp(token, "movs\n") == 0) {
       movs(e);
    }
    else if (strcmp(token, "pos") == 0) {
        token = strtok(NULL, " \n");
        x = *token -'0';
        if (token != NULL && x >= 0 && x < e->num_jogadas) {
            printf ("Jogada %s\n",token);
            pos(e, x);
            mostrar_tabuleiro(e);
            prompt(e);
        }
        else printf("Comando pos inválido.");
    }
    else if (strcmp(token, "gr") == 0) {
        // Ler nome do ficheiro
        token = strtok(NULL, " \n");
        if (token != NULL) {
            printf("Gravar o jogo no seguinte ficheiro: %s\n", token);
            guardar_tabuleiro(token,e);
            mostrar_tabuleiro(e);
            prompt(e);
        }
    }
    else if (strcmp(token, "ler") == 0) {
        // Ler nome do ficheiro
        token = strtok(NULL, " \n");
        if (token != NULL) {
            printf("Ler o jogo no seguinte ficheiro: %s\n", token);
            ler_tabuleiro(token,e);
            mostrar_tabuleiro(e);
            prompt(e);
            }
    }
    else {
        if (strlen(linha) == 3 && sscanf(linha, "%[a-h]%[1-8]", col, lin) == 2) {
            COORDENADA coord = {*col - 'a', 7 - (*lin - '1')};
            if (valida_jogada(e, coord)) {
                jogar(e, coord);
                putchar('\n');
                mostrar_tabuleiro(e);
                prompt(e);
            } else jogada_invalida();
        } else jogada_invalida();
    }
    return 1;
}

void movs (ESTADO *e) {
    int i;
    if (e->num_jogadas == 0) printf("Comando movs inválido. Ainda não foram efetuadas jogadas.\n");
    else {
        if (e->jogador_atual == 1) {
            for (i = 0; i < e->num_jogadas; i++) {
                printf("%02d: %c%d %c%d\n", i + 1, (e->jogadas[i].jogador1.coluna + 97),
                       8 - (e->jogadas[i].jogador1.linha),
                       (e->jogadas[i].jogador2.coluna + 97),
                       8 - (e->jogadas[i].jogador2.linha));
            }
        } else {
            for (i = 0; i < (e->num_jogadas)-1; i++) {
                printf("%02d: %c%d %c%d\n", i + 1, (e->jogadas[i].jogador1.coluna + 97),
                       8 - (e->jogadas[i].jogador1.linha),
                       (e->jogadas[i].jogador2.coluna + 97),
                       8 - (e->jogadas[i].jogador2.linha));
            }
                printf("%02d: %c%d\n", i + 1, (e->jogadas[(e->num_jogadas)-1].jogador1.coluna + 97),
                       8 - (e->jogadas[(e->num_jogadas)-1].jogador1.linha));
        }
    }
}

void pos (ESTADO *e, int n){
    int i, j;
    for (i=0; i<8; i++){
        for (j=0; j<8; j++){
            e->tab[i][j] = VAZIO;
        }
    }
    e->tab[4][3] = BRANCA;
    e->tab[0][7] = UM;
    e->tab[7][0] = DOIS;
    e->jogador_atual = 1;
    e->ultima_jogada.coluna = 4;
    e->ultima_jogada.linha = 3;
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

void congratula_jogador (ESTADO *e){
    printf ("Parabéns jogador %i! Ganhaste!", verifica_vencedor(e));
}

void jogada_invalida(){
    printf("Jogada inválida, tenta novamente> ");
}