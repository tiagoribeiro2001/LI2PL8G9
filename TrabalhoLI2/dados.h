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
    /** Coluna */
    int coluna;
    /** Linha */
    int linha;
} COORDENADA;

/**
\brief Tipo de dados para a jogada
*/
typedef struct {
    /** Coordenada do jogador 1 */
    COORDENADA jogador1;
    /** Coordenada do jogador 2 */
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
    int total_jogadas_pos;
    /** O jogador atual aquando da utilização do comando pos */
    int numero_jogador_pos;
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
\brief Altera o número de jogadas
@param e Apontador para o estado
@param n Número de jogadas para o qual se pretende alterar
*/
void alterar_numero_de_jogadas(ESTADO *e, int n);

/**
\brief Devolve o jogador atual
@param e Apontador para o estado
@returns O jogador atual
*/
int obter_jogador_atual(ESTADO *e);

/**
\brief Altera o jogador atual
@param e Apontador para o estado
@param n Jogador para o qual se pretende alterar
*/
void alterar_jogador_atual(ESTADO *e, int n);

/**
\brief Devolve o número de comandos
@param e Apontador para o estado
@returns O número de comandos
*/
int obter_numero_comandos(ESTADO *e);

/**
\brief Altera o número de comandos
@param e Apontador para o estado
@param n Valor para o qual se pretende alterar o número de comandos
*/
void alterar_numero_comandos(ESTADO *e, int n);

/**
\brief Devolve o número de jogadas ocorridas aquando da utilização do comando pos
@param e Apontador para o estado
@returns O número de jogadas ocorridas aquando da utilização do comando pos
*/
int obter_total_jogadas(ESTADO *e);

/**
\brief Altera o número de jogadas ocorridas aquando da utilização do comando pos
@param e Apontador para o estado
@param n Valor para o qual se pretende alterar o número de jogadas ocorridas aquando da utilização do comando pos
*/
void alterar_total_jogadas(ESTADO *e, int n);

/**
\brief Devolve o jogador atual aquando da utilização do comando pos
@param e Apontador para o estado
@returns O jogador atual aquando da utilização do comando pos
*/
int obter_numj_pos(ESTADO *e);

/**
\brief Altera o jogador atual aquando da utilização do comando pos
@param e Apontador para o estado
@param n Jogador para o qual se pretende alterar
*/
void alterar_numero_jogador_pos(ESTADO *e, int n);

/**
\brief Devolve a coluna que está no array jogadas na posição i do jogador 1
@param e Apontador para o estado
@param i Posição do array
@returns Coluna que está no array jogadas na posição i do jogador 1
*/
int obter_jogadas_jog1_coluna (ESTADO *e, int i);

/**
\brief Devolve a linha que está no array jogadas na posição i do jogador 1
@param e Apontador para o estado
@param i Posição do array
@returns Linha que está no array jogadas na posição i do jogador 1
*/
int obter_jogadas_jog1_linha (ESTADO *e, int i);

/**
\brief Devolve a coluna que está no array jogadas na posição i do jogador 2
@param e Apontador para o estado
@param i Posição do array
@returns Coluna que está no array jogadas na posição i do jogador 2
*/
int obter_jogadas_jog2_coluna (ESTADO *e, int i);

/**
\brief Devolve a linha que está no array jogadas na posição i do jogador 2
@param e Apontador para o estado
@param i Posição do array
@returns Linha que está no array jogadas na posição i do jogador 2
*/
int obter_jogadas_jog2_linha (ESTADO *e, int i);

/**
\brief Altera a coordenada do jogador 1 no array jogadas na posição i
@param e Apontador para o estado
@param i Índice que pretendemos alterar
@param c Coordenada para o qual se pretende alterar
*/
void alterar_jogadas_jog1 (ESTADO *e, int i, COORDENADA c);

/**
\brief Altera a coluna do jogador 1 no array jogadas na posição i
@param e Apontador para o estado
@param i Índice que pretendemos alterar
@param c Coluna para o qual se pretende alterar
*/
void alterar_jogadas_jog1_coluna (ESTADO *e, int i, int c);

/**
\brief Altera a linha do jogador 1 no array jogadas na posição i
@param e Apontador para o estado
@param i Índice que pretendemos alterar
@param c Linha para o qual se pretende alterar
*/
void alterar_jogadas_jog1_linha (ESTADO *e, int i, int l);

/**
\brief Altera a coordenada do jogador 2 no array jogadas na posição i
@param e Apontador para o estado
@param i Índice que pretendemos alterar
@param c Coordenada para o qual se pretende alterar
*/
void alterar_jogadas_jog2 (ESTADO *e, int i, COORDENADA c);

/**
\brief Altera a coluna do jogador 2 no array jogadas na posição i
@param e Apontador para o estado
@param i Índice que pretendemos alterar
@param c Coluna para o qual se pretende alterar
*/
void alterar_jogadas_jog2_coluna (ESTADO *e, int i, int c);

/**
\brief Altera a linha do jogador 2 no array jogadas na posição i
@param e Apontador para o estado
@param i Índice que pretendemos alterar
@param c Linha para o qual se pretende alterar
*/
void alterar_jogadas_jog2_linha (ESTADO *e, int i, int l);

/**
\brief Altera a casa de uma dada coordenada
@param e Apontador para o estado
@param c Coluna da coordenada a alterar
@param l Linha da coordenada a alterar
@param casa Casa para a qual pretendemos alterar
*/
void alterar_tab (ESTADO *e, int c, int l, CASA casa);

/**
\brief Altera a coluna da última jogada
@param e Apontador para o estado
@param c Coluna para a qual pretendemos alterar
*/
void alterar_ultima_jogada_coluna (ESTADO *e, int c);

/**
\brief Altera a linha da última jogada
@param e Apontador para o estado
@param l Linha para a qual pretendemos alterar
*/
void alterar_ultima_jogada_linha (ESTADO *e, int l);

/**
\brief Devolve a coluna da última jogada
@param e Apontador para o estado
@returns A coluna da última jogada
*/
int obter_ultima_jogada_coluna (ESTADO *e);

/**
\brief Devolve a linha da última jogada
@param e Apontador para o estado
@returns A linha da última jogada
*/
int obter_ultima_jogada_linha (ESTADO *e);

/**
\brief Devolve a coordenada da última jogada
@param e Apontador para o estado
@returns A coordenada da última jogada
*/
COORDENADA obter_ultima_jogada (ESTADO *e);

#endif //TRABALHOLI2_DADOS_H