#include "interface.h"
#include "dados.h"
#include <stdio.h>
#include <string.h>
#include "logica.h"

#define BUF_SIZE 1024

int nc=1; // número de comandos

void mostrar_tabuleiro(ESTADO *e) {
    for (int l = 0; l < 8; l++) {
        printf ("%i ",8-l);
        for (int c = 0; c < 8; c++) {
            printf((obter_casa(e, c, l) == VAZIO) ? "." : (obter_casa(e, c, l) == BRANCA) ? "*" : (obter_casa(e, c, l) == UM) ? "1" : (obter_casa(e, c, l) == DOIS) ? "2" : "#" );
        }
        putchar('\n');
    }
    printf ("  abcdefgh\n");
    printf ("# %i PL%i (%i)> ", nc++, obter_jogador_atual(e), obter_numero_de_jogadas(e));
}

int interpretador(ESTADO *e) {
    char linha[BUF_SIZE];
    char col[2], lin[2];
    if(fgets(linha, BUF_SIZE, stdin) == NULL)
        return 0;
    if(strlen(linha) == 3 && sscanf(linha, "%[a-h]%[1-8]", col, lin) == 2) {
        COORDENADA coord = {*col - 'a', 7-(*lin - '1')};
        jogar(e, coord);
        putchar('\n');
        mostrar_tabuleiro(e);
    }
    return 1;
}

void congratula_jogador (ESTADO *e){
    printf ("Parabéns jogador %i! Ganhaste!", verifica_vencedor(e));
}


