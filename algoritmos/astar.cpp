#include "astar.h"

std::unordered_set<ESTADO, EstadoHash, EstadoEqual> closed;


std::vector<NO*> geraVizinhos(NO* estado_atual)
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

        if(closed.find(novo->estado) != closed.end())
            continue;

        closed.insert(novo->estado);
        vizinhos.push_back(novo);
    }
    return vizinhos;
}

ESTATISTICAS* loop(ESTADO estado_inicial, ESTATISTICAS* estatisticas){
    std::priority_queue<NO*, std::vector<NO*>, PrioridadeCaminhoMaisHeuristica> open;
    std::vector<NO*> structPointers;
    NO* no = novoNo(NULL, estado_inicial, NENHUM, 0);
    open.push(no);
    closed.insert(estado_inicial);
#ifdef _debug
structPointers.push_back(no);
imprimirEstados(1, &estado_inicial);
printf("g = %d , h = %d, g+h = %d\n", no->g, no->heuristica, no->g+no->heuristica);
#endif

    while(!open.empty())
    {
        NO* atual = open.top(); open.pop();
        estatisticas->nodos_visitados++;
        for (auto it = structPointers.begin(); it != structPointers.end(); ++it) {
            if (*it == atual) {
                structPointers.erase(it);
                break; // Exit the loop after erasing the element
            }
        }

        if(is_objetivo(atual->estado) == true)
        {
            estatisticas->comprimento = comprimentoSolucao(atual);
            return estatisticas;
        }
        std::vector<NO*> vizinhos = geraVizinhos(atual);

#ifdef _debug
printf("ATUAL:\n");
imprimirEstados(1, &atual->estado);
printf("g = %d , h = %d, g+h = %d\n", atual->g, atual->heuristica, atual->g+atual->heuristica);
printf("expandido - \n");
#endif    
    
        for (auto& vizinho : vizinhos) 
        {
            estatisticas->nodos_expandidos++;
            estatisticas->heuristica_media += atual->heuristica;
            open.push(vizinho);
#ifdef _debug
imprimirEstados(1, &vizinho->estado);
printf("g = %d , h = %d, g+h = %d\n\n", vizinho->g, vizinho->heuristica, vizinho->g+vizinho->heuristica);
structPointers.push_back(vizinho);
#endif
        }

#ifdef _debug
printf("=====\ntotal = %d\n", estatisticas->nodos_expandidos);
printf("OPEN======================\n");
for (auto it = structPointers.begin(); it != structPointers.end(); ++it) {
    imprimirEstados(1, &(*it)->estado);
    printf("g = %d , h = %d, g+h = %d\n", (*it)->g, (*it)->heuristica, (*it)->g+(*it)->heuristica);
    
}
printf("================= \n");
getchar();
#endif

    }
    return estatisticas;
}

ESTATISTICAS* busca_ASTAR(ESTADO estado_inicial)
{
    ESTATISTICAS* estatisticas = inicializaEstatisticas(estado_inicial);

    if(is_objetivo(estado_inicial) == true)
    {
        finalizaEstatisticas(estatisticas);
        return estatisticas;
    }
    
    loop(estado_inicial, estatisticas);
    finalizaEstatisticas(estatisticas);
    return estatisticas;
}
