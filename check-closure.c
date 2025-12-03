/*
 INSTITUTO FEDERAL DE MINAS GERAIS - CAMPUS FORMIGA
 Bacharelado em Ciência da Computação
 Disciplina: Matemática Discreta
 Professor: Diego Mello da Silva

 Aplicativo: MatematicaDiscreta

 Integrantes do Grupo:
 1. Kaua Teixeira Nascimento - Matrícula: 0117182
 2. Gabriel Mendonça de Oliveira - Matrícula: 0117251
 3. Felipe de Castro Leal Ribeiro - Matrícula: 0117037
 4. Sofia Maria Jesus Leal - Matrícula: 0120376

 Instruções de compilação:
  ->Linux:
    -gcc -lm check-closure.c -o check-closure.bin
    -./check-closure.bin <arquivo-entrada> <preâmbulo-saída>
  ->Windows:
    -gcc check-closure.c -o check-closure.exe
    -.\check-closure.exe <arquivo-entrada> <preâmbulo-saída>
  ->dot -Tpdf arquivo.dot -o saida.pdf

 Ambiente de desenvolvimento: vscode

 Data: 10/12/2025

 Objetivo: Verificação de Propriedades e Cálculo de Fechos

*/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

void lerArquivo(char *nomeArquivo, int ***matriz, int *n);
void gerarArquivo(char *nomeArquivo, int ***matrizOriginal, int ***matrizFechos, int *n, int tipo);
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
        exit(1);
    }

    // Obtem os parametros argv para receber o nome dos arquivos
    StrEntrada = argv[1];
    StrSaida = argv[2];

    char nomeSaida[200];
    strcpy(nomeSaida, argv[2]);

    // Remove ".txt" do nome do arquivo de saida
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

/**
 * Nome: lerArquivo
 * Objetivo:
 *    Ler um arquivo de entrada e construir a matriz da relação.
 *
 * Descrição:
 *    O arquivo de entrada possui linhas que definem:
 *      - 'n X' : tamanho do conjunto (X elementos)
 *      - 'r U V' : relação (U, V) pertencente a R
 *      - 'f' : indica o fim da leitura e imprime a matriz
 *
 *    A função aloca dinamicamente a matriz de tamanho (n+1) x (n+1)
 *    (para index de 1 até n) e preenche com 0 ou 1 de acordo
 *    com as relações.
 *
 * Parâmetros:
 *    - nomeArquivo: caminho para o arquivo de entrada (.txt)
 *    - matriz: ponteiro para ponteiro de matriz que será alocada e preenchida
 *    - n: ponteiro para inteiro que armazenará o tamanho do conjunto
 *
 * Retorno: nenhum.
 *
 * Observações:
 *    - Imprime a matriz lida no console ao encontrar 'f'.
 *    - Encerra o programa se não conseguir abrir o arquivo.
 */
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

    while (fgets(linha, 100, f) != NULL)//Lê o arquivo até a última linha encontrada
    {
        sscanf(linha, "%c", &comando);//Lê a linha e o primeiro caracter da linha

        if (comando == 'n')
        {
            //lê N, dimensão da matriz
            sscanf(linha, "%*c %d", n);

            //aloca a matriz e preenche ela com 0
            *matriz = calloc((*n) + 1, sizeof(int *));
            for (int i = 1; i <= *n; i++)
                (*matriz)[i] = calloc((*n) + 1, sizeof(int));
        }
        else if (comando == 'r')
        {
            //lê a relação
            sscanf(linha, "%*c %d %d", &u, &v);

            //preenche com 1 na matriz onde houver relação
            if (u <= *n && v <= *n)
                (*matriz)[u][v] = 1;
        }
        else if (comando == 'f')
        {
            // imprime a matriz final
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

/**
 * Nome: gerarArquivo
 * Objetivo:
 *    Gerar arquivos .dot para visualização do grafo da relação e seus fechos.
 *
 * Descrição:
 *    A função cria um arquivo Graphviz (.dot) contendo:
 *      - Todos os elementos do conjunto como nós
 *      - Todas as relações originais
 *      - Fechos adicionados (destacados em vermelho)
 *
 *    O nome do arquivo de saída é definido pelo parâmetro 'tipo':
 *      - 1: fechos reflexivos      → nome-ref.dot
 *      - 2: fechos simétricos      → nome-sim.dot
 *      - 3: fechos transitivos     → nome-tra.dot
 *
 * Parâmetros:
 *    - nomeArquivo: prefixo do arquivo de saída (sem extensão)
 *    - matrizOriginal: ponteiro triplo para a matriz original
 *    - matrizFechos: ponteiro triplo para a matriz contendo os fechos adicionados
 *    - n: ponteiro para a quantidade de elementos do conjunto
 *    - tipo: inteiro indicando o tipo de fecho (1=reflexivo, 2=simétrico, 3=transitivo)
 *
 * Retorno: nenhum.
 *
 * Observações:
 *    - Se não conseguir abrir o arquivo para escrita, retorna sem gerar nada.
 *    - Destaca os fechos aplicados com cor vermelha no grafo.
 */
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

    //imprime o conjunto primeiro no arquivo
    for (int i = 1; i <= *n; i++)
    {
        fprintf(temp, "%d;\n", i);
    }

    //imprime as relações originais no arquivo
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

    //imprime os fechos no arquivo
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

/**
 * Nome: verificaReflexiva
 * Objetivo: Recebe uma matriz e verifica se possui a propriedade reflexiva
 * Descrição:
 *    Uma relação R é reflexiva quando:
 *        Para todo elemento i do conjunto, (i R i) pertence a R.
 *
 *    A função percorre toda a diagonal principal da matriz[i][i] e valida se todos
 *    esses elementos são 1.
 * Parâmetros:
 *   - matriz: ponteiro para matriz de relação
 *   - n: ponteiro para dimensão da matriz
 * Retorno:
 *    - 1 caso a relação seja reflexiva.
 *    - 0 caso a relação não seja reflexiva.
 * Observações:
 *   - A função apenas verifica; não altera a matriz original.
 *   - Imprime no console "Reflexiva:Sim" ou "Reflexiva:Nao".
 */
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

/**
 * Nome: verificaSimetrica
 * Objetivo: Recebe uma matriz e verifica se possui a propriedade simétrica
 * Descrição:
 *    Uma relação R é simétrica quando:
 *        Se (i R j), então (j R i)
 *
 *    A função percorre toda a matriz comparando as posições
 *    espelhadas (i, j) e (j, i).
 * Parâmetros:
 *   - matriz: ponteiro para matriz de relação
 *   - n: ponteiro para dimensão da matriz
 * Retorno:
 *    - 1 caso a relação seja simétrica.
 *    - 0 caso a relação não seja simétrica.
 * Observações:
 *   - A função apenas verifica; não altera a matriz original.
 *   - Imprime no console "Simétrica:Sim" ou "Simétrica:Nao".
 */
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

/**
 * Nome: verificaTransitiva
 * Objetivo: Recebe uma matriz e verifica se possui a propriedade transitiva
 * Descrição:
 *    A relação R é transitiva quando:
 *        Se (i R j) e (j R k), então (i R k)
 *
 *    Ou seja, sempre que existe um caminho i → j e j → k,
 *    deve obrigatoriamente existir também i → k na matriz.
 * Parâmetros:
 *   - matriz: ponteiro para matriz de relação
 *   - n: ponteiro para dimensão da matriz
 * Retorno:
 *    - 1 caso a relação seja transitiva.
 *    - 0 caso a relação não seja transitiva.
 * Observações:
 *   - A função apenas verifica; não altera a matriz original.
 *   - Imprime no console "Transitiva:Sim" ou "Transitiva:Nao".
 */
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

/**
 * Nome: checkFechoReflexivo
 * Objetivo: Recebe uma matriz não reflexiva e busca os fechos reflexivos necessários.
 * Parâmetros:
 *   - matriz: ponteiro para matriz de relação
 *   - n: ponteiro para dimensão da matriz
 *   - nomeSaida: prefixo do arquivo para gerar o .dot
 * Retorno: nenhum
 * Observações:
 *   - Gera arquivo .dot com as relações iniciais e com os fechos destacados em vermelho
 */
void checkFechoReflexivo(int ***matriz, int *n, char *nomeSaida)
{
    int **matrizAux;//matriz a ser preenchida com os fechos
    int encontrou = 0;//contador de fechos encontrados

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

/**
 * Nome: checkFechoSimetrico
 * Objetivo: Recebe uma matriz não simétrica e busca os fechos simétricos necessários.
 * Parâmetros:
 *   - matriz: ponteiro para matriz de relação
 *   - n: ponteiro para dimensão da matriz
 *   - nomeSaida: prefixo do arquivo para gerar o .dot
 * Retorno: nenhum
 * Observações:
 *   - Gera arquivo .dot com as relações iniciais e com os fechos destacados em vermelho
 */
void checkFechoSimetrico(int ***matriz, int *n, char *nomeSaida)
{
    int **matrizAux;//matriz a ser preenchida com os fechos
    int encontrou = 0;//contador de fechos encontrados

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

/**
 * Nome: checkFechoTransitivo
 * Objetivo: Recebe uma matriz não transitiva e busca os fechos transitivos necessários.
 * Parâmetros:
 *   - matriz: ponteiro para matriz de relação
 *   - n: ponteiro para dimensão da matriz
 *   - nomeSaida: prefixo do arquivo para gerar o .dot
 * Retorno: nenhum
 * Observações:
 *   - Gera arquivo .dot com as relações iniciais e com os fechos destacados em vermelho
 */
void checkFechoTransitivo(int ***matriz, int *n, char *nomeSaida)
{
    int **matrizAux;//matriz a ser preenchida com os fechos
    int encontrou = 0;//contador de fechos encontrados

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