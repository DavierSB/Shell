#include <glib.h>
#include <orden.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

void Loop();
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
        line = readline ("ourshell~$ ");
        args = Split(line);
        status = Execute(args);
        free(line);
        free(args);
    }while(status);
}

void ReadLine(char* line)
{
    ssize_t sz = 0;
    getline(line, &sz, stdin);
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

void Parsear(Orden *A[], int* results)
{
    char* args[] = {"ls", 0};
    A[0] = orden_new(args[0], args);
}

int Execute(char* args[])
{
    //Parser parser = new Parser(args);
    int *results;//Resultado de las ejecuciones
    Orden* ordenes[1];
    /*Parser.*/Parsear(ordenes, results);
    do
    {
        for(int i = 0; ordenes[i] != NULL; i++)
           Ejecutar(ordenes[i], results);
        /*Parser.*/Parsear(ordenes, results);
        ordenes[0] = NULL;//Para salir del ciclo xd
    }while(ordenes[0] != NULL);
    return 0;
}
