#ifndef COMMAND_H
#define COMMAND_H

typedef struct
{
  int ref_count;
  char* instruction;
  char* parameters;
  int Fd_int;
  int Fd_out;
  int index_of_termination;
  Command* next;
  Command* previous;
  Command* if_cond;
  Command* if_then;
  Command* if_else;
} Command;

#endif