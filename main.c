/** 
 * @file main.c
 * @brief Programa para manipular antenas e identificar locais com efeito nefasto. 
 * 
 * Este programa carrega um mapa de antenas a partir de um ficheiro,
 * armazena as antenas numa lista ligada e determina as posições
 * com efeito nefasto ao redor de cada antena.
 * Ele também permite a remoção de antenas e listagem das informações no terminal. 
 */

#include <stdio.h>
#include "funcoes.h"

/**
 * @brief Função principal do programa. 
 * 
 * O programa lê um ficheiro de entrada que contêm um mapa de antenas,
 * carrega as antenas em lista ligada, remove uma antena de teste,
 * deduz locais nefastos e exibe os resultados na tela. 
 * 
 */

int main() {

    Antena *lista = NULL;
    Matriz mapa;

    carregarMatriz(&mapa,"uploadantenas.txt");

    lista = carregarAntenas(lista, &mapa.linhas, &mapa.colunas, "uploadantenas.txt");

    if(!lista) {
        printf("Nenhuma antena encontrada.\n");
    } else {
        printf("Antenas carregadas:\n");
        imprimirAntenas(lista);

        // Teste para remover uma antena na posicao (1,2)
        lista = removerAntena(lista, 1, 2, "uploadantenas.txt", mapa.linhas, mapa.colunas);
        printf("\nLista de antenas apos remocao:\n");
        imprimirAntenas(lista);

        // 3c - deduzir locais com efeito nefasto
        PosicaoNefasta *nefastos = detectarLocaisNefastos(lista);

        // 3d - Listar Locais Nefastos
        imprimirPosicoesNefastas(nefastos);

        // Limpar memoria das listas
        limparListaNefasta(nefastos);
        
    }
    
    limparLista(lista);
    return 0;

}