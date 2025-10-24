##include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_ITENS 10  // Capacidade máxima da mochila

// ----------------------------
// Estrutura que representa um item do inventário
// ----------------------------
typedef struct {
    char nome[30];      // Nome do item
    char tipo[20];      // Tipo do item (arma, munição, cura, etc.)
    int quantidade;     // Quantidade do item
} Item;

// ----------------------------
// Funções do sistema
// ----------------------------
void inserirItem(Item mochila[], int *total);
void removerItem(Item mochila[], int *total);
void listarItens(Item mochila[], int total);
void buscarItem(Item mochila[], int total);

int main() {
    Item mochila[MAX_ITENS];
    int total = 0;
    int opcao;

    do {
        printf("\n==============================\n");
        printf("      MOCHILA DO JOGADOR\n");
        printf("==============================\n");
        printf("1 - Adicionar item\n");
        printf("2 - Remover item\n");
        printf("3 - Listar itens\n");
        printf("4 - Buscar item\n");
        printf("0 - Sair\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);
        getchar(); // Limpar o buffer do teclado

        switch (opcao) {
            case 1:
                inserirItem(mochila, &total);
                break;
            case 2:
                removerItem(mochila, &total);
                break;
            case 3:
                listarItens(mochila, total);
                break;
            case 4:
                buscarItem(mochila, total);
                break;
            case 0:
                printf("Saindo do sistema...\n");
                break;
            default:
                printf("Opcao invalida! Tente novamente.\n");
        }

    } while (opcao != 0);

    return 0;
}

// ----------------------------
// Função: inserirItem
// Cadastra um novo item na mochila
// ----------------------------
void inserirItem(Item mochila[], int *total) {
    if (*total >= MAX_ITENS) {
        printf("Mochila cheia! Nao e possivel adicionar mais itens.\n");
        return;
    }

    Item novo;

    printf("\nDigite o nome do item: ");
    fgets(novo.nome, sizeof(novo.nome), stdin);
    novo.nome[strcspn(novo.nome, "\n")] = 0; // Remove o \n

    printf("Digite o tipo do item (arma, municao, cura...): ");
    fgets(novo.tipo, sizeof(novo.tipo), stdin);
    novo.tipo[strcspn(novo.tipo, "\n")] = 0;

    printf("Digite a quantidade: ");
    scanf("%d", &novo.quantidade);
    getchar();

    mochila[*total] = novo;
    (*total)++;

    printf("\n✅ Item adicionado com sucesso!\n");
    listarItens(mochila, *total);
}

// ----------------------------
// Função: removerItem
// Remove um item pelo nome (caso exista)
// ----------------------------
void removerItem(Item mochila[], int *total) {
    if (*total == 0) {
        printf("Mochila vazia! Nao ha itens para remover.\n");
        return;
    }

    char nomeBusca[30];
    printf("\nDigite o nome do item que deseja remover: ");
    fgets(nomeBusca, sizeof(nomeBusca), stdin);
    nomeBusca[strcspn(nomeBusca, "\n")] = 0;

    int encontrado = 0;
    for (int i = 0; i < *total; i++) {
        if (strcmp(mochila[i].nome, nomeBusca) == 0) {
            encontrado = 1;
            // Desloca os próximos itens para "tampar o buraco"
            for (int j = i; j < *total - 1; j++) {
                mochila[j] = mochila[j + 1];
            }
            (*total)--;
            printf("\n🗑️ Item '%s' removido com sucesso!\n", nomeBusca);
            break;
        }
    }

    if (!encontrado)
        printf("\nItem nao encontrado!\n");

    listarItens(mochila, *total);
}

// ----------------------------
// Função: listarItens
// Exibe todos os itens da mochila
// ----------------------------
void listarItens(Item mochila[], int total) {
    if (total == 0) {
        printf("\nMochila vazia.\n");
        return;
    }

    printf("\n==============================\n");
    printf("   ITENS NA MOCHILA (%d)\n", total);
    printf("==============================\n");

    for (int i = 0; i < total; i++) {
        printf("Item %d:\n", i + 1);
        printf("  Nome: %s\n", mochila[i].nome);
        printf("  Tipo: %s\n", mochila[i].tipo);
        printf("  Quantidade: %d\n", mochila[i].quantidade);
        printf("------------------------------\n");
    }
}

// ----------------------------
// Função: buscarItem
// Localiza e exibe um item específico
// ----------------------------
void buscarItem(Item mochila[], int total) {
    if (total == 0) {
        printf("Mochila vazia!\n");
        return;
    }

    char nomeBusca[30];
    printf("\nDigite o nome do item que deseja buscar: ");
    fgets(nomeBusca, sizeof(nomeBusca), stdin);
    nomeBusca[strcspn(nomeBusca, "\n")] = 0;

    int encontrado = 0;

    for (int i = 0; i < total; i++) {
        if (strcmp(mochila[i].nome, nomeBusca) == 0) {
            printf("\n✅ Item encontrado:\n");
            printf("  Nome: %s\n", mochila[i].nome);
            printf("  Tipo: %s\n", mochila[i].tipo);
            printf("  Quantidade: %d\n", mochila[i].quantidade);
            encontrado = 1;
            break;
        }
    }

    if (!encontrado)
        printf("\n❌ Item nao encontrado na mochila.\n");
}

// Struct Item:
// Representa um componente com nome, tipo, quantidade e prioridade (1 a 5).
// A prioridade indica a importância do item na montagem do plano de fuga.

// Enum CriterioOrdenacao:
// Define os critérios possíveis para a ordenação dos itens (nome, tipo ou prioridade).

// Vetor mochila:
// Armazena até 10 itens coletados.
// Variáveis de controle: numItens (quantidade atual), comparacoes (análise de desempenho), ordenadaPorNome (para controle da busca binária).

// limparTela():
// Simula a limpeza da tela imprimindo várias linhas em branco.

// exibirMenu():
// Apresenta o menu principal ao jogador, com destaque para status da ordenação.

// inserirItem():
// Adiciona um novo componente à mochila se houver espaço.
// Solicita nome, tipo, quantidade e prioridade.
// Após inserir, marca a mochila como "não ordenada por nome".

// removerItem():
// Permite remover um componente da mochila pelo nome.
// Se encontrado, reorganiza o vetor para preencher a lacuna.

// listarItens():
// Exibe uma tabela formatada com todos os componentes presentes na mochila.

// menuDeOrdenacao():
// Permite ao jogador escolher como deseja ordenar os itens.
// Utiliza a função insertionSort() com o critério selecionado.
// Exibe a quantidade de comparações feitas (análise de desempenho).

// insertionSort():
// Implementação do algoritmo de ordenação por inserção.
// Funciona com diferentes critérios de ordenação:
// - Por nome (ordem alfabética)
// - Por tipo (ordem alfabética)
// - Por prioridade (da mais alta para a mais baixa)

// buscaBinariaPorNome():
// Realiza busca binária por nome, desde que a mochila esteja ordenada por nome.
// Se encontrar, exibe os dados do item buscado.
// Caso contrário, informa que não encontrou o item.
