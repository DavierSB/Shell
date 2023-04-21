#include<glib.h>
#include "readline/readline.h"
#include "utils.h"
void Actualizar_Historia(char* line)
{

}
char *ReadLine()
{
    char* line = readline ("ourshell~$ ");
    //m dices q podemos actualizar la historia d esta manera porq es global en readline
    //Actualizar_Historia(line);
    return line;
}
char** Split (char* input)
{
    char** result = NULL;

    if (!strcmp (input, ""))
    {
        result = g_new (char*, 1);
        result [0] = NULL;
    }
    else
    {
        result = g_strsplit_set (input, " ", -1);
        //for (int i = 0; result[i] != NULL; i++, printf("\n"))
        //    printf(result[i]);
    }
return result;
}