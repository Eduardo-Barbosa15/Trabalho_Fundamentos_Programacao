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

void valores_iniciais_local(FILE* dados_discentes, discente discentes[])
{
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
}

void valores_iniciais_file(FILE* dados_discentes, discente discentes[], FILE* posicoes, fpos_t posicao[])
{
    dados_discentes = fopen("discentes.txt", "w");
    posicoes = fopen("posicoes.txt", "w");
    for (int i = 0; i < 10; i++)
    {            
            fprintf(dados_discentes, "%d\n", discentes[i].matricula);
            fprintf(dados_discentes, "%s\n", discentes[i].nome);
            fprintf(dados_discentes, "%d\n", discentes[i].num_presencas);
            fprintf(dados_discentes, "%.2f %.2f %.2f\n", discentes[i].notas[0], discentes[i].notas[1], discentes[i].notas[2]);
            fgetpos(dados_discentes, &posicao[i]);
            fprintf(posicoes, "%lld\n", &posicao[i]);
    }
    fclose(dados_discentes);
    fclose(posicoes);
}

void baixar_dados_discentes_txt(FILE* dados_discentes, discente discentes[], fpos_t posicao[], FILE* posicoes)
{
    dados_discentes = fopen("discentes.txt", "r");
    posicoes = fopen("posicoes.txt", "r");
    char buffer[100];
    int i = 0;
    while(fscanf(dados_discentes, "%[^\n]\n", buffer) == 1)
    {
        discentes[i].matricula = atoi(buffer);
        strcpy(discentes[i].nome, buffer);
        discentes[i].num_presencas = atoi(buffer);
        for(int j = 0; fscanf(dados_discentes, "%f %f %f\n", &discentes[i].notas[0], &discentes[i].notas[1], &discentes[i].notas[2]) == 3; j++);
        i++;
    }
    for(int j = 0; j < 10; j++)
    {
        fscanf(posicoes, "%lld\n", &posicao[j]);
    }
    fclose(dados_discentes);
    fclose(posicoes);
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

void cadastrar_discente(discente discentes[], FILE* dados_discentes, FILE* posicoes, fpos_t posicao[])
{
    char buffer[100];
    dados_discentes = fopen("dados_discentes.txt", "r");
    int j = 0;
    for(int i = 10; i >= 0; i--)
    {
        posicao[i] -= 24;
        fsetpos(dados_discentes, &posicao[i]);
        fscanf(dados_discentes, "%s", &buffer);
        if ('buffer' == '\n')
        {
            j = i;
        }
    }
    if (j == 10)
    {
        printf("Limite de discentes atingido. Nao e possivel cadastrar mais discentes.\n");
        return;
    }
    printf("Digite a matricula do discente: ");
    scanf("%d", &discentes[j].matricula);
    for (int i = 0; i < 10; i++)
    {
        if (discentes[i].matricula == discentes[j].matricula && i != j)
        {
            printf("Matricula ja cadastrada. Digite novamente: ");
            scanf("%d", &discentes[j].matricula);
            i--;
        }
    }
    printf("Digite o nome do discente: ");
    scanf(" %[^\n]s", discentes[j].nome);
    if (discentes[j].nome[0] >= 'a' && discentes[j].nome[0] <= 'z')
    {
        discentes[j].nome[0] -= 32;
    }
    discentes[j].num_presencas = 0;
    for (int k = 0; k < 3; k++)
    {
        discentes[j].notas[k] = 0.0;
    }
    printf("Discente %s cadastrado com sucesso.\n", discentes[j].nome);
    fclose(dados_discentes);
}

void salvar_dados_discentes_txt(discente discentes[], FILE* dados_discentes)
{
    dados_discentes = fopen("discentes.txt", "w");
    for (int i = 0; i < 10; i++)
    {            
            fprintf(dados_discentes, "%d\n", discentes[i].matricula);
            fprintf(dados_discentes, "%s\n", discentes[i].nome);
            fprintf(dados_discentes, "%d\n", discentes[i].num_presencas);
            fprintf(dados_discentes, "%.2f %.2f %.2f\n", discentes[i].notas[0], discentes[i].notas[1], discentes[i].notas[2]);
    }
    fclose(dados_discentes);
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
    fpos_t posicao[10];
    FILE* posicoes = fopen("posicoes.txt", "r");
    if (posicoes == NULL)
    {
        fclose(posicoes);
        posicoes = fopen("posicoes.txt", "w+");
    }
    fclose(posicoes);
    FILE* dados_discentes = fopen("discentes.txt", "r");
    valores_iniciais_local(dados_discentes, discentes);
    if (dados_discentes == NULL)
    {
        fclose(dados_discentes);
        posicoes = fopen("posicoes.txt", "w+");
        valores_iniciais_file(dados_discentes, discentes, posicoes, posicao);
    }
    fclose(dados_discentes);
    dados_discentes = fopen("discentes.txt", "r");
    baixar_dados_discentes_txt(dados_discentes, discentes, posicao, posicoes);
    fclose(dados_discentes);
    cadastrar_discente(discentes, dados_discentes, posicoes, posicao);
    salvar_dados_discentes_txt(discentes, dados_discentes);
    lista_discentes(discentes);
    return 0;
}