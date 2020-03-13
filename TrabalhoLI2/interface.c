#include "interface.h"
#include "dados.h"
#include <stdio.h>

void mostrar_tabuleiro(ESTADO *e) {
    for (int i=0; i<8; i++) {
        if (i == 0) {
            for (int j = 0; j < 7; j++) {
                if (e->tab[i][j] == VAZIO) printf(".");
                if (e->tab[i][j] == BRANCA) printf("*");
                if (e->tab[i][j] == PRETA) printf("#");
            }
            if (e->tab[0][7] == BRANCA)  printf("*");
            else printf("2");
        }
        else if (i == 7) {
            for (int p = 0; p < 8; p++) {
                if (p == 0) {
                    if (e->tab[7][0] == BRANCA) printf("*");
                    else printf("1");
                }
                else {
                    if (e->tab[i][p] == VAZIO) printf(".");
                    if (e->tab[i][p] == BRANCA) printf("*");
                    if (e->tab[i][p] == PRETA) printf("#");
                }
            }
        }
        else
            for (int z = 0; z < 8; z++) {
                if (e->tab[z][i] == VAZIO) printf(".");
                if (e->tab[z][i] == BRANCA) printf("*");
                if (e->tab[z][i] == PRETA) printf("#");
            }
            printf("\n");
    }
}

