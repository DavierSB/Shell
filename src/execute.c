#include <stdlib.h>
#include <command.h>
#include <unistd.h>
#include <fcntl.h>
int Execute(Command *command)
{
    // Mostrar(command, 0);
    if (strcmp(command->instruction, "exit") == 0)
        exit(EXIT_SUCCESS);
    if (strcmp(command->instruction, "true") == 0)
        return 0;
    if (strcmp(command->instruction, "false") == 0)
        return 1;
    if (strcmp(command->instruction, "if") == 0)
    {
        if (!Execute(command->if_cond))
            return Execute(command->if_then);
        else
            return Execute(command->if_else);
    }
    if (strcmp(command->instruction, "&&") == 0)
        return Execute(command->previous) && Execute(command->next);
    if (strcmp(command->instruction, "||") == 0)
        return Execute(command->previous) || Execute(command->next);
    if (strcmp(command->instruction, "cd") == 0)
        return chdir(command->parameters[0]);
    int old_fd_in = dup(0);
    int old_fd_out = dup(1);
    if (command->file_in != NULL)
    {
        int fd_in = open(command->file_in, O_RDONLY);
        dup2(fd_in, 0);
        close(fd_in);
    }
    if (command->file_out != NULL)
    {
        int fd_out = open(command->file_out, O_WRONLY);
        dup2(fd_out, 1);
        close(fd_out);
    }
    int pid = fork();
    int status;
    if (pid == 0)
    {
        char **args;
        if (command->parameters != NULL)
        {
            args = malloc(sizeof(char *) + sizeof(command->parameters));
            for (int i = 0; command->parameters[i] != NULL; i++)
                args[i + 1] = command->parameters[i];
        }
        else
            args = malloc(sizeof(char *));
        args[0] = strdup(command->instruction);
        return execvp(command->instruction, args);
    }
    else
    {
        waitpid(pid, &status, 0);
        dup2(old_fd_in, 0);
        dup2(old_fd_out, 1);
        close(old_fd_in);
        close(old_fd_out);
    }
    return 0;
}