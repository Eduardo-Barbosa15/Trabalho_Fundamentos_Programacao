#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct
{
    int matricula;
    char nome[100];
    int num_presencas;
    float notas[3];
} discente;

void valores_iniciais(FILE* dados_discentes, discente discentes[])
{
    int i = 0;
    for (int j = 0; j < 10; j++)
    {
        discentes[j].matricula = 0;
        strcpy(discentes[j].nome, " ");
        discentes[j].num_presencas = 0;
        for (int k = 0; k < 3; k++)
        {
            discentes[j].notas[k] = 0.0;
        }
    }
    dados_discentes = fopen("discentes.txt", "w");
    for (int i = 0; i < 10; i++)
    {            
            fprintf(dados_discentes, "********************************\n");
            fprintf(dados_discentes, "matricula: %d\n", discentes[i].matricula);
            fprintf(dados_discentes, "nome: %s\n", discentes[i].nome);
            fprintf(dados_discentes, "presencas: %d\n", discentes[i].num_presencas);
            fprintf(dados_discentes, "notas: %.2f, %.2f, %.2f\n", discentes[i].notas[0], discentes[i].notas[1], discentes[i].notas[2]);
            fprintf(dados_discentes, "********************************\n");
    }
    fclose(dados_discentes);
}

void baixar_dados_discentes_txt(FILE* dados_discentes, discente discentes[])
{
    dados_discentes = fopen("discentes.txt", "r");
    char buffer[100];
    int i = 0;
    while(fscanf(dados_discentes, "%s", buffer) == 1)
    {
        if (buffer[0] != '*' && buffer[0] != 'm' && buffer[0] != 'n' && buffer[0] != 'p')
        {
            discentes[i].matricula = atoi(buffer);
            strcpy(discentes[i].nome, buffer);
            discentes[i].num_presencas = atoi(buffer);
            discentes[i].notas[0] = atof(buffer);
            discentes[i].notas[1] = atof(buffer);
            discentes[i].notas[2] = atof(buffer);
        }
        i++;
    }
    fclose(dados_discentes);
}

void lista_discentes(discente discentes[])
{
    for (int i = 0; i < 10; i++)
    {            
            printf("Discente: %d\n", i + 1);
            printf("********************************\n");
            printf("Matricula: %d\n", discentes[i].matricula);
            printf("Nome: %s\n", discentes[i].nome);
            printf("Numero de Presencas: %d\n", discentes[i].num_presencas);
            printf("Notas: %.2f, %.2f, %.2f\n", discentes[i].notas[0], discentes[i].notas[1], discentes[i].notas[2]);
            printf("********************************\n");
    }
}

void cadastrar_discente(discente discentes[], int i)
{
    if (i >= 10)
    {
        printf("Limite de discentes atingido. Nao e possivel cadastrar mais discentes.\n");
        return;
    }
    printf("Digite a matricula do discente: ");
    scanf("%d", &discentes[i].matricula);
    for (int j = 0; j < 10; j++)
    {
        if (discentes[j].matricula == discentes[i].matricula && j != i)
        {
            printf("Matricula ja cadastrada. Digite novamente: ");
            scanf("%d", &discentes[i].matricula);
            j = -1;
        }
    }
    printf("Digite o nome do discente: ");
    scanf(" %[^\n]s", discentes[i].nome);
    discentes[i].nome[0] = toupper(discentes[i].nome[0]);
    discentes[i].num_presencas = 0;
    for (int j = 0; j < 3; j++)
    {
        discentes[i].notas[j] = 0.0;
    }
    printf("Discente %s cadastrado com sucesso.\n", discentes[i].nome);
    i++;
}

///void atualizar_notas(discente discentes[])
//{
//    printf("Digite a matricula do discente para atualizar as notas: ");
//    scanf("%d", &discentes[0].matricula);
//    for (int i = 0; i < 10; i++)
//    {}
//}

int main()
{
    discente discentes[10];
    FILE* dados_discentes = fopen("discentes.txt", "W");
    if (dados_discentes == NULL)
    {
        valores_iniciais(dados_discentes, discentes);
    }
    fclose(dados_discentes);
    dados_discentes = fopen("discentes.txt", "r");
    baixar_dados_discentes_txt(dados_discentes, discentes);
    fclose(dados_discentes);
    lista_discentes(discentes);
    return 0;
}