#include <stdlib.h>
#include <command.h>

Command* Command_new ()
{
  Command* self;

  self = malloc (sizeof (Command));
  self->ref_count = 1;
  
  self->if_cond = malloc (sizeof (Command));
  self->if_else = malloc (sizeof (Command));
  self->if_then = malloc (sizeof (Command));
  self->previous = malloc(sizeof(Command));
  self->next = malloc (sizeof (Command));
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