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

void lista_discentes(discente discentes[], FILE* num_cadastros)
{
    int j;
    num_cadastros = fopen("num_cadastros.txt", "r");
    fscanf(num_cadastros, "%d", &j);
    fclose(num_cadastros);
    if (discentes[0].nome[0] == ' ')
    {
        printf("Nenhum discente cadastrado.\n");
        return;
    }
    for (int i = 0; i < j; i++)
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
    fclose(num_cadastros);
    if (j == 10)
    {
        printf("Limite de discentes atingido. Nao e possivel cadastrar mais discentes.\n");
        return;
    }
    printf("********************************\n");
    printf("Digite a matricula do discente: ");
    scanf("%d", &discentes[j].matricula);
    printf("********************************\n");
    for (int i = 0; i < 10; i++)
    {
        if ((discentes[i].matricula == discentes[j].matricula) && (i != j))
        {
            printf("*******************************************\n");
            printf("Matricula ja cadastrada. Digite novamente: ");
            scanf("%d", &discentes[j].matricula);
            printf("*******************************************\n");
            i--;
        }
    }
    printf("********************************\n");
    printf("Digite o nome do discente: ");
    scanf(" %[^\n]s", &discentes[j].nome);
    printf("********************************\n");
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
    int buffer;
    printf("Digite a matricula do discente para atualizar as notas: ");
    scanf("%d", &buffer);
    for (int i = 0; i < 10; i++)
    {
        if (discentes[i].matricula == buffer)
        {
            printf("Digite as novas notas do discente (separadas por espaco): ");
            scanf("%f %f %f", &discentes[i].notas[0], &discentes[i].notas[1], &discentes[i].notas[2]);
            printf("Notas do discente %s atualizadas com sucesso.\n", discentes[i].nome);
            return;
        }
    }
    printf("Discente nao encontrado, tente novamente.\n");
}

void atualizar_frequencias(discente discentes[])
{
    int buffer;
    printf("Digite a matricula do discente para atualizar as frequencias: ");
    scanf("%d", &buffer);
    for (int i = 0; i < 10; i++)
    {
        if (discentes[i].matricula == buffer)
        {
            printf("Digite o numero de presencas do discente: ");
            scanf("%d", &discentes[i].num_presencas);
            if(discentes[i].num_presencas > 30)
            {
                printf("O numero de presencas do discente deveser no maximo 30, digite um valor valido: ");
                scanf("%d", &discentes[i].num_presencas);
            }
            
            printf("Frequencias do discente %s atualizadas com sucesso.\n", discentes[i].nome);
            return;
        }
    }
    printf("Discente nao encontrado, tente novamente.\n");
}

void remove_discente(discente discentes[], FILE* num_cadastros, FILE* dados_discentes)
{
    int j;
    num_cadastros = fopen("num_cadastros.txt", "r");
    fscanf(num_cadastros, "%d", &j);
    fclose(num_cadastros);
    int buffer;
    printf("Digite a matricula do discente para remover: ");
    scanf("%d", &buffer);
    for (int i = 0; i < 10; i++)
    {
        if(j == 0)
        {
            printf("Nenhum discente cadastrado.\n");
            return;
        }
        if (discentes[i].matricula == buffer)
        {
            discentes[i].matricula = 0;
            strcpy(discentes[i].nome, " ");
            discentes[i].num_presencas = 0;
            for (int k = 0; k < 3; k++)
            {
                discentes[i].notas[k] = 0.0;
            }
            num_cadastros = fopen("num_cadastros.txt", "r");
            int j;
            fscanf(num_cadastros, "%d", &j);
            j--;
            num_cadastros = fopen("num_cadastros.txt", "w");
            fprintf(num_cadastros, "%d", j);
            fclose(num_cadastros);
            printf("Discente removido com sucesso.\n");
            return;
        }
    }
    printf("Discente nao encontrado, tente novamente.\n");
}

void imprimir_relatorio(discente discentes[], FILE* num_cadastros)
{
    int j;
    num_cadastros = fopen("num_cadastros.txt", "r");
    fscanf(num_cadastros, "%d", &j);
    fclose(num_cadastros);
    int contador = 0;
    printf("***********************\n");
    printf("Relatorio de discentes:\n");
    printf("***********************\n");
    printf("Numero de discentes aprovados por nota:\n");
    if(j == 0)
    {
        printf("Nenhum discente cadastrado.\n");
        return;
    }
    for(int i = 0; i < j; i++)
    {
        int media_notas = (discentes[i].notas[0] + discentes[i].notas[1] + discentes[i].notas[2]) / 3;
        if (media_notas >= 7.0 )
        {
            contador++;
        }
    }
    printf("%d\n", contador);
    printf("********************************\n");
    printf("Numero de discentes reprovados por frequencia:\n");
    contador = 0;
    for(int i = 0; i < j; i++)
    {
        if (discentes[i].num_presencas < 22.5)
        {
            contador++;
        }
    }
    printf("%d\n", contador);
    printf("********************************\n");
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
    printf("\n***********************************************************\n");
    printf("Seja bem vindo(a) ao sistema de gerenciamento de discentes!\n");
    printf("***********************************************************\n");
    while (opicao != 7)
    {
        fclose(dados_discentes);
        printf("\n");
        printf("*********************************\n");
        printf("Oque deseja fazer?\n");
        printf("1 - Cadastrar discente\n");
        printf("2 - Listar discentes\n");
        printf("3 - Atualizar notas\n");
        printf("4 - Atualizar frequncias\n");
        printf("5 - Remover discente\n");
        printf("6 - Imprimir relatorio\n");
        printf("7 - Sair\n");
        printf("*********************************\n");
        printf("\nDigite o numero da opcao desejada: ");
        scanf("%d", &opicao);
        printf("\n*********************************\n");
        if (opicao == 1)
        {
            cadastrar_discente(discentes, dados_discentes, num_cadastros);
            salvar_dados_discentes_txt(discentes, dados_discentes);
        }
        if (opicao == 2)
        {
            lista_discentes(discentes, num_cadastros);
        }
        if (opicao == 3)
        {
            atualizar_notas(discentes);
            salvar_dados_discentes_txt(discentes, dados_discentes);
        }
        if (opicao == 4)
        {
            atualizar_frequencias(discentes);
            salvar_dados_discentes_txt(discentes, dados_discentes);
        }
        if (opicao == 5)
        {
            remove_discente(discentes, num_cadastros, dados_discentes);
            salvar_dados_discentes_txt(discentes, dados_discentes);
        }
        if (opicao == 6)
        {
            imprimir_relatorio(discentes, num_cadastros);
        }
    }
    printf("\n");
    printf("********************************************************************\n");
    printf("Obrigado por usar o sistema de gerenciamento de discentes. Ate mais!\n");
    printf("********************************************************************\n");
    return 0;
}