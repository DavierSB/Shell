#include <stdlib.h>
#include <command.h>
#include <unistd.h>
#include <fcntl.h>
#include <glib.h>
#include "help.h"
int Execute(Command *command, GQueue *history)
{
    int status;
    //Mostrar(command, 0);
    if (strcmp(command->instruction, "exit") == 0)
        exit(EXIT_SUCCESS);
    if (strcmp(command->instruction, "true") == 0)
        return 0;
    if (strcmp(command->instruction, "false") == 0)
        return 1;
    if (strcmp(command->instruction, "help") == 0)
        return Print_Help(command->parameters);
    if (strcmp(command->instruction, "history") == 0)
    {
        for (int i = 2; (i <= history->length) && (i <= 11); i++)
            printf("\n %d %s", i - 1, g_strdup(g_queue_peek_nth(history, i - 1)));
        printf("\n");
    }
    if (strcmp(command->instruction, "if") == 0)
    {
        if (!Execute(command->if_cond, history))
            return Execute(command->if_then, history);
        else
            return Execute(command->if_else, history);
    }
    if (strcmp(command->instruction, "&&") == 0)
        return (Execute(command->previous, history) == 0) && (Execute(command->next, history) == 0);
    if (strcmp(command->instruction, "||") == 0)
        return Execute(command->previous, history) || Execute(command->next, history);
    if (strcmp(command->instruction, "cd") == 0)
        return chdir(command->parameters[0]);
    if (strcmp(command->instruction,"|") == 0)
    {
        int fdpipe[2];
        pipe(fdpipe);
        if (command->fd_in != -1)
            command->previous->fd_in = command->fd_in;
        command->previous->fd_out = fdpipe[1];
        command->next->fd_in = fdpipe[0];
        status = Execute(command->previous, history);
        status = status || Execute(command->next, history);
        close(fdpipe[0]);
        close(fdpipe[1]);
    }

    int old_fd_in = dup(0);
    int old_fd_out = dup(1);
    if (command->file_in != NULL)
    {
        int fd_in = open(command->file_in, O_RDONLY);
        dup2(fd_in, 0);
        close(fd_in);
    }
    if (command->fd_in != -1)
    {
        dup2(command->fd_in, 0);
        close(command->fd_in);
    }
    if (command->file_out != NULL)
    {
        int fd_out;
        if (command->append)
            fd_out = open(command->file_out, O_WRONLY | O_APPEND);
        else fd_out = creat(command->file_out, 0644);
        dup2(fd_out, 1);
        close(fd_out);
    }
    if (command->fd_out != -1){
        dup2(command->fd_out, 1);
        close(command->fd_out);
    }
    int pid = fork();
    if (pid == 0)
    {
        char **args;
        if (command->parameters != NULL)
        {
            args = malloc(sizeof(char *) + sizeof(command->parameters));
            for (int i = 0; ; i++)
            {
                if (command->parameters[i] != NULL)args[i + 1] = strdup(command->parameters[i]);
                else
                {
                    args[i + 1] = NULL;
                    break;
                }
            }
        }
        else
        {
            args = malloc(sizeof(char *)*2);
            args[1] = NULL;
        }
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