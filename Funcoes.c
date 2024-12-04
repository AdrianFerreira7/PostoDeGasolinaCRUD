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
