#include <glib.h>
#include <stdio.h>
#include <stdlib.h>
#include<unistd.h>
#include <sys/types.h>
#include<sys/wait.h>
void Loop();
char *ReadLine();
char **Split(char*);
//Espero q GetCommands devuelva un arreglo NULL terminated

int Execute(char **);

int main()
{
    Loop();
    return 0;
}

void Loop()
{
    char *line;
    char **args;
    int status;
    do
    {
        printf("ourshell $ ");
        line = ReadLine();
        args = Split(line);
        status = Execute(args);
        free(line);
        free(args);
    }while(status);
}

char *ReadLine()
{
    char *line = NULL;
    ssize_t sz = 0;
    getline(&line, &sz, stdin);
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
        result = g_strsplit_set (input, " ", -1);
    }
return result;
}

int Execute(char* args[])
{
    return 0;
}