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
 * 4. Sofia Maria Jesus eeLeal - Matrícula: 0120376
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

void lerArquivo(char *nomeArquivo, int **matriz, int n)
{
    FILE *f = fopen(nomeArquivo, "r");
    if (f == NULL)
    {
        printf("Erro ao abrir o arquivo!\n");
        exit(1);
    }

    char linha[100]; // linha inteira
    char comando;    // Para ler 'n', 'r' ou 'f'
    int u, v;        // Para ler os vértices (origem -> destino)

    while (fgets(linha, 100, f) != NULL)
    {
        // Lê o primeiro caractere da linha para saber o tipo
        sscanf(linha, "%c", &comando);

        if (comando == 'n')
        {
            // Lê o tamanho da matriz (N)
            sscanf(linha, "%*c %d", &n);

            // inicializa as 'n' linhas da matriz com 0
            matriz = (int **)calloc(n + 1, sizeof(int *));

            // inicializa as 'n' colunas da matriz com 0
            for (int i = 1; i <= n; i++)
            {
                matriz[i] = (int *)calloc(n + 1, sizeof(int));
            }

            if (comando == 'r')
            {
                // Lê o tamanho da matriz (N)
                sscanf(linha, "%*c %d", &n);
            }
        }
        else if (comando == 'r')
        {
            sscanf(linha, "%*c %d %d", &u, &v);

            if(u <= n && v <= n) {
                matriz[u][v] = 1; 
            }
        }
        else if (comando == 'f')
        {
            break;
        }
        else
        {
            break;
        }
    }
    fclose(f);
}
void escreverArquivo();
int verificaReflexiva();
int verificaSimetrica();
int verificaTransitiva();
void calculaFechoReflexivo(char *nomeSaida);
void calculaFechoSimetrico(char *nomeSaida);
void calculaFechoTransitivo(char *nomeSaida);
/*void liberaMemoria()
{
    if (adj != NULL)
    {
        int i;
        for (i = 0; i < n; i++)
        {
            free(adj[1]);
        }
        free(adj);
        adj = NULL;
    }
}*/

int main(int argc, char **argv)
{
    char *StrEntrada;
    char *StrSaida;
    /* Testa se a quantidade de parâmetros informada esta correta */
    if (argc != 3)
    {
        printf("\nErro de Sintaxe\n");
        printf("Usar: ./check-closure.bin <entrada> <saida>\n\n");
        exit(1);
    }
    /* Obtem os parametros informados */
    StrEntrada = argv[1];
    StrSaida = argv[2];
    /* Restante do código */

    int **matriz;
    int n = 1;
    lerArquivo(StrEntrada, matriz, &n);
    /*....*/
    /* Encerra a aplicacao */
    exit(0);
}
