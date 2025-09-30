#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_ITENS 10

// =============================
// Structs
// =============================
typedef struct {
    char nome[30];
    char tipo[20];
    int quantidade;
} Item;

typedef struct No {
    Item dados;
    struct No* proximo;
} No;

// =============================
// Funções para vetor
// =============================
void inserirVetor(Item mochila[], int *numItens) {
    if (*numItens >= MAX_ITENS) {
        printf("Mochila cheia (vetor)!\n");
        return;
    }
    Item novo;
    printf("Digite o nome: ");
    fgets(novo.nome, 30, stdin);
    novo.nome[strcspn(novo.nome, "\n")] = '\0';
    printf("Digite o tipo: ");
    fgets(novo.tipo, 20, stdin);
    novo.tipo[strcspn(novo.tipo, "\n")] = '\0';
    printf("Digite a quantidade: ");
    scanf("%d", &novo.quantidade);
    getchar();

    mochila[*numItens] = novo;
    (*numItens)++;
    printf("Item '%s' inserido no vetor.\n", novo.nome);
}

void removerVetor(Item mochila[], int *numItens) {
    if (*numItens == 0) {
        printf("Mochila vazia (vetor)!\n");
        return;
    }
    char nome[30];
    printf("Digite o nome para remover: ");
    fgets(nome, 30, stdin);
    nome[strcspn(nome, "\n")] = '\0';

    for (int i = 0; i < *numItens; i++) {
        if (strcmp(mochila[i].nome, nome) == 0) {
            mochila[i] = mochila[*numItens - 1];
            (*numItens)--;
            printf("Item '%s' removido (vetor).\n", nome);
            return;
        }
    }
    printf("Item nao encontrado (vetor).\n");
}

void listarVetor(Item mochila[], int numItens) {
    printf("\n--- Mochila (Vetor) ---\n");
    for (int i = 0; i < numItens; i++) {
        printf("%d) Nome: %s | Tipo: %s | Quantidade: %d\n", 
               i+1, mochila[i].nome, mochila[i].tipo, mochila[i].quantidade);
    }
    if (numItens == 0) printf("Mochila vazia.\n");
}

int buscarSequencialVetor(Item mochila[], int numItens, char nome[]) {
    int comparacoes = 0;
    for (int i = 0; i < numItens; i++) {
        comparacoes++;
        if (strcmp(mochila[i].nome, nome) == 0) {
            printf("Item encontrado (sequencial vetor): %s (%s, %d)\n",
                   mochila[i].nome, mochila[i].tipo, mochila[i].quantidade);
            printf("Comparacoes: %d\n", comparacoes);
            return i;
        }
    }
    printf("Item nao encontrado (sequencial vetor).\n");
    printf("Comparacoes: %d\n", comparacoes);
    return -1;
}

// Ordenação por nome (Bubble Sort)
void ordenarVetor(Item mochila[], int numItens) {
    for (int i = 0; i < numItens - 1; i++) {
        for (int j = 0; j < numItens - i - 1; j++) {
            if (strcmp(mochila[j].nome, mochila[j+1].nome) > 0) {
                Item temp = mochila[j];
                mochila[j] = mochila[j+1];
                mochila[j+1] = temp;
            }
        }
    }
    printf("Itens ordenados por nome (vetor).\n");
}

// Busca binária
int buscarBinariaVetor(Item mochila[], int numItens, char nome[]) {
    int inicio = 0, fim = numItens - 1, comparacoes = 0;
    while (inicio <= fim) {
        int meio = (inicio + fim) / 2;
        comparacoes++;
        int cmp = strcmp(mochila[meio].nome, nome);
        if (cmp == 0) {
            printf("Item encontrado (binaria vetor): %s (%s, %d)\n",
                   mochila[meio].nome, mochila[meio].tipo, mochila[meio].quantidade);
            printf("Comparacoes: %d\n", comparacoes);
            return meio;
        } else if (cmp < 0) {
            inicio = meio + 1;
        } else {
            fim = meio - 1;
        }
    }
    printf("Item nao encontrado (binaria vetor).\n");
    printf("Comparacoes: %d\n", comparacoes);
    return -1;
}

// =============================
// Funções para lista encadeada
// =============================
No* inserirLista(No* inicio) {
    No* novo = (No*)malloc(sizeof(No));
    if (!novo) {
        printf("Erro de alocacao.\n");
        return inicio;
    }
    printf("Digite o nome: ");
    fgets(novo->dados.nome, 30, stdin);
    novo->dados.nome[strcspn(novo->dados.nome, "\n")] = '\0';
    printf("Digite o tipo: ");
    fgets(novo->dados.tipo, 20, stdin);
    novo->dados.tipo[strcspn(novo->dados.tipo, "\n")] = '\0';
    printf("Digite a quantidade: ");
    scanf("%d", &novo->dados.quantidade);
    getchar();

    novo->proximo = inicio;
    printf("Item '%s' inserido (lista).\n", novo->dados.nome);
    return novo;
}

No* removerLista(No* inicio) {
    if (!inicio) {
        printf("Mochila vazia (lista).\n");
        return NULL;
    }
    char nome[30];
    printf("Digite o nome para remover: ");
    fgets(nome, 30, stdin);
    nome[strcspn(nome, "\n")] = '\0';

    No* atual = inicio;
    No* anterior = NULL;

    while (atual) {
        if (strcmp(atual->dados.nome, nome) == 0) {
            if (anterior == NULL) {
                inicio = atual->proximo;
            } else {
                anterior->proximo = atual->proximo;
            }
            free(atual);
            printf("Item '%s' removido (lista).\n", nome);
            return inicio;
        }
        anterior = atual;
        atual = atual->proximo;
    }
    printf("Item nao encontrado (lista).\n");
    return inicio;
}

void listarLista(No* inicio) {
    printf("\n--- Mochila (Lista Encadeada) ---\n");
    No* atual = inicio;
    int i = 1;
    while (atual) {
        printf("%d) Nome: %s | Tipo: %s | Quantidade: %d\n", 
               i++, atual->dados.nome, atual->dados.tipo, atual->dados.quantidade);
        atual = atual->proximo;
    }
    if (i == 1) printf("Mochila vazia.\n");
}

void buscarSequencialLista(No* inicio, char nome[]) {
    int comparacoes = 0;
    No* atual = inicio;
    while (atual) {
        comparacoes++;
        if (strcmp(atual->dados.nome, nome) == 0) {
            printf("Item encontrado (sequencial lista): %s (%s, %d)\n",
                   atual->dados.nome, atual->dados.tipo, atual->dados.quantidade);
            printf("Comparacoes: %d\n", comparacoes);
            return;
        }
        atual = atual->proximo;
    }
    printf("Item nao encontrado (sequencial lista).\n");
    printf("Comparacoes: %d\n", comparacoes);
}

// =============================
// Main
// =============================
int main() {
    Item mochilaVetor[MAX_ITENS];
    int numItens = 0;
    No* mochilaLista = NULL;

    int opcao;
    do {
        printf("\n===== MENU MOCHILA =====\n");
        printf("1. Inserir (vetor)\n");
        printf("2. Remover (vetor)\n");
        printf("3. Listar (vetor)\n");
        printf("4. Buscar sequencial (vetor)\n");
        printf("5. Ordenar + buscar binaria (vetor)\n");
        printf("6. Inserir (lista)\n");
        printf("7. Remover (lista)\n");
        printf("8. Listar (lista)\n");
        printf("9. Buscar sequencial (lista)\n");
        printf("0. Sair\n");
        printf("Opcao: ");
        scanf("%d", &opcao);
        getchar();

        char nomeBusca[30];
        switch(opcao) {
            case 1: inserirVetor(mochilaVetor, &numItens); break;
            case 2: removerVetor(mochilaVetor, &numItens); break;
            case 3: listarVetor(mochilaVetor, numItens); break;
            case 4:
                printf("Digite o nome: ");
                fgets(nomeBusca, 30, stdin);
                nomeBusca[strcspn(nomeBusca, "\n")] = '\0';
                buscarSequencialVetor(mochilaVetor, numItens, nomeBusca);
                break;
            case 5:
                ordenarVetor(mochilaVetor, numItens);
                printf("Digite o nome: ");
                fgets(nomeBusca, 30, stdin);
                nomeBusca[strcspn(nomeBusca, "\n")] = '\0';
                buscarBinariaVetor(mochilaVetor, numItens, nomeBusca);
                break;
            case 6: mochilaLista = inserirLista(mochilaLista); break;
            case 7: mochilaLista = removerLista(mochilaLista); break;
            case 8: listarLista(mochilaLista); break;
            case 9:
                printf("Digite o nome: ");
                fgets(nomeBusca, 30, stdin);
                nomeBusca[strcspn(nomeBusca, "\n")] = '\0';
                buscarSequencialLista(mochilaLista, nomeBusca);
                break;
            case 0: printf("Saindo...\n"); break;
            default: printf("Opcao invalida!\n");
        }
    } while(opcao != 0);

    return 0;
}
