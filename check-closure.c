/*
 INSTITUTO FEDERAL DE MINAS GERAIS - CAMPUS FORMIGA
 Bacharelado em Ciência da Computação
 Disciplina: Matemática Discreta
 Professor: Diego Mello da Silva

 Trabalho Prático: Verificação de Propriedades e Cálculo de Fechos

 Integrantes do Grupo:
 1. Kaua Teixeira Nascimento - Matrícula: 0117182
 2. Gabriel Mendonça de Oliveira - Matrícula: 0117251
 3. Felipe de Castro Leal Ribeiro - Matrícula: 0117037
 4. Sofia Maria Jesus eeLeal - Matrícula: 0120376
*/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

void lerArquivo(char *nomeArquivo, int ***matriz, int *n)
{
    FILE *f = fopen(nomeArquivo, "r");
    if (!f)
    {
        printf("Erro ao abrir o arquivo!\n");
        exit(1);
    }

    char linha[100];
    char comando;
    int u, v;

    while (fgets(linha, 100, f) != NULL)
    {
        sscanf(linha, "%c", &comando);

        if (comando == 'n')
        {
            // lê N
            sscanf(linha, "%*c %d", n);

            // aloca a matriz
            *matriz = calloc((*n) + 1, sizeof(int *));
            for (int i = 1; i <= *n; i++)
                (*matriz)[i] = calloc((*n) + 1, sizeof(int));
        }
        else if (comando == 'r')
        {
            sscanf(linha, "%*c %d %d", &u, &v);
            if (u <= *n && v <= *n)
                (*matriz)[u][v] = 1;
        }
        else if (comando == 'f')
        {
            // imprime
            for (int i = 1; i <= *n; i++)
            {
                for (int j = 1; j <= *n; j++)
                    printf("%d ", (*matriz)[i][j]);
                printf("\n");
            }
            break;
        }
    }

    fclose(f);
}

void gerarArquivo(char *nomeArquivo, int ***matrizOriginal, int ***matrizFechos, int *n, int tipo)
{
    char aux[200];
    if (tipo == 1) // Se os fechos forem de uma matriz não reflexiva
    {
        sprintf(aux, "%s-ref.dot", nomeArquivo);
    }
    else if (tipo == 2) // Se os fechos forem de uma matriz não simétrica
    {
        sprintf(aux, "%s-sim.dot", nomeArquivo);
    }
    else if (tipo == 3) // Se os fechos forem de uma matriz não transitiva
    {
        sprintf(aux, "%s-tra.dot", nomeArquivo);
    }

    FILE *temp = fopen(aux, "w");
    if (!temp)
    {
        return;
    }

    fprintf(temp, "digraph {\n");

    // imprime o conjunto primeiro
    for (int i = 1; i <= *n; i++)
    {
        fprintf(temp, "%d;\n", i);
    }

    for (int i = 1; i <= *n; i++)
    {
        for (int j = 1; j <= *n; j++)
        {
            if ((*matrizOriginal)[i][j] == 1)
            {
                fprintf(temp, "%d -> %d;\n", i, j);
            }
        }
    }

    for (int i = 1; i <= *n; i++)
    {
        for (int j = 1; j <= *n; j++)
        {
            if ((*matrizFechos)[i][j] == 1)
            {
                fprintf(temp, "%d -> %d [color=red];\n", i, j);
            }
        }
    }

    fprintf(temp, "}");
    fclose(temp);
}

int verificaReflexiva(int ***matriz, int *n);
int verificaSimetrica(int ***matriz, int *n);
int verificaTransitiva(int ***matriz, int *n);
void checkFechoReflexivo(int ***matriz, int *n, char *nomeSaida);
void checkFechoSimetrico(int ***matriz, int *n, char *nomeSaida);
void checkFechoTransitivo(int ***matriz, int *n, char *nomeSaida);
void checkFechoSimetrico(int ***matriz, int *n, char *nomeSaida);
void checkFechoTransitivo(int ***matriz, int *n, char *nomeSaida);

int main(int argc, char **argv)
{
    char *StrEntrada;
    char *StrSaida;

    // Testa se a quantidade de parâmetros informada esta correta */
    if (argc != 3)
    {
        printf("\nErro de Sintaxe\n");
        printf("Usar: ./check-closure.bin <entrada> <saida>\n\n");
        exit(1);
    }

    // Obtem os parametros argv para receber o nome dos arquivos
    StrEntrada = argv[1];
    StrSaida = argv[2];

    char nomeSaida[200];
    strcpy(nomeSaida, argv[2]);

    // Remove ".txt" se existir no final
    char *p = strstr(nomeSaida, ".txt");
    if (p && p == nomeSaida + strlen(nomeSaida) - 4)
    {
        *p = '\0'; // Corta a string
    }

    StrSaida = nomeSaida;

    int **matriz;
    int n = 1;

    lerArquivo(StrEntrada, &matriz, &n);
    verificaSimetrica(&matriz, &n);
    verificaReflexiva(&matriz, &n);
    verificaTransitiva(&matriz, &n);
    checkFechoReflexivo(&matriz, &n, StrSaida);
    checkFechoSimetrico(&matriz, &n, StrSaida);
    checkFechoTransitivo(&matriz, &n, StrSaida);

    exit(0);
}

int verificaReflexiva(int ***matriz, int *n)
{
    for (int i = 1; i < *n; i++)
    {
        if ((*matriz)[i][i] != 1)
        {
            printf("Reflexiva:Nao\n");
            return 0;
        }
    }

    printf("Reflexiva:Sim \n");
    return 1;
}

int verificaSimetrica(int ***matriz, int *n)
{
    for (int i = 1; i < *n; i++)
    {
        for (int j = 1; j <= *n; j++)
        {
            if ((*matriz)[i][j] != (*matriz)[j][i])
            {
                printf("Simetrica:Nao\n");
                return 0;
            }
        }
    }
    printf("Simetrica:Sim\n");
    return 1;
}

int verificaTransitiva(int ***matriz, int *n)
{
    for (int i = 1; i < *n; i++)
    {
        for (int j = 1; j <= *n; j++)
        {
            if ((*matriz)[i][j] == 1)
            {
                for (int k = 0; k <= *n; k++)
                {
                    if ((*matriz)[j][k] == 1 && (*matriz)[i][k] == 0)
                    {
                        printf("Transitiva:Nao\n");
                        return 0;
                    }
                }
            }
        }
    }
    printf("Transitiva:Sim\n");
    return 1;
}

void checkFechoReflexivo(int ***matriz, int *n, char *nomeSaida)
{
    int **matrizAux;
    int encontrou = 0;

    // aloca matriz auxiliar zerada
    matrizAux = calloc((*n) + 1, sizeof(int *));
    for (int i = 1; i <= *n; i++)
        matrizAux[i] = calloc((*n) + 1, sizeof(int));

    // acha os fechos necessários da matriz e insere na matrizAux
    for (int i = 1; i < *n; i++)
    {
        if ((*matriz)[i][i] != 1)
        {
            (matrizAux)[i][i] = 1;
            encontrou++;
        }
    }

    if (!encontrou)
    {
        printf("\nA matriz ja e reflexiva. Nenhum fecho reflexivo aplicado.\n");
        // libera matrizAux pois ela não será usada para gerar arquivo
        for (int i = 1; i <= *n; i++)
            free(matrizAux[i]);
        free(matrizAux);
        return;
    }

    // Gera o arquivo com os fechos reflexivos
    gerarArquivo(nomeSaida, matriz, &matrizAux, n, 1);

    // libera matrizAux após uso
    for (int i = 1; i <= *n; i++)
        free(matrizAux[i]);
    free(matrizAux);
}

void checkFechoSimetrico(int ***matriz, int *n, char *nomeSaida)
{
    int **matrizAux;
    int encontrou = 0;

    // aloca matriz auxiliar zerada
    matrizAux = calloc((*n) + 1, sizeof(int *));
    for (int i = 1; i <= *n; i++)
        matrizAux[i] = calloc((*n) + 1, sizeof(int));

    // acha os fechos necessários da matriz e insere na matrizAux
    for (int i = 1; i < *n; i++)
    {
        for (int j = 1; j <= *n; j++)
        {
            if ((*matriz)[i][j] != (*matriz)[j][i])
            {
                matrizAux[i][j] = 1;
                encontrou++;
            }
        }
    }

    if (!encontrou)
    {
        printf("\nA matriz ja e simetrica. Nenhum fecho simetrico aplicado.\n");
        // libera matrizAux pois ela não será usada para gerar arquivo
        for (int i = 1; i <= *n; i++)
            free(matrizAux[i]);
        free(matrizAux);
        return;
    }

    // Gera o arquivo com os fechos simétricos
    gerarArquivo(nomeSaida, matriz, &matrizAux, n, 2);

    // libera matrizAux após uso
    for (int i = 1; i <= *n; i++)
        free(matrizAux[i]);
    free(matrizAux);
}

void checkFechoTransitivo(int ***matriz, int *n, char *nomeSaida)
{
    int **matrizAux;
    int encontrou = 0;

    // aloca matriz auxiliar zerada
    matrizAux = calloc((*n) + 1, sizeof(int *));
    for (int i = 1; i <= *n; i++)
        matrizAux[i] = calloc((*n) + 1, sizeof(int));

    // acha os fechos necessários da matriz e insere na matrizAux
    for (int i = 1; i < *n; i++)
    {
        for (int j = 1; j <= *n; j++)
        {
            if ((*matriz)[i][j] == 1)
            {

                for (int k = 0; k <= *n; k++)
                {
                    if ((*matriz)[j][k] == 1 && (*matriz)[i][k] == 0)
                    {
                        matrizAux[i][k] = 1;
                        encontrou++;
                    }
                }
            }
        }
    }

    if (!encontrou)
    {
        printf("\nA matriz ja e transitiva. Nenhum fecho transitivo aplicado.\n");
        // libera matrizAux pois ela não será usada para gerar arquivo
        for (int i = 1; i <= *n; i++)
            free(matrizAux[i]);
        free(matrizAux);
        return;
    }

    // Gera o arquivo com os fechos transitivos
    gerarArquivo(nomeSaida, matriz, &matrizAux, n, 3);

    // libera matrizAux após uso
    for (int i = 1; i <= *n; i++)
        free(matrizAux[i]);
    free(matrizAux);
}