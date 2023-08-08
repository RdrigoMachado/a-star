#ifndef idastar_h
#define idastar_h

#include <unordered_set> 
#include <queue>
#include "../estruturas.h"
#include "../utils.h"


#define INFINITO 200
#define ENCONTRADA_SOLUCAO -1

ESTATISTICAS* busca_IDA(ESTADO estado_inicial);

#endif