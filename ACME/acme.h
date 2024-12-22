typedef struct cliente{
    int identificador;
    char nome[80];
    char empresa[80];
    char departamento[80];
    char telefone[15];
    char celular[15];
    char email[80];   
}CLIENTE;

typedef struct elemento* Lista;

Lista *criaLista();

void abortaPrograma();

void apagaLista(Lista *li);

FILE* abriArquivo(Lista *li);

int listaCheia(Lista *li);

int listaVazia(Lista *li);

int insereOrdenado(Lista *li, CLIENTE al);

int removeOrdenado(Lista *li, int id);

int consultaIdentificador(Lista *li, int id, CLIENTE *al);

int confereDupllicidade(Lista *li, int id);

void consultaNome(Lista *li, char nome[]);

void converteNome(char nome[]);

void relatorio(CLIENTE *al);

struct cliente coletadados(Lista *li, int id);

void listarTodos(Lista *li);

void editarCliente(Lista *li, int id);

void salvarArquivo(Lista *li);
