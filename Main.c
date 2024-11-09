#include "Funcoes.h"

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
                printf("Número de combustiveis na arvore: %d\n", contarArvore(raiz));
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
