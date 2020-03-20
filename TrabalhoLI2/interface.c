#include "interface.h"
#include "dados.h"
#include <stdio.h>
#include <string.h>
#include "logica.h"

#define BUF_SIZE 1024

void mostrar_tabuleiro(ESTADO *e) {
    for (int i = 0; i < 8; i++) {
        for (int k = 0; k < 8; k++) {
            printf((obter_casa(e, i, k) == VAZIO) ? "." : (obter_casa(e, i, k) == BRANCA) ? "*" : (obter_casa(e, i, k) == UM) ? "1" : (obter_casa(e, i, k) == DOIS) ? "2" : "#" );
        }
        putchar('\n');
    }
}

int interpretador(ESTADO *e) {
    char linha[BUF_SIZE];
    char col[2], lin[2];
    if(fgets(linha, BUF_SIZE, stdin) == NULL)
        return 0;
    if(strlen(linha) == 3 && sscanf(linha, "%[a-h]%[1-8]", col, lin) == 2) {
        COORDENADA coord = {*col - 'a', *lin - '1'};
        jogar(e, coord);
        mostrar_tabuleiro(e);
    }
    return 1;
}



