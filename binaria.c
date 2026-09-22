#include <stdio.h>
#include <stdlib.h>

/*
    ============================================================
    ÁRVORE DE BUSCA BINÁRIA (BST)
    ============================================================

    Regra da BST:
    - Valores menores ficam à esquerda.
    - Valores maiores ficam à direita.
    - Valores repetidos serão ignorados.
*/


/* ============================================================
   ESTRUTURA DO NÓ
   ============================================================ */

typedef struct No {
    int inteiro;
    struct No *esquerda;
    struct No *direita;
} No;


/* ============================================================
   FUNÇÃO PARA CRIAR UM NOVO NÓ
   ============================================================ */

No *criarNo(int valor) {

    No *novoNo = (No *) malloc(sizeof(No));

    if (novoNo == NULL) {
        printf("Erro: nao foi possivel alocar memoria.\n");
        return NULL;
    }

    novoNo->inteiro = valor;
    novoNo->esquerda = NULL;
    novoNo->direita = NULL;

    return novoNo;
}


/* ============================================================
   FUNÇÃO DE INSERÇÃO
   ============================================================ */

No *inserir(No *raiz, int valor) {

    /* Se chegamos a uma posição vazia, criamos o nó */
    if (raiz == NULL) {
        return criarNo(valor);
    }

    /* Valor menor: vai para a esquerda */
    if (valor < raiz->inteiro) {
        raiz->esquerda = inserir(raiz->esquerda, valor);
    }

    /* Valor maior: vai para a direita */
    else if (valor > raiz->inteiro) {
        raiz->direita = inserir(raiz->direita, valor);
    }

    /*
        Valor igual:
        valores repetidos serão ignorados.
    */

    return raiz;
}


/* ============================================================
   FUNÇÃO DE BUSCA
   ============================================================ */

No *buscar(No *raiz, int valor) {

    /* Árvore vazia ou valor não encontrado */
    if (raiz == NULL) {
        return NULL;
    }

    /* Encontrou o valor */
    if (valor == raiz->inteiro) {
        return raiz;
    }

    /* Procura na esquerda */
    if (valor < raiz->inteiro) {
        return buscar(raiz->esquerda, valor);
    }

    /* Procura na direita */
    return buscar(raiz->direita, valor);
}


/* ============================================================
   FUNÇÃO PARA ENCONTRAR O MENOR VALOR
   ============================================================ */

No *menorNo(No *raiz) {

    No *atual = raiz;

    /*
        O menor elemento de uma BST está no
        nó mais à esquerda.
    */
    while (atual != NULL && atual->esquerda != NULL) {
        atual = atual->esquerda;
    }

    return atual;
}


/* ============================================================
   FUNÇÃO DE REMOÇÃO
   ============================================================ */

No *remover(No *raiz, int valor) {

    /* Caso o valor não esteja na árvore */
    if (raiz == NULL) {
        return NULL;
    }

    /* Procurando o valor na esquerda */
    if (valor < raiz->inteiro) {

        raiz->esquerda = remover(raiz->esquerda, valor);
    }

    /* Procurando o valor na direita */
    else if (valor > raiz->inteiro) {

        raiz->direita = remover(raiz->direita, valor);
    }

    /*
        Encontramos o nó que deve ser removido.
    */
    else {

        /* ====================================================
           CASO 1: NÓ FOLHA
           Não possui filhos.
           ==================================================== */

        if (raiz->esquerda == NULL &&
            raiz->direita == NULL) {

            free(raiz);
            return NULL;
        }


        /* ====================================================
           CASO 2: NÓ COM APENAS FILHO DIREITO
           ==================================================== */

        if (raiz->esquerda == NULL) {

            No *auxiliar = raiz->direita;

            free(raiz);

            return auxiliar;
        }


        /* ====================================================
           CASO 2: NÓ COM APENAS FILHO ESQUERDO
           ==================================================== */

        if (raiz->direita == NULL) {

            No *auxiliar = raiz->esquerda;

            free(raiz);

            return auxiliar;
        }


        /* ====================================================
           CASO 3: NÓ COM DOIS FILHOS

           Utilizamos o sucessor in-order:
           menor elemento da subárvore direita.
           ==================================================== */

        No *sucessor = menorNo(raiz->direita);

        /* Copia o valor do sucessor para o nó atual */
        raiz->inteiro = sucessor->inteiro;

        /*
            Remove o sucessor da subárvore direita.
        */
        raiz->direita = remover(raiz->direita, sucessor->inteiro);
    }

    return raiz;
}


/* ============================================================
   PERCURSO PRÉ-ORDEM
   ============================================================ */

void preOrdem(No *raiz) {

    if (raiz != NULL) {

        printf("%d ", raiz->inteiro);

        preOrdem(raiz->esquerda);

        preOrdem(raiz->direita);
    }
}


/* ============================================================
   PERCURSO EM ORDEM
   ============================================================ */

void emOrdem(No *raiz) {

    if (raiz != NULL) {

        emOrdem(raiz->esquerda);

        printf("%d ", raiz->inteiro);

        emOrdem(raiz->direita);
    }
}


/* ============================================================
   PERCURSO PÓS-ORDEM
   ============================================================ */

void posOrdem(No *raiz) {

    if (raiz != NULL) {

        posOrdem(raiz->esquerda);

        posOrdem(raiz->direita);

        printf("%d ", raiz->inteiro);
    }
}


/* ============================================================
   FUNÇÃO PARA LIBERAR TODA A ÁRVORE
   ============================================================ */

void liberarArvore(No *raiz) {

    if (raiz != NULL) {

        liberarArvore(raiz->esquerda);

        liberarArvore(raiz->direita);

        free(raiz);
    }
}


/* ============================================================
   SUBMENU DE PERCURSOS
   ============================================================ */

void menuPercursos(No *raiz) {

    int opcao;

    do {

        printf("\n===== PERCORRER ARVORE =====\n");
        printf("1 - Pre-ordem\n");
        printf("2 - Em ordem\n");
        printf("3 - Pos-ordem\n");
        printf("0 - Voltar\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);

        switch (opcao) {

            case 1:
                printf("\nPre-ordem: ");
                preOrdem(raiz);
                printf("\n");
                break;

            case 2:
                printf("\nEm ordem: ");
                emOrdem(raiz);
                printf("\n");
                break;

            case 3:
                printf("\nPos-ordem: ");
                posOrdem(raiz);
                printf("\n");
                break;

            case 0:
                break;

            default:
                printf("\nOpcao invalida.\n");
        }

    } while (opcao != 0);
}


/* ============================================================
   FUNÇÃO PRINCIPAL
   ============================================================ */

int main() {

    No *raiz = NULL;

    int opcao;
    int valor;

    do {

        printf("\n====================================\n");
        printf("       ARVORE DE BUSCA BINARIA\n");
        printf("====================================\n");
        printf("1 - Inserir valor\n");
        printf("2 - Buscar valor\n");
        printf("3 - Remover valor\n");
        printf("4 - Percorrer arvore\n");
        printf("0 - Sair\n");
        printf("Escolha uma opcao: ");

        scanf("%d", &opcao);

        switch (opcao) {

            case 1:

                printf("Digite o valor a inserir: ");
                scanf("%d", &valor);

                if (buscar(raiz, valor) != NULL) {

                    printf("O valor %d ja existe na arvore.\n", valor);

                } else {

                    raiz = inserir(raiz, valor);

                    printf("Valor %d inserido com sucesso.\n", valor);
                }

                break;


            case 2:

                printf("Digite o valor a buscar: ");
                scanf("%d", &valor);

                if (buscar(raiz, valor) != NULL) {

                    printf("O valor %d esta presente na arvore.\n", valor);

                } else {

                    printf("O valor %d nao esta presente na arvore.\n", valor);
                }

                break;


            case 3:

                printf("Digite o valor a remover: ");
                scanf("%d", &valor);

                if (buscar(raiz, valor) == NULL) {

                    printf("O valor %d nao foi encontrado na arvore.\n", valor);

                } else {

                    raiz = remover(raiz, valor);

                    printf("Valor %d removido com sucesso.\n", valor);
                }

                break;


            case 4:

                menuPercursos(raiz);

                break;


            case 0:

                liberarArvore(raiz);

                printf("\nMemoria liberada.\n");
                printf("Programa encerrado.\n");

                break;


            default:

                printf("\nOpcao invalida.\n");
        }

    } while (opcao != 0);

    return 0;
}