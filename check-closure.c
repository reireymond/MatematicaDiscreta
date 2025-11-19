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
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

/* Variáveis Globais para a Matriz e Tamanho */
int **adj;  // Matriz de adjacência alocada dinamicamente
int n;      // Número de nós (elementos do conjunto)

/* Protótipos das Funções (assinaturas) */
void lerArquivo(char *nomeArquivo){
    FILE *f = fopen(nomeArquivo, "r");
    if(f==NULL){
        printf("Erro ao abrir o arquivo!/n");
        exit(1);


        
    }
     
};
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
