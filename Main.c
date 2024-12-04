#include "Funcoes.h"

ArvBin* criarArvBin() {
    ArvBin* novaArvore = (ArvBin*)malloc(sizeof(ArvBin));
    novaArvore->raiz = NULL;
    return novaArvore;
}

int insere_ArvBin(ArvBin *arvore, Combustivel combustivel) {
    NoArv *novoNo = (NoArv*)malloc(sizeof(NoArv));
    if (!novoNo) return 0;
    novoNo->combustivel = combustivel;
    novoNo->esq = NULL;
    novoNo->dir = NULL;

    if (arvore->raiz == NULL) {
        arvore->raiz = novoNo;
        return 1;
    }

    NoArv *atual = arvore->raiz;
    NoArv *anterior = NULL;
    while (atual != NULL) {
        anterior = atual;
        if (combustivel.id < atual->combustivel.id) {
            atual = atual->esq;
        } else if (combustivel.id > atual->combustivel.id) {
            atual = atual->dir;
        } else {
            free(novoNo);
            return 0;
        }
    }

    if (combustivel.id < anterior->combustivel.id) {
        anterior->esq = novoNo;
    } else {
        anterior->dir = novoNo;
    }
    return 1;
}

NoArv* removerNo(NoArv *atual) {
    NoArv *no1, *no2;
    if (atual->esq == NULL) {
        no2 = atual->dir;
        free(atual);
        return no2;
    }
    no1 = atual;
    no2 = atual->esq;
    while (no2->dir != NULL) {
        no1 = no2;
        no2 = no2->dir;
    }
    if (no1 != atual) {
        no1->dir = no2->esq;
        no2->esq = atual->esq;
    }
    no2->dir = atual->dir;
    free(atual);
    return no2;
}

int remove_ArvBin(ArvBin *arvore, int id) {
    if (arvore == NULL || arvore->raiz == NULL) return 0;
    NoArv *atual = arvore->raiz;
    NoArv *anterior = NULL;

    while (atual != NULL) {
        if (id == atual->combustivel.id) {
            if (atual == arvore->raiz)
                arvore->raiz = removerNo(atual);
            else {
                if (anterior->esq == atual)
                    anterior->esq = removerNo(atual);
                else
                    anterior->dir = removerNo(atual);
            }
            return 1;
        }
        anterior = atual;
        if (id < atual->combustivel.id)
            atual = atual->esq;
        else
            atual = atual->dir;
    }
    return 0;
}

int consulta_ArvBin(ArvBin *arvore, int id) {
    NoArv *atual = arvore->raiz;
    while (atual != NULL) {
        if (id == atual->combustivel.id) {
            exibirCombustivel(atual->combustivel);
            return 1;
        }
        if (id < atual->combustivel.id) {
            atual = atual->esq;
        } else {
            atual = atual->dir;
        }
    }
    return 0;
}

int atualizar_ArvBin(ArvBin *arvore, int id, Combustivel novoCombustivel) {
    if (arvore == NULL || arvore->raiz == NULL) return 0;
    NoArv *atual = arvore->raiz;

    while (atual != NULL) {
        if (id == atual->combustivel.id) {
            atual->combustivel = novoCombustivel;
            return 1;
        }
        if (id < atual->combustivel.id)
            atual = atual->esq;
        else
            atual = atual->dir;
    }
    return 0;
}

int contarArvore(ArvBin *arvore) {
    return contarNo(arvore->raiz);
}

int contarNo(NoArv *no) {
    if (no == NULL) return 0;
    return 1 + contarNo(no->esq) + contarNo(no->dir);
}

int altura_ArvBin(ArvBin *arvore) {
    return alturaNo(arvore->raiz);
}

int alturaNo(NoArv *no) {
    if (no == NULL) return -1;
    int alturaEsq = alturaNo(no->esq);
    int alturaDir = alturaNo(no->dir);
    return (alturaEsq > alturaDir ? alturaEsq : alturaDir) + 1;
}

void libera_ArvBin(ArvBin *arvore) {
    liberaNo(arvore->raiz);
    free(arvore);
}

void liberaNo(NoArv *no) {
    if (no == NULL) return;
    liberaNo(no->esq);
    liberaNo(no->dir);
    free(no);
}

void exibirCombustivel(Combustivel c) {
    printf("ID: %d\n", c.id);
    printf("Nome: %s\n", c.nome);
    printf("Preco por litro: R$ %.2f\n", c.preco);
}

void listarCombustiveis(NoArv *raiz) {
    if (raiz != NULL) {
        listarCombustiveis(raiz->esq);
        exibirCombustivel(raiz->combustivel);
        listarCombustiveis(raiz->dir);
    }
}


int main() {
    ArvBin *raiz = criarArvBin();
    int opcao, id;
    Combustivel novoCombustivel;

    do {
        #ifdef _WIN32
            system("cls");
        #else
            system("clear");
        #endif

        printf("\n----- Menu de Operacoes -----\n");
        printf("1. Inserir tipo de combustivel\n");
        printf("2. Remover tipo de combustivel\n");
        printf("3. Consultar tipo de combustivel\n");
        printf("4. Atualizar tipo de combustivel\n");
        printf("5. Contar numero de combustiveis\n");
        printf("6. Calcular altura da arvore\n");
        printf("7. Listar todos os combustiveis\n");
        printf("8. Liberar arvore e sair\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                printf("Digite o ID do combustivel: ");
                scanf("%d", &novoCombustivel.id);
                printf("Digite o nome do combustivel: ");
                scanf(" %[^\n]%*c", novoCombustivel.nome);
                printf("Digite o preco por litro: R$ ");
                scanf("%f", &novoCombustivel.preco);

                if (insere_ArvBin(raiz, novoCombustivel)) {
                    printf("Combustivel inserido com sucesso!\n");
                } else {
                    printf("Falha ao inserir. ID ja existente.\n");
                }
                break;

            case 2:
                printf("Digite o ID do combustivel a ser removido: ");
                scanf("%d", &id);
                if (remove_ArvBin(raiz, id)) {
                    printf("Combustivel removido com sucesso!\n");
                } else {
                    printf("Combustivel nao encontrado.\n");
                }
                break;

            case 3:
                printf("Digite o ID do combustivel a ser consultado: ");
                scanf("%d", &id);
                if (!consulta_ArvBin(raiz, id)) {
                    printf("Combustivel nao encontrado.\n");
                }
                break;

            case 4:
                printf("Digite o ID do combustivel a ser atualizado: ");
                scanf("%d", &id);
                printf("Digite o novo nome do combustivel: ");
                scanf(" %[^\n]%*c", novoCombustivel.nome);
                printf("Digite o novo preco por litro: R$ ");
                scanf("%f", &novoCombustivel.preco);
                if (atualizar_ArvBin(raiz, id, novoCombustivel)) {
                    printf("Combustivel atualizado com sucesso!\n");
                } else {
                    printf("Combustivel nao encontrado.\n");
                }
                break;

            case 5:
                printf("N�mero de combustiveis na arvore: %d\n", contarArvore(raiz));
                break;

            case 6:
                printf("Altura da arvore: %d\n", altura_ArvBin(raiz));
                break;

            case 7:
                printf("Listando todos os combustiveis cadastrados:\n");
                listarCombustiveis(raiz->raiz);
                break;

            case 8:
                libera_ArvBin(raiz);
                printf("arvore liberada e programa encerrado.\n");
                break;

            default:
                printf("Opcao invalida!\n");
        }

        printf("\nPressione qualquer tecla para continuar...");
        getchar();
        getchar();

    } while (opcao != 8);

    return 0;
}
