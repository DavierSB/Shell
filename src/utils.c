#include<stdio.h>
#include<unistd.h>
#include<glib.h>
#include "readline/readline.h"
#include "utils.h"
void Actualizar_Historia(char* line)
{

}
char *ReadLine()
{
    char directorio[100];
    printf("ourshell:");
    printf("%s", getcwd(directorio, 100));
    char* line = readline ("$ ");
    //m dices q podemos actualizar la historia d esta manera porq es global en readline
    //Actualizar_Historia(line);
    return line;
}
char** Split (char* input)
{
    char** result = NULL;

    if (!strcmp (input, ""))
    {
        result = g_new (char*, 1);
        result [0] = NULL;
    }
    else
    {
        result = g_strsplit_set (input, " \t\r\n\a" ,-1);
        //for (int i = 0; result[i] != NULL; i++, printf("\n"))
        //    printf(result[i]);
    }
return result;
}
char *Substring (char* line, int start, int end, char* new)
{
    new = malloc(sizeof(char*)*(end - start + 1));
    for (int i = start; i <= end; i++)
        new[i - start] = line[i];
    new[end - start + 1] = NULL;
    return new;
}
int Contar_Puntos_Comas(char* line)
{
    int count = 0;
    for (int i = 0; line[i] != NULL; i++)
        if(line[i] == ';')count++;
    return count;
}
char** Separar_Puntos_Comas(char* line, char** answer)
{
    int dots = Contar_Puntos_Comas(line);
    char *new;
    answer = malloc(sizeof(char*)*(dots+1));
    for (int i = 0, start = 0, end = 0; i <= dots; i++)
    {
        if (i == dots)
        {
            while(line[end] != NULL)end++;
            end--;
            answer[i] = strdup(Substring(line, start, end, new));
            answer[i + 1] = NULL;
            return answer;
        }
        while(line[end] != ';')end++;
        end--;
        while(line[end] == ' ')end--;
        answer[i] = strdup(Substring(line, start, end, new));
        while(line[end] != ';')end++;
        end++;
        while(line[end] == ' ')end++;
        start = end;
        new = NULL;
    }
}