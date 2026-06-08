#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct
{
    int matricula;
    char nome[100];
    float notas[3];
} discente;

int main()
{
    int i = 0;
    char buffer[100];
    fpos_t pos[3];
    discente discentes[3];
    FILE* dados_dicentes = fopen("teste.txt", "w");
    fprintf(dados_dicentes, "eduardo de campos barbosa\n");
    fprintf(dados_dicentes, "123456\n");
    fprintf(dados_dicentes, "8.5\n");
    fprintf(dados_dicentes, "9.0\n");
    fprintf(dados_dicentes, "7.5\n");
    fgetpos(dados_dicentes, &pos[0]);
    fprintf(dados_dicentes, "maria da silva\n");
    fprintf(dados_dicentes, "654321\n");
    fprintf(dados_dicentes, "9.0\n");
    fprintf(dados_dicentes, "8.0\n");
    fprintf(dados_dicentes, "7.0\n");
    fgetpos(dados_dicentes, &pos[1]);
    fprintf(dados_dicentes, "joao pereira\n");
    fprintf(dados_dicentes, "111111\n");
    fprintf(dados_dicentes, "7.5\n");
    fprintf(dados_dicentes, "8.0\n");
    fprintf(dados_dicentes, "9.0\n");
    fgetpos(dados_dicentes, &pos[2]);
    fclose(dados_dicentes);
    dados_dicentes = fopen("teste.txt", "r");
    pos[2] -= 37;
    fsetpos(dados_dicentes, &pos[2]);
    fscanf(dados_dicentes, "%[^\n]\n", buffer);
    printf("%s\n", buffer);
    return 0;
}