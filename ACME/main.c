#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "acme.h"

int main()
{
    Lista *li = NULL;
    int x, identificador, quantidade, escolha = 0;
    char nome[80];

    CLIENTE al_consulta, al;

    if ((li = criaLista()) == NULL)
    {
        abortaPrograma();
    }

    FILE *arquivo = NULL;
    arquivo = abriArquivo(li);

    printf("\n\n");
    printf("##########################################################################################################################\n");
    printf("Bem vindo ao sistema de gerenciamento de contatos\n\n");
    printf("Desenvolvido por: \n");
    printf("Christopher Willians - Gu3054047\n");
    printf("Gabriel Vitor - Gu3054446\n");
    printf("##########################################################################################################################\n");

    while (escolha != 7)
    {
        printf("\nEscolha uma das opcoes:\n\n");
        printf("1 - Incluir um novo contato\n");
        printf("2 - Relatorio de todos os contatos\n");
        printf("3 - Buscar contato pelo identificador\n");
        printf("4 - Buscar contatos pelo nome\n");
        printf("5 - Editar as informacoes de um contato\n");
        printf("6 - Excluir um contato com base no identificador\n");
        printf("7 - Sair\n\n");
        printf("Digite a sua escolha: ");
        scanf("%d", &escolha);
        getchar();

        switch (escolha)
        {

        case 1:
            printf("\nDigite a quantidade de contatos que deseja inserir: ");
            scanf(" %d", &quantidade);
            getchar();

            for (int i = 0; i < quantidade; i++)
            {
                printf("\n");
                al = coletadados(li, 0);
                x = insereOrdenado(li, al);
                if (x)
                {
                    printf("\nAluno %d inserido ordenado com sucesso!", x);
                    printf("\n\n");
                    system("pause");
                    system("cls");                    
                }
                else
                {
                    printf("\nnao foi possivel inserir ordenado");
                    printf("\n\n");
                    system("pause");
                    system("cls");       
                }
            }
            break;

        case 2:
            listarTodos(li);
            printf("\n\n");
            system("pause");
            system("cls");
            break;

        case 3:
            printf("\n\n");

            printf("Digite a identificador do aluno que deseja buscar: ");
            scanf("%d", &identificador);
            getchar();

            x = consultaIdentificador(li, identificador, &al_consulta);
            if (x)
            {
                printf("\n\n");
                relatorio(&al_consulta);
                printf("\n\n");
                system("pause");
                system("cls"); 
            }
            else
            {
                printf("\nidentificador %d nao existe.", 110);
                printf("\n\n");
                system("pause");
                system("cls"); 
            }
            break;

        case 4:
            printf("\n\n");

            printf("Digite o nome do aluno que deseja buscar: ");
            fgets(nome, sizeof(nome), stdin);

            if (strlen(nome) > 0 && nome[strlen(nome) - 1] == '\n')
            {
                nome[strlen(nome) - 1] = '\0';
            }

            consultaNome(li, nome);

            printf("\n\n");
            system("pause");
            system("cls"); 
            break;

        case 5:
            printf("\nDigite a identificador do aluno que deseja editar: ");
            scanf("%d", &identificador);
            getchar();

            editarCliente(li, identificador);
            printf("\n\n");
            system("pause");
            system("cls"); 
            break;

        case 6:
            printf("\nDigite a identificador do aluno que deseja excluir: ");
            scanf("%d", &identificador);
            getchar();

            x = removeOrdenado(li, identificador);
            if (x)
            {
                printf("\nAluno %d removido ordenado com sucesso!", x);
                printf("\n\n");
                system("pause");
                system("cls"); 
            }
            else
            {
                printf("\nnao foi possivel remover ordenado");
                printf("\n\n");
                system("pause");
                system("cls");
            }
            break;

        case 7:
            printf("\n\n");
            printf("Fim do programa");
            printf("\n\n"); 
            break;

        default:
            printf("\n\n");
            printf("Opcao invalida");
            printf("\n\n");
            system("pause");
            system("cls");
            break;
        }
    }

    salvarArquivo(li);
    
    apagaLista(li);

    printf("\n\n\n");
    system("pause");
    system("cls");
    return 0;
}
