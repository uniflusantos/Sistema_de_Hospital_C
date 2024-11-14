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

typedef struct CelulaStackInt{
    struct CelulaStackInt* proximo;
    int valor;
}CelulaStackInt;

typedef struct{
    CelulaStackInt *topo;
    int qtde;
}StackInt;

typedef struct CelulaStackRegistro{
    struct CelulaStackRegistro* proximo;
    Registro *valor;
}CelulaStackRegistro;

typedef struct{
    CelulaStackRegistro *topo;
    int qtde;
}StackRegistro;


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
StackInt* iniciarStackInt();
void push_stackInt(StackInt * pilha, int valor);
int pop_stackInt(StackInt * pilha);
void show_stackInt(StackInt* pilha);
CelulaStackInt* instanciar_celulaInt(CelulaStackInt* proximo,int valor);

StackRegistro* iniciarStackRegistro();
void push_StackRegistro(StackRegistro * pilha, Registro* valor);
Registro* pop_StackRegistro(StackRegistro * pilha);
void show_StackRegistro(StackRegistro* pilha);
CelulaStackRegistro* instanciar_celula_registro(CelulaStackRegistro* proximo,Registro* valor);

Data* iniciarData(int aleatorio);
Registro *iniciarRegistro(int dia, int mes, int ano);
Lista *iniciarLista();
ELista *iniciarELista(Registro *registro);
VerticeArvore *iniciarVerticeArvoreBinaria(Registro* registrado);
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
void inserirFila(Fila *fila, Registro *reg, StackRegistro *pilhaRegistro, StackInt *pilhaOperacao);
Registro removerFila(Fila *fila, StackRegistro *pilhaRegistro, StackInt *pilhaOperacao);
void mostrarFila(Fila *fila);
void printarArvoreEmOrdemCrescente(VerticeArvore *raiz);
void inserirArvoreIdade(ArvoreBinaria* arvore, Registro* valor);
void inserirArvoreAno(ArvoreBinaria* arvore, Registro* valor);
void inserirArvoreMes(ArvoreBinaria* arvore, Registro* valor);
void inserirArvoreDia(ArvoreBinaria* arvore, Registro* valor);
int removerVerticeArvoreBinaria(ArvoreBinaria* arvore, VerticeArvore* vertice);
ArvoreBinaria *iniciarArvoreBinaria();
ArvoreBinaria* criarArvoreAPartirDeUmaLista(Lista* lista,int variavelAnalizada);
void editarIdadePeloRG(Lista *lista, char *rg, int novaIdade);
void editarNomePeloRG(Lista *lista, char *rg, const char *novoNome);
void editarDataDia(Lista *lista, char *rg, int novoDia);
void editarDataMes(Lista *lista, char *rg, int novoMes);
void editarDataAno(Lista *lista, char *rg, int novoAno);
void desfazerOperacao(Fila *fila, StackRegistro *pilhaRegistro, StackInt *pilhaOperacao);
void removerFilaTail(Fila *fila);
Registro* verificarRGDuplicado(Lista* lista, const char* rg);


#endif 
