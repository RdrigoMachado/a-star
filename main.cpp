#include <cstring>
#include "estruturas.h"
#include "utils.h"
#include "algoritmos/astar.h"
#include "algoritmos/idastar.h"
#include "algoritmos/bfs.h"

using namespace std;

enum PUZZLE { PUZZLE8, PUZZLE15 };

void imprimiResultados(ESTATISTICAS* estatisticas){
    if(estatisticas->heuristica_media == 0)
        printf("%d,%d,%d,%.9f,0,%d\n", 
            estatisticas->nodos_expandidos, 
            estatisticas->nodos_visitados, 
            estatisticas->comprimento,
            estatisticas->duracao_segundos,
            estatisticas->heuristica_inicial);
    else
        printf("%d,%d,%d,%.9f,%.5f,%d\n", 
            estatisticas->nodos_expandidos, 
            estatisticas->nodos_visitados, 
            estatisticas->comprimento,
            estatisticas->duracao_segundos, 
            estatisticas->heuristica_media,
            estatisticas->heuristica_inicial);
}



int main(int argc, char* argv[]){

    // ESTADO estado_inicial1 {
    //     .posicao={
    //                 {0, 6, 1},
    //                 {7, 4, 2},
    //                 {3, 8, 5}
    //             }
    // };
    //  ESTADO estado_inicial2 {
    //     .posicao={
    //                 {0, 6, 1},
    //                 {7, 4, 2},
    //                 {3, 8, 5}
    //             }
    // };
    //  ESTADO estado_inicial3 {
    //     .posicao={
    //                 {0, 6, 1},
    //                 {7, 4, 2},
    //                 {3, 8, 5}
    //             }
    // };
    // ESTADO estado_inicial1 {
    //     .posicao={
    //                 {5, 0, 2},
    //                 {6, 4, 8},
    //                 {1, 7, 3}
    //             }
    // };
    // ESTADO estado_inicial2 {
    //     .posicao={
    //                 {5, 0, 2},
    //                 {6, 4, 8},
    //                 {1, 7, 3}
    //             }
    // };
    // ESTADO estado_inicial3 {
    //     .posicao={
    //                 {5, 0, 2},
    //                 {6, 4, 8},
    //                 {1, 7, 3}
    //             }
    // };
    ESTADO estado_inicial1 {
        .posicao={
                    {2, 4, 7},
                    {0, 3, 6},
                    {8, 1, 5}
                }
    };
    ESTADO estado_inicial2 {
        .posicao={
                    {2, 4, 7},
                    {0, 3, 6},
                    {8, 1, 5}
                }
    };
    ESTADO estado_inicial3 {
        .posicao={
                    {2, 4, 7},
                    {0, 3, 6},
                    {8, 1, 5}
                }
    };



    //     std::priority_queue<NO*, std::vector<NO*>, PrioridadeCaminhoMaisHeuristica> open;
    // NO n1; NO n2; NO n3;
    // n1.g = 1;
    // n1.heuristica = 13;
    // n2.g = 2;
    // n2.heuristica = 12;
    // n3.g=2;
    // n3.heuristica = 1;
    
    // open.push(&n1);
    // open.push(&n2);
    // open.push(&n3);


    //     NO* atual;
        
    //     atual = open.top(); open.pop();
    //     printf("g = %d , h = %d, g+h = %d\n", atual->g, atual->heuristica, atual->g+atual->heuristica);
    //     atual = open.top(); open.pop();
    //     printf("g = %d , h = %d, g+h = %d\n", atual->g, atual->heuristica, atual->g+atual->heuristica);
    //     atual = open.top(); open.pop();
    //     printf("g = %d , h = %d, g+h = %d\n" ,atual->g, atual->heuristica, atual->g+atual->heuristica);
       
    printf("ASTAR\n");
    ESTATISTICAS* estatisticas = busca_ASTAR(estado_inicial1);                
    imprimiResultados(estatisticas);
    
    printf("BFS\n");
    ESTATISTICAS* estatisticas2 = busca_BFS(estado_inicial2);                
    imprimiResultados(estatisticas2);

    printf("IDA\n");
    ESTATISTICAS* estatisticas3 = busca_IDA(estado_inicial3);                
    imprimiResultados(estatisticas3);
    return 0;
}