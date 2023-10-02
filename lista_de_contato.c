#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TAMANHO_TABELA 32

// Estrutura para armazenar informações de contato
struct Contato {
    char nome[50];
    char email[50];
    char telefone[20];
};

// Estrutura para um item na tabela de dispersão
struct ItemTabelaHash {
    struct Contato contato;
    int ocupado; // Indica se o slot está ocupado (0 se vazio, 1 se ocupado)
};

// Estrutura para a tabela de dispersão
struct TabelaHash {
    struct ItemTabelaHash tabela[TAMANHO_TABELA];
};

// Função de hash simples (dobra)
int hash(char* chave) {
    int soma = 0;
    for (int i = 0; chave[i] != '\0'; i++) {
        soma += chave[i];
    }
    return soma % TAMANHO_TABELA;
}

// Inicializa a tabela de dispersão
void inicializarTabela(struct TabelaHash* tabela) {
    for (int i = 0; i < TAMANHO_TABELA; i++) {
        tabela->tabela[i].ocupado = 0;
    }
}

// Insere um contato na tabela de dispersão
int inserir(struct TabelaHash* tabela, char* nome, char* email, char* telefone) {
    int indice = hash(email);
    int tentativas = 0;

    while (tabela->tabela[indice].ocupado == 1) {
        // Implementando tratamento de colisões com sondagem linear
        indice = (indice + 1) % TAMANHO_TABELA;
        tentativas++;

        // Se tentamos inserir em todos os slots e não encontramos um vazio, a tabela está cheia
        if (tentativas >= TAMANHO_TABELA) {
            printf("A tabela está cheia. Não é possível adicionar mais contatos.\n");
            return 0; // Falha ao inserir
        }
    }

    struct Contato novoContato;
    strcpy(novoContato.nome, nome);
    strcpy(novoContato.email, email);
    strcpy(novoContato.telefone, telefone);

    tabela->tabela[indice].contato = novoContato;
    tabela->tabela[indice].ocupado = 1; // Marca o slot como ocupado

    return 1; // Inserção bem-sucedida
}

// Edita um contato na tabela de dispersão
int editar(struct TabelaHash* tabela, char* email, char* novoNome, char* novoTelefone) {
    int indice = hash(email);
    int tentativas = 0;

    while (tabela->tabela[indice].ocupado == 1) {
        if (strcmp(tabela->tabela[indice].contato.email, email) == 0) {
            strcpy(tabela->tabela[indice].contato.nome, novoNome);
            strcpy(tabela->tabela[indice].contato.telefone, novoTelefone);
            return 1; // Edição bem-sucedida
        }
        indice = (indice + 1) % TAMANHO_TABELA;
        tentativas++;

        // Se tentamos encontrar o contato em todos os slots e não encontramos, ele não existe
        if (tentativas >= TAMANHO_TABELA) {
            printf("Contato não encontrado.\n");
            return 0; // Falha na edição
        }
    }

    return 0; // Falha na edição (caso o contato não seja encontrado)
}

// Estrutura principal
int main (){
    struct TabelaHash tabela;
    inicializarTabela(&tabela);

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
                    if (inserir(&tabela, nome, email, telefone)) {
                        printf("Contato criado com sucesso!\n");
                    } else {
                        printf("Falha ao criar o contato.\n");
                    }
                    break;
                }
            case 2:
                {
                    char email[50];
                    char novoNome[50];
                    char novoTelefone[20];
                    printf("Digite o email do contato a ser editado: ");
                    scanf("%s", email);
                    printf("Digite o novo nome: ");
                    scanf("%s", novoNome);
                    printf("Digite o novo número de telefone: ");
                    scanf("%s", novoTelefone);
                    if (editar(&tabela, email, novoNome, novoTelefone)) {
                        printf("Contato editado com sucesso!\n");
                    } else {
                        printf("Falha ao editar o contato.\n");
                    }
                    break;
                }
        }
    }
}