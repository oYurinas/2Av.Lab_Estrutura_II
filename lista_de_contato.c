#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Estrutura para armazenar informações de contato
struct Contato {
    char nome[50];
    char email[50];
    char telefone[20];
};


struct ItemTabelaHash {
    struct Contato contato;
    int ocupado;
};

struct TabelaHash {
    struct ItemTabelaHash tabela[TAMANHO_TABELA];
};

int hash(char* chave) {
    int soma = 0;
    for (int i = 0; chave[i] != '\0'; i++) {
        soma += chave[i];
    }
    return soma % TAMANHO_TABELA;
}

void inicializarTabela(struct TabelaHash* tabela) {
    for (int i = 0; i < TAMANHO_TABELA; i++) {
        tabela->tabela[i].ocupado = 0;
    }
}

// Estrutura principal
int main (){
    while(1){
        printf("\nMenu:\n");
        printf("1. Criar Contato\n");
        printf("2. Editar Contato\n");
        printf("3. Listar Contatos\n");
        printf("4. Exportar Contatos\n");
        printf("5. Apagar Contato\n");
        printf("6. Sair\n");

        int escolha;
        printf("Escolha uma opcao: ");
        scanf("%d", &escolha);

        switch (escolha) {
            case 1:
                {
                    char nome[50];
                    char email[50];
                    char telefone[20];
                    printf("Digite o nome do contato: ");
                    scanf("%s", nome);
                    printf("Digite o email do contato: ");
                    scanf("%s", email);
                    printf("Digite o telefone do contato: ");
                    scanf("%s", telefone);

                    break;
                }
        }
    }
}