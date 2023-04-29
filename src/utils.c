#include <stdio.h>
#include <unistd.h>
#include <glib.h>
#include "readline/readline.h"
#include "utils.h"

char *Eliminar_Comentarios(char *, char *);
char *Unificar(char **, char *);
int IsDigit(char *);
int Contar_Caracteres(char **);
char *ReadLine(GQueue *history)
{
    char directorio[100];
    printf("ourshell:");
    printf("%s", getcwd(directorio, 100));
    char *line = readline("$ ");
    int Empieza_Con_Espacio = (line[0] == ' ');
    char *pure_line = Eliminar_Comentarios(line, pure_line);
    if (g_queue_is_empty(history))
    {
        g_queue_push_head(history, g_strdup(pure_line));
        return pure_line;
    }
    char **chunks = Split(pure_line);
    char *aux;
    for (int i = 0, j; chunks[i] != NULL; i++)
        if (strcmp(chunks[i], "again") == 0)
        {
            if ((chunks[i + 1] != NULL) && IsDigit(chunks[i + 1]))
            {
                chunks[i] = g_strdup(g_queue_peek_nth(history, chunks[i + 1][0] - '0' - 1));
                for (j = i + 1; chunks[j + 1] != NULL; j++)
                {
                    chunks[j] = strdup(chunks[j + 1]);
                }
                chunks[j] = NULL;
            }
            else
                chunks[i] = g_strdup(g_queue_peek_head(history));
        }
    char *history_line = Unificar(chunks, history_line);
    if(!Empieza_Con_Espacio)
        g_queue_push_head(history, g_strdup(history_line));
    return history_line;
    //return pure_line;
}
char **Split(char *input)
{
    char **result = NULL;

    if (!strcmp(input, ""))
    {
        result = g_new(char *, 1);
        result[0] = NULL;
    }
    else
    {
        result = g_strsplit_set(input, " \t\r\n\a", -1);
        // for (int i = 0; result[i] != NULL; i++, printf("\n"))
        //     printf(result[i]);
    }
    return result;
}
char *Substring(char *line, int start, int end, char *new)
{
    new = malloc(sizeof(char *) * (end - start + 1));
    for (int i = start; i <= end; i++)
        new[i - start] = line[i];
    new[end - start + 1] = NULL;
    return new;
}
int Contar_Puntos_Comas(char *line)
{
    int count = 0;
    for (int i = 0; line[i] != NULL; i++)
        if (line[i] == ';')
            count++;
    return count;
}
char **Separar_Puntos_Comas(char *line, char **answer)
{
    int dots = Contar_Puntos_Comas(line);
    char *new;
    answer = malloc(sizeof(char *) * (dots + 1));
    for (int i = 0, start = 0, end = 0; i <= dots; i++)
    {
        if (i == dots)
        {
            while (line[end] != NULL)
                end++;
            end--;
            answer[i] = strdup(Substring(line, start, end, new));
            answer[i + 1] = NULL;
            return answer;
        }
        while (line[end] != ';')
            end++;
        end--;
        while (line[end] == ' ')
            end--;
        answer[i] = strdup(Substring(line, start, end, new));
        while (line[end] != ';')
            end++;
        end++;
        while (line[end] == ' ')
            end++;
        start = end;
        new = NULL;
    }
}
char *Eliminar_Comentarios(char *line, char *pure_line)
{
    for (int i = 0;; i++)
    {
        if (line[i] == NULL)
            return line;
        if (line[i] == '#')
        {
            do
            {
                i--;
            } while (line[i] == ' ');
            i++;
            pure_line = malloc(sizeof(char *) * i);
            for (int j = 0; j < i; j++)
                pure_line[j] = line[j];
            pure_line[i] = NULL;
            return pure_line;
        }
    }
}
char *Unificar(char **chunks, char *line)
{
    int cant_char = Contar_Caracteres(chunks);
    line = malloc(sizeof(char) * cant_char);
    for (int i = 0, k = 0; chunks[i] != NULL; i++)
    {
        for (int j = 0; chunks[i][j] != NULL; j++, k++)
            line[k] = chunks[i][j];
        line[k++] = ' ';
    }
    line[cant_char - 1] = NULL;
    return line;
}
int IsDigit(char *line)
{
    if ((line[0] == '1') && (line[1] != NULL) && (line[1] == '0'))
        return 10;
    return ((line[0] - '0') < 10) && (line[1] == NULL);
}
int Contar_Caracteres(char **chunks)
{
    int cont = 0;
    for (int i = 0; chunks[i] != NULL; i++)
    {
        for (int j = 0; chunks[i][j] != NULL; j++)
            cont++;
        cont++;
    }
    return cont;
}