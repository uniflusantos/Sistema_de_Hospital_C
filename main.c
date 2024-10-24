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

Data* iniciarData(int aleatorio){
    Data* data = malloc(sizeof(Data));
    // time_t tempo;
    // time(&tempo);
    // struct tm *hora_local = localtime(&tempo);
    if(aleatorio){
        data->ano = 2020 +rand()%5; //hora_local->tm_year;
        data->dia = rand()%30;
        data->mes = rand()%12;
        return;
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

void printarData(Data * data){
    printf("Data: %02d/%02d/%04d \n",data->dia,data->mes,data->ano);
}

void printarCadastro(Registro* registro){
    printarData(registro->entrada);
    printf("Nome: %s\nIdade: %d\nRG: %s \n\n",registro->nome, registro->idade, registro->rg);
}

void mostrarListaCadastros(Lista* lista,char* rg){
    ELista *inicio = lista->inicio;
    while(inicio != NULL){
        printarCadastro(inicio->Dados);
        inicio = inicio->proximo;
    }
    printf("\n");
}

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
        Registro reg;
        reg.nome = atual->nome;
        reg.rg = atual->rg;
        reg.idade = atual->idade;
        reg.entrada = &atual->entrada;
        inserirLista(lista,&reg);
        
    }
    fclose(file);
    return lista;    
} 

int main(){
    
    Lista* lista = iniciarLista();
    Registro reg = {.entrada=iniciarData(0),.idade=19,.nome="Giovanni",.rg="123"};
    inserirLista(lista,&reg);
    inserirLista(lista,&reg);
    inserirLista(lista,&reg);
    inserirLista(lista,&reg);
    mostrarListaCadastros(lista,"123");
    salvarDados(lista);
    
    while(1){
    	printf("1 - Cadastrar");
    	printf("2 - Atendimento");
    	printf("3 - Pesquisa");
    	printf("4 - Desfazer ultima opercao");
    	printf("5 - Carregar / Salvar");
    	printf("6 - Sobre o programa");
    	printf("Digite qual opcao deseja utilizar");
  	}
    	
    Lista* lista2 = lerDados();
    mostrarListaCadastros(lista2,"123");
    


    return 1;
}
