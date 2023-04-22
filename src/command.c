#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <command.h>

Command* Command_new ()
{
  Command* self;

  self = malloc (sizeof (Command));
  self->ref_count = 1;
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
void Mostrar(Command *command, int espacios)
{
  if (command == NULL)return;
  for (int i = 0; i < espacios; i++)
    printf(" ");
  printf("%s", command->instruction);
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