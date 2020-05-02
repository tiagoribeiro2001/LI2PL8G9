#include <stdio.h>
#include "bot.h"

int main(int argc, char *argv[]) {
    if (argc == 3) {
        ESTADO *e = inicializar_estado();
        char *nome = argv[1];
        ler_tabuleiro(nome, e);
        COORDENADA C = jog2(*e);
        jogar(e, C);
        guardar_tabuleiro(argv[2], e);
    }
    else {
        printf ("Erro\n");
    }
    return 0;
}
