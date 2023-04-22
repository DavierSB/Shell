#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <command.h>

Command* Command_new ()
{
  Command* self;

  self = malloc (sizeof (Command));
  self->ref_count = 1;
  self->parameters = NULL;
  self->file_in = NULL;
  self->file_out = NULL;
  return self;
}

Command* Command_ref (Command* self)
{
  ++self->ref_count;
  return self;
}

void Command_unref (Command* self)
{
  if (--self->ref_count == 0)
    {
      free (self);
    }
}

int IsConcatenation(char *inst)
{
        return ((strcmp(inst, "&&") == 0) || (strcmp(inst, "||") == 0) || (strcmp(inst, ";") == 0) || (strcmp(inst, "|") == 0));
}
void Mostrar_Parametros(Command* command)
{
  if (command->parameters != NULL){
    printf("( ");
    for (int i = 0; command->parameters[i] != NULL; i++, printf(", "))
      printf(command->parameters[i]);
    printf(")");
  }
}
void Mostrar_In_Out(Command* command)
{
  if (command->file_out != NULL)
    printf(" > %s", command->file_out);
  if (command->file_in != NULL)
    printf(" < %s", command->file_in);
}
void Mostrar(Command *command, int espacios)
{
  if (command == NULL)return;
  for (int i = 0; i < espacios; i++)
    printf(" ");
  printf("%s", command->instruction);
  Mostrar_Parametros(command);
  Mostrar_In_Out(command);
  printf("\n");
  if(strcmp(command->instruction, "if") == 0)
  {
    Mostrar(command->if_cond, espacios + 2);
    Mostrar(command->if_then, espacios + 2);
    Mostrar(command->if_else, espacios + 2);
    return;
  }
  if (IsConcatenation(command->instruction))
  {
    if(command->previous != NULL)Mostrar(command->previous, espacios + 2);
    if(command->next != NULL)Mostrar(command->next, espacios + 2);
  }
}