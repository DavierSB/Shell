typedef struct
{
  int ref_count;
  char* instruction;
  char* parameters;
  int Fd_int;
  int Fd_out;
  int Terminada;
} Orden;

void Ejecutar(Orden *orden, int* results);