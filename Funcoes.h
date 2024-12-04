#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define FUNCOES.H


typedef struct Combustivel {
    int id;
    char nome[30];
    float preco;
} Combustivel;

typedef struct NoArv {
    Combustivel combustivel;
    struct NoArv *esq;
    struct NoArv *dir;
} NoArv;

typedef struct ArvBin {
    NoArv *raiz;
} ArvBin;

ArvBin* criarArvBin();
int insere_ArvBin(ArvBin *raiz, Combustivel combustivel);
int remove_ArvBin(ArvBin *raiz, int id);
int consulta_ArvBin(ArvBin *raiz, int id);
int atualizar_ArvBin(ArvBin *raiz, int id, Combustivel novoCombustivel);
int contarArvore(ArvBin *raiz);
int altura_ArvBin(ArvBin *raiz);
void libera_ArvBin(ArvBin *raiz);
void exibirCombustivel(Combustivel c);
void listarCombustiveis(NoArv *raiz);
