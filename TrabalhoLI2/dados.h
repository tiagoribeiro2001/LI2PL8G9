#ifndef TRABALHOLI2_DADOS_H
#define TRABALHOLI2_DADOS_H

typedef enum {VAZIO, BRANCA, PRETA, UM, DOIS} CASA;
typedef struct {
    int coluna;
    int linha;
} COORDENADA;
typedef struct {
    COORDENADA jogador1;
    COORDENADA jogador2;
} JOGADA;
typedef JOGADA JOGADAS[32];
typedef struct {
    CASA tab[8][8];
    COORDENADA ultima_jogada;
    JOGADAS jogadas;
    int num_jogadas;
    int jogador_atual;
} ESTADO;

ESTADO *inicializar_estado();

CASA obter_casa (ESTADO *e, int i, int k);

int obter_numero_de_jogadas(ESTADO *e);

int obter_jogador_atual(ESTADO *e);

#endif //TRABALHOLI2_DADOS_H
