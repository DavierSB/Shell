#include<stdlib.h>
#include<command.h>
#include<string.h>
#include<glib.h>

int Concatenation_Command(char ** tokens, int index)
{
    if (tokens[index] == NULL)return 0;
    return ((strcmp(tokens[index], "&&") == 0) || (strcmp(tokens[index], "||") == 0) || (strcmp(tokens[index], "|") == 0));
}
int EsBuiltIn(char **tokens, int index)
{
    if (tokens[index] == NULL)return 1;
    return Concatenation_Command(tokens, index) || (strcmp(tokens[index], "then") == 0) || (strcmp(tokens[index], "else") == 0) || (strcmp(tokens[index], "end") == 0);
}
char** SubArray(char **tokens, char **nuevo, int inicio, int final)
{
    nuevo = malloc(sizeof(char*)*(final - inicio + 1));
    for (int i = inicio; i < final; i++)
        nuevo[i - inicio] = strdup(tokens[i]);
    nuevo[final - inicio] = NULL;
    return nuevo;
}

Command* Parsear(Command * current_command, Command * previous_command, char ** tokens, int index)
{
    if (tokens[index] == NULL)
    {
        if (previous_command != NULL)
        {
            return previous_command;
        }
        return current_command;
    }
    current_command->instruction = strdup(tokens[index]);
    if (Concatenation_Command(tokens, index))
    {
        current_command->previous = previous_command;
        current_command->next = Parsear(Command_new(), NULL, tokens, ++index);
        current_command->index_of_termination = (current_command->next)->index_of_termination;
        return current_command;
    }
    if (strcmp(tokens[index], "if") == 0)
    {
        current_command->if_cond = Parsear(Command_new(), NULL, tokens, ++index);
        index = (current_command->if_cond)->index_of_termination;
        if (strcmp(tokens[index], "then") == 0)
        {
            current_command->if_then = Parsear(Command_new(), NULL, tokens, ++index);
            index = (current_command->if_then)->index_of_termination;
        }
        if(strcmp(tokens[index], "else") == 0)
        {
            current_command->if_else = Parsear(Command_new(), NULL, tokens, ++index);
            index = (current_command->if_else)->index_of_termination;
        }
        if(strcmp(tokens[index], "end") == 0)
        {
            //for (int i = 0; current_command->parameters[i] != NULL; i++, printf(", "))
                //printf(current_command->parameters[i]);
            current_command->index_of_termination = index + 1;
            return current_command;
        }
        //Lanzar_Error If mal escrito
        return NULL;
    }

    if(tokens[++index] == NULL)
    {
        return current_command;
    }
    
    if (strcmp(tokens[index], "<") == 0)
    {
        strcpy(current_command->file_in, tokens[++index]);
        index++;
    }
    if (strcmp(tokens[index], ">") == 0)
    {
        strcpy(current_command->file_out, tokens[++index]);
        index++;
    }
    if (strcmp(tokens[index], ">>") == 0)
    {
        //Q hago aqui?
    }
    int index_d_inicio = index;
    for(; EsBuiltIn(tokens, index) == 0; index++);
    current_command->index_of_termination = index;
    current_command->parameters = SubArray(tokens, current_command->parameters, index_d_inicio, index);
    if (!Concatenation_Command(tokens, index))
        return current_command;
    return Parsear(Command_new(), current_command, tokens, index);
}