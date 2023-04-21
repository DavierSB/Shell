#include <stdlib.h>
#include <stdio.h>
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

void Mostrar(Command *command, int espacios)
{
  for (int i = 0; i < espacios; i++)
    printf(" ");
  printf("%s", command->instruction);
  if(command->instruction == "if")
  {
    Mostrar(command->if_cond, espacios + 1);
    Mostrar(command->if_then, espacios + 1);
    Mostrar(command->if_else, espacios + 1);
  }else{
    if(command->previous != NULL)Mostrar(command->previous, espacios + 1);
    if(command->next != NULL)Mostrar(command->next, espacios + 1);
  }
}