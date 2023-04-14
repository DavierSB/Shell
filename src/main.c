#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
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
int Execute(char* args[])
{
    int status = 1;
    for(int i = 0; status && args[i] != NULL; i++)
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