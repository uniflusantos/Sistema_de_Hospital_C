#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include "Estruturas.h"
#include "Funcoes.h"
#define STR_LIM 50




Data* iniciarData(int aleatorio) {
    Data* data = malloc(sizeof(Data));
    if (aleatorio) {
        data->ano = 2020 + rand() % 5; // Ano aleatório entre 2020 e 2024
        data->dia = 1 + rand() % 30;    // Dia aleatório entre 1 e 30
        data->mes = 1 + rand() % 12;    // Mês aleatório entre 1 e 12
    } else {
        data->ano = 0;
        data->dia = 0;
        data->mes = 0;
    }
    return data;
}


Registro *iniciarRegistro(int dia, int mes, int ano) {
    Registro *reg = malloc(sizeof(Registro));
    reg->entrada = iniciarData(1); // Passa 1 para gerar uma data aleatória
    if (dia && mes && ano) {
        reg->entrada->ano = ano;
        reg->entrada->mes = mes;
        reg->entrada->dia = dia;
    }
    reg->idade = 0;

    reg->nome = malloc(STR_LIM);
    reg->rg = malloc(STR_LIM);
    strcpy(reg->nome, "");
    strcpy(reg->rg, "");

    return reg;
}


Lista *iniciarLista() {
    Lista *lista = malloc(sizeof(Lista));
    lista->quantidade = 0;
    lista->inicio = NULL;
    return lista;
}

ELista *iniciarELista(Registro *registro) {
    ELista *celula = malloc(sizeof(ELista));
    celula->Dados = registro;
    celula->proximo = NULL;
    return celula;
}

VerticeArvore *iniciarVerticeArvoreBinaria(Registro* registrado){
	VerticeArvore* novo = malloc(sizeof(VerticeArvore));
	novo->dir = NULL;
	novo->esq = NULL;
	novo->pai = NULL;
	novo->valor = registrado;
	
	return novo;
}

void inserirLista(Lista *lista, Registro *valor) {
    ELista* novo = iniciarELista(valor);
    if (lista->quantidade == 0) {
        lista->inicio = novo;
    } else {
        novo->proximo = lista->inicio;
        lista->inicio = novo;        
    }
    lista->quantidade++;
}

Registro *removerListaRG(Lista *lista, char* rg) {
    if (lista->quantidade == 0) return NULL;
    ELista* anterior = NULL;
    ELista* atual = lista->inicio;

    while (atual != NULL && strcmp(atual->Dados->rg, rg) != 0) {
        anterior = atual;
        atual = atual->proximo;
    }
    if (atual == NULL) return NULL;
    if (anterior == NULL) {
        lista->inicio = atual->proximo;
    } else {
        anterior->proximo = atual->proximo;
    }
    Registro *registroRemovido = atual->Dados;
    free(atual);
    lista->quantidade--;
    return registroRemovido;
}

Registro *removerListaNome(Lista *lista, char* nome) {
    if (lista->quantidade == 0) return NULL;
    ELista* anterior = NULL;
    ELista* atual = lista->inicio;

    while (atual != NULL && strcmp(atual->Dados->nome, nome) != 0) {
        anterior = atual;
        atual = atual->proximo;
    }
    if (atual == NULL) return NULL;
    if (anterior == NULL) {
        lista->inicio = atual->proximo;
    } else {
        anterior->proximo = atual->proximo;
    }
    Registro *registroRemovido = atual->Dados;
    free(atual);
    lista->quantidade--;
    return registroRemovido;
}

Registro *procurarRegistroPeloNome(Lista* lista, char* nome) {
    ELista* atual = lista->inicio;
    while (atual != NULL && strcmp(atual->Dados->nome, nome) != 0) {
        atual = atual->proximo;
    }
    if (atual == NULL) return NULL;
    return atual->Dados;
}

Registro *procurarRegistroPeloRG(Lista* lista, char* rg) {
    ELista* atual = lista->inicio;
    while (atual != NULL && strcmp(atual->Dados->rg, rg) != 0) {
        atual = atual->proximo;
    }
    if (atual == NULL) return NULL;
    return atual->Dados;
}

void printarData(Data *data) {
    printf("Data: %02d/%02d/%04d\n", data->dia, data->mes, data->ano);
}

void printarCadastro(Registro* registro) {
    printarData(registro->entrada);
    printf("Nome: %s\nIdade: %d\nRG: %s\n\n", registro->nome, registro->idade, registro->rg);
}

void mostrarListaCadastros(Lista* lista) {
    ELista *inicio = lista->inicio;
    while (inicio != NULL) {
        printarCadastro(inicio->Dados);
        inicio = inicio->proximo;
    }
    printf("\n");
}

void editarNomePeloRG(Lista *lista, char *rg, const char *novoNome) {
    Registro *paciente = procurarRegistroPeloRG(lista, rg);
    
    if (paciente != NULL) {
        strcpy(paciente->nome, novoNome);
        printf("Nome atualizado\n");
    }
}


void editarIdadePeloRG(Lista *lista, char *rg, int novaIdade) {
    Registro *paciente = procurarRegistroPeloRG(lista, rg);

    if (paciente != NULL) {
        paciente->idade = novaIdade;
        printf("Idade atualizada\n");
    }
}

void editarDataDia(Lista *lista, char *rg, int novoDia){
    Registro *paciente = procurarRegistroPeloRG(lista, rg);

    if(paciente != NULL){
        paciente->entrada->dia = novoDia;
        printf("Dia atualizado\n");
    }
}

void editarDataMes(Lista *lista, char *rg, int novoMes){
    Registro *paciente = procurarRegistroPeloRG(lista, rg);

    if(paciente != NULL){
        paciente->entrada->mes = novoMes;
        printf("Mes atualizado\n");
    }
}

void editarDataAno(Lista *lista, char *rg, int novoAno){
    Registro *paciente = procurarRegistroPeloRG(lista, rg);

    if(paciente != NULL){
        paciente->entrada->ano = novoAno;
        printf("Ano atualizado\n");
    }
}

void limparArquivoBinario(const char *caminho) {
    FILE *file = fopen(caminho, "wb");
    if (file == NULL) {
        printf("Erro ao abrir o arquivo!\n");
        return;
    }
    fclose(file);
}

void salvarDados(Lista* lista) {
    limparArquivoBinario("dados.bin");
    FILE *file = fopen("dados.bin", "ab");
    ELista *inicio = lista->inicio;
    while (inicio != NULL) {
        RegistroFull regAtual = {
            .entrada = {.ano = inicio->Dados->entrada->ano, .mes = inicio->Dados->entrada->mes, .dia = inicio->Dados->entrada->dia},
            .idade = inicio->Dados->idade
        };
        strcpy(regAtual.nome, inicio->Dados->nome);
        strcpy(regAtual.rg, inicio->Dados->rg);        
        fwrite(&regAtual, sizeof(RegistroFull), 1, file);
        inicio = inicio->proximo;
    }
    fclose(file);
}

Lista *lerDados() {
    Lista *lista = iniciarLista();
    RegistroFull atual;
    FILE *file = fopen("dados.bin", "rb");
    if (file == NULL) {
        printf("Erro ao abrir o arquivo para leitura!\n");
        file = fopen("dados.bin", "w");
        fclose(file);
        return lista;
    }
    while (fread(&atual, sizeof(RegistroFull), 1, file) == 1) {
        Registro *reg = iniciarRegistro(atual.entrada.dia, atual.entrada.mes, atual.entrada.ano);
        strcpy(reg->nome, atual.nome);
        strcpy(reg->rg, atual.rg);
        reg->idade = atual.idade;
        inserirLista(lista, reg);
    }
    fclose(file);
    return lista;    
} 

EFila *iniciarEFila() {
    EFila *celulaFila = malloc(sizeof(EFila));
    celulaFila->Dados = iniciarRegistro(0, 0, 0);
    celulaFila->proximo = NULL;
    return celulaFila;
}

EFila *iniciarEFilaReg(Registro* registro) {
    EFila *celulaFila = malloc(sizeof(EFila));
    celulaFila->Dados = registro;
    celulaFila->proximo = NULL;
    return celulaFila;
}

Fila *iniciarFila() {
    Fila *fila = malloc(sizeof(Fila));
    fila->head = NULL;
    fila->tail = NULL;
    fila->quantidade = 0;
    return fila;
}

void inserirFila(Fila *fila, Registro *reg) {
    EFila *novo = iniciarEFilaReg(malloc(sizeof(Registro)));
    *novo->Dados = *reg; // Cópia profunda dos dados do registro
    if (fila->quantidade == 0) {
        fila->head = novo;
    } else {
        fila->tail->proximo = novo;
    }
    fila->tail = novo;
    fila->quantidade++;
}


Registro removerFila(Fila *fila) {
    if (fila->quantidade == 0) return *iniciarRegistro(0, 0, 0);
    Registro valorRemocao = *fila->head->Dados;
    EFila *remover = fila->head;
    fila->head = fila->head->proximo;
    free(remover->Dados); // Liberar apenas o registro que foi alocado na fila
    free(remover);
    fila->quantidade--;
    return valorRemocao;
}


void mostrarFila(Fila *fila) {
    EFila *inicio = fila->head;
    while (inicio != NULL) {
        printarCadastro(inicio->Dados);
        inicio = inicio->proximo;
    }
    printf("\n");
}

void printarArvoreEmOrdemCrescente(VerticeArvore *raiz) {
    if(raiz != NULL){
        printarArvoreEmOrdemCrescente(raiz->esq);
        printarCadastro(raiz->valor);
        printarArvoreEmOrdemCrescente(raiz->dir);
    }
}

void inserirArvoreIdade(ArvoreBinaria* arvore, Registro* valor){

	VerticeArvore* novo = iniciarVerticeArvoreBinaria(valor);
    if(arvore->qtde==0){
        arvore->raiz=novo;
    }   
    else{
        VerticeArvore * anterior = NULL;
        VerticeArvore * atual = arvore->raiz;
        while( atual!= NULL){
            if(valor->idade > atual->valor->idade){
                anterior = atual;
                atual = atual->dir;
            }else{
                anterior = atual;
                atual = atual->esq;
            }
        }
        if(valor->idade > anterior->valor->idade){
            anterior->dir=novo;
            novo->pai=anterior;
        }else{
            anterior->esq = novo;
            novo->pai= anterior;
        }
    }
    arvore->qtde++;
}

void inserirArvoreAno(ArvoreBinaria* arvore, Registro* valor){

	VerticeArvore* novo = iniciarVerticeArvoreBinaria(valor);
    if(arvore->qtde==0){
        arvore->raiz=novo;
    }   
    else{
        VerticeArvore * anterior = NULL;
        VerticeArvore * atual = arvore->raiz;
        while( atual!= NULL){
            if(valor->entrada->ano > atual->valor->entrada->ano){
                anterior = atual;
                atual = atual->dir;
            }else{
                anterior = atual;
                atual = atual->esq;
            }
        }
        if(valor->entrada->ano > anterior->valor->entrada->ano){
            anterior->dir=novo;
            novo->pai=anterior;
        }else{
            anterior->esq = novo;
            novo->pai= anterior;
        }
    }
    arvore->qtde++;
}

void inserirArvoreMes(ArvoreBinaria* arvore, Registro* valor){

	VerticeArvore* novo = iniciarVerticeArvoreBinaria(valor);
    if(arvore->qtde==0){
        arvore->raiz=novo;
    }   
    else{
        VerticeArvore * anterior = NULL;
        VerticeArvore * atual = arvore->raiz;
        while( atual!= NULL){
            if(valor->entrada->mes > atual->valor->entrada->mes){
                anterior = atual;
                atual = atual->dir;
            }else{
                anterior = atual;
                atual = atual->esq;
            }
        }
        if(valor->entrada->mes > anterior->valor->entrada->mes){
            anterior->dir=novo;
            novo->pai=anterior;
        }else{
            anterior->esq = novo;
            novo->pai= anterior;
        }
    }
    arvore->qtde++;
}

void inserirArvoreDia(ArvoreBinaria* arvore, Registro* valor){

	VerticeArvore* novo = iniciarVerticeArvoreBinaria(valor);
    if(arvore->qtde==0){
        arvore->raiz=novo;
    }   
    else{
        VerticeArvore * anterior = NULL;
        VerticeArvore * atual = arvore->raiz;
        while( atual!= NULL){
            if(valor->entrada->dia > atual->valor->entrada->dia){
                anterior = atual;
                atual = atual->dir;
            }else{
                anterior = atual;
                atual = atual->esq;
            }
        }
        if(valor->entrada->dia > anterior->valor->entrada->dia){
            anterior->dir=novo;
            novo->pai=anterior;
        }else{
            anterior->esq = novo;
            novo->pai= anterior;
        }
    }
    arvore->qtde++;
}


int removerVerticeArvoreBinaria(ArvoreBinaria* arvore, VerticeArvore* vertice) {
    int filhos = (vertice->dir? 1: 0)+(vertice->esq? 1: 0);
    if (filhos ==0) {
        if (vertice->pai) {
            if (vertice->pai->esq == vertice) {
                vertice->pai->esq = NULL;
            } else {
                vertice->pai->dir = NULL;
            }
        } else {
            arvore->raiz = NULL; // Remoção da raiz se for o único nó
        }
        free(vertice);
    }
    // Caso 2: VerticeArvore tem um único filho
    else if (filhos == 1) {
        VerticeArvore* filho = (vertice->esq != NULL) ? vertice->esq : vertice->dir;
        
        if (vertice->pai) {
            if (vertice->pai->esq == vertice) {
                vertice->pai->esq = filho;
            } else {
                vertice->pai->dir = filho;
            }
        } else {
            arvore->raiz = filho; // Atualiza a raiz se o nó removido for a raiz
        }
        filho->pai = vertice->pai;
        free(vertice);
    }
    // Caso 3: VerticeArvore tem dois filhos
    else {
        // Encontra o sucessor in-ordem (menor valor na subárvore direita)
        VerticeArvore* sucessor = vertice->esq;
        while (sucessor->dir != NULL) {
            sucessor = sucessor->dir;
        }
    
        // Copia o valor do sucessor para o nó a ser removido
        vertice->valor = sucessor->valor;

        // Remove o sucessor que agora é duplicado
        removerVerticeArvoreBinaria(arvore, sucessor);
    }

    arvore->qtde--;
    return 1; // Indica sucesso
}

ArvoreBinaria *iniciarArvoreBinaria(){
	ArvoreBinaria* arvore = malloc(sizeof(ArvoreBinaria));
	arvore->raiz = NULL;
	arvore->qtde = 0;
    arvore->inserirArvore[0] = inserirArvoreIdade;
    arvore->inserirArvore[1] = inserirArvoreDia;
    arvore->inserirArvore[2] = inserirArvoreMes;
    arvore->inserirArvore[3] = inserirArvoreAno;
    arvore->remover = removerVerticeArvoreBinaria;
	return arvore;
}

ArvoreBinaria* criarArvoreAPartirDeUmaLista(Lista* lista,int variavelAnalizada){
    ELista* primeiro = lista->inicio;
    ArvoreBinaria* arvore = iniciarArvoreBinaria();
    while (primeiro != NULL) {
        arvore->inserirArvore[variavelAnalizada](arvore,primeiro->Dados);
        primeiro = primeiro->proximo;
    }
    return arvore;
}


StackRegistro* iniciarStackRegistro(){
    StackRegistro* pilha = malloc(sizeof(StackRegistro));
    pilha->qtde=0;
    pilha->topo= NULL;
    return pilha;
}
void push_StackRegistro(StackRegistro * pilha, Registro* valor){
    pilha->topo = instanciar_celula_registro(pilha->topo,valor);
    pilha->qtde++;
}
Registro* pop_StackRegistro(StackRegistro * pilha){
    if (pilha->qtde==0)return NULL;
    CelulaStackRegistro* deletando = pilha->topo;
    Registro* valor = deletando->valor;
    pilha->topo=pilha->topo->proximo;
    free(deletando);
    pilha->qtde--;
    return valor;
}
// void show_StackRegistro(StackRegistro* pilha){
//     CelulaStackRegistro *topo = pilha->topo;
//     while(topo!=NULL){
//         printarCadastro(topo->valor);
//         topo = topo->proximo;
//     }
//     printf("\n");
// }


CelulaStackRegistro* instanciar_celula_registro(CelulaStackRegistro* proximo,Registro* valor){
    CelulaStackRegistro * cell = malloc(sizeof(CelulaStackInt));
    cell->valor= valor;
    cell->proximo = proximo;
    return cell;
}

StackInt * iniciarStackInt(){
    StackInt* pilha = malloc(sizeof(StackInt));
    pilha->qtde=0;
    pilha->topo= NULL;
    return pilha;
}
CelulaStackInt* instanciar_celulaInt(CelulaStackInt* proximo,int valor){
    CelulaStackInt * cell = malloc(sizeof(CelulaStackInt));
    cell->valor= valor;
    cell->proximo = proximo;
    return cell;
}
void push_stackInt(StackInt * pilha, int valor){
    pilha->topo = instanciar_celulaInt(pilha->topo,valor);
    pilha->qtde++;
}

int pop_stackInt(StackInt * pilha){
    if (pilha->qtde==0)return -1;
    CelulaStackInt* deletando = pilha->topo;
    int valor = deletando->valor;
    pilha->topo=pilha->topo->proximo;
    free(deletando);
    pilha->qtde--;
    return valor;
}

void show_stackInt(StackInt* pilha){
    CelulaStackInt *topo = pilha->topo;
    while(topo!=NULL){
        printf("%d ",topo->valor);
        topo = topo->proximo;
    }
    printf("\n");
}




