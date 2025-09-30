#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_COMP 20

// =============================
// Struct principal
// =============================
typedef struct {
    char nome[30];
    char tipo[20];
    int prioridade;
} Componente;

// =============================
// Funções utilitárias
// =============================
void mostrarComponentes(Componente v[], int n) {
    printf("\n--- Componentes da Torre ---\n");
    for (int i = 0; i < n; i++) {
        printf("%d) Nome: %s | Tipo: %s | Prioridade: %d\n",
               i+1, v[i].nome, v[i].tipo, v[i].prioridade);
    }
}

// =============================
// Algoritmos de ordenação
// =============================
int bubbleSortNome(Componente v[], int n) {
    int comparacoes = 0;
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            comparacoes++;
            if (strcmp(v[j].nome, v[j+1].nome) > 0) {
                Componente tmp = v[j];
                v[j] = v[j+1];
                v[j+1] = tmp;
            }
        }
    }
    return comparacoes;
}

int insertionSortTipo(Componente v[], int n) {
    int comparacoes = 0;
    for (int i = 1; i < n; i++) {
        Componente chave = v[i];
        int j = i - 1;
        while (j >= 0 && strcmp(v[j].tipo, chave.tipo) > 0) {
            comparacoes++;
            v[j+1] = v[j];
            j--;
        }
        if (j >= 0) comparacoes++;
        v[j+1] = chave;
    }
    return comparacoes;
}

int selectionSortPrioridade(Componente v[], int n) {
    int comparacoes = 0;
    for (int i = 0; i < n-1; i++) {
        int min = i;
        for (int j = i+1; j < n; j++) {
            comparacoes++;
            if (v[j].prioridade < v[min].prioridade) {
                min = j;
            }
        }
        if (min != i) {
            Componente tmp = v[i];
            v[i] = v[min];
            v[min] = tmp;
        }
    }
    return comparacoes;
}

// =============================
// Busca binária (após ordenar por nome)
// =============================
int buscaBinariaPorNome(Componente v[], int n, char chave[]) {
    int inicio = 0, fim = n - 1, comparacoes = 0;
    while (inicio <= fim) {
        int meio = (inicio + fim) / 2;
        comparacoes++;
        int cmp = strcmp(v[meio].nome, chave);
        if (cmp == 0) {
            printf("\nComponente encontrado: %s | Tipo: %s | Prioridade: %d\n",
                   v[meio].nome, v[meio].tipo, v[meio].prioridade);
            printf("Comparacoes (binaria): %d\n", comparacoes);
            return meio;
        } else if (cmp < 0) {
            inicio = meio + 1;
        } else {
            fim = meio - 1;
        }
    }
    printf("\nComponente '%s' nao encontrado.\n", chave);
    printf("Comparacoes (binaria): %d\n", comparacoes);
    return -1;
}

// =============================
// Função para medir tempo
// =============================
double medirTempo(int (*algoritmo)(Componente[], int), Componente v[], int n, int *comparacoes) {
    clock_t inicio = clock();
    *comparacoes = algoritmo(v, n);
    clock_t fim = clock();
    return (double)(fim - inicio) / CLOCKS_PER_SEC;
}

// =============================
// Main
// =============================
int main() {
    Componente torre[MAX_COMP];
    int n = 0, opcao;
    char chave[30];

    do {
        printf("\n===== MENU TORRE DE FUGA =====\n");
        printf("1. Cadastrar componente\n");
        printf("2. Mostrar componentes\n");
        printf("3. Ordenar por Nome (Bubble Sort)\n");
        printf("4. Ordenar por Tipo (Insertion Sort)\n");
        printf("5. Ordenar por Prioridade (Selection Sort)\n");
        printf("6. Buscar componente-chave (binaria - por Nome)\n");
        printf("0. Sair\n");
        printf("Opcao: ");
        scanf("%d", &opcao);
        getchar();

        int comparacoes;
        double tempo;
        switch(opcao) {
            case 1:
                if (n >= MAX_COMP) {
                    printf("Limite maximo atingido.\n");
                } else {
                    printf("Digite o nome: ");
                    fgets(torre[n].nome, 30, stdin);
                    torre[n].nome[strcspn(torre[n].nome, "\n")] = '\0';

                    printf("Digite o tipo: ");
                    fgets(torre[n].tipo, 20, stdin);
                    torre[n].tipo[strcspn(torre[n].tipo, "\n")] = '\0';

                    printf("Digite a prioridade (1-10): ");
                    scanf("%d", &torre[n].prioridade);
                    getchar();

                    n++;
                    printf("Componente cadastrado!\n");
                }
                break;

            case 2:
                mostrarComponentes(torre, n);
                break;

            case 3:
                tempo = medirTempo(bubbleSortNome, torre, n, &comparacoes);
                printf("Ordenado por Nome (Bubble Sort).\n");
                printf("Comparacoes: %d | Tempo: %.6f s\n", comparacoes, tempo);
                mostrarComponentes(torre, n);
                break;

            case 4:
                tempo = medirTempo(insertionSortTipo, torre, n, &comparacoes);
                printf("Ordenado por Tipo (Insertion Sort).\n");
                printf("Comparacoes: %d | Tempo: %.6f s\n", comparacoes, tempo);
                mostrarComponentes(torre, n);
                break;

            case 5:
                tempo = medirTempo(selectionSortPrioridade, torre, n, &comparacoes);
                printf("Ordenado por Prioridade (Selection Sort).\n");
                printf("Comparacoes: %d | Tempo: %.6f s\n", comparacoes, tempo);
                mostrarComponentes(torre, n);
                break;

            case 6:
                printf("Digite o nome do componente-chave: ");
                fgets(chave, 30, stdin);
                chave[strcspn(chave, "\n")] = '\0';
                buscaBinariaPorNome(torre, n, chave);
                break;

            case 0:
                printf("Encerrando montagem da torre...\n");
                break;

            default:
                printf("Opcao invalida.\n");
        }
    } while(opcao != 0);

    return 0;
}
