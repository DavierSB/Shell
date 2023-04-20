#include<stdlib.h>
#include<signal.h>
#include "readline/readline.h"
#include "utils.h"
#include "execute.h"
#include "command.h"
#include "parser.h"
void Loop();
int killer();

int main()
{
    //Init_Variables();
    //Init_BackGroung();
    signal(SIGINT, &killer);
    Loop();
    return 0;
}

void Loop()
{
    char *line;
    char **tokens;
    Command *comando;
    int status;
    do
    {
        line = ReadLine();
        tokens = Split(line);
        comando = Parsear(Command_new(), NULL, tokens, 0);
        status = Execute(comando);
        free(line);
        free(tokens);
    }while(status);
}