#ifndef COMMAND_H
#define COMMAND_H

typedef struct Command
{
  int ref_count;
  char* instruction;
  char** parameters;
  char* file_in;
  char* file_out;
  int fd_in;
  int fd_out;
  int index_of_termination;
  struct Command* next;
  struct Command* previous;
  struct Command* if_cond;
  struct Command* if_then;
  struct Command* if_else;
} Command;

Command *Command_new();
void Mostrar(Command*, int);

#endif