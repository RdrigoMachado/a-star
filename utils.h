// Aqui ficam as funcoes que criam nos, expandem os estados, comparam heuristicas,
// calculam o comprimento da solucao, pulam a exeucao de no pai, verificam se estado e objetivo
// e fazem a leitura das instancias de entrada e o nome dos algoritmos

#ifndef utils_h
#define utils_h

#include <cstdio>
#include <cmath>

#include "estruturas.h"


void imprimirEstados(int qtdEstados, ESTADO* estados);
COORDENADA encontraZero(ESTADO estado);
NO* expandeNo(NO* anterior, acoes acao);
int comprimentoSolucao(NO* final);
bool pularExpansao(char a, char b);
ESTADO* geraNovoEstado(ESTADO estado, acoes acao);
#endif