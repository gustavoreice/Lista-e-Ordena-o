#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Definição da Struct Item 
// Agrega as informações essenciais de cada objeto na mochila.
typedef struct {
    char nome[30];
    char tipo[20];
    int quantidade;
} Item;

// Constante para o tamanho máximo da mochila 
#define CAPACIDADE_MAXIMA 10

// ----------------------------------------------------------------------
// Função de Busca Sequencial 
// ----------------------------------------------------------------------
// Busca um item pelo nome e retorna seu índice no vetor.
// Retorna -1 se o item não for encontrado.
int buscarItem(Item inventario[], int numItens, const char nomeBusca[]) {
    // Percorre o vetor sequencialmente
    for (int i = 0; i < numItens; i++) {
        // Compara o nome do item atual com o nome buscado (ignorando maiúsculas/minúsculas para robustez)
        if (strcasecmp(inventario[i].nome, nomeBusca) == 0) {
            return i; // Item encontrado
        }
    }
    return -1; // Item não encontrado
}

// ----------------------------------------------------------------------
// Função para Inserir Item 
// ----------------------------------------------------------------------
void inserirItem(Item inventario[], int *numItens) {
    if (*numItens >= CAPACIDADE_MAXIMA) {
        printf("\nMochila cheia! Capacidade máxima (%d itens) atingida.\n", CAPACIDADE_MAXIMA);
        return;
    }

    Item novoItem;

    printf("\n--- CADASTRO DE NOVO ITEM ---\n");
    
    // Leitura do Nome
    printf("Nome do Item (max 29 caracteres): ");
    // Limpa o buffer de entrada antes de usar fgets
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
    // Usa fgets para capturar strings com espaços e evitar overflow
    if (fgets(novoItem.nome, sizeof(novoItem.nome), stdin) != NULL) {
        // Remove a quebra de linha ('\n') adicionada por fgets, se houver
        novoItem.nome[strcspn(novoItem.nome, "\n")] = 0;
    }

    // Verifica se o item já existe para evitar duplicatas simples
    if (buscarItem(inventario, *numItens, novoItem.nome) != -1) {
        printf("Item '%s' já existe na mochila. Ação cancelada.\n", novoItem.nome);
        return;
    }

    // Leitura do Tipo
    printf("Tipo do Item (ex: arma, municao, cura): ");
    scanf("%19s", novoItem.tipo);
    
    // Leitura da Quantidade
    printf("Quantidade: ");
    while (scanf("%d", &novoItem.quantidade) != 1 || novoItem.quantidade <= 0) {
        printf("Quantidade inválida. Digite um número positivo: ");
        // Limpa o buffer em caso de erro de leitura
        while ((c = getchar()) != '\n' && c != EOF); 
    }
    
    // Insere o novo item na próxima posição livre do vetor
    inventario[*numItens] = novoItem;
    (*numItens)++;

    printf("Item '%s' adicionado à mochila com sucesso.\n", novoItem.nome);
}

// ----------------------------------------------------------------------
// Função para Remover Item 
// ----------------------------------------------------------------------
void removerItem(Item inventario[], int *numItens) {
    if (*numItens == 0) {
        printf("\n Mochila vazia. Nada a remover.\n");
        return;
    }

    char nomeBusca[30];
    printf("\n--- REMOÇÃO DE ITEM ---\n");
    printf("Digite o NOME do item a ser removido: ");
    
    // Limpa o buffer de entrada antes de usar scanf para string
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
    scanf("%29s", nomeBusca);
    
    int indice = buscarItem(inventario, *numItens, nomeBusca);

    if (indice != -1) {
        // Remove o item e preenche o "buraco" 
        for (int i = indice; i < (*numItens) - 1; i++) {
            inventario[i] = inventario[i + 1];
        }

        (*numItens)--;
        printf("🗑️ Item '%s' removido da mochila com sucesso.\n", nomeBusca);
    } else {
        printf("Item '%s' não encontrado na mochila.\n", nomeBusca);
    }
}

// ----------------------------------------------------------------------
// Função para Listar Itens 
// ----------------------------------------------------------------------
void listarItens(Item inventario[], int numItens) {
    printf("\n--- INVENTÁRIO (MOCHILA) ---\n");

    if (numItens == 0) {
        printf("Mochila vazia. Colete alguns itens!\n");
        return;
    }

    // Tabela para melhor visualização 
    printf("+------------------------------+--------------------+------------+\n");
    printf("| Nome                         | Tipo               | Quantidade |\n");
    printf("+------------------------------+--------------------+------------+\n");
    
    for (int i = 0; i < numItens; i++) {
        printf("| %-28s | %-18s | %10d |\n", 
               inventario[i].nome, inventario[i].tipo, inventario[i].quantidade);
    }
    printf("+------------------------------+--------------------+------------+\n");
    printf("Total de Itens: %d/%d\n", numItens, CAPACIDADE_MAXIMA);
}

// ----------------------------------------------------------------------
// Função para Buscar e Exibir Item 
// ----------------------------------------------------------------------
void buscarEExibirItem(Item inventario[], int numItens) {
    if (numItens == 0) {
        printf("\n Mochila vazia. Nada para buscar.\n");
        return;
    }
    
    char nomeBusca[30];
    printf("\n--- BUSCA SEQUENCIAL DE ITEM ---\n");
    printf("Digite o NOME do item para buscar: ");
    
    // Limpa o buffer de entrada antes de usar scanf para string
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
    scanf("%29s", nomeBusca);
    
    int indice = buscarItem(inventario, numItens, nomeBusca);

    if (indice != -1) {
        printf("\nItem encontrado no inventário:\n");
        printf("  Nome: %s\n", inventario[indice].nome);
        printf("  Tipo: %s\n", inventario[indice].tipo);
        printf("  Quantidade: %d\n", inventario[indice].quantidade);
    } else {
        printf("\n Item '%s' não encontrado na mochila.\n", nomeBusca);
    }
}


// ----------------------------------------------------------------------
// Função Principal (Fluxo de Execução)
// ----------------------------------------------------------------------
int main() {
    // Vetor de structs (Lista Sequencial) e contador (variáveis globais implícitas)
    Item inventario[CAPACIDADE_MAXIMA];
    int numItens = 0; // Inicialmente a mochila está vazia
    int opcao;

    printf("=== SISTEMA DE INVENTÁRIO (MOCHILA DE LOOT) ===\n");

    do {
        // Menu Principal (Requisito de Usabilidade)
        printf("\n--- MENU DE AÇÕES ---\n");
        printf("1. Cadastrar Novo Item\n");
        printf("2. Remover Item\n");
        printf("3. Listar Itens (Visualizar Mochila)\n");
        printf("4. Buscar Item por Nome\n");
        printf("0. Sair do Jogo e Salvar Inventário\n");
        printf("Escolha uma opção: ");

        // Garante que a entrada seja um número válido
        if (scanf("%d", &opcao) != 1) {
            printf("\nOpção inválida. Digite um número.\n");
            // Limpa o buffer de entrada para evitar loop infinito
            int c;
            while ((c = getchar()) != '\n' && c != EOF);
            continue;
        }

        // Chama a função apropriada com base na opção
        switch (opcao) {
            case 1:
                inserirItem(inventario, &numItens);
                listarItens(inventario, numItens); // Lista após cada operação
                break;
            case 2:
                removerItem(inventario, &numItens);
                listarItens(inventario, numItens); // Lista após cada operação
                break;
            case 3:
                listarItens(inventario, numItens);
                break;
            case 4:
                buscarEExibirItem(inventario, numItens);
                break;
            case 0:
                printf("\n Fechando sistema. Inventário salvo! Boa sorte no jogo!\n");
                break;
            default:
                printf("\nOpção inválida. Tente novamente.\n");
        }
    } while (opcao != 0);

    return 0;
}