#include "idastar.h"

std::vector<NO*> geraVizinhosIDA(NO* estado_atual)
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

        vizinhos.push_back(novo);
    }
    return vizinhos;
}

int procura_recursiva(NO* atual, int f_limit, ESTATISTICAS* estatisticas){
    int f = atual->g + atual->heuristica;
    int proximo_limite = INFINITO;

    if(f > f_limit)
        return f;

    if(is_objetivo(atual->estado))
    {
        estatisticas->comprimento = comprimentoSolucao(atual);
        return ENCONTRADA_SOLUCAO;
    }

    std::vector<NO*> vizinhos = geraVizinhosIDA(atual);

    for (auto& vizinho : vizinhos) 
    {
        estatisticas->nodos_expandidos++;
        estatisticas->heuristica_media += vizinho->heuristica;
        int rec_limit = procura_recursiva(vizinho, f_limit, estatisticas);
        if(rec_limit == ENCONTRADA_SOLUCAO)
            return ENCONTRADA_SOLUCAO;
            
        if(proximo_limite > rec_limit)
            proximo_limite = rec_limit;
    }
    
    return proximo_limite;
}

ESTATISTICAS* busca_IDA(ESTADO estado_inicial)
{
    ESTATISTICAS* estatisticas = inicializaEstatisticas(estado_inicial);

    NO* raiz = novoNo(NULL, estado_inicial, NENHUM, 0);
    int f_limit = estatisticas->heuristica_inicial = raiz->heuristica;

    while(f_limit < INFINITO)
    {
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