#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "acme.h"

// struct para armazenar os dados dos clientes e a struct elemento para armazenar os dados da struct cliente e o endereço da proxima struct
struct elemento
{
    CLIENTE dados;
    struct elemento *prox;
}; // struct Lista

typedef struct elemento ELEM;

// ################################################## FUNÇÕES AUXILIARES ##########################################################

// Aqui estão as funções auxiliares que são utilizadas para a manipulação de strings e para a abertura e fechamento de arquivos.

/* Função para a criação da lista:
Aqui é alocado espaço na memória para a lista e é feita a verificação se a lista foi alocada corretamente.*/

Lista *criaLista()
{
    Lista *li;
    li = (Lista *)malloc(sizeof(Lista));
    if (li != NULL)
    {
        *li = NULL;
    }
    return li;
}

/* Função para abrir o arquivo:
Aqui é aberto o arquivo clientes.bin e é feita a verificação se o arquivo foi aberto corretamente, caso o arquivo não exista, ele é criado.*/

FILE *abriArquivo(Lista *li)
{
    FILE *arquivo = fopen("clientes.bin", "rb");

    if (arquivo == NULL)
    {
        printf("Arquivo inexistente, abrindo sem dados\n");

        return arquivo;
    }

    CLIENTE cliente;
    while (fread(&cliente, sizeof(CLIENTE), 1, arquivo) == 1)
    {
        insereOrdenado(li, cliente);
    }

    return arquivo;
}

/* Função de encerramento do programa:
Aqui chamamos essa função quando é verificado que a lista não foi alocada corretamente*/

void abortaPrograma()
{
    printf("ERRO! Lista nao foi alocado, ");
    printf("programa sera encerrado....\n\n\n");
    system("pause");
    exit(1);
}

/* Função para verificar se a lista está cheia:
Embora não exista o conceito de lista cheia em uma Lista sequencial(uma vez que o limite é a memoria do computador),
colocamos essa função por padrão*/
int listaCheia(Lista *li)
{
    if (li == NULL)
    {
        abortaPrograma();
    }
    return 0;
}

/* Função para verificar se a lista está vazia:
Aqui verificamos se a lista tem algum elemento*/
int listaVazia(Lista *li)
{
    if (li == NULL)
    {
        abortaPrograma();
    }
    if (*li == NULL)
    {
        return 1;
    }
    return 0;
}

/* Função para converter o a string em minuscula:
Essa é uma função auxiliar para as funções de busca de usuarios com o mesmo nome, uma vez que o C é case sensitive */
void converteNome(char nome[])
{
    for (int i = 0; i < strlen(nome); i++)
    {
        nome[i] = tolower(nome[i]);
    }
}

/* Função de exibição:
Essa é uma função auxiliar para a maioria das outras funções, uma vez que utilizamos ela para exibição dos dados */
void relatorio(CLIENTE *al)
{
    printf("\n\nIdentificador: %d", al->identificador);
    printf("\nNome: %s", al->nome);
    printf("\nEmpresa: %s", al->empresa);
    printf("\nDepartamento: %s", al->departamento);
    printf("\nTelefone: %s", al->telefone);
    printf("\nCelular: %s", al->celular);
    printf("\nEmail: %s", al->email);
}

/* Função contra Duplicidade de usuarios na lista:
Essa é uma função auxilizar para função de inserção de novos usuarios, ela é usada para garantir que não seja registrado
usuario com identificares repitidos*/
int confereDupllicidade(Lista *li, int id)
{
    if (li == NULL)
    {
        abortaPrograma();
    }
    if (listaVazia(li))
    {
        return 1;
    }

    ELEM *no = *li;
    while (no != NULL)
    {
        if (no->dados.identificador == id)
        {
            return 0;
        }
        no = no->prox;
    }

    return 1;
}

/* Funçã de encerramento da lista:
Essa função é usada para encerrar a lista e liberar o bloco de memória alocada para ela.*/
void apagaLista(Lista *li)
{
    if (li != NULL)
    {
        ELEM *no;
        while ((*li) != NULL)
        {
            no = *li;
            *li = (*li)->prox; // anda para a proxima estrutura sozinho
            free(no);
        }
        free(li);
    }
}

// ################################################## FUNÇÕES PRINCIPAIS ##########################################################

// Aqui estão as funções principais que são usadas para a manipulação de dados no programa.

/* Função de coleta de dados:
Essa função coleta os dados dos clientes que serão inseridos na lista, antes de inserir verifica se há um usuario existente
com o mesmo identificador do usuario a ser posto na lista.*/
struct cliente coletadados(Lista *li, int id)
{

    struct cliente al1;
    int verificador = 0;

    if (id != 0)
    {
        al1.identificador = id;
        verificador = 1;
    }
    while (verificador == 0)
    {

        printf("\nDigite o identificador (id) do cliente:");
        scanf("%d", &al1.identificador);
        getchar();

        verificador = confereDupllicidade(li, al1.identificador);
        if (verificador == 0)
        {
            printf("\n\nIdentificador ja existente, digite outro identificador.\n\n");
        }
    }

    printf("\nDigite o nome do cliente:");
    fgets(al1.nome, sizeof(al1.nome), stdin);
    al1.nome[strcspn(al1.nome, "\n")] = '\0';

    printf("\nDigite a empresa do cliente:");
    fgets(al1.empresa, sizeof(al1.empresa), stdin);
    al1.empresa[strcspn(al1.empresa, "\n")] = '\0';

    printf("\nDigite o departamento do cliente:");
    fgets(al1.departamento, sizeof(al1.departamento), stdin);
    al1.departamento[strcspn(al1.departamento, "\n")] = '\0';

    printf("\nDigite o telefone do cliente:");
    fgets(al1.telefone, sizeof(al1.telefone), stdin);
    al1.telefone[strcspn(al1.telefone, "\n")] = '\0';

    printf("\nDigite o celular do cliente:");
    fgets(al1.celular, sizeof(al1.celular), stdin);
    al1.celular[strcspn(al1.celular, "\n")] = '\0';

    printf("\nDigite o email do cliente:");
    fgets(al1.email, sizeof(al1.email), stdin);
    al1.email[strcspn(al1.email, "\n")] = '\0';

    return al1;
}

/* Função de inserção ordenada:
Essa função insere os clientes de forma ordenada com base no valor do campo identificador da struct cliente, de forma simples ela
copiar os dados de uma struct fornecida para a struct dados dentro da struct elemento, e endereça o ponteiro do tipo strcut para a
proxima struct da lista ou para NULL*/
int insereOrdenado(Lista *li, CLIENTE al)
{
    if (li == NULL)
    {
        abortaPrograma();
    }
    ELEM *no = (ELEM *)malloc(sizeof(ELEM));
    if (no == NULL)
    {
        return 0;
    }
    no->dados = al;
    if (listaVazia(li))
    {
        no->prox = (*li);
        *li = no;
        return al.identificador;
    }
    else
    {
        ELEM *ant, *atual = *li;
        while (atual != NULL && atual->dados.identificador < al.identificador)
        {
            ant = atual;
            atual = atual->prox;
        }
        if (atual == *li)
        {
            no->prox = (*li);
            *li = no;
        }
        else
        {
            no->prox = ant->prox;
            ant->prox = no;
        }
        return al.identificador;
    }
}

/* Função de remoção ordenada:
Essa função funciona de forma semelhante a de inserção, a diferença é que ela varre a lista é encontrar a strcut com o
identificador igual ao da struct fornecida e apaga ela, após isso reordena os proximos elementos da lista*/
int removeOrdenado(Lista *li, int id)
{
    if (li == NULL)
    {
        abortaPrograma();
    }
    if (listaVazia(li))
    {
        return 0;
    }

    int identificador;
    ELEM *ant, *no = *li;
    while (no != NULL && no->dados.identificador != id)
    {
        ant = no;
        no = no->prox;
    }
    if (no == NULL)
    {
        return 0;
    }
    if (no == *li)
    {
        *li = no->prox;
    }
    else
    {
        ant->prox = no->prox;
    }
    identificador = no->dados.identificador;
    free(no);
    return identificador;
}

/* Função para consulta com base no identificador:
Essa função varre toda lista até encontrar a struct que o identificador igual ao fornecido e copiar os dados dessa struct
para dentro do endereço de memória da struct de exibição*/
int consultaIdentificador(Lista *li, int id, CLIENTE *al)
{
    if (li == NULL)
    {
        abortaPrograma();
    }
    if (listaVazia(li))
    {
        return 0;
    }

    ELEM *no = *li;
    while (no != NULL && no->dados.identificador != id)
    {
        no = no->prox;
    }
    if (no == NULL)
    {
        return 0;
    }
    *al = no->dados;
    return 1;
}

/* Função para consulta com base no nome:
Essa função varre toda lista até encontrar a struct que o nome igual ao fornecido e exibe os dados dessa struct
(caso haja mais de um cliente com o mesmo nome exibe os exibe também), caso não encontre nenhum usuario com o nome
fornecido, exibe uma mensagem de erro*/
void consultaNome(Lista *li, char nome[])
{
    if (li == NULL)
    {
        abortaPrograma();
    }
    if (listaVazia(li))
    {
        return;
    }
    if (nome == NULL)
    {
        printf("\n\nNome invalido\n\n");
        return;
    }

    converteNome(nome);

    ELEM *no = *li;
    int tamanho = 0;
    char nomePesquisa[80];

    while (no != NULL)
    {

        strcpy(nomePesquisa, no->dados.nome);

        converteNome(nomePesquisa);
        if (strstr(nomePesquisa, nome) != NULL)
        {

            tamanho++;

            printf("\n\nCliente %d\n\n", tamanho);

            relatorio(&no->dados);
        }
        no = no->prox;
    }

    if (tamanho == 0)
    {
        printf("\n\nNenhum cliente encontrado com o nome %s\n\n", nome);
    }
    else
    {
        printf("\n\nTotal de clientes encontrados: %d\n\n", tamanho);
    }
}

/* Função para listar todos os clientes:
Essa função percorre toda a lista dada e exibe os dados de cada struct de cliente
chamando a função de relatorio para cada item*/
void listarTodos(Lista *li)
{
    if (li == NULL)
    {
        abortaPrograma();
    }
    if (listaVazia(li))
    {
        printf("\n\nLista vazia\n\n");
        return;
    }

    ELEM *no = *li;
    int tamanho = 0;

    while (no != NULL)
    {

        tamanho++;

        printf("\n\n\nCliente %d", tamanho);

        relatorio(&no->dados);

        no = no->prox;
    }

    printf("\n\nTotal de clientes encontrados: %d\n\n", tamanho);
}

/* Função para editar um cliente:
Essa função varre toda a lista até encontrar a struct que o identificador igual ao fornecido e exibe os dados dessa struct
para o usuario confirmar se realmente quer editar, caso o usuario confirme, ele coletará os novos dados, excluirá o usuario
antigo e inserirá o novo usuario com os novos dados*/
void editarCliente(Lista *li, int id)
{
    if (li == NULL)
    {
        abortaPrograma();
    }
    if (listaVazia(li))
    {
        return;
    }

    CLIENTE al;
    int x;
    ELEM *no = *li;
    while (no != NULL && no->dados.identificador != id)
    {
        no = no->prox;
    }
    if (no == NULL)
    {
        printf("\n\nCliente nao encontrado\n\n");
        return;
    }

    printf("\n\n");
    relatorio(&no->dados);

    printf("\n\nDeseja editar esse cliente? (1 - Sim / 0 - Nao): ");
    scanf("%d", &x);
    getchar();

    if (x == 1)
    {
        al = coletadados(li, no->dados.identificador);
        removeOrdenado(li, id);
        insereOrdenado(li, al);
        printf("\n\nCliente editado com sucesso!\n\n");
    }
    else
    {
        printf("\n\nCliente nao editado\n\n");
    }
}

/* Função para salvar os dados no arquivo:
Essa função salva os dados da lista no arquivo clientes.bin, ela abre o arquivo em modo de escrita e salva os dados
de cada struct cliente no arquivo*/
void salvarArquivo(Lista *li)
{
    if (li == NULL)
    {
        abortaPrograma();
    }
    if (listaVazia(li))
    {
        return;
    }

    FILE *arquivo = fopen("clientes.bin", "wb");

    if (arquivo == NULL)
    {
        printf("Erro ao abrir o arquivo\n");
        exit(1);
    }

    ELEM *no = *li;

    while (no != NULL)
    {
        fwrite(&no->dados, sizeof(CLIENTE), 1, arquivo);
        no = no->prox;
    }

    fclose(arquivo);
}