#ifndef Estruturas_H
#define Estruturas_H

#define STR_LIM 50
typedef struct Data {
    int dia, mes, ano;
} Data;

typedef struct Registro {
    char *nome;
    short idade;
    char *rg;
    Data *entrada;
} Registro;

typedef struct {
    char nome[STR_LIM];
    short idade;
    char rg[STR_LIM];
    Data entrada;
} RegistroFull;

typedef struct ELista {
    struct ELista *proximo;
    Registro *Dados;
} ELista;

typedef struct {
    ELista *inicio;
    int quantidade;
} Lista;

typedef struct EFila {
    struct EFila *proximo;
    Registro *Dados;
} EFila;

typedef struct {
    EFila *head;
    EFila *tail;
    int quantidade;
} Fila;

typedef struct CelulaStack{
    struct CelulaStack* proximo;
    int valor;
}CelulaStack;

typedef struct{
    CelulaStack *topo;
    int qtde;
}StackInt;

typedef struct VerticeArvore{
	Registro *valor;
	struct VerticeArvore* esq;
	struct VerticeArvore* dir;
	struct VerticeArvore* pai;
} VerticeArvore;

typedef struct ArvoreBinaria{
	VerticeArvore* raiz;
	int qtde;
    void (*inserirArvore[4])(struct ArvoreBinaria*, Registro*);
    int (*remover)(struct ArvoreBinaria* ,VerticeArvore*);
} ArvoreBinaria;



ArvoreBinaria* criarArvoreAPartirDeUmaLista(Lista* lista,int variavelAnalizada);
StackInt* iniciarStack();
CelulaStack* instanciar_celula(CelulaStack* proximo,int valor);
Data* iniciarData(int aleatorio);
Registro *iniciarRegistro(int dia, int mes, int ano);
Lista *iniciarLista();
ELista *iniciarELista(Registro *registro);
VerticeArvore *iniciarVerticeArvoreBinaria(Registro* registrado);
void push_stack(StackInt * pilha, int valor);
int pop_stack(StackInt * pilha);
void show_stack(StackInt* pilha);
void inserirLista(Lista *lista, Registro *valor);
Registro *removerListaRG(Lista *lista, char* rg);
Registro *removerListaNome(Lista *lista, char* nome);
Registro *procurarRegistroPeloNome(Lista* lista, char* nome);
Registro *procurarRegistroPeloRG(Lista* lista, char* rg);
void printarData(Data *data);
void printarCadastro(Registro* registro);
void mostrarListaCadastros(Lista* lista);
void limparArquivoBinario(const char *caminho);
void salvarDados(Lista* lista);
Lista *lerDados();
EFila *iniciarEFila();
EFila *iniciarEFilaReg(Registro* registro);
Fila *iniciarFila();
void inserirFila(Fila *fila, Registro *reg);
Registro removerFila(Fila *fila);
void mostrarFila(Fila *fila);
void printarArvoreEmOrdemCrescente(VerticeArvore *raiz);
void inserirArvoreIdade(ArvoreBinaria* arvore, Registro* valor);
void inserirArvoreAno(ArvoreBinaria* arvore, Registro* valor);
void inserirArvoreMes(ArvoreBinaria* arvore, Registro* valor);
void inserirArvoreDia(ArvoreBinaria* arvore, Registro* valor);
int removerVerticeArvoreBinaria(ArvoreBinaria* arvore, VerticeArvore* vertice);
ArvoreBinaria *iniciarArvoreBinaria();
ArvoreBinaria* criarArvoreAPartirDeUmaLista(Lista* lista,int variavelAnalizada);


#endif 