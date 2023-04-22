#include<stdlib.h>
#include<signal.h>
#include "readline/readline.h"
#include "utils.h"
#include "execute.h"
#include "command.h"
#include "parser.h"
void Loop();

int Size(char** arr)
{
    int count = 0;
    for(; arr[count] != NULL; count++);
    return count;
}

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
    char *line, *aux;
    char **tokens, **chunks;
    Command *comando;
    int status = 1;
    do
    {
        line = ReadLine();
        chunks = Separar_Puntos_Comas(line, chunks);
        for (int i = 0; chunks[i] != NULL; i++)
        {
            tokens = Split(chunks[i]);
            comando = Parsear(Command_new(), NULL, tokens, 0);
            status = Execute(comando);
            //free(aux);
            free(tokens);
            free(comando);
        }
        free(line);
    }while(status);
}