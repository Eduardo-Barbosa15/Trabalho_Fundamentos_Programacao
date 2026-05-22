#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main()
{
    int i = 0;
    char buffer[100];
    int discentes[3];
    FILE* dados_dicentes = fopen("discentes.txt", "w");
    fprintf(dados_dicentes, "**********\n");
    fprintf(dados_dicentes, "Discente 1\n");
    fprintf(dados_dicentes, "Discente 2\n");
    fprintf(dados_dicentes, "Discente 3\n");
    fprintf(dados_dicentes, "**********\n");
    fclose(dados_dicentes);
    dados_dicentes = fopen("discentes.txt", "r");
    while(fscanf(dados_dicentes, "%s", buffer) == 1)
    {
        if (buffer[0] != '*' && buffer[0] != 'D')
        {
            discentes[i] = atoi(buffer);
            i++;
        }
    }
    fclose(dados_dicentes);
    for (int j = 0; j < 3; j++)
    {
        printf("%d\n", discentes[j]);
    }
    return 0;
}