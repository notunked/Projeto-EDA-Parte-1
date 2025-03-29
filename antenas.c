/**
 * @file antenas.c 
 * @brief Implementação das funções para manipulação da lista ligada de antenas. 
 */

#include <stdio.h>
#include <stdlib.h>
#include "antenas.h"

/** 
 * @brief Insere uma nova antena na lista ligada.
 * @param lista Apontador para a lista de antenas.
 * @param frequencia Característica da antena. 
 * @param x Posição X da antena. 
 * @param y Posição Y da antena. 
 */

Antena *inserirAntena(Antena *lista, char frequencia, int x, int y) {

    // Verifica se já existe uma antena na posição (x,y)
    Antena *atual = lista;
    while (atual) {

        if (atual -> x == x && atual->y == y) {
            printf("Erro: Ja existe uma antena na posicao (%d, %d)\n",x,y);
            return lista; // Mantém a lista sem alterações
        }

        atual = atual-> proximo;
    }

    // Aloca memória para a nova antena
    Antena *nova = (Antena *)malloc(sizeof(Antena));
    if (!nova) {
        printf("Erro ao alocar memória para nova antena.\n");
        return lista; // Retorna a lista sem modificações
    }

    // Inicializa os dados da antena
    nova -> frequencia = frequencia;
    nova -> x = x;
    nova -> y = y;
    nova -> proximo = lista; // Insere no início da lista

    return nova; // Retorna na nova lista com a antena inserida

}
