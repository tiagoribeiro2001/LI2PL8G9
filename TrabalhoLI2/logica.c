#include "logica.h"
#include "dados.h"
#include <stdio.h>

int joga_branca(ESTADO *e, COORDENADA c) {
    e -> tab[c.coluna][c.linha] = BRANCA;
    return 0;
}