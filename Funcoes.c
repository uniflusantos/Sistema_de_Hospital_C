#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include "Estruturas.h"
#include "Funcoes.h"
#define STR_LIM 50

void limpa_buffer(){
    int c;
    while ((c = getchar()) != '\n' && c != EOF) { }
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
    limpa_buffer();

    if (opcao_1 == 1) {
        Registro *reg = iniciarRegistro(0, 0, 0);
        printf("Digite o nome do paciente: ");
        scanf("%s", reg->nome);
        limpa_buffer();
        printf("Digite a idade do paciente: ");
        scanf("%hd", &reg->idade);
        limpa_buffer();
        printf("Digite o RG do paciente: ");
        scanf("%s", reg->rg);
        inserirLista(lista, reg);
        limpa_buffer();
    } else if (opcao_1 == 2) {
        int opcao_consultar;
        printf("1 - Consultar por nome\n");
        printf("2 - Consultar por RG\n");
        printf("Digite por qual opcao deseja consultar\n");
        scanf("%d", &opcao_consultar);
        limpa_buffer();
        if (opcao_consultar == 1) {
            char nome[STR_LIM];
            printf("Digite o nome que deseja consultar: ");
            scanf("%s", nome);
            printf("Lista de pacientes: \n");
            printarCadastro(procurarRegistroPeloNome(lista, nome));
            limpa_buffer();
        } else if (opcao_consultar == 2) {
            char rg[STR_LIM];
            printf("Digite o RG que deseja consultar: ");
            scanf("%s", rg);
            printf("Lista de pacientes: \n");
            printarCadastro(procurarRegistroPeloRG(lista, rg));
            limpa_buffer();
        }
    } else if (opcao_1 == 3) {
        printf("Lista de pacientes cadastrados: \n");
        mostrarListaCadastros(lista);

    } 
    
    else if (opcao_1 == 4){
        int opcao_editar;
        printf("Digite qual informacao quer editar do paciente\n");
        printf("1 - Nome\n");
        printf("2 - Idade\n");
        printf("3 - Data\n");
        scanf("%d", &opcao_editar);
        limpa_buffer();
        if(opcao_editar == 1){
            char rg_edicao[STR_LIM];
            printf("Digite o rg do paciente que deseja editar o nome: \n");
            scanf("%s", rg_edicao);
            limpa_buffer();
            char novo_nome[STR_LIM];
            printf("Digite o novo nome do paciente\n");
            scanf("%s", &novo_nome);
            editarNomePeloRG(lista, rg_edicao, novo_nome);
            limpa_buffer();
        }
        else if(opcao_editar == 2){
            char rg_edicao[STR_LIM];
            printf("Digite o rg do paciente que deseja a editar a idade: ");
            scanf("%s", rg_edicao);
            limpa_buffer();
            int nova_idade;
            printf("Digite a nova idade do paciente\n");
            scanf("%d", &nova_idade);
            editarIdadePeloRG(lista, rg_edicao, nova_idade);
            limpa_buffer();
        }
        else if(opcao_editar == 3){
            int opcao_data;
            printf("Digite qual dado da data deseja alterar: \n");
            printf("1 - Dia\n");
            printf("2 - Mes\n");
            printf("3 - Ano\n");
            printf("4 - Alterar a dadta inteira\n");
            scanf("%d", &opcao_data);
            limpa_buffer();

            if(opcao_data == 1){
                char rg_edicao[STR_LIM];
                printf("Digite o rg do paciente que deseja editar a dia: ");
                scanf("%s", &rg_edicao);
                limpa_buffer();
                int novo_dia;
                printf("Digite o novo dia da data: \n");
                scanf("%d", &novo_dia);
                editarDataDia(lista, rg_edicao, novo_dia);
                limpa_buffer();
            }
            else if(opcao_data == 2){
                char rg_edicao[STR_LIM];
                printf("Digite o rg do paciente que deseja editar a dia: ");
                scanf("%s", &rg_edicao);
                limpa_buffer();
                int novo_mes;
                printf("Digite o novo mes da data: \n");
                scanf("%d", &novo_mes);
                editarDataMes(lista, rg_edicao, novo_mes);
                limpa_buffer();
            }
            else if(opcao_data == 3){
                char rg_edicao[STR_LIM];
                printf("Digite o rg do paciente que deseja editar a dia: ");
                scanf("%s", &rg_edicao);
                limpa_buffer();
                int novo_ano;
                printf("Digite o novo ano da data: \n");
                scanf("%d", &novo_ano);
                editarDataMes(lista, rg_edicao, novo_ano);
                limpa_buffer();
            }
            else if(opcao_data == 4){
                char rg_edicao[STR_LIM];
                printf("Digite o rg do paciente que deseja editar a dia: ");
                scanf("%s", &rg_edicao);
                limpa_buffer();
                int novo_dia;
                int novo_mes;
                int novo_ano;
                printf("Digite o novo dia: \n");
                scanf("%d", &novo_dia);
                limpa_buffer();
                printf("Digite o novo mes: \n");
                scanf("%d", &novo_mes);
                limpa_buffer();
                printf("Digite o novo ano: \n");
                scanf("%d", &novo_ano);
                editarDataDia(lista, rg_edicao, novo_dia);
                editarDataMes(lista, rg_edicao, novo_mes);
                editarDataAno(lista, rg_edicao, novo_ano);
                limpa_buffer();
            }
        }
    }

    else if (opcao_1 == 5) {
        int opcao_remover;
        printf("1 - Remover por nome\n");
        printf("2 - Remover por RG\n");
        scanf("%d", &opcao_remover);
        limpa_buffer();
        if (opcao_remover == 1) {
            char nome_remover[STR_LIM];
            printf("Digite o nome do paciente que deseja remover: ");
            scanf("%s", nome_remover);
            removerListaNome(lista, nome_remover);
            limpa_buffer();
        } else if (opcao_remover == 2) {
            char rg_remover[STR_LIM];
            printf("Digite o RG do paciente que deseja remover: ");
            scanf("%s", rg_remover);
            removerListaRG(lista, rg_remover);
            limpa_buffer();
        }
    }
}

void opcao2(Fila *fila, Lista *lista) {
    int opcao_2;
    printf("1 - Inserir paciente na fila de atendimento\n");
    printf("2 - Remover paciente da fila de atendimento\n");
    printf("3 - Mostrar fila de atendimento\n");
    printf("Digite qual opcao deseja utilizar\n");
    scanf("%d", &opcao_2);
    
    if (opcao_2 == 1) {
        char rg[STR_LIM];
        printf("Digite o RG do paciente que deseja enfileirar: \n");
        scanf("%s", rg);
        Registro *registro = procurarRegistroPeloRG(lista, rg);
        limpa_buffer();
        if (registro) {
            inserirFila(fila, registro);
        } else {
            printf("Paciente com RG %s não encontrado.\n", rg);
        }
    } else if (opcao_2 == 2) {
        removerFila(fila);
    } else if (opcao_2 == 3) {
        mostrarFila(fila);
     } else if (opcao_2 == 3) {
        printf("Fila de atendimento completa: \n");
        mostrarFila(fila);
    }
}

void opcao3(Lista *lista){
    int opcao_3;
    printf("1 - Mostrar registros ordenados por ano \n");
    printf("2 - Mostrar registros ordenados por mes \n");
    printf("3 - Mostrar registros ordenados por dia \n");
    printf("4 - Mostrar registros ordenados por idade \n");
    printf("Digite qual opcao deseja utilizar: \n");
    scanf("%d", &opcao_3);
    limpa_buffer();
    if(opcao_3 == 1){
        printf("Registros ordenados por ano: \n");
            ArvoreBinaria *arvore = criarArvoreAPartirDeUmaLista(lista,3);
        arvore = criarArvoreAPartirDeUmaLista(lista, 3);
        printarArvoreEmOrdemCrescente(arvore->raiz);
    }
    if(opcao_3 == 2){
        printf("Registros ordenados por mes: \n");
            ArvoreBinaria *arvore = criarArvoreAPartirDeUmaLista(lista,2);
        arvore = criarArvoreAPartirDeUmaLista(lista, 2);
        printarArvoreEmOrdemCrescente(arvore->raiz);
    }
    if(opcao_3 == 3){
        printf("Registros ordenados por dia: \n");
            ArvoreBinaria *arvore = criarArvoreAPartirDeUmaLista(lista,1);
        arvore = criarArvoreAPartirDeUmaLista(lista, 1);
        printarArvoreEmOrdemCrescente(arvore->raiz);
    }
    if(opcao_3 == 4){
        printf("Registros ordenados por idade: \n");
        ArvoreBinaria *arvore = criarArvoreAPartirDeUmaLista(lista,0);
        arvore = criarArvoreAPartirDeUmaLista(lista, 0);
        printarArvoreEmOrdemCrescente(arvore->raiz);
    }
}

void opcao5(Lista *lista){
    int opcao_5;
    printf("1 - Salvar dados em arquivo binario\n");
    printf("2 - Ler dados do arquivo binario\n");
    printf("Digite qual opcao deseja utilizar:\n");
    scanf("%d", &opcao_5);
    limpa_buffer();
    if(opcao_5 == 1){
        salvarDados(lista);
    }
    else if(opcao_5 == 2){
        lerDados();
    }
}

void opcao6(){
    printf("Programa de: \n");
    printf("Lucas Roberto Boccia dos Santos (22.123.012-1)\n");
    printf("Giovanni Chahin Morassi (22.123.025-3)\n");
    printf("Ciclo: 4\n");
    printf("Curso: Ciencias da Computacao\n");
    printf("Disciplina: Estrutura de Dados\n\n");
}
