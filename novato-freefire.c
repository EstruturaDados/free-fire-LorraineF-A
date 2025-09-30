#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_ITENS 10

// Struct que representa um item da mochila
typedef struct {
    char nome[30];     // Nome do item (ex: "AK-47", "Kit Médico")
    char tipo[20];     // Tipo do item (ex: "arma", "munição", "cura")
    int quantidade;    // Quantidade do item
} Item;

// Protótipos das funções
void inserirItem(Item mochila[], int *numItens);
void removerItem(Item mochila[], int *numItens);
void listarItens(Item mochila[], int numItens);
void buscarItem(Item mochila[], int numItens);

int main() {
    Item mochila[MAX_ITENS];
    int numItens = 0; // Contador de itens cadastrados
    int opcao;

    do {
        printf("\n======= MENU - MOCHILA FREE FIRE =======\n");
        printf("1. Cadastrar item\n");
        printf("2. Remover item\n");
        printf("3. Listar itens\n");
        printf("4. Buscar item\n");
        printf("0. Sair\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);
        getchar(); // Consumir o '\n' deixado pelo scanf

        switch(opcao) {
            case 1:
                inserirItem(mochila, &numItens);
                listarItens(mochila, numItens);
                break;
            case 2:
                removerItem(mochila, &numItens);
                listarItens(mochila, numItens);
                break;
            case 3:
                listarItens(mochila, numItens);
                break;
            case 4:
                buscarItem(mochila, numItens);
                break;
            case 0:
                printf("Saindo do jogo... Ate mais, guerreiro!\n");
                break;
            default:
                printf("Opcao invalida! Tente novamente.\n");
        }
    } while(opcao != 0);

    return 0;
}

// Função para inserir um item na mochila
void inserirItem(Item mochila[], int *numItens) {
    if (*numItens >= MAX_ITENS) {
        printf("Mochila cheia! Nao e possivel adicionar mais itens.\n");
        return;
    }

    Item novo;
    printf("Digite o nome do item: ");
    fgets(novo.nome, 30, stdin);
    novo.nome[strcspn(novo.nome, "\n")] = '\0'; // Remover \n

    printf("Digite o tipo do item (arma, municao, cura): ");
    fgets(novo.tipo, 20, stdin);
    novo.tipo[strcspn(novo.tipo, "\n")] = '\0';

    printf("Digite a quantidade: ");
    scanf("%d", &novo.quantidade);
    getchar(); // Consumir \n

    mochila[*numItens] = novo;
    (*numItens)++;

    printf("Item '%s' adicionado com sucesso!\n", novo.nome);
}

// Função para remover um item pelo nome
void removerItem(Item mochila[], int *numItens) {
    if (*numItens == 0) {
        printf("Mochila vazia! Nao ha itens para remover.\n");
        return;
    }

    char nomeRemover[30];
    printf("Digite o nome do item que deseja remover: ");
    fgets(nomeRemover, 30, stdin);
    nomeRemover[strcspn(nomeRemover, "\n")] = '\0';

    int encontrado = 0;
    for (int i = 0; i < *numItens; i++) {
        if (strcmp(mochila[i].nome, nomeRemover) == 0) {
            // Substituir item removido pelo último da lista
            mochila[i] = mochila[*numItens - 1];
            (*numItens)--;
            encontrado = 1;
            printf("Item '%s' removido com sucesso!\n", nomeRemover);
            break;
        }
    }

    if (!encontrado) {
        printf("Item '%s' nao encontrado na mochila.\n", nomeRemover);
    }
}

// Função para listar todos os itens
void listarItens(Item mochila[], int numItens) {
    if (numItens == 0) {
        printf("Mochila vazia! Nenhum item cadastrado.\n");
        return;
    }

    printf("\n=== Itens na mochila ===\n");
    for (int i = 0; i < numItens; i++) {
        printf("%d) Nome: %s | Tipo: %s | Quantidade: %d\n", 
               i+1, mochila[i].nome, mochila[i].tipo, mochila[i].quantidade);
    }
}

// Função para buscar item pelo nome
void buscarItem(Item mochila[], int numItens) {
    if (numItens == 0) {
        printf("Mochila vazia! Nenhum item para buscar.\n");
        return;
    }

    char nomeBusca[30];
    printf("Digite o nome do item que deseja buscar: ");
    fgets(nomeBusca, 30, stdin);
    nomeBusca[strcspn(nomeBusca, "\n")] = '\0';

    for (int i = 0; i < numItens; i++) {
        if (strcmp(mochila[i].nome, nomeBusca) == 0) {
            printf("Item encontrado!\n");
            printf("Nome: %s | Tipo: %s | Quantidade: %d\n", 
                   mochila[i].nome, mochila[i].tipo, mochila[i].quantidade);
            return;
        }
    }

    printf("Item '%s' nao encontrado.\n", nomeBusca);
}
