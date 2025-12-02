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

int verificaReflexiva(int ***matriz, int *n);
int verificaSimetrica(int ***matriz, int *n);
int verificaTransitiva(int ***matriz, int *n);
void checkFechoReflexivo(int ***matriz, int *n, char *nomeSaida);
void checkFechoSimetrico(int ***matriz, int *n, char *nomeSaida);
void checkFechoTransitivo(int ***matriz, int *n, char *nomeSaida);

int verificaReflexiva(int ***matriz, int *n)
{
    for (int i = 1; i < *n; i++)
    {
        if ((*matriz)[i][i] != 1)
        {
            printf("\nReflexiva:Nao");
            return 0;
        }
    }

    printf("\nReflexiva:Sim");
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
                printf("\nSimetrica:Nao");
                return 0;
            }
        }
    }
    printf("\nSimetrica:Sim");
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
                        printf("\nTransitiva:Nao");
                        return 0;
                    }
                }
            }
        }
    }
    printf("\nTransitiva:Sim");
    return 1;
}

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

    int **matriz;
    int n = 1;

    lerArquivo(StrEntrada, &matriz, &n);
    verificaSimetrica(&matriz, &n);
    verificaReflexiva(&matriz, &n);
    verificaTransitiva(&matriz, &n);

    exit(0);
}
void checkFechoReflexivo(int ***matriz, int *n, char *nomeSaida){
    int encontrado = 0;//contador para verificar se ja e reflexiva
    int **matrizAux; //matriz auxiliar para o fecho reflexivo
    *matrizAux = calloc((*n) + 1, sizeof(int *));
            for (int i = 1; i <= *n; i++)
                (*matriz)[i] = calloc((*n) + 1, sizeof(int));

    for (int i = 0; i < *n; i++)
    {
        if ((*matriz)[i][i] != 1)
        {
            (matrizAux)[i][i] = 1;
            encontrado++;
        }
        else if ((*matriz)[i][i] == 1)
        {
            (matrizAux)[i][i] = 0;
       }
   }
    if(encontrado == 0)
        {
            printf("A matriz ja ereflexiva, portanto nao ha fecho reflexivo a ser aplicado\n");
            return;
        }
    for (int i = 1; i <= *n; i++)
            {
                for (int j = 1; j <= *n; j++)
                    printf("%d ", (matrizAux)[i][j]);
                printf("\n");
            }
            return;

}