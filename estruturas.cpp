#include "estruturas.h"

bool is_objetivo(ESTADO estado){
    int estado_objetivo[3][3] = {
        {0, 1, 2},
        {3, 4, 5},
        {6, 7, 8}
    };
    for(int x = 0; x < 3; x++)
        for(int y = 0; y < 3; y++)
            if(estado.posicao[x][y] != estado_objetivo[x][y])
                return false;

    return true;
}

int pega_x_destino(int digito){
    return digito / 3;
}

int pega_y_destino(int digito){
    return digito % 3;
}

int manhattan(ESTADO estado){
    int h = 0;
    int distancia = 0, valor_posicao;
    int x, y, x_destino, y_destino;

    for (int x =0 ; x < 3; x++)
            for (int y =0 ; y < 3; y++)
            {
                if(estado.posicao[x][y] == 0)
                    continue;
                x_destino = pega_x_destino(estado.posicao[x][y]);
                y_destino = pega_y_destino(estado.posicao[x][y]);
                distancia = fabs(x - x_destino) + fabs(y - y_destino);
                h += distancia;
            }
    return h;
}

NO* novoNo(NO *anterior, ESTADO estado_atual, acoes acao, int g){
    NO* novo_no = (NO*) malloc(sizeof(NO));
    novo_no->anterior = anterior;
    novo_no->estado = estado_atual;
    novo_no->acao = acao;
    novo_no->g = g;
    novo_no->heuristica = manhattan(estado_atual);
    return novo_no;
}

void finalizaEstatisticas(ESTATISTICAS* estatisticas)
{
    estatisticas->fim = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> duracao = estatisticas->fim - estatisticas->inicio;
    estatisticas->duracao_segundos = duracao.count();

    if(estatisticas->nodos_expandidos != 0)
        estatisticas->heuristica_media = estatisticas->heuristica_media / estatisticas->nodos_expandidos;
    else
        estatisticas->heuristica_media = 0;

}

ESTATISTICAS* inicializaEstatisticas(ESTADO estado_inicial)
{
    ESTATISTICAS* estatisticas = (ESTATISTICAS*) malloc(sizeof(ESTATISTICAS));
    estatisticas->inicio = std::chrono::high_resolution_clock::now();
    estatisticas->nodos_expandidos = 0;
    estatisticas->comprimento = 0;
    estatisticas->heuristica_media = 0;
    estatisticas->duracao_segundos = 0;
    estatisticas->heuristica_inicial = manhattan(estado_inicial);
    return estatisticas;
}