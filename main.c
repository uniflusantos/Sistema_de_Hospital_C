#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
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

Data* iniciarData(int aleatorio) {
    Data* data = malloc(sizeof(Data));
    if (aleatorio) {
        data->ano = 2020 + rand() % 5;
        data->dia = rand() % 30;
        data->mes = rand() % 12;
        return data;
    }
    data->ano = 0;
    data->dia = 0;
    data->mes = 0;
    return data;
}

Registro *iniciarRegistro(int dia, int mes, int ano) {
    Registro *reg = malloc(sizeof(Registro));
    reg->entrada = iniciarData((dia && mes && ano) ? 0 : 1);
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
        return lista;
    }
    while (fread(&atual, sizeof(RegistroFull), 1, file) == 1) {
        Registro *reg = iniciarRegistro(atual.entrada.dia, atual.entrada.mes, atual.entrada.ano);
        strcpy(reg->nome, atual.nome);
        strcpy(reg->rg, atual.rg);
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
    EFila *novo = iniciarEFilaReg(reg);
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
    free(remover->Dados->nome);
    free(remover->Dados->rg);
    free(remover->Dados);
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
void opcoesCadastro(Lista* lista) {
    int opcao_1;
    printf("1 - Cadastrar novo paciente\n");
    printf("2 - Consultar paciente cadastrado\n");
    printf("3 - Mostrar lista de pacientes completa\n");
    printf("4 - Atualizar dados de paciente\n");
    printf("5 - Remover paciente\n");
    printf("Digite qual opcao deseja utilizar\n");
    scanf("%d", &opcao_1);

    if (opcao_1 == 1) {
        Registro *reg = iniciarRegistro(0, 0, 0);
        printf("Digite o nome do paciente: ");
        scanf("%s", reg->nome);
        printf("Digite a idade do paciente: ");
        scanf("%hd", &reg->idade);
        printf("Digite o RG do paciente: ");
        scanf("%s", reg->rg);
        inserirLista(lista, reg);
    } else if (opcao_1 == 2) {
        int opcao_consultar;
        printf("1 - Consultar por nome\n");
        printf("2 - Consultar por RG\n");
        printf("Digite por qual opcao deseja consultar\n");
        scanf("%d", &opcao_consultar);
        if (opcao_consultar == 1) {
            char nome[STR_LIM];
            printf("Digite o nome que deseja consultar: ");
            scanf("%s", nome);
            printarCadastro(procurarRegistroPeloNome(lista, nome));
        } else if (opcao_consultar == 2) {
            char rg[STR_LIM];
            printf("Digite o RG que deseja consultar: ");
            scanf("%s", rg);
            printarCadastro(procurarRegistroPeloRG(lista, rg));
        }
    } else if (opcao_1 == 3) {
        mostrarListaCadastros(lista);
    } else if (opcao_1 == 5) {
        int opcao_remover;
        printf("1 - Remover por nome\n");
        printf("2 - Remover por RG\n");
        scanf("%d", &opcao_remover);
        if (opcao_remover == 1) {
            char nome_remover[STR_LIM];
            printf("Digite o nome do paciente que deseja remover: ");
            scanf("%s", nome_remover);
            removerListaNome(lista, nome_remover);
        } else if (opcao_remover == 2) {
            char rg_remover[STR_LIM];
            printf("Digite o RG do paciente que deseja remover: ");
            scanf("%s", rg_remover);
            removerListaRG(lista, rg_remover);
        }
    }
}

int main() {
    Lista* lista2 = lerDados();
    mostrarListaCadastros(lista2);
    
    while (1) {
        int opcao;
        printf("1 - Opcoes de cadastro\n");
        printf("2 - Atendimento\n");
        printf("3 - Pesquisa\n");
        printf("4 - Desfazer ultima operacao\n");
        printf("5 - Carregar / Salvar\n");
        printf("6 - Sobre o programa\n");
        printf("7 - Sair do programa\n");
        printf("Digite qual opcao deseja utilizar\n");
        scanf("%d", &opcao);

        if (opcao == 1) {
            opcoesCadastro(lista2);
        }
        
        // Aqui você pode adicionar as outras opções do menu principal.
        
        if (opcao == 7) {
            break;
        }
    }
    
    // Liberar memória
    free(lista2);
    return 0;
}

