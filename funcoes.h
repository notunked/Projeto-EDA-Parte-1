/**
 * @file funcoes.h 
 * @brief Declarações de funções auxiliares para a manipulação de antenas e locais nefastos. 
 * 
 * Este ficheiro contém as definições das funções responsáveis por: 
 * - Carregar antenas e a matriz do mapa a partir de ficheiros. 
 * - Gerenciar a lista ligada de antenas, incluindo inserção e remoção. 
 * - Identificar e armazenar locais considerados nefastos com base na posição das antenas. 
 * - Limpar a memória alocada dinamicamente para as listas.
 */

#ifndef FUNCOES_H
#define FUNCOES_H

#include "antenas.h"

#define MAX_LINHAS 100
#define MAX_COLUNAS 100

/** 
 * @struct PosicaoNefasta
 * @brief Estrutura para armazenar posições nefastas.
 * 
 * Contém as coordenadas (x,y) da posição e um apontador para a
 * próxima posição na lista ligada. 
 */

typedef struct PosicaoNefasta {
    int x,y; /**< Coordenadas (x,y) da posição nefasta. */
    struct PosicaoNefasta *proximo; /**< Apontador para a próxima posição na lista. */
} PosicaoNefasta;

// Declaração das funções auxiliares

Antena *carregarAntenas(Antena *lista, int *linhas, int *colunas, const char *nomeFicheiro);
void limparLista(Antena *lista);
void imprimirAntenas(Antena *lista);
Antena *removerAntena(Antena *lista, int x, int y, char *nomeFicheiro, int linhas, int colunas);
void carregarMatriz(Matriz *matriz, const char *nomeFicheiro);
int existePosicao(PosicaoNefasta *lista, int x, int y);
PosicaoNefasta *detectarLocaisNefastos(Antena *lista);
void imprimirPosicoesNefastas(PosicaoNefasta *lista);
void limparListaNefasta(PosicaoNefasta *lista);
void atualizarFicheiro(Antena*lista, const char *nomeFicheiro, int linhas, int colunas);

#endif