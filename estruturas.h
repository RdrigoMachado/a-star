// Estruturas tem a definicao das estruturas usadas pelos algoritmos
// Geral:       COORDENADA, ESTATISTICAS
// 8-puzzle:    NO8, ESTADO8 
// 15-puzzle:   NO15, ESTADO15
// Definicoes de hash e comparacao de estruturas e funcoes de trato de estatisticas


#ifndef estruturas_h
#define estruturas_h

#include <cstring>
#include <cstdio>
#include <functional>
#include <chrono>
#include <cmath>

enum acoes {CIMA, ESQUERDA, DIREITA, BAIXO, NENHUM};

struct COORDENADA{
    int x, y;
};

struct  ESTADO{
    int posicao[3][3];
};

struct NO{
    NO* anterior;
    ESTADO estado;
    char acao;
    int g;
    int heuristica;
};

struct EstadoHash {
    std::size_t operator()(const ESTADO& estado) const {
        std::size_t seed = 0;
        for (int i = 0; i < 3; ++i) {
            for (int j = 0; j < 3; ++j) {
                seed ^= std::hash<short>{}(estado.posicao[i][j]) + 0x9e3779b9 + (seed << 6) + (seed >> 2);
            }
        }
        return seed;
    }
};

struct EstadoEqual {
    bool operator()(const ESTADO& estado1, const ESTADO& estado2) const {
        return std::memcmp(&estado1, &estado2, sizeof(ESTADO)) == 0;
    }
};



struct ESTATISTICAS{
    int nodos_expandidos;
    int comprimento;
    double duracao_segundos;
    float heuristica_media;
    int heuristica_inicial;
    std::chrono::time_point<std::chrono::high_resolution_clock> inicio;
    std::chrono::time_point<std::chrono::high_resolution_clock> fim;
};
struct PrioridadeHeuristica {
    bool operator()(const NO* s1, const NO* s2) {
        return s1->heuristica > s2->heuristica;
    }
};



struct PrioridadeCaminhoMaisHeuristica {
    bool operator()(const NO* s1, const NO* s2) {
        if((s1->g + s1->heuristica) == (s2->g + s2->heuristica))
            return s1->heuristica > s2->heuristica;

        return ((s1->g + s1->heuristica) > (s2->g + s2->heuristica));
    }
};
bool is_objetivo(ESTADO estado);
NO* novoNo(NO *anterior, ESTADO estado_atual, acoes acao, int g);
ESTATISTICAS* inicializaEstatisticas(ESTADO estado_inicial);
void finalizaEstatisticas(ESTATISTICAS* estatisticas);

#endif