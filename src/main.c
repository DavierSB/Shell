#include<stdlib.h>
#include<stdio.h>
#include<signal.h>
#include<fcntl.h>
#include<unistd.h>
#include<glib.h>
#include "readline/readline.h"
#include "utils.h"
#include "execute.h"
#include "command.h"
#include "parser.h"
void Loop();
void Iniciar_History(GQueue *);
int Size(char **);
void Guardar_History(GQueue *);
void Quitar_Salto_de_Linea(char *);

int killer()
{
    signal(SIGINT, &killer);
    printf("\n");
    Loop();
}
int main()
{
    //Init_Variables();
    //Init_BackGroung();
    signal(SIGINT, &killer);
    Loop();
    return 0;
}

void Loop()
{
    char *line;
    char **tokens, **chunks;
    Command *comando;
    GQueue* history = g_queue_new();
    Iniciar_History(history);
    int status = 0;
    do
    {
        line = ReadLine(history);
        Guardar_History(history);
        chunks = Separar_Puntos_Comas(line, chunks);
        for (int i = 0; chunks[i] != NULL; i++)
        {
            tokens = Split(chunks[i]);
            comando = Parsear(Command_new(), NULL, tokens, 0);
            status = Execute(comando, history);
            free(tokens);
            free(comando);
        }
        free(line);
    }while(!status);
}

void Iniciar_History(GQueue *history)
{
    char *line = NULL;
    size_t len = 0;
    FILE *file = fopen("./history.txt", "r");
    while ((getline(&line, &len, file)) != -1)
    {
        Quitar_Salto_de_Linea(line);
        g_queue_push_head(history, g_strdup(line));
    }
    fclose(file);
}
void Guardar_History(GQueue *history)
{
    FILE *file = fopen("./history.txt", "w");
    for (int i = 0; i < history->length; i++)
    {
        fprintf(file, g_strdup(g_queue_peek_nth(history, i)));
        fprintf(file, "\n");
    }
    fclose(file);
}

int Size(char** arr)
{
    int count = 0;
    for(; arr[count] != NULL; count++);
    return count;
}
void Quitar_Salto_de_Linea(char *line)
{
    for (int i = 0; line[i] != NULL; i++)
        if(line[i] == '\n')
        {
            line[i] = NULL;
            return;
        }
}