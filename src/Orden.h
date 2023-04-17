//Se aceptan cambios de nombres de los campos de la struct
typedef struct Orden
{
    char *instruction;
    char *parameters;
    int Fd_int;
    int Fd_out;
    bool Terminada;
}Orden;