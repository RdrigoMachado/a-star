#include "utils.h"



COORDENADA encontraZero(ESTADO estado){
    COORDENADA coordenada;
    coordenada.x = -1; coordenada.y = -1;
    for(int x = 0; x < 3; x++)
        for(int y = 0; y < 3; y++)
            if(estado.posicao[x][y] == 0){
                coordenada.x = x;
                coordenada.y = y;
                return coordenada;
            }
    return coordenada;
}

ESTADO* geraNovoEstado8(ESTADO estado, acoes acao){
    COORDENADA coordenada = encontraZero(estado);
    ESTADO* novo_estado = (ESTADO*) malloc(sizeof(ESTADO));
    *novo_estado = estado;

    switch(acao){
        case BAIXO:
            if(coordenada.x == 2)
                return NULL;
            novo_estado->posicao[coordenada.x][coordenada.y] = estado.posicao[coordenada.x + 1][coordenada.y];
            novo_estado->posicao[coordenada.x + 1][coordenada.y] = 0;    
            return novo_estado;

        case DIREITA:
            if(coordenada.y == 2)
                return NULL;
            novo_estado->posicao[coordenada.x][coordenada.y] = estado.posicao[coordenada.x][coordenada.y + 1];
            novo_estado->posicao[coordenada.x][coordenada.y + 1] = 0;    
            return novo_estado;
            
        case ESQUERDA:
            if(coordenada.y == 0)
                return NULL;
            novo_estado->posicao[coordenada.x][coordenada.y] = estado.posicao[coordenada.x][coordenada.y - 1];
            novo_estado->posicao[coordenada.x][coordenada.y - 1] = 0;    
            return novo_estado;
            
        case CIMA:
            if(coordenada.x == 0)
                return NULL;
            novo_estado->posicao[coordenada.x][coordenada.y] = estado.posicao[coordenada.x - 1][coordenada.y];
            novo_estado->posicao[coordenada.x - 1][coordenada.y] = 0;    
            return novo_estado;
        default:
            return NULL;
    }
}


NO* expandeNo(NO* anterior, acoes acao){
    ESTADO *novo_estado = geraNovoEstado8(anterior->estado, acao);
    if(novo_estado == NULL)
        return NULL;

    NO* novo_no = novoNo(anterior, *novo_estado, acao, anterior->g + 1);
    return novo_no;
}

int comprimentoSolucao(NO* final){
    if(final == NULL){
        return 0;
    }
    NO* no = final;
    int comprimento = 0;
    while(no->anterior != NULL){
        comprimento++;
        no = no->anterior;
    }
    return comprimento;
}

bool pularExpansao(char a, char b){
    if(a == 'c' && b == 'b')
        return true;
    if(a == 'b' && b == 'c')
        return true; 
    if(a == 'd' && b == 'e')
        return true;
    if(a == 'e' && b == 'd')
        return true;

    return false;
}


void imprimirEstados(int qtdEstados, ESTADO* estados){
    for(int i = 0; i < qtdEstados; i++){
        ESTADO estado_atual = estados[i];
        for (int x =0 ; x < 3; x++){
            for (int y =0 ; y < 3; y++)
                printf("%d ", estado_atual.posicao[x][y]);
            printf("\n");
        }
            
        printf("\n");
    }
}
