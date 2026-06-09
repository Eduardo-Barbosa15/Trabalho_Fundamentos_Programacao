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
        fprintf(dados_discentes, "%d\n", discentes[i].matricula);
        fprintf(dados_discentes, "%s\n", discentes[i].nome);
        fprintf(dados_discentes, "%d\n", discentes[i].num_presencas);
        fprintf(dados_discentes, "%.2f %.2f %.2f\n", discentes[i].notas[0], discentes[i].notas[1], discentes[i].notas[2]);
    }
    fclose(dados_discentes);
}

void baixar_dados_discentes_txt(FILE* dados_discentes, discente discentes[])
{
    dados_discentes = fopen("discentes.txt", "r");
    char buffer[100];
    int i = 0;
    while (fgets(buffer, sizeof(buffer), dados_discentes) != NULL) 
    {
        discentes[i].matricula = atoi(buffer);
        if (fgets(discentes[i].nome, sizeof(discentes[i].nome), dados_discentes) != NULL) 
        {
            discentes[i].nome[strcspn(discentes[i].nome, "\n")] = '\0';
        }
        if (fgets(buffer, sizeof(buffer), dados_discentes) != NULL)
        {
            discentes[i].num_presencas = atoi(buffer);
        }
        fscanf(dados_discentes, "%f %f %f\n", &discentes[i].notas[0], &discentes[i].notas[1], &discentes[i].notas[2]);
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

void cadastrar_discente(discente discentes[], FILE* dados_discentes, FILE* num_cadastros)
{
    dados_discentes = fopen("dados_discentes.txt", "r");
    int j;
    num_cadastros = fopen("num_cadastros.txt", "r");
    fscanf(num_cadastros, "%d", &j);
    printf("Posicao do novo discente: %d\n", j);
    if (j == 10)
    {
        printf("Limite de discentes atingido. Nao e possivel cadastrar mais discentes.\n");
        return;
    }
    printf("Digite a matricula do discente: ");
    scanf("%d", &discentes[j].matricula);
    for (int i = 0; i < 10; i++)
    {
        if ((discentes[i].matricula == discentes[j].matricula) && (i != j))
        {
            printf("Matricula ja cadastrada. Digite novamente: ");
            scanf("%d", &discentes[j].matricula);
        }
    }
    printf("Digite o nome do discente: ");
    scanf(" %[^\n]s", &discentes[j].nome);
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
    num_cadastros = fopen("num_cadastros.txt", "w");
    fprintf(num_cadastros, "%d", j + 1);
    fclose(num_cadastros);
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

void atualizar_notas(discente discentes[])
{
    char buffer[100];
    printf("Digite a matricula do discente para atualizar as notas: ");
    scanf("%d", buffer);
    for (int i = 0; i < 10; i++)
    {
        if (discentes[i].matricula == atoi(buffer))
        {
            printf("Digite as novas notas do discente (separadas por espaco): ");
            scanf("%f %f %f", &discentes[i].notas[0], &discentes[i].notas[1], &discentes[i].notas[2]);
            printf("Notas do discente %s atualizadas com sucesso.\n", discentes[i].nome);
            return;
        }
    }
    printf("Discente nao encontrado.\n");
}

int main()
{
    discente discentes[10];
    FILE* num_cadastros = fopen("num_cadastros.txt", "r");
    int opicao = 0;
    if (num_cadastros == NULL)
    {
        fclose(num_cadastros);
        num_cadastros = fopen("num_cadastros.txt", "w+");
        fprintf(num_cadastros, "%d", 0);
    }
    fclose(num_cadastros);
    FILE* dados_discentes = fopen("discentes.txt", "r");
    if (dados_discentes == NULL)
    {
        fclose(dados_discentes);
        dados_discentes = fopen("discentes.txt", "w+");
        valores_iniciais(dados_discentes, discentes);
    }
    baixar_dados_discentes_txt(dados_discentes, discentes);
    while (opicao != 7)
    {
        fclose(dados_discentes);
        printf("Seja bem vindo(a) ao sistema de gerenciamento de discentes!\n");
        printf("Oque deseja fazer?\n");
        printf("1 - Cadastrar discente\n");
        printf("2 - Listar discentes\n");
        printf("3 - Atualizar notas\n");
        printf("4 - Atualizar frequncias\n");
        printf("5 - Remover discente\n");
        printf("6 - Imprimir relatório\n");
        printf("7 - Sair\n");
        printf("Digite o numero da opcao desejada: ");
        scanf("%d", &opicao);
        if (opicao == 1)
        {
            cadastrar_discente(discentes, dados_discentes, num_cadastros);
            salvar_dados_discentes_txt(discentes, dados_discentes);
        }
        if (opicao == 2)
        {
            lista_discentes(discentes);
        }
        if (opicao == 3)
        {
            atualizar_notas(discentes);
            salvar_dados_discentes_txt(discentes, dados_discentes);
        }
    }
    return 0;
}