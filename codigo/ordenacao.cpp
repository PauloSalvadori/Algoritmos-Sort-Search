#include <stdio.h>
#include <stdlib.h> 
#include <time.h>   
#include <string.h> 


/*--------------- PROTÓTIPOS ---------------*/

// Algoritmos de Sorting
void quick_sort(int arr[], int low, int high);

// Funções de Carregamento e Teste
int* carregar_arquivo_memoria(const char *nome_arquivo, int *tamanho_ptr);
void executar_teste(const char *nome_arquivo, const char *nome_algoritmo);


/*--------------- ALGORITMOS DE SORTING ---------------*/


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

void executar_teste(const char *nome_arquivo, const char *nome_algoritmo) {
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

    clock_t inicio, fim;
    double tempo_execucao;

    // Cronômetro
    printf("Testando %s em %s (Tamanho: %d)...\n", nome_algoritmo, nome_arquivo, tamanho_vetor);
    inicio = clock();
    
    // Chamada das funções de sorting
    if (strcmp(nome_algoritmo, "Quicksort") == 0) {
        quick_sort(vetor_teste, 0, tamanho_vetor - 1);
    } 
    /* Adicione seus outros algoritmos aqui (ex: Mergesort) */
    
    fim = clock();

    // Cálculo do tempo de execução
    tempo_execucao = (double)(fim - inicio) / CLOCKS_PER_SEC;
    printf("Tempo de execução: %.4f segundos\n", tempo_execucao);
    
    // Liberação de memória
    free(vetor_teste);
    free(vetor_original); 
}


/*--------------- FUNÇÃO MAIN ---------------*/

int main() {
    // Lista dos arquivos
    const char *arquivos[] = {
        "grande_aleatorio.bin",
        "grande_crescente.bin",
        "grande_decrescente.bin",
        "medio_aleatorio.bin",
        "medio_crescente.bin",
        "medio_decrescente.bin",
        "pequeno_aleatorio.bin",
        "pequeno_crescente.bin",
        "pequeno_decrescente.bin"
    };
    int num_arquivos = sizeof(arquivos) / sizeof(arquivos[0]);
    
    // Lista dos algoritmos 
    const char *algoritmos[] = {
        "Selection Sort",
        "Insertion Sort",
        "Bubble Sort",
        "Bubble Sort Otimizado"
    };
    int num_algoritmos = sizeof(algoritmos) / sizeof(algoritmos[0]);
  
    int escolha_arquivo = -1;
    int escolha_algoritmo = -1;
    char continuar = 's';


    printf("--- Iniciando Teste Empírico de Algoritmos de Ordenação ---\n\n");

    while (continuar == 's' || continuar == 'S') {
        
        // Menu de arquivos
        printf("\n| Escolha o Arquivo de Entrada: |\n");
        for (int i = 0; i < num_arquivos; i++) {
            printf("| %d - %s\n", i + 1, arquivos[i]);
        }
        printf("Selecione (1 a %d): ", num_arquivos);
        
        // Menu de algoritmos
        printf("\n| Escolha o Algoritmo de Ordenação: |\n");
        for (int i = 0; i < num_algoritmos; i++) {
            printf("| %d - %s\n", i + 1, algoritmos[i]);
        }
        printf("Selecione (1 a %d): ", num_algoritmos);

        printf("\n============================================\n");
        
        // Execução do teste       
        const char *arquivo_selecionado = arquivos[escolha_arquivo - 1];
        const char *algoritmo_selecionado = algoritmos[escolha_algoritmo - 1];
        
        executar_teste(arquivo_selecionado, algoritmo_selecionado);
        
        printf("============================================\n");
        
        // Continuidade no teste
        printf("\nDeseja executar outro teste? (s/n): ");
        if (scanf(" %c", &continuar) != 1) {
             continuar = 'n'; 
        }
    }

    printf("\nTestes encerrados.\n");
    return 0;
}