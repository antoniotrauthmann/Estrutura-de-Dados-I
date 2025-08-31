//Agenda usando Struct
//Aluno : Antonio Andrade Trauthmann
#include <stdio.h>
#include <string.h>
#define max_contatos 100

typedef struct
{
    int id;
    char nome[128];
    char telefone[16];
    int apagado;
}Agenda;


int carregar_agenda(Agenda agendas[]) {
    FILE *carregar_agenda = fopen("agenda.txt", "r");
    char linha[256];
    int total = 0;
    if (carregar_agenda == NULL) {
        printf("Erro ao abrir arquivo agenda.txt ao inicializar o programa.\n");
    }
    while (fgets(linha, sizeof(linha), carregar_agenda) != NULL && total < max_contatos) {
        if (sscanf(linha,"%d;%127[^;];%15[^;];%d",&agendas[total].id,agendas[total].nome,agendas[total].telefone,&agendas[total].apagado) == 4) {
            total++;
        }
    }
    fclose(carregar_agenda);
    printf("agenda carregada com sucesso.inicializando programa.\n");
    return total;
}

int registrar_contato(Agenda agendas[],int total) {
    Agenda novo;
    novo.id = total;
    novo.apagado = 0;

    printf("digite o nome do contato:\n");
    scanf(" %127[^\n]",novo.nome);

    printf("digite o telefone do contato\n(exemplo:063-XXXXX-XXXX)\n");
    scanf(" %15[^\n]",novo.telefone);
    agendas[total] = novo;
    printf("contato registrado.\n");

    return total + 1;

}

int busca_contato(Agenda agendas[], int total, char chave[]) {
    for (int i = 0; i < total; i++) {
        if (!agendas[i].apagado && (strcmp(chave, agendas[i].nome) == 0 || strcmp(chave, agendas[i].telefone) == 0)) {
            return i;
        }
    }
    return -1;
}

// verificar dps que corrigir registrar contato
//apagar_contato parece deboa

void apagar_contato(Agenda agendas[],int total) {
    char chave[128];
    int opc;
    printf("digite o telefone ou nome do contato que deseja excluir.\n");
    fflush(stdin);
    scanf(" %127[^\n]",chave);

    int busca = busca_contato(agendas, total, chave);
    if (busca >= 0) {
        printf("encontrado: %s - %s.\n", agendas[busca].nome, agendas[busca].telefone);
        printf("confirmar exclusao? (1)sim (0)nao.\n");
        scanf("%d", &opc);
        if (opc == 1) {
            agendas[busca].apagado = 1;
            printf("contato apagado.\n");
        }
    }
    else {
        printf("contato nao encontrado.\n");
    }
}

//salvar deboa
void salvar_agenda(Agenda agendas[],int total) {
    FILE *salvar_arquivo = fopen("agenda.txt", "w");

    if (salvar_arquivo == NULL) {
        printf("Erro na abertura do arquivo.\n");
        return;
    }

    for (int i = 0; i < total; ++i) {
        fprintf(salvar_arquivo, "%d;%s;%s;%d\n",agendas[i].id,agendas[i].nome,agendas[i].telefone,agendas[i].apagado);
    }

    fclose(salvar_arquivo);
    printf("agenda salva em 'agenda.txt'.\n");
}

//main deboa

int main(){
    Agenda agendas[max_contatos];

    int total = carregar_agenda(agendas);

    int opc;
    do {
        printf("\n[1]registrar novo contato.\n");
        printf("[2]apagar um contato\n");
        printf("[3]buscar contato por telefone ou nome.\n");
        printf("[4]Salvar agenda em disco.\n");
        printf("[5]sair\n");

        scanf("%d", &opc);

        switch (opc){
        case 1:
                total = registrar_contato(agendas,total);
            break;
        case 2:
                apagar_contato(agendas,total);
            break;
        case 3:{
                char chave[128];
                printf("digite o nome ou telefone do contato.\n");
                scanf(" %127[^\n]",chave);
                int id = busca_contato(agendas,total,chave);
                if (id >= 0) {
                    printf("contato encontrado: %s - %s .\n",agendas[id].nome,agendas[id].telefone);
                }
                else
                    printf("contato nao encontrado.\n");
        }
            break;
            case 4:
                salvar_agenda(agendas,total);
                break;
        }

    } while (opc != 5);
}