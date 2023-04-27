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

int main()
{
    //Init_Variables();
    //Init_BackGroung();
    //signal(SIGINT, &killer);
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
    Guardar_History(history);
}

void Iniciar_History(GQueue *history)
{
    char *line = NULL;
    size_t len = 0;
    FILE *file = fopen("/home/davier/Apuntes/history.txt", "r");
    while ((getline(&line, &len, file)) != -1)
        g_queue_push_head(history, g_strdup(line));
    fclose(file);
}
void Guardar_History(GQueue *history)
{
    
}

int Size(char** arr)
{
    int count = 0;
    for(; arr[count] != NULL; count++);
    return count;
}