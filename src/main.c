#include <glib.h>
#include <stdio.h>
#include <stdlib.h>
#include<unistd.h>
#include <sys/types.h>
#include<sys/wait.h>
void Loop();
char *ReadLine();
char **GetCommands(char*);
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
        args = GetCommands(line);
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

char** GetCommands (char* input)
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

        int i;
        for (i = 0; result [i]; i++)
            {
                g_print ("token [i] = '%s'\n", result [i]);
            }
    }
return result;
}

int Execute(char* args[])
{
    int i, status = 1;
    /* no pongas for (unsigned int i = 0; ...) porque muchos compiladores no lo soportan    */
    /* eso en C++ es estandar pero en C demor\'o bastante en serlo                          */
    for (i = 0; status && args[i] != NULL; i++)
    {
        pid_t child_pid = fork();
        if (child_pid == 0)
        {
            //Ejecutar el comando
            printf("Ejecutando: %s \n", args[i]);
        }else{
            waitpid(child_pid, &status, 0);
            //Aqui puedo perfectamente en lugar d esperar q se termine de ejecutar
            //el proceso hijo, llamar otros procesos mientras espero y asi correrlos
            //en paralelo y moverlos d background a foreground y todo eso
        }
    }
}
