/*
 * INSTITUTO FEDERAL DE MINAS GERAIS - CAMPUS FORMIGA
 * Bacharelado em Ciência da Computação
 * Disciplina: Matemática Discreta
 * Professor: Diego Mello da Silva
 *
 * Trabalho Prático: Verificação de Propriedades e Cálculo de Fechos
 *
 * Integrantes do Grupo:
 * 1. Kaua Teixeira Nascimento - Matrícula: 0117182
 * 2. Gabriel Mendonça de Oliveira - Matrícula: 0117251
 * 3. Felipe de Castro Leal Ribeiro - Matrícula: 0117037
 * 4. Sofia Maria Jesus Leal - Matrícula: 0120376
 *
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int **adj;
int n;

/* Protótipos das Funções (assinaturas) */
void lerArquivo(char *nomeArquivo){
    FILE *f = fopen(nomeArquivo, "r");
    if(f == NULL){
        printf("Erro ao abrir o arquivo!\n");
        exit(1);
    }

    char buffer[100]; // Buffer para ler a linha inteira
    char comando;     // Para ler 'n', 'r' ou 'f'
    int u, v;         // Para ler os vértices (origem -> destino)

    while(fgets(buffer, 100, f) != NULL) {
        // Lê o primeiro caractere da linha para saber o tipo
        sscanf(buffer, "%c", &comando);

        if (comando == 'n') {
            // Lê o tamanho do grafo (N)
            sscanf(buffer, "%*c %d", &n);

            // --- APLICAÇÃO DO CONCEITO BINÁRIO (PARTE 1: ZEROS) ---
            // Alocamos (n+1) linhas. Usamos calloc para garantir que tudo seja 0.
            adj = (int**) calloc(n + 1, sizeof(int*));
            
            for(int i = 1; i <= n; i++) {
                // Para cada linha, alocamos (n+1) colunas, todas inicializadas com 0.
                adj[i] = (int*) calloc(n + 1, sizeof(int));
            }
            // Agora temos uma matriz NxN cheia de zeros (falsos).

        } else if (comando == 'r') {
            // Lê a relação "u -> v"
            sscanf(buffer, "%*c %d %d", &u, &v);

            // --- APLICAÇÃO DO CONCEITO BINÁRIO (PARTE 2: UMS) ---
            // Se existe a relação no arquivo, marcamos como 1 (verdadeiro)
            if(u <= n && v <= n) {
                adj[u][v] = 1; 
            }
            
        } else if (comando == 'f') {
            // Fim do arquivo
            break;
        }
    }
    fclose(f);
}
int verificaReflexiva();
int verificaSimetrica();
int verificaTransitiva();
void calculaFechoReflexivo(char *nomeSaida);
void calculaFechoSimetrico(char *nomeSaida);
void calculaFechoTransitivo(char *nomeSaida);
void liberaMemoria(){
    if (adj != NULL){
        int i;
        for (i=0; i<n; i++){
            free(adj[1]);
        }
        free(adj);
        adj = NULL;
    }
}

int main(int argc, char **argv){
    char* StrEntrada;
    char* StrSaida;
    /* Testa se a quantidade de parâmetros informada esta correta */
    if(argc != 3){
        printf("\nErro de Sintaxe\n");
        printf("Usar: ./check-closure.bin <entrada> <saida>\n\n");
        exit(1);
    }
    /* Obtem os parametros informados */
    StrEntrada = argv[1];
    StrSaida = argv[2];
    /* Restante do código */

    lerArquivo(StrEntrada);
    /*....*/
    /* Encerra a aplicacao */
    exit(0);
}
