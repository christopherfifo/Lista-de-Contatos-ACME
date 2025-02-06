# Documentação do Projeto ACME

## Introdução
O **ACME** é um sistema de gerenciamento de contatos desenvolvido em **C**, utilizando **listas dinâmicas** para manipulação dos dados e **arquivos binários** para armazenamento persistente. O projeto foi criado em conjunto com o programador **[GabrielVitorGL](https://github.com/GabrielVitorGL)** como parte da disciplina **Estrutura de Dados 1** do curso de **Análise e Desenvolvimento de Sistemas** do **IFSP - Guarulhos**.

## Funcionalidades
- Cadastro de novos clientes.
- Busca de clientes por identificador ou nome.
- Listagem de todos os clientes cadastrados.
- Edição dos dados de um cliente.
- Remoção de clientes.
- Armazenamento e recuperação de dados em um arquivo binário.

## Estrutura do Projeto
O projeto é composto por três arquivos principais:
- `main.c`: Responsável pela interface com o usuário e fluxo principal do programa.
- `acme.h`: Arquivo de cabeçalho contendo definições de estruturas e protótipos de funções.
- `acme.c`: Implementação das funções do sistema.

## Estruturas de Dados
O projeto utiliza uma **lista encadeada** para armazenar os clientes dinamicamente.

```c
typedef struct cliente {
    int identificador;
    char nome[80];
    char empresa[80];
    char departamento[80];
    char telefone[15];
    char celular[15];
    char email[80];   
} CLIENTE;

typedef struct elemento {
    CLIENTE dados;
    struct elemento *prox;
} ELEM;
```

## Principais Funções

### Criar Lista
```c
Lista *criaLista() {
    Lista *li = (Lista *)malloc(sizeof(Lista));
    if (li != NULL) {
        *li = NULL;
    }
    return li;
}
```

### Inserir Cliente
```c
int insereOrdenado(Lista *li, CLIENTE al) {
    if (li == NULL) {
        abortaPrograma();
    }
    ELEM *no = (ELEM *)malloc(sizeof(ELEM));
    if (no == NULL) {
        return 0;
    }
    no->dados = al;
    no->prox = (*li);
    *li = no;
    return al.identificador;
}
```

### Buscar Cliente pelo Nome
```c
void consultaNome(Lista *li, char nome[]) {
    if (li == NULL || listaVazia(li)) {
        return;
    }
    ELEM *no = *li;
    while (no != NULL) {
        if (strstr(no->dados.nome, nome) != NULL) {
            relatorio(&no->dados);
        }
        no = no->prox;
    }
}
```

### Salvar Dados no Arquivo
```c
void salvarArquivo(Lista *li) {
    FILE *arquivo = fopen("clientes.bin", "wb");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo\n");
        exit(1);
    }
    ELEM *no = *li;
    while (no != NULL) {
        fwrite(&no->dados, sizeof(CLIENTE), 1, arquivo);
        no = no->prox;
    }
    fclose(arquivo);
}
```

## Como Executar o Programa
1. Compilar o projeto com o `gcc`:
   ```sh
   gcc main.c acme.c -o acme
   ```
2. Executar o programa:
   ```sh
   ./acme
   ```

## Considerações Finais
Este projeto demonstra a aplicação prática de **listas dinâmicas**, **ponteiros** e **manipulação de arquivos** em C. Foi desenvolvido com foco em **modularização**, **eficiência** e **boas práticas de programação**.

Para saber mais detalhes acesse a **[documentação do projeto](./documentation/projeto%20ACME.pdf)**.
