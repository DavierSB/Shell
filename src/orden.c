#include <stdlib.h>
#include <orden.h>
#include<unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

Orden* orden_new (char* instruction, char* parameters, int Fd_int, int Fd_out)
{
  Orden* self;

  self = malloc (sizeof (Orden));
  self->ref_count = 1;
  self->instruction = instruction;
  self->parameters = parameters;
  self->Fd_int = Fd_int;
  self->Fd_out = Fd_out;
  self->Terminada = 0;
return self;
}

Orden* orden_ref (Orden* self)
{
  ++self->ref_count;
  return self;
}

void orden_unref (Orden* self)
{
  if (--self->ref_count == 0)
    {
      free (self);
    }
}

void Ejecutar(Orden* orden, int* results)
{
  int old_Fd_int = dup(0);
  int old_Fd_out = dup(1);
  dup2(orden->Fd_int, STDIN_FILENO);
  dup2(orden->Fd_out, STDOUT_FILENO);
  pid_t pid_hijo = fork();
  if(pid_hijo)
  {
    execvp(orden->instruction, orden->parameters);
  }
  else
  {
    int status;
    waitpid(pid_hijo, &status, WNOHANG);
    orden->Terminada = 1;
  }
}