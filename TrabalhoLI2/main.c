#include "dados.h"
#include "interface.h"
#include "logica.h"

int main(){
    ESTADO *e = inicializar_estado();
    mostrar_tabuleiro(e);
    while (verifica_fim(e)) interpretador(e);
    return 0;
}