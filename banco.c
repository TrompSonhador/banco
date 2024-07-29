#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include <time.h>
#include <stdbool.h>

#define MAX 60

struct transacao {
    char tipo[MAX];
    float valor;
    char data_hora[MAX];
};

struct usuario {
    char nome[MAX];
    int idade;
    char email[MAX];
    char cpf[MAX];
    char senha[MAX];
    float saldo;
    struct transacao *historico;
    int numTransacoes;
};

typedef struct usuario usuario;
typedef struct transacao transacao;

int s;
int numUsuarios = 0;
usuario *cip = NULL;

void registrar_transacao(usuario *u, const char *tipo, float valor) {

    time_t now;
    struct tm *tm_info;
    char buffer[26];

    time(&now);
    tm_info = localtime(&now);

    strftime(buffer, 26, "%Y-%m-%d %H:%M:%S", tm_info);

    u->historico = realloc(u->historico, (u->numTransacoes + 1) * sizeof(transacao));
    strcpy(u->historico[u->numTransacoes].tipo, tipo);
    u->historico[u->numTransacoes].valor = valor;
    strcpy(u->historico[u->numTransacoes].data_hora, buffer);

    u->numTransacoes++;
}


void exibir_historico(usuario *u) {
    printf("Histórico de Transações:\n");
    for (int i = 0; i < u->numTransacoes; i++) {
        printf("Tipo: %s | Valor: %.2f | Data e Hora: %s\n",
               u->historico[i].tipo, u->historico[i].valor, u->historico[i].data_hora);
    }
    printf("\n");
}


void mudar_dados(usuario *cip) {
    setlocale(LC_ALL, "Portuguese_Brazil.UTF-8");
    char escolha[MAX];
    char sucesso[MAX];
    char senha[MAX];
    int repeticao;

    sprintf(sucesso, "Modificação feita com sucesso\n");

    printf("Qual dado você quer modificar? (nome, idade, email, cpf, senha)\n");
    scanf(" %59[^\n]", escolha);
    printf("\n");

    if (strcmp(escolha, "nome") == 0) {
        char novo_nome[MAX];

        do{
        repeticao = 0;

        printf("Digite o novo nome do usuário: ");
        scanf(" %59[^\n]", novo_nome);

        for(int i=0; i<numUsuarios; i++){
            if(strcmp(novo_nome, cip[i].nome) == 0){
                printf("\n");
                printf("Este nome já existe em ou outro usuário\n");
                repeticao = 1;
                break;
            }
        }
        }while(repeticao == 1);

        printf("Coloque sua senha\n");
        scanf(" %59[^\n]", senha);

        while(strcmp(senha, cip->senha) != 0){
            printf("Senha incorreta\n");
            printf("Coloque sua senha\n");
            scanf(" %59[^\n]", senha);
        }

        strcpy(cip->nome, novo_nome);
        puts(sucesso);

    } else if (strcmp(escolha, "idade") == 0) {
        int nova_idade;

        printf("Digite a idade do usuário: ");
        scanf("%d", &nova_idade);

        while(nova_idade < 18){
            printf("\n");
            printf("Esta conta é para maiores de 18 anos\n");
            printf("Digite a idade do usuário: ");
            scanf("%d", &nova_idade);
       }

       printf("Coloque sua senha\n");
       scanf(" %59[^\n]", senha);

        while(strcmp(senha, cip->senha) != 0){
            printf("Senha incorreta\n");
            printf("Coloque sua senha\n");
            scanf(" %59[^\n]", senha);
        }

        cip->idade = nova_idade;
        puts(sucesso);

    } else if (strcmp(escolha, "email") == 0) {
        char novo_email[MAX];

        bool gmail_com(){
            return strstr(novo_email, "@gmail.com") == NULL;
        }

        bool yahoo_com(){
            return strstr(novo_email, "@yahoo.com") == NULL;
        }

        bool outlook_com(){
            return strstr(novo_email, "@outlook.com") == NULL;
        }

        bool hotmail_com(){
            return strstr(novo_email, "@hotmail.com") == NULL;
        }

        bool iCloud_com(){
            return strstr(novo_email, "@icloud.com") == NULL;
        }


        do{
            repeticao = 0;

            printf("Digite o email do usuário: ");
            scanf(" %59[^\n]", novo_email);

            while(gmail_com() && yahoo_com() && outlook_com() && hotmail_com() && iCloud_com()){
                printf("Email inválido\n");
                printf("Digite o email do usuário: ");
                scanf(" %59[^\n]", novo_email);
            }

            for(int i=0; i<numUsuarios; i++){
                if(strcmp(novo_email, cip[i].email) == 0){
                    printf("Este email já está inserido em uma outra conta\n");
                    repeticao = 1;
                    break;
                }
            }
        }while(repeticao == 1);

        printf("Coloque sua senha\n");
        scanf(" %59[^\n]", senha);

        while(strcmp(senha, cip->senha) != 0){
            printf("Senha incorreta\n");
            printf("Coloque sua senha\n");
            scanf(" %59[^\n]", senha);
        }
        strcpy(cip->email, novo_email);
        puts(sucesso);

    } else if (strcmp(escolha, "cpf") == 0) {
        char novo_cpf[MAX];

        do{
        repeticao = 0;

        printf("Digite o CPF do usuário: ");
        scanf(" %59[^\n]", novo_cpf);

        while(strlen(novo_cpf) != 11){
            printf("\n");
            printf("CPF inválido\n");
            printf("Digite o CPF do usuário: ");
            scanf(" %59[^\n]", novo_cpf);
        }

        for(int i=0; i<numUsuarios; i++){
            if(strcmp(novo_cpf, cip[i].cpf) == 0){
                printf("\n");
                printf("Este CPF já está inserido em uma outra conta\n");
                repeticao = 1;
                break;
            }
        }
    }while(repeticao == 1);

        printf("Coloque sua senha\n");
        scanf(" %59[^\n]", senha);

        while(strcmp(senha, cip->senha) != 0){
            printf("Senha incorreta\n");
            printf("Coloque sua senha\n");
            scanf(" %59[^\n]", senha);
        }
        strcpy(cip->cpf, novo_cpf);
        puts(sucesso);

    } else if (strcmp(escolha, "senha") == 0) {
        char nova_senha[MAX];
        printf("Digite a nova senha\n");
        scanf(" %59[^\n]", nova_senha);

        printf("Coloque sua senha atual\n");
        scanf(" %59[^\n]", senha);

        while(strcmp(senha, cip->senha) != 0){
            printf("Senha incorreta\n");
            printf("Coloque sua senha atual\n");
            scanf(" %59[^\n]", senha);
        }
        strcpy(cip->senha, nova_senha);
        puts(sucesso);

    } else {
        printf("Opção não disponível\n");
    }
}


void consultar_dados(usuario *cip) {
    setlocale(LC_ALL, "Portuguese_Brazil.UTF-8");
    printf("Nome: %s\n", cip->nome);
    printf("Idade: %d\n", cip->idade);
    printf("Email: %s\n", cip->email);
    printf("CPF: %s\n", cip->cpf);
    printf("Senha: %s\n\n", cip->senha);

    char modificar[MAX];

    do{
    printf("Você quer modificar algum dado? Digite sim ou nao\n");
    scanf(" %59[^\n]", modificar);
    printf("\n");

    while(strcmp(modificar, "sim") != 0 &&  strcmp(modificar, "nao") != 0){
        printf("Opção não disponível\nDigite sim ou nao\n");
        scanf(" %59[^\n]", modificar);
        printf("\n");}

    if (strcmp(modificar, "sim") == 0) {
        mudar_dados(cip);
    }

    else if (strcmp(modificar, "nao") == 0){
        return;
    }

   }while(strcmp(modificar, "sim") == 0);

}


void consultar_saldo(usuario *cip){
    setlocale(LC_ALL, "Portuguese_Brazil.UTF-8");
    printf("Seu saldo é %.2f\n\n", cip->saldo);
}


void emprestimo(usuario *cip){
    setlocale(LC_ALL, "Portuguese_Brazil.UTF-8");

    float valor;
    char senha[MAX];

    printf("Qual valor você quer emprestar?\n");
    scanf("%f", &valor);
    printf("\n");
    printf("Digite sua senha\n");
    scanf(" %59[^\n]", senha);
    printf("\n");

    while(strcmp(senha, cip->senha) != 0){
        printf("Senha incorreta\n");
        printf("Digite sua senha\n");
        scanf(" %59[^\n]", senha);
        printf("\n");

    }

    cip->saldo += valor;
    printf("Empréstimo feito com sucesso\n\n");
    registrar_transacao(cip, "Empréstimo", valor);
}


void transferencia(usuario *cip){
     setlocale(LC_ALL, "Portuguese_Brazil.UTF-8");

     if(numUsuarios <= 1){
        printf("Opção não disponível, pois há a necessidade de 2 usuários ou mais\n");
        return;
     }
     else{
        char email[MAX];
        printf("Digite o email do usuário que ira receber:\n");
        scanf(" %59[^\n]", email);
        printf("\n");

        for (int i = 0; i < numUsuarios; i++) {
        if (strcmp(email, cip[i].email) == 0) {

            float valor_transfe;
            printf("Digite o valor que será transferido\n");
            scanf("%f", &valor_transfe);

            while(valor_transfe > cip->saldo){
                 printf("O valor ultrapassa o saldo\nDigite um valor inferior ou igual ao saldo\n");
                 scanf("%f", &valor_transfe);
            }

            char senha[MAX];
            printf("Digite sua senha: ");
            scanf(" %59[^\n]", senha);

            while (strcmp(senha, cip->senha) != 0) {
                printf("Senha incorreta. Digite novamente: ");
                scanf(" %59[^\n]", senha);
            }
            printf("Transferência feita com sucesso\n");
            cip[i].saldo += valor_transfe;
            cip->saldo -= valor_transfe;
            registrar_transacao(cip, "Transferência", valor_transfe);
            registrar_transacao(&cip[i], "Recebimento de transferência", valor_transfe);
            return;
        }
    }
    printf("Nenhum usuário encontrado com o email \"%s\".\n", email);
    }
}


void app(usuario *cip) {
    setlocale(LC_ALL, "Portuguese_Brazil.UTF-8");
    int i;

    do {
        printf("Digite o número de acordo com as opções que você quer\n\n");
        printf("1 - Consultar dados do usuário\n");
        printf("2 - Consultar saldo\n");
        printf("3 - Fazer empréstimo\n");
        printf("4 - Fazer transferência\n");
        printf("5 - Consultar histórico de transação\n");
        printf("6 - Sair da conta\n");
        scanf("%d", &i);
        printf("\n");

        switch (i) {

            case 1:
                consultar_dados(cip);
                break;

            case 2:
                consultar_saldo(cip);
                break;

            case 3:
                emprestimo(cip);
                break;

            case 4:
                transferencia(cip);
                break;

            case 5:
                exibir_historico(cip);
                break;

            case 6:
                return;
                break;

            default:
                printf("Opção não disponível\n");
        }
    } while (i != 6);
}


void cadastro() {
    numUsuarios++;

    setlocale(LC_ALL, "Portuguese_Brazil.UTF-8");
    cip = realloc(cip, numUsuarios * sizeof(usuario));

    if (cip == NULL) {
        printf("Erro ao alocar memória.\n");
        return;
    }

    char novo_nome[MAX];
    int repeticao;

    do{
        repeticao = 0;

        printf("Digite o nome do usuário: ");
        scanf(" %59[^\n]", novo_nome);

        for(int i=0; i<numUsuarios; i++){
            if(strcmp(novo_nome, cip[i].nome) == 0){
                printf("\n");
                printf("Este nome já existe\n");
                repeticao = 1;
                break;
            }
        }
    }while(repeticao == 1);
    strcpy(cip[numUsuarios - 1].nome, novo_nome);

    int nova_idade;

    printf("Digite a idade do usuário: ");
    scanf("%d", &nova_idade);

    while(nova_idade < 18){
        printf("\n");
        printf("Esta conta é para maiores de 18 anos\n");
        printf("Digite a idade do usuário: ");
        scanf("%d", &nova_idade);
    }
    cip[numUsuarios - 1].idade = nova_idade;

    char novo_email[MAX];


    bool gmail_com(){
        return strstr(novo_email, "@gmail.com") == NULL;
    }

    bool yahoo_com(){
        return strstr(novo_email, "@yahoo.com") == NULL;
    }

    bool outlook_com(){
        return strstr(novo_email, "@outlook.com") == NULL;
    }

    bool hotmail_com(){
        return strstr(novo_email, "@hotmail.com") == NULL;
    }

    bool iCloud_com(){
        return strstr(novo_email, "@icloud.com") == NULL;
    }


    do{
        repeticao = 0;

        printf("Digite o email do usuário: ");
        scanf(" %59[^\n]", novo_email);

        while(gmail_com() && yahoo_com() && outlook_com() && hotmail_com() && iCloud_com()){
            printf("Email inválido\n");
            printf("Digite o email do usuário: ");
            scanf(" %59[^\n]", novo_email);
        }

        for(int i=0; i<numUsuarios; i++){
            if(strcmp(novo_email, cip[i].email) == 0){
                printf("Este email já está inserido em uma outra conta\n");
                repeticao = 1;
                break;
            }
        }
    }while(repeticao == 1);
    strcpy(cip[numUsuarios - 1].email, novo_email);

    char novo_cpf[MAX];

    do{
        repeticao = 0;

        printf("Digite o CPF do usuário: ");
        scanf(" %59[^\n]", novo_cpf);

        while(strlen(novo_cpf) != 11){
            printf("\n");
            printf("CPF inválido\n");
            printf("Digite o CPF do usuário: ");
            scanf(" %59[^\n]", novo_cpf);
        }

        for(int i=0; i<numUsuarios; i++){
            if(strcmp(novo_cpf, cip[i].cpf) == 0){
                printf("\n");
                printf("Este CPF já está inserido em uma outra conta\n");
                repeticao = 1;
                break;
            }
        }
    }while(repeticao == 1);
    strcpy(cip[numUsuarios - 1].cpf, novo_cpf);

    char nova_senha[MAX];

    printf("Crie sua senha inicial com 4 digitos: ");
    scanf(" %59[^\n]", nova_senha);

    while(strlen(nova_senha) != 4){
        printf("Senha inválida\n");
        printf("Crie sua senha inicial com 4 digitos: ");
        scanf(" %59[^\n]", nova_senha);
        printf("\n");
        }
    strcpy(cip[numUsuarios - 1].senha, nova_senha);

    printf("\n");

    printf("Usuário criado com sucesso\n\n");
}


void login() {
    setlocale(LC_ALL, "Portuguese_Brazil.UTF-8");

    if (numUsuarios == 0) {
        printf("Não há usuários cadastrados.\n");
        return;
    }

    char email[MAX];
    printf("Digite o seu email: ");
    scanf(" %59[^\n]", email);
    printf("\n");

    for (int i = 0; i < numUsuarios; i++) {
        if (strcmp(email, cip[i].email) == 0) {
            char senha[MAX];
            printf("Digite sua senha: ");
            scanf(" %59[^\n]", senha);

            while (strcmp(senha, cip[i].senha) != 0) {
                printf("Senha incorreta. Digite novamente: ");
                scanf(" %59[^\n]", senha);
            }

            printf("Bem-vindo à sua conta %s\n", cip[i].nome);
            printf("\n");
            app(&cip[i]);
            return;
        }
    }
    printf("Nenhum usuário encontrado com o email \"%s\".\n", email);
}



int main() {
    setlocale(LC_ALL, "Portuguese_Brazil.UTF-8");

    printf("Bem-vindo ao Banco Panamericano\n\n");

    do {
        printf("Digite 1 para cadastrar\n");
        printf("Digite 2 para fazer login\n");
        printf("Digite 3 para fechar o aplicativo\n");


        scanf("%d", &s);
        printf("\n");

        switch (s) {
            case 1:
                cadastro();
                break;
            case 2:
                login();
                break;
            case 3:
                printf("Fechando o aplicativo\n");
                break;
            default:
                printf("Opção inválida. Por favor, tente novamente.\n");
        }
    } while (s != 3);

    free(cip);
    return 0;
}
