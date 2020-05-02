/**
@file bot.h
Definição das funções utilizadas pelo bot
*/

#ifndef BOT_BOT_H
#define BOT_BOT_H

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
\brief Tipo para as listas ligadas
*/
typedef struct nodo {
    /** Apontador para o valor*/
    void *valor;
    /** Apontador para o próximo nodo */
    struct nodo *proximo;
} NODO, *LISTA;

/**
\brief Cria uma lista vazia
@returns Devolve a lista vazia criada
*/
LISTA criar_lista();

/**
\brief Insere um valor na cabeça da lista
@param L Apontador para a lista
@param v Apontador para a nova cabeça
@returns Devolve a lista com a nova cabeça
*/
LISTA insere_cabeca(LISTA L, void *v);

/**
\brief Indica qual é a cauda da lista
@param L Apontador para a lista
@returns Devolve a cauda da lista
*/
LISTA proximo(LISTA L);

/**
\brief Testa se uma lista é vazia
@param L Apontador para a lista
@returns Devolve verdareiro se a lista é vazia, caso contrário devolve falso
*/
int lista_esta_vazia(LISTA L);

/**
\brief Inicializa o valor do estado
Esta função inicializa o valor do estado. Isso implica o tabuleiro ser colocado na posição inicial e todos os campos do estado estarem com o valor por omissão.
@returns O novo estado
*/
ESTADO *inicializar_estado();

/**
\brief Lê um ficheiro que contêm um jogo
@param nome Apontador para o ficheiro
@param e Apontador para o estado
*/
void ler_tabuleiro(char *nome, ESTADO *e);

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
\brief Altera o número de jogadas ocorridas aquando da utilização do comando pos
@param e Apontador para o estado
@param n Valor para o qual se pretende alterar o número de jogadas ocorridas aquando da utilização do comando pos
*/
void alterar_total_jogadas(ESTADO *e, int n);

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

/**
\brief Cria uma lista de possíveis jogadas a executar
@param e Apontador para o estado
@returns A lsita com as jogadas possíveis
*/
LISTA lista_jogadas_possiveis (ESTADO *e);

/**
\brief Define a melhor jogada possível
@param e  Estado atual do jogo
@param depth Profundidade da escolha da jogada
@returns Retorna o valor da melhor jogada possível
*/
int minimax(ESTADO e, int depth);

/**
\brief Permite ao jogador atual que peça ao computador para jogar por si
@param e  Estado atual do jogo
@returns A melhor jogada escolhida para ser realizada
*/
COORDENADA jog2(ESTADO e);

/**
\brief Calcula a distância entre duas coordenadas
@param c  Coordenada
@param d  Coordenada
@returns A distância entre as duas coordenadas
*/
double dist_2_coordenadas(COORDENADA c, COORDENADA d);

/**
\brief Determina a posição da casa UM
@returns A coordenada da casa UM
*/
COORDENADA casa_1();

/**
\brief Determina a posição da casa DOIS
@returns A coordenada da casa DOIS
*/
COORDENADA casa_2();

/**
\brief Verifica se o jogo chegou ao fim
@param e Apontador para o estado
@returns Devolve zero caso o jogo tenha acabado ou um em caso contrário.
*/
int verifica_fim(ESTADO *e);

/**
\brief Verifica se o jogador tem algum sitio aonde jogar
@param e Apontador para o estado
@returns Devolve um caso seja possível jogar e zero caso contrário.
*/
int verifica_pos(ESTADO *e);

/**
\brief Verifica qual jogador venceu o jogo
@param e Apontador para o estado
@returns Devolve um caso o jogador um tenha ganho ou dois caso o jogador dois tenha ganho.
*/
int verifica_vencedor(ESTADO *e);

/**
\brief Altera os parâmetros no estado mediante a jogada
@param e Apontador para o estado
@param c A coordenada da jogada a efetuar
@returns Devolve um se for possível jogar e zero caso não seja possível.
*/
int jogar(ESTADO *e, COORDENADA c);

/**
\brief Verifica se a jogada introduzida é valida
@param e Apontador para o estado
@param c A coordenada da jogada a efetuar
@returns Devolve um se for possível jogar e zero caso não seja possível.
*/
int valida_jogada(ESTADO *e, COORDENADA c);

/**
\brief Guarda o jogo num ficheiro
@param nome Apontador para o ficheiro
@param e Apontador para o estado
*/
void guardar_tabuleiro(char *nome, ESTADO *e);

#endif //BOT_BOT_H
