#include "bfs.h"

ESTATISTICAS* busca_BFS(ESTADO estado_inicial)
{
    ESTATISTICAS* estatisticas = inicializaEstatisticas(estado_inicial);    
    
    if(is_objetivo(estado_inicial) == true)
    {
        finalizaEstatisticas(estatisticas);
        return estatisticas;
    }

    std::deque<NO*> open;
    std::unordered_set<ESTADO, EstadoHash, EstadoEqual> closed;
    
    open.push_back(novoNo(NULL, estado_inicial, NENHUM, 0));
    closed.insert(estado_inicial);

    while (!open.empty()){
        NO *atual = open.front(); open.pop_front();
        estatisticas->nodos_visitados++;
        for(int i = 0; i < 4; i++){
            //nao gerar estado-pai do estado atual 
            if(pularExpansao(atual->acao, (acoes)i))
                continue;
            
            NO* novo;
            if((novo = expandeNo(atual, (acoes)i)) != NULL){
                if(is_objetivo(novo->estado)){
                    estatisticas->comprimento = comprimentoSolucao(novo);
                    finalizaEstatisticas(estatisticas);
                    return estatisticas;
                }
                //tenta adicionar e verifica se estado esta em closed
                if(closed.insert(novo->estado).second == true){
                    open.push_back(novo);
                    estatisticas->nodos_expandidos++;
                }
            }
        }
    }
    finalizaEstatisticas(estatisticas);
    estatisticas->nodos_expandidos = -1;
    estatisticas->comprimento = -1;
    return estatisticas;
}