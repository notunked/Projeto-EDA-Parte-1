/**
 * @file antenas.h 
 * @brief Definições de estruturas e constantes para manipulação de antenas. 
 * 
 * Este ficheiro contém a definição das estruturas utilizadas para
 * representar antenas e a matriz do mapa, além de constantes de
 * tamanho máximo. 
 */

#ifndef ANTENAS_H
#define ANTENAS_H

#define MAX_LINHAS 100
#define MAX_COLUNAS 100

/** 
 * @struct Antena
 * @brief Estrutura que representa uma antena.
 * 
 * Contém a frequência da antena, a sua posição (x,y) no mapa e 
 * um apontador para a próxima antena na lista ligada. 
 */

typedef struct Antena {
    char frequencia; /**< Frequência da antena */
    int x, y;        /**< Coordenadas (x,y) da antena no mapa. */
    struct Antena *proximo; /**< Apontador para a próxima antena na lista */
} Antena;

/** 
 * @struct Matriz
 * @brief Estrutura que representa a matriz do mapa.
 * 
 * Contém uma matriz de caracteres que representa o mapa e
 * as dimensões (linhas e colunas)
 */

typedef struct {
    char matrizchar[MAX_LINHAS][MAX_COLUNAS]; /**< Matriz de caracteres */
    int linhas, colunas; /**< Dimensões da matriz (x,y) */
} Matriz;

/**
 * @brief Insere uma nova antena na lista ligada. 
 * @param lista Apontador para a lista de antenas.
 * @param frequencia Característica da antena. 
 * @param x Posição X da antena. 
 * @param y Posição Y da antena. 
 */
Antena *inserirAntena(Antena *lista, char frequencia, int x, int y);

#endif
