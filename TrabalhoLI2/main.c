#include "dados.h"
#include "interface.h"
#include "logica.h"

int main(){
    ESTADO *e = inicializar_estado();
    mostrar_tabuleiro(e);
    prompt(e);
    while (verifica_fim(e)) interpretador(e);
    congratula_jogador(e);
    return 0;
}