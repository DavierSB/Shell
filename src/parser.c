#include<stdlib.h>
#include<command.h>
#include<string.h>
#include<glib.h>
int Concatenation_Command(char ** tokens, int index)
{
    return ((strcmp(tokens[index], "&&") == 0) || (strcmp(tokens[index], "||") == 0) || (strcmp(tokens[index], ";") == 0) || (strcmp(tokens[index], "|") == 0));
}
int EsBuiltIn(char **tokens, int index)
{
    return Concatenation_Command(tokens, index) || (strcmp(tokens[index], "then") == 0) || (strcmp(tokens[index], "else") == 0) || (strcmp(tokens[index], "end") == 0);
}
void SubArray(char **tokens, char **nuevo, int inicio, int final)
{
    nuevo = malloc(sizeof(char*)*(final - inicio));
    for (int i = inicio; i < final; i++)
        nuevo[i - inicio] = tokens[i];
}

Command* Parsear(Command * current_command, Command * previous_command, char ** tokens, int index)
{
    current_command->instruction = tokens[index];
    if (tokens[index] == NULL)
    {
        if (previous_command != NULL)
        {
            return previous_command;
        }
        return current_command;
    }
    if (Concatenation_Command(tokens, index))
    {
        current_command->previous = previous_command;
        current_command->next = Parsear(Command_new(), NULL, tokens, ++index);
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
            current_command->index_of_termination = index;
            return current_command;
        }
        //Lanzar_Error If mal escrito
        return NULL;
    }

    if (strcmp(tokens[index], "<") == 0)
    {
        current_command->file_in = tokens[++index];
        index++;
    }
    if (strcmp(tokens[index], ">") == 0)
    {
        current_command->file_out = tokens[++index];
        index++;
    }
    if (strcmp(tokens[index], ">>") == 0)
    {
        //Q hago aqui?
    }
    int index_d_inicio = index;
    for(int HayComillas = 0; EsBuiltIn(tokens, index) == 0; index++);
    current_command->index_of_termination = index;
    SubArray(tokens, current_command->parameters, index_d_inicio, index);
    return Parsear(Command_new(), current_command, tokens, index);
}