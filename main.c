#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include "Estruturas.h"
#include "Funcoes.h"
#define STR_LIM 50


int main() {
    srand(time(NULL));
    Lista* lista = lerDados();
    mostrarListaCadastros(lista);
    Fila *queue = iniciarFila();
    // StackInt *pilha = iniciarStack();
    
    while (1) {
        int opcao;
        printf("\nGivas Health Care System\n");
        printf("Bem-vindo!\n\n");
        printf("1 - Opcoes de cadastro\n");
        printf("2 - Atendimento\n");
        printf("3 - Pesquisa\n");
        printf("4 - Desfazer ultima operacao\n");
        printf("5 - Carregar / Salvar\n");
        printf("6 - Sobre o programa\n");
        printf("7 - Sair do programa\n");
        printf("Digite qual opcao deseja utilizar: \n");
        scanf("%d", &opcao);

        if (opcao == 1) {
            opcoesCadastro(lista);
        }

        if (opcao == 2){
            opcao2(queue, lista);
        }

        if (opcao == 3){
            opcao3(lista);
        }

        if (opcao == 5){
            opcao5(lista);
        }
        
        if (opcao == 6){
            opcao6();
        }
        
        if (opcao == 7) {
            salvarDados(lista);
            printf("Saindo do programa...\n");
            break;
        }
    }
    
    // Liberar memória
    free(lista);

    return 0;
}
