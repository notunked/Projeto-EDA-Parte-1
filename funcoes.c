/**
 * @file funcoes.c
 * @brief Implementação de funções auxiliares para manipulação de antenas e locais nefastos. 
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "funcoes.h"

/** 
 * @brief Carrega antenas a partir de um ficheiro e armazena na lista ligada.
 * 
 * @param lista Apontador para a lista de antenas.
 * @param linhas Apontador para armazenar o número de linhas. 
 * @param colunas Apontador para armazenar o número de colunas. 
 * @param nomeFicheiro Nome do ficheiro de entrada. 
 */

Antena *carregarAntenas(Antena *lista, int *linhas, int *colunas, const char *nomeFicheiro) {
    
    FILE *ficheiro = fopen(nomeFicheiro, "r");
    
    if (!ficheiro) {
        printf("Erro ao abrir o ficheiro %s\n", nomeFicheiro);
        return NULL;
    }

    char linha[100]; // Armazenar temporariamente cada linha lida com máx de 100 characteres
    *linhas = 0; // contador

    while (fgets(linha, sizeof(linha), ficheiro)) { // ler uma linha do ficheiro
        
        int tamanho = 0;
        
        while (linha[tamanho] != '\n' && linha[tamanho] != '\0') {
            
            tamanho++;

        }

        if (*linhas == 0) {

            *colunas = tamanho; // Definir o número de colunas baseado na primeira linha            
        
        } else if (*colunas != tamanho) {
            printf("Erro: Linhas de tamanhos diferentes encontradas.\n");
            fclose(ficheiro);
            
            // Limpar memória
            while (lista) {
                Antena *temp = lista;
                lista = lista -> proximo;
                free(temp);
            }

            return NULL;

        }

        linha[tamanho] = '\0';
        *colunas = tamanho;
        (*linhas)++;

        // Adicionar uma antena nova à lista
        for (int j = 0; j < *colunas; j++) {

            if (linha[j] != '.' && linha[j] != '\0') { // Considerar apenas antenas válidas
                Antena *nova = (Antena *) malloc(sizeof(Antena));
                if (!nova) {
                    printf("Erro ao alocar memória para nova antena.\n");
                    return NULL;
                }

                nova -> frequencia = linha[j];
                nova -> x = *linhas - 1;
                nova -> y = j;
                nova -> proximo = lista;
                lista = nova;

            }

        }

    }   

    if (!lista) {
        printf("Lista de antenas vazia.\n");
        return NULL;
    }

    fclose(ficheiro);
    return lista;

}

/** 
 * @brief Remove uma antena da lista ligada com base na sua posição. 
 * 
 * Percorre a lista até encontrar a antena com as coordenadas especificadas. 
 * Se encontrada, remove-a e ajusta os apontadores da lista ligada. 
 * Se não encontrada, a lista permanece inalterada. 
 * 
 * @param lista Apontador para a lista de antenas.
 * @param x Posição X da antena a ser removida. 
 * @param y Posição Y da antena a ser removida. 
 * @param linhas Número de linhas do mapa. 
 * @param colunas Número de colunas do mapa. 
 * @param nomeFicheiro Nome do ficheiro de antenas.
 */

 Antena *removerAntena(Antena *lista, int x, int y, char *nomeFicheiro, int linhas, int colunas) {
    Antena *atual = lista;
    Antena *anterior = NULL;

    while (atual) {
        if (atual-> x == x && atual -> y == y ) { // Se encontrou a antena na posicao desejada

            if (anterior) {

                anterior -> proximo = atual -> proximo; // Ajusta o apontador do elemento anterior

            } else {

                lista = atual -> proximo; // Remover primeiro elemento

            }

            free(atual);
            printf("Antena removida em (%d, %d)\n",x ,y);

            // Atualizar o ficheiro após remoção
            atualizarFicheiro(lista, nomeFicheiro, linhas, colunas);
            
            return lista;

        }

        anterior = atual;
        atual = atual -> proximo;

    }

    atualizarFicheiro(lista,nomeFicheiro, linhas, colunas);
    return lista;

}

/** 
 * @brief Imprime todas as antenas da lista ligada. 
 * @param lista Apontador para a lista de antenas.
 */

void imprimirAntenas(Antena *lista) {

    if (!lista) {
        printf("Nenhuma antena registrada.\n");
        return;
    }

    while (lista) {
        printf("Antena %c em (%d, %d)\n", lista -> frequencia, lista -> x, lista -> y);
        lista = lista -> proximo;
    }
}

/** 
 * @brief Limpa a memória ocupada pela lista ligada de antenas. 
 * @param lista Apontador para a lista de antenas.
 */

void limparLista(Antena *lista) {
    Antena *aux;
    while (lista) {
        aux = lista;
        lista = lista -> proximo;
        free (aux);
    }
}

/** 
 * @brief Carrega a matriz de um ficheiro para a estrutura Matriz.
 * 
 * Lê um ficheiro linha por linha e armazena os dados na matriz de caracteres. 
 * O número de colunas é calculado com base na primeira linha lida (removendo o '\n'). 
 * 
 * @param matriz Apontador para a estrutura Matriz.
 * @param nomeFicheiro Nome do ficheiro a ser lido. 
 */

void carregarMatriz(Matriz *matriz, const char *nomeFicheiro) {

    FILE *ficheiro = fopen(nomeFicheiro, "r");

    if (!ficheiro) {
        printf("Erro ao abrir o ficheiro!\n");
        return;
    }

    matriz -> linhas = 0; // contador de linhas
    char linha[MAX_COLUNAS];

    while(fgets(linha, sizeof(linha), ficheiro)) {
        linha[strcspn(linha, "\n")] = '\0';
        strcpy(matriz->matrizchar[matriz->linhas],linha);
        matriz -> linhas++;
    }

    if (matriz->linhas == 0) {
        printf("Erro: Ficheiro vazio ou formato inválido.\n");
        fclose(ficheiro);
        return;
    }

    matriz ->colunas = strcspn(matriz -> matrizchar[0], "\n");

    fclose(ficheiro);
}

/** 
 * @brief Adiciona uma posição nefasta à lista ligada.
 * @param lista Apontador para a lista de posições nefastas.
 * @param x Coordenada X da posição nefasta. 
 * @param y Coordenada Y da posição nefasta. 
 */

PosicaoNefasta *adicionarPosicao(PosicaoNefasta *lista, int x, int y) {

    PosicaoNefasta *nova = (PosicaoNefasta *)malloc(sizeof(PosicaoNefasta));

    if (!nova) {

        printf("Erro ao alocar memoria\n");
        return lista;

    }

    nova -> x = x;
    nova -> y = y;
    nova -> proximo = lista;
    return nova;

}

/** 
 * @brief Detecta e armazena locais nefastos próximos às antenas. 
 * 
 * A função percorre a lista de antenas e adiciona à lista de posições nefastas
 * as quatro coordenadas adjacentes (cima, baixo, esquerda, direita).
 * Evita posições duplicadas verificando antes de inserir.
 * 
 * @param lista Apontador para a lista de antenas.
 */

PosicaoNefasta *detectarLocaisNefastos(Antena *lista) {

    PosicaoNefasta *nefastos = NULL;
    int mapa_nefastos[MAX_LINHAS][MAX_COLUNAS] = {0}; // Inicializa tudo com 0 (falso)

    int direcoes[4][2] = {{-1,0},{1,0},{0,-1},{0,1}}; // cima, baixo, esquerda, direita (coordenado)

    while (lista) {
        
        for (int i = 0; i < 4; i++) {

            int nx = lista -> x + direcoes[i][0];
            int ny = lista -> y + direcoes[i][1];
            
            // Verifica se a posição já foi adicionada e se está dentro dos limites
            if(nx>=0 && ny>=0 && nx<MAX_LINHAS && ny<MAX_COLUNAS && !mapa_nefastos[nx][ny]) {
                nefastos = adicionarPosicao(nefastos, nx, ny);
                mapa_nefastos[nx][ny] = 1; // Marca como já adicionado
            }

        }

        lista = lista -> proximo;

    }

    return nefastos;

}

/** 
 * @brief Imprime os locais nefastos na tela. 
 * @param lista Apontador para a lista de locais nefastos.
 */
void imprimirPosicoesNefastas(PosicaoNefasta *lista) {

    printf("\nLocais com efeito nefasto:\n");
    printf("===========\n");
    printf("| X  | Y  |\n");
    printf("===========\n");

    while (lista) {

    printf("| %2d | %2d |\n", lista->x, lista->y);
    lista = lista->proximo;

    }

    printf("===========\n");

}

/** 
 * @brief Verifica se uma posição nefasta existe na lista. 
 * 
 * @param lista Apontador para a lista de posições nefastas.
 * @param x Coordenada X da posição a ser verificada. 
 * @param y Coordenada Y da posição a ser verificada. 
 */

 int existePosicao(PosicaoNefasta *lista, int x, int y) {
    while (lista) {
        if (lista->x == x && lista->y == y) return 1;
        lista = lista->proximo;
    }
    return 0;
}

/** 
 * @brief Limpa a memória ocupada pela lista de posições nefastas.
 * @param lista Apontador para a lista de posições nefastas.
 */

void limparListaNefasta(PosicaoNefasta *lista) {

    PosicaoNefasta *aux;

    while (lista) {

        aux = lista;
        lista = lista -> proximo;
        free(aux);

    }
}

/**
 * @brief Atualiza o ficheiro de antenas após modificações na lista ligada.abort
 * 
 * Esta função recria o ficheiro de antenas com os dados atualizados, assim removendo ou adicionando antenas conforme necessário. 
 * Primeiro, inicializa uma matriz preenchida com '.', depois preenche com as antenas restantes e grava no ficheiro. 
 * 
 * @param lista Apontador para a lista ligada de antenas. 
 * @param nomeFicheiro Nome do ficheiro onde os dados serão armazenados. 
 * @param linhas Número de linhas do mapa. 
 * @param colunas Número de colunas do mapa. 
 */
void atualizarFicheiro(Antena*lista, const char *nomeFicheiro, int linhas, int colunas) {

    FILE *ficheiro =fopen(nomeFicheiro, "w");

    if (!ficheiro) {
        printf("Erro ao abrir o ficheiro para escrita: %s\n", nomeFicheiro);
        return;
    }

    // Criar uma matriz preenchida com '.'
    char matriz[linhas][colunas];
    for (int i=0; i<linhas; i++) {
        for (int j = 0; j < colunas; j++) {
            matriz [i][j] = '.';
        }
    }

    // Preencher matriz com as antenas restantes
    while (lista) {

        matriz[lista->x][lista->y] = lista->frequencia;
        lista = lista -> proximo;

    }

    // Escrever a matriz no ficheiro
    for (int i = 0; i < linhas; i++) {
        fprintf(ficheiro, "%.*s\n", colunas, matriz[i]); //Escreve a linha inteira de uma vez
    }

    fclose(ficheiro);

}
