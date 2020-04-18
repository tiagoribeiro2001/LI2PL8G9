/**
@file dados.h
Definição do estado e das funções que o manipulam
*/
#ifndef TRABALHOLI2_DADOS_H
#define TRABALHOLI2_DADOS_H

/**
\brief Tipo de dados para a casa
*/
typedef enum {VAZIO, BRANCA, PRETA, UM, DOIS, ERRO} CASA;

/**
\brief Tipo de dados para as coordenadas
*/
typedef struct {
    int coluna;
    int linha;
} COORDENADA;

/**
\brief Tipo de dados para a jogada
*/
typedef struct {
    COORDENADA jogador1;
    COORDENADA jogador2;
} JOGADA;

/**
\brief Tipo de dados para as jogadas
*/
typedef JOGADA JOGADAS[32];

/**
\brief Tipo de dados para o estado
*/
typedef struct {
    /** O tabuleiro */
    CASA tab[8][8];
    /** A coordenada da última jogada */
    COORDENADA ultima_jogada;
    /** As jogadas */
    JOGADAS jogadas;
    /** O número das jogadas, usado no prompt */
    int num_jogadas;
    /** O jogador atual */
    int jogador_atual;
    /** O número de comando, usado no prompt */
    int num_comandos;
    /** O número de jogadas ocorridas aquando da utilização do comando pos */
    int total_jogadas;
    /** O jogador atual aquando da utilização do comando pos */
    int numj_pos;
} ESTADO;

/**
\brief Inicializa o valor do estado
Esta função inicializa o valor do estado. Isso implica o tabuleiro ser colocado na posição inicial e todos os campos do estado estarem com o valor por omissão.
@returns O novo estado
*/
ESTADO *inicializar_estado();

/**
\brief Devolve o valor de uma casa
@param e Apontador para o estado
@param c O número da coluna
@param l O número da linha
@returns O valor da casa
*/
CASA obter_casa (ESTADO *e, int c, int l);

/**
\brief Devolve o número de jogadas
@param e Apontador para o estado
@returns O número de jogadas
*/
int obter_numero_de_jogadas(ESTADO *e);

/**
\brief Devolve o jogador atual
@param e Apontador para o estado
@returns O jogador atual
*/
int obter_jogador_atual(ESTADO *e);

/**
\brief Devolve o número de comandos
@param e Apontador para o estado
@returns O número de comandos
*/
int obter_numero_comandos(ESTADO *e);

/**
\brief Devolve o número de jogadas ocorridas aquando da utilização do comando pos
@param e Apontador para o estado
@returns O número de jogadas ocorridas aquando da utilização do comando pos
*/
int obter_total_jogadas(ESTADO *e);

/**
\brief Devolve o jogador atual aquando da utilização do comando pos
@param e Apontador para o estado
@returns O jogador atual aquando da utilização do comando pos
*/
int obter_numj_pos(ESTADO *e);

#endif //TRABALHOLI2_DADOS_H
