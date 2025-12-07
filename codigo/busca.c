#include <stdio.h>
#include <stdlib.h> 
#include <time.h>


/*--------------- ALGORITMOS DE BUSCA ---------------*/
//1. Busca Sequencial
int busca_sequencial(int arr[], int n, int elemento, long long *comparacoes) {
    *comparacoes = 0;

    for (int i = 0; i < n; i++) {
        (*comparacoes)++;
        if (arr[i] == elemento) {
            return i; 
        }
    }
    return -1; 
}



/*--------------- CARREGAMENTO DE ARQUIVO ---------------*/

int* carregar_arquivo_memoria(const char *nome_arquivo, int *tamanho_ptr) {
    FILE *arquivo = fopen(nome_arquivo, "rb");

    if (arquivo == NULL) {
        perror("Erro ao abrir o arquivo");
        *tamanho_ptr = 0;
        return NULL;
    }

    // Determina o tamanho do arquivo em inteiros
    fseek(arquivo, 0, SEEK_END);
    long tamanho_em_bytes = ftell(arquivo);
    rewind(arquivo);

    int num_inteiros = tamanho_em_bytes / sizeof(int);
    *tamanho_ptr = num_inteiros;

    // Aloca memória
    int *vetor = (int *)malloc(tamanho_em_bytes);
    if (vetor == NULL) {
        perror("Erro ao alocar memória");
        fclose(arquivo);
        *tamanho_ptr = 0;
        return NULL;
    }

    // Lê o conteúdo
    fread(vetor, sizeof(int), num_inteiros, arquivo);

    fclose(arquivo);
    return vetor;
}


/*--------------- AUXILIARES CHAMADA DO TESTE ---------------*/

void executar_teste(const char *nome_arquivo, const char *nome_algoritmo, const int elemento) {
    int tamanho_vetor;
    
    // Carrega o vetor original do .bin
    int *vetor_original = carregar_arquivo_memoria(nome_arquivo, &tamanho_vetor);

    if (vetor_original == NULL || tamanho_vetor == 0) {
        return;
    }
    
    // Criar uma cópia para o teste 
    int *vetor_teste = (int *)malloc(tamanho_vetor * sizeof(int));
    if (vetor_teste == NULL) {
        perror("Erro ao alocar memória para cópia");
        free(vetor_original);
        return;
    }
    
    memcpy(vetor_teste, vetor_original, tamanho_vetor * sizeof(int));

    // Variáveis de controle
    clock_t inicio, fim;
    double tempo_execucao;

    long long comparacoes = 0;

    // Cronômetro
    printf("Testando %s em %s (Tamanho: %d)...\n", nome_algoritmo, nome_arquivo, tamanho_vetor);
    inicio = clock();
    
    // Chamada das funções de busca
    if (strcmp(nome_algoritmo, "Busca Sequencial") == 0) {
        busca_sequencial(vetor_teste, tamanho_vetor, elemento, &comparacoes);
    }
    /*else if (strcmp(nome_algoritmo, "Busca Binária") == 0) {
        bubble_sort_otimizado(vetor_teste, tamanho_vetor, &comparacoes);
    } */
    else printf("Algoritmo não reconhecido.\n");

    
    fim = clock();

    // Cálculo do tempo de execução
    tempo_execucao = (double)(fim - inicio) / CLOCKS_PER_SEC;
   
    // Exibição dos resultados
    printf("Tempo de execucao: %.15f segundos\n", tempo_execucao); 
    printf("Numero de comparacoes: %lld\n", comparacoes); 

    // Liberação de memória
    free(vetor_teste);
    free(vetor_original); 
}


/*--------------- FUNÇÃO MAIN ---------------*/
