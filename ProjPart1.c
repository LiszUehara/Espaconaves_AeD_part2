#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <locale.h>

#define MAX_PASSAGEIROS 10
#define MAX_RECURSOS 5

typedef struct {
    char nome[50];
    int idade;
    char planeta[50];
    int identificador;
} Passageiro;

typedef struct {
    int prioridade;
    Passageiro passageiros[MAX_PASSAGEIROS];
    char recursos[MAX_RECURSOS][50];
} Espaconave;

void verificar_prioridade(Espaconave *espaconave) {
    if (rand() < RAND_MAX * 0.1) {
        espaconave->prioridade = rand() % 100 + 1;
    }
}

void heapify(Espaconave fila[], int tamanho_fila, int indice) {
    int maior = indice;
    int filho_esq = 2 * indice + 1;
    int filho_dir = 2 * indice + 2;

    if (filho_esq < tamanho_fila && fila[filho_esq].prioridade > fila[maior].prioridade) {
        maior = filho_esq;
    }

    if (filho_dir < tamanho_fila && fila[filho_dir].prioridade > fila[maior].prioridade) {
        maior = filho_dir;
    }

    if (maior != indice) {
        Espaconave temp = fila[indice];
        fila[indice] = fila[maior];
        fila[maior] = temp;
        heapify(fila, tamanho_fila, maior);
    }
}

void inserir_espaconave(Espaconave fila[], int *tamanho_fila, Espaconave nova_espaconave) {
    verificar_prioridade(&nova_espaconave);
    (*tamanho_fila)++;
    int i = *tamanho_fila - 1;

    while (i > 0 && nova_espaconave.prioridade > fila[(i - 1) / 2].prioridade) {
        fila[i] = fila[(i - 1) / 2];
        i = (i - 1) / 2;
    }

    fila[i] = nova_espaconave;
}

Espaconave remover_espaconave(Espaconave fila[], int *tamanho_fila) {
    Espaconave raiz = fila[0];
    fila[0] = fila[*tamanho_fila - 1];
    (*tamanho_fila)--;
    heapify(fila, *tamanho_fila, 0);
    return raiz;
}

int main() {
    setlocale(LC_ALL, "Portuguese");
    srand(time(NULL));
    Espaconave fila_de_prioridades[100];  // Tamanho da fila ajustável
    int tamanho_fila = 0;

    while (1) {
        printf("1. Inserir espaçonave\n");
        printf("2. Remover espaçonave\n");
        printf("3. Sair\n");
        int opcao;
        scanf("%d", &opcao);

        if (opcao == 1) {
            Espaconave nova_espaconave;
            nova_espaconave.prioridade = rand() % 100 + 1;
            for (int i = 0; i < MAX_PASSAGEIROS; i++) {
                Passageiro novo_passageiro;
                printf("Digite o nome do passageiro %d: ", i + 1);
                scanf("%s", novo_passageiro.nome);
                nova_espaconave.passageiros[i] = novo_passageiro;
}

for (int i = 0; i < MAX_RECURSOS; i++) {
    printf("Digite o recurso %d: ", i + 1);
    scanf("%s", nova_espaconave.recursos[i]);
}

            inserir_espaconave(fila_de_prioridades, &tamanho_fila, nova_espaconave);
        } else if (opcao == 2) {
            if (tamanho_fila > 0) {
                Espaconave espaconave_removida = remover_espaconave(fila_de_prioridades, &tamanho_fila);
                printf("Espaçonave removida: Prioridade %d\n", espaconave_removida.prioridade);
            } else {
                printf("Fila vazia\n");
            }
        } else if (opcao == 3) {
            break;
        } else {
            printf("Opção inválida\n");
        }
    }

    return 0;
}
