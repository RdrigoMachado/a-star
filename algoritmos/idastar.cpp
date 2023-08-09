#include "idastar.h"

std::unordered_set<ESTADO, EstadoHash, EstadoEqual> visitados;

std::vector<NO*> geraVizinhosIDA(NO* estado_atual, ESTATISTICAS* estatisticas)
{
    std::vector<NO*> vizinhos;
    for(int i = 0; i < 4; i++)
    {
        //nao gerar estado-pai do estado atual 
        if(pularExpansao(estado_atual->acao, (acoes)i))
            continue;
        
        NO* novo = expandeNo(estado_atual, (acoes)i);

        if(novo == NULL)
            continue;

        if(visitados.insert(novo->estado).second == false)
            continue;

        vizinhos.push_back(novo);
    }
    return vizinhos;
}

int procura_recursiva(NO* atual, int f_limit, ESTATISTICAS* estatisticas){
    int f = atual->g + atual->heuristica;
    int proximo_limite = INFINITO;

estatisticas->nodos_visitados++;
    if(is_objetivo(atual->estado))
    {
        estatisticas->comprimento = comprimentoSolucao(atual);
#ifdef _debug
printf("PAI %d %d\n", atual->anterior->g, atual->anterior->heuristica);
imprimirEstados(1, &(atual->anterior->estado));
printf("filho %d %d\n", atual->g, atual->heuristica);
imprimirEstados(1, &(atual->estado));
printf("f_limit %d      expandidos %d visitados %d\n", f_limit, estatisticas->nodos_expandidos,estatisticas->nodos_visitados);
#endif
        return ENCONTRADA_SOLUCAO;
    }

    if(f > f_limit)
        return f;

    std::vector<NO*> vizinhos = geraVizinhosIDA(atual, estatisticas);

    for (auto& vizinho : vizinhos) 
    {
        estatisticas->nodos_expandidos++;
        estatisticas->heuristica_media += vizinho->heuristica;
        if(is_objetivo(atual->estado))
        {
            estatisticas->comprimento = comprimentoSolucao(atual);
            return ENCONTRADA_SOLUCAO;
        }
        int rec_limit = procura_recursiva(vizinho, f_limit, estatisticas);

#ifdef _debug
printf("[%d %d] ", atual->g + atual->heuristica, rec_limit);
#endif

        if(rec_limit == ENCONTRADA_SOLUCAO)
            return ENCONTRADA_SOLUCAO;
            
        if(proximo_limite > rec_limit)
            proximo_limite = rec_limit;
    }

#ifdef _debug
printf("\n");
#endif
    
    return proximo_limite;
}

ESTATISTICAS* busca_IDA(ESTADO estado_inicial)
{
    ESTATISTICAS* estatisticas = inicializaEstatisticas(estado_inicial);

    NO* raiz = novoNo(NULL, estado_inicial, NENHUM, 0);
    int f_limit = estatisticas->heuristica_inicial = raiz->heuristica;

    while(f_limit < INFINITO)
    {

#ifdef _debug
printf("f_limit %d      expandidos %d visitados %d\n", f_limit, estatisticas->nodos_expandidos,estatisticas->nodos_visitados);
estatisticas->nodos_visitados = 0;
#endif
        
        visitados = std::unordered_set<ESTADO, EstadoHash, EstadoEqual>();

        // estatisticas->heuristica_media = 0;
        f_limit = procura_recursiva(raiz, f_limit, estatisticas);
        if(f_limit == ENCONTRADA_SOLUCAO)
        {
            finalizaEstatisticas(estatisticas);
            return estatisticas;
        }
    }
    finalizaEstatisticas(estatisticas);
    estatisticas->comprimento = -1;
    estatisticas->nodos_expandidos = -1;
    return estatisticas;
}