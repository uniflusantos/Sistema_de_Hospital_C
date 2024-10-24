#include <stdlib.h>
#include <stdio.h>
#include <conio.h>
#include <time.h>
#define STR_LIM 50

typedef struct Data{
    int dia,mes,ano;
}Data;

typedef struct Registro{
    char * nome;
    short idade;
    char * rg;
    Data *entrada;
}Registro;

typedef struct{
    char nome[STR_LIM];
    short idade;
    char rg[STR_LIM];
    Data entrada;
}RegistroFull;

typedef struct ELista
{
    struct Elista * proximo;
    Registro * Dados;    
}ELista;

typedef struct{
    ELista * inicio;
    int quantidade;
}Lista;

typedef struct EFila
{
    struct EFila * proximo;
    Registro * Dados;    
}EFila;

typedef struct{
    EFila * head;
    EFila * tail;
    int quantidade;
}Fila;

//Funções da lista

Data* iniciarData(int aleatorio){
    Data* data = malloc(sizeof(Data));
    // time_t tempo;
    // time(&tempo);
    // struct tm *hora_local = localtime(&tempo);
    if(aleatorio){
        data->ano = 2020 +rand()%5; //hora_local->tm_year;
        data->dia = rand()%30;
        data->mes = rand()%12;
        return NULL;
    }
    data->ano = 0; //hora_local->tm_year;
    data->dia = 0;
    data->mes = 0;
    return data;
}

Registro * iniciarRegistro(int dia, int mes, int ano){
    
    Registro *reg = malloc(sizeof(Registro));   
    reg->entrada = iniciarData((dia&&mes&&ano)? 0 : 1);
    if ((dia&&mes&&ano)){
        reg->entrada->ano = ano;
        reg->entrada->mes = mes;
        reg->entrada->dia = dia;
    }
    reg->idade =0;
    reg->nome = "";
    reg->rg = "";
    return reg;
};

//Funções da lista

Lista * iniciarLista(){
    Lista * lista = malloc(sizeof(Lista));
    lista->quantidade =0;
    return lista;
}

ELista * iniciarELista(Registro * registro){
    ELista * celula = malloc(sizeof(ELista));
    celula->Dados = registro;
    celula->proximo = NULL;
    return celula;
}

void inserirLista(Lista * lista, Registro *valor){
    ELista* novo = iniciarELista(valor);
    if(lista->quantidade ==0){
        lista->inicio = novo;
    }else{
        novo->proximo = lista->inicio;
        lista->inicio = novo;        
    }
    lista->quantidade++;
    return;
}

Registro removerListaRG(Lista * lista, char* rg){
    if(lista->quantidade == 0)return *iniciarRegistro(0,0,0);
    ELista* anterior = NULL;
    ELista* atual = lista->inicio;

    while(atual !=NULL && strcmp(atual->Dados->rg, rg)!=0){
        anterior = atual;
        atual = atual->proximo;
    }
    if(atual == NULL)return *iniciarRegistro(0,0,0);
    if(anterior == NULL){
        lista->inicio = atual->proximo;
    }
    if(atual->proximo == NULL){
        anterior->proximo = NULL;
    }else{
        anterior = atual->proximo;
    }
    free(atual);
    lista->quantidade--;
    
}

Registro removerListaNome(Lista * lista, char* nome){
    if(lista->quantidade == 0)return *iniciarRegistro(0,0,0);
    ELista* anterior = NULL;
    ELista* atual = lista->inicio;

    while(atual !=NULL && strcmp(atual->Dados->nome, nome)!=0){
        anterior = atual;
        atual = atual->proximo;
    }
    if(atual == NULL)return *iniciarRegistro(0,0,0);
    if(anterior == NULL){
        lista->inicio = atual->proximo;
    }
    if(atual->proximo == NULL){
        anterior->proximo = NULL;
    }else{
        anterior = atual->proximo;
    }
    free(atual);
    lista->quantidade--;
    
}

Registro * procurarRegistroPeloNome(Lista* lista, char* nome){
    ELista* atual = lista->inicio;
    while(atual !=NULL && strcmp(atual->Dados->nome, nome)!=0){
        atual = atual->proximo;
    }
    if(atual == NULL)return NULL;
    return atual->Dados;
    
}

Registro * procurarRegistroPeloRG(Lista* lista, char* rg){
    ELista* atual = lista->inicio;
    while(atual !=NULL && strcmp(atual->Dados->rg, rg)!=0){
        atual = atual->proximo;
    }
    if(atual == NULL)return NULL;
    return atual->Dados;
    
}

//Prints 

void printarData(Data * data){
    printf("Data: %02d/%02d/%04d \n",data->dia,data->mes,data->ano);
}

void printarCadastro(Registro* registro){
    printarData(registro->entrada);
    printf("Nome: %s\nIdade: %d\nRG: %s \n\n",registro->nome, registro->idade, registro->rg);
}

void mostrarListaCadastros(Lista* lista){
    ELista *inicio = lista->inicio;
    while(inicio != NULL){
        printarCadastro(inicio->Dados);
        inicio = inicio->proximo;
    }
    printf("\n");
}

// Funções de load e save

void limparArquivoBinario(const char *caminho) {
    FILE *file = fopen(caminho, "wb");
    if (file == NULL) {
        printf("Erro ao abrir o arquivo!\n");
        return;
    }
    fclose(file);
}

void salvarDados(Lista* lista){
    limparArquivoBinario("dados.bin");
    FILE *file = fopen("dados.bin", "ab");
    ELista *inicio = lista->inicio;
    while(inicio != NULL){
        RegistroFull regAtual = {
            .entrada={.ano = inicio->Dados->entrada->ano, .mes = inicio->Dados->entrada->mes, .dia = inicio->Dados->entrada->dia},
            .idade=inicio->Dados->idade
            };
        strcpy(regAtual.nome,inicio->Dados->nome);
        strcpy(regAtual.rg,inicio->Dados->rg);        
        fwrite(&regAtual, sizeof(RegistroFull), 1, file);
        inicio = inicio->proximo;
    }
    fclose(file);
}

Lista * lerDados(){
    Lista* lista = iniciarLista();
    RegistroFull* atual = malloc(sizeof(RegistroFull));
    FILE *file = fopen("dados.bin", "rb");
    while (fread(atual, sizeof(RegistroFull), 1, file) == 1) {
        Registro * reg = malloc(sizeof(Registro));
        reg->nome = atual->nome;
        reg->rg = atual->rg;
        reg->idade = atual->idade;
        reg->entrada = &(atual->entrada);
        inserirLista(lista,&reg);
        
    }
    fclose(file);
    return lista;    
} 

//Funções da Fila

EFila * iniciarEFila(){
    EFila* celulaFila = malloc(sizeof(EFila));
    celulaFila->Dados = iniciarRegistro(0,0,0);
    celulaFila->proximo = NULL;
    return celulaFila;
}

EFila * iniciarEFilaReg(Registro* registro){
    EFila* celulaFila = malloc(sizeof(EFila));
    celulaFila->Dados = registro;
    celulaFila->proximo = NULL;
    return celulaFila;
}

Fila * iniciarFila(){
    Fila* fila = malloc(sizeof(Fila));
    fila->head = NULL;
    fila->tail = NULL;
    fila->quantidade = 0;
    return fila;
}

void inserirFila(Fila * fila,Registro* reg){
    EFila * novo = iniciarEFila(reg);
    if(fila->quantidade== 0){
        fila->head = novo;
    }else{
        fila->tail->proximo = novo;
    }
    fila->tail = novo;
    fila->quantidade++;    
}

Registro removerFila(Fila * fila){
    if(fila->quantidade ==0)return *iniciarRegistro(0,0,0);
    Registro valorRemocao = *fila->head->Dados;
    EFila * remover = fila->head;
    fila->head = fila->head->proximo;
    free(remover);
    fila->quantidade--;
    return valorRemocao;
}

void mostrarFila(Fila * fila){
    EFila * inicio = fila->head;
    while(inicio != NULL){
        printarCadastro(inicio->Dados);
        inicio=inicio->proximo;
    }
    printf("\n\n\n\n");
}



int main(){
    
    // Lista* lista = lerDados();
    // Lista * lista= iniciarLista();
    // Registro reg = {.entrada=iniciarData(0),.idade=19,.nome="Giovanni",.rg="123"};
    // Registro reg2 = {.entrada=iniciarData(0),.idade=19,.nome="Julia",.rg="321"}; 

    // inserirLista(lista,&reg2);
    // inserirLista(lista,&reg);
    // // mostrarListaCadastros(lista);
    // // printf("Removido nome Giovanni \n\n\n\n\n");
    // // removerListaNome(lista,"Giovanni");
    
    // mostrarListaCadastros(lista);
    // // printarCadastro(procurarRegistroPeloNome(lista,"Giovanni"));
    // // printarCadastro(procurarRegistroPeloRG(lista,"321"));

    // // Registro * regAtual = procurarRegistroPeloRG(lista,"321");
    // // regAtual->entrada->ano= 2024;
    // // printarCadastro(procurarRegistroPeloRG(lista,"321"));

    // salvarDados(lista);
    
    
    Lwhile(1){
    	int opcao;
	printf("1 - Opcoes de cadastro\n");
	printf("2 - Atendimento\n");
	printf("3 - Pesquisa\n");
	printf("4 - Desfazer ultima opercao\n");
	printf("5 - Carregar / Salvar\n");
	printf("6 - Sobre o programa\n");
	printf("Digite qual opcao deseja utilizar\n");
	scanf("%d", &opcao);

	if(opcao == 1){
		int opcao_1;
		printf("1 - Cadastrar novo paciente\n");
		printf("2 - Consultar paciente cadastrado\n");
		printf("3 - Mostrar lista de pacientes completa\n");
		printf("4 - Atualizar dados de paciente\n");
		printf("5 - Remover paciente\n");
		printf("Digite qual opcao deseja utilizar\n");
		scanf("%d", &opcao_1);
			
			if(opcao_1 == 1){
				inserirLista(lista, &reg);
			}
			else if(opcao_1 == 2){
				printarCadastro(&reg);
			}
			else if(opcao_1 == 3){
				mostrarListaCadastrados(lista, "123");
			}	
		}

	if(opcao == 2){
		int opcao_2;
		printf("1 - Enfileirar paciente na lista de atendimento\n");
		printf("2 - Desenfileirar paciente na lista de atendimento\n");
		printf("3 - Mostrar fila completa de atendimento\n");
		scanf("%d", &opcao_2);
		}
	if(opcao == 3){
		int opcao_3;
		printf("1 - Mostrar registros ordenados por ano de registro\n");
		printf("2 - Mostrar registros ordenados por mes de registro\n");
		printf("3 - Mostrar registros ordenados por dia de registro\n");
		printf("4 - Mostrar registros ordenados por idade do paciente\n");
		scanf("%d", &opcao_3);
		}
	if(opcao == 4){
		int opcao_4;
		printf("Deseja desfazer a ultima operacao?\n1 - sim / 2 - nao\n");
		}
	if(opcao == 5){
		int opcao_5;
		printf("1 - Carregar arquivo com os dados dos pacientes\n");
		printf("2 - Salvar arquivo com os dados dos pacientes\n");
		scanf("%d", &opcao_5);
		}
	if(opcao == 6){
		printf("Criadores: Giovanni Chahin Morassi\nLucas Roberto Boccia dos Santos\n");
		printf("Ciclo: 4° semestre\n"):
		printf("Curso: Ciencias da Computacao\n");
		printf("Disciplina: Estrutura de dados\n");
		printf("Data: \n");
	}
}
    Lista* lista2 = lerDados();
    mostrarListaCadastros(lista2,"123");
    


    return 1;
	
}
