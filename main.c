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

void valores_iniciais()
{
    int i = 0;
    discente discentes[10];
    for (int j = 0; j < 10; j++)
    {
        discentes[j].matricula = 0;
        strcpy(discentes[j].nome, "");
        discentes[j].num_presencas = 0;
        for (int k = 0; k < 3; k++)
        {
            discentes[j].notas[k] = 0.0;
        }
    }
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
//    }

int main(discente discentes[])
{
    valores_iniciais();
    lista_discentes(discentes);
    return 0;
}