#include<stdlib.h>
#include "readline/readline.h"
#include "utils.h"
#include "execute.h"
void Loop();

int main()
{
    //Init_Variables();
    //Init_BackGroung();
    Loop();
    return 0;
}

void Loop()
{
    char *line;
    char **args;
    int status;
    do
    {
        line = ReadLine();
        args = Split(line);
        status = Execute(args);
        free(line);
        free(args);
    }while(status);
}