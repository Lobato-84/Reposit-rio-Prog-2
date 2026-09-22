#include <stdio.h>
#include <stdlib.h>

/* ---------- Estrutura do nó ---------- */
typedef struct No {
    int valor;
    struct No *anterior;
    struct No *proximo;
} No;

/* ---------- Lista (apenas o ponteiro para a cabeça) ---------- */
No *cabeca = NULL;

/* Cria um novo nó */
No *criarNo(int valor) {
    No *novo = (No *) malloc(sizeof(No));
    if (novo == NULL) {
        printf("Erro ao alocar memoria!\n");
        exit(1);
    }
    novo->valor = valor;
    novo->anterior = NULL;
    novo->proximo = NULL;
    return novo;
}

/* ---------- Inserir no início ---------- */
void inserirInicio(int valor) {
    No *novo = criarNo(valor);
    if (cabeca == NULL) {
        cabeca = novo;
    } else {
        novo->proximo = cabeca;
        cabeca->anterior = novo;
        cabeca = novo;
    }
    printf("Valor %d inserido no inicio.\n", valor);
}

/* ---------- Inserir no final ---------- */
void inserirFinal(int valor) {
    No *novo = criarNo(valor);
    if (cabeca == NULL) {
        cabeca = novo;
    } else {
        No *atual = cabeca;
        while (atual->proximo != NULL) {
            atual = atual->proximo;
        }
        atual->proximo = novo;
        novo->anterior = atual;
    }
    printf("Valor %d inserido no final.\n", valor);
}

/* ---------- Inserir em posição específica (posição inicial = 1) ---------- */
void inserirPosicao(int valor, int posicao) {
    if (posicao <= 0) {
        printf("Posicao invalida!\n");
        return;
    }
    if (posicao == 1) {
        inserirInicio(valor);
        return;
    }

    No *atual = cabeca;
    int contador = 1;
    while (atual != NULL && contador < posicao - 1) {
        atual = atual->proximo;
        contador++;
    }

    if (atual == NULL) {
        printf("Posicao %d fora dos limites da lista!\n", posicao);
        return;
    }

    if (atual->proximo == NULL) {
        inserirFinal(valor);
        return;
    }

    No *novo = criarNo(valor);
    novo->proximo = atual->proximo;
    novo->anterior = atual;
    atual->proximo->anterior = novo;
    atual->proximo = novo;
    printf("Valor %d inserido na posicao %d.\n", valor, posicao);
}

/* ---------- Remover nó de posição específica ---------- */
void remover(int posicao) {
    if (cabeca == NULL) {
        printf("Lista vazia! Nada para remover.\n");
        return;
    }
    if (posicao <= 0) {
        printf("Posicao invalida!\n");
        return;
    }

    No *atual = cabeca;
    int contador = 1;
    while (atual != NULL && contador < posicao) {
        atual = atual->proximo;
        contador++;
    }

    if (atual == NULL) {
        printf("Posicao %d nao encontrada na lista!\n", posicao);
        return;
    }

    if (atual->anterior != NULL) {
        atual->anterior->proximo = atual->proximo;
    } else {
        cabeca = atual->proximo; /* removendo a cabeça */
    }

    if (atual->proximo != NULL) {
        atual->proximo->anterior = atual->anterior;
    }

    printf("Valor %d removido da posicao %d.\n", atual->valor, posicao);
    free(atual);
}

/* ---------- Buscar valor na lista ---------- */
int buscar(int valor) {
    No *atual = cabeca;
    int posicao = 1;
    while (atual != NULL) {
        if (atual->valor == valor) {
            return posicao;
        }
        atual = atual->proximo;
        posicao++;
    }
    return -1; /* não encontrado */
}

/* ---------- Listar todos os elementos ---------- */
void listar() {
    if (cabeca == NULL) {
        printf("Lista vazia!\n");
        return;
    }

    No *atual = cabeca;
    int posicao = 1;
    printf("\n--- Conteudo da lista ---\n");
    while (atual != NULL) {
        printf("Posicao %d | Valor: %d | Endereco: %p | Anterior: %p | Proximo: %p\n",
               posicao,
               atual->valor,
               (void *) atual,
               (void *) atual->anterior,
               (void *) atual->proximo);
        atual = atual->proximo;
        posicao++;
    }
    printf("-------------------------\n");
}

/* ---------- Liberar toda a memória da lista ---------- */
void liberarLista() {
    No *atual = cabeca;
    while (atual != NULL) {
        No *proximo = atual->proximo;
        free(atual);
        atual = proximo;
    }
    cabeca = NULL;
}

/* ---------- Menu principal ---------- */
int main() {
    int opcao, valor, posicao, resultado;

    do {
        printf("\n===== MENU - LISTA DUPLAMENTE ENCADEADA =====\n");
        printf("1. Inserir no inicio\n");
        printf("2. Inserir em posicao especifica\n");
        printf("3. Inserir no final\n");
        printf("4. Remover de uma posicao\n");
        printf("5. Buscar valor\n");
        printf("6. Listar elementos\n");
        printf("0. Sair\n");
        printf("Escolha uma opcao: ");

        if (scanf("%d", &opcao) != 1) {
            printf("Entrada invalida!\n");
            /* limpa buffer de entrada */
            while (getchar() != '\n');
            continue;
        }

        switch (opcao) {
            case 1:
                printf("Digite o valor a inserir: ");
                scanf("%d", &valor);
                inserirInicio(valor);
                break;

            case 2:
                printf("Digite o valor a inserir: ");
                scanf("%d", &valor);
                printf("Digite a posicao (inicia em 1): ");
                scanf("%d", &posicao);
                inserirPosicao(valor, posicao);
                break;

            case 3:
                printf("Digite o valor a inserir: ");
                scanf("%d", &valor);
                inserirFinal(valor);
                break;

            case 4:
                printf("Digite a posicao a remover (inicia em 1): ");
                scanf("%d", &posicao);
                remover(posicao);
                break;

            case 5:
                printf("Digite o valor a buscar: ");
                scanf("%d", &valor);
                resultado = buscar(valor);
                if (resultado != -1) {
                    printf("Valor %d encontrado na posicao %d.\n", valor, resultado);
                } else {
                    printf("Valor %d nao encontrado na lista.\n", valor);
                }
                break;

            case 6:
                listar();
                break;

            case 0:
                printf("Saindo do programa...\n");
                break;

            default:
                printf("Opcao invalida! Tente novamente.\n");
        }

    } while (opcao != 0);

    liberarLista();
    return 0;
}
