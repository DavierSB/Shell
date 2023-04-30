#include<stdlib.h>
#include "help.h"
int Print_Help(char **funcionalidad)
{
    if(funcionalidad == NULL)
    {
        printf("Este es el proyecto de Davier Sanchez Bello del grupo C312\n");
        printf("El nucleo d este proyecto parte de la utilizacion de una\n");
        printf("estructura arborea recursiva llamada command que permite modelar\n");
        printf("muy bien toda posible cadena de instrucciones\n\n");
        printf("Las funcionalidades implementadas son:\n");

        printf("\nbasic\n");
        printf("multipipe\n");
        printf("history\n");
        //printf("ctrl + c\n");
        printf("chain");
        printf("if\n");
        printf("multi-if\n");
        printf("help\n\n");

        printf("Si desea conocer como implemente determinada funcionalidad\n");
        printf("Tan solo tipee en la terminal help funcionalidad\n\n");

        printf("Los built-in implementados son:\n");
        printf("cd\n");
        printf("exit\n");
        printf("history\n");
        printf("again\n");
        printf("true\n");
        printf("false\n");
        printf("if\n");
        printf("help\n\n");
    }else
    {
        char *s = strdup(funcionalidad[0]);
        if(strcmp(s, "basic") == 0)
        {
            printf("La estructura command tiene un campo de tipo string que guarda el nombre\n");
            printf("de la introduccion a ejecutar y otros dos campos de tipo string llamados\n");
            printf("file_in y file_out que guardan la direccion de los archivos a donde es\n");
            printf("redireccionada la entrada y la salida con <, > o >>. Luego a la hora de\n");
            printf("ejecutar el comando se abren y usa el pid de tales archivos como nueva\n");
            printf("salida/entrada estandar mientras q la instruccion guardada se ejecuta con\n");
            printf("execvp. Uso las funciones creat y open con bandera O_APPEND para > y >>.\n");
            printf("En el caso de los pipes usamos otros dos campos de la struct command, de\n");
            printf("tipo entero, los cuales toman el valor de los pid extremos de un pipe,\n");
            printf("y luego de establecerlos como entrada o salida estandar de los procesos\n");
            printf("correspondientes ejecutamos los comandos\n");
            return 0;   
        }
        if(strcmp(s, "multipipe") == 0)
        {
            printf("Los pipes son interpretados por nuestro parser como un tipo de comando.\n");
            printf("Luego tiene al igual que cualquier otro comando dos campos de tipo comando\n");
            printf("llamados previous y next que en el caso del pipe se refieren al lado izquierdo\n");
            printf("y al lado derecho del pipe respectivamente.");
            printf("Cuando execute va a ejecutar un comando de tipo pipe, crea un pipe y establece\n");
            printf("la salida estandar del comando previous como un extremo del pipe y la entrada\n");
            printf("estandar del comando next como el otro extremo.\n");
            printf("Este esquema permite modelar comandos multipipe sin problemas, creando primero\n");
            printf("un pipe que toma como previous al primer comando de los comandos encadenadados\n");
            printf("por el multipipe y toma como next a otro pipe que tendra como previous\n");
            printf("al segundo comando y como next posiblemente a otro pipe y asi hasta que los\n");
            printf("n comandos esten enlazaos jerarquicamente. Dado que un comando pipe puede tomar\n");
            printf(" un fd_in, podemos establecer la entrada del comando pipe como la salida del\n");
            printf("anterior asi tantas veces como queramos bajando por la jerarquia.\nNo se si me hice explicar, pero pincha :)\n");
            return 0;
        }
        if(strcmp(s, "history") == 0)
        {
            printf("La historia la implemente simulando una pila con la estructura GQueue de la\n");
            printf("libreria glib. Para guardarla hago uso de archivos externos.\n");
        }
        if(strcmp(s, "if") == 0)
        {
            printf("La estructura command tiene campos de tipo command llamados if_cond, if_then\n");
            printf("y if_else. A la hora de ejecutar un comando de tipo if siempre se ejecuta la\n");
            printf("condicion de if_cond de tener status 0 se ejecuta el comando apuntado por if_then, si no el apuntado por if_else.\n");
        }
        if(strcmp(s, "multi-if") == 0)
        {
            printf("Dentro de los campos if_cond, if_then o if_else los comandos apuntados pueden ser tambien if\n");
        }
        if(strcmp(s, "chain") == 0)
        {
            printf("La estructura command tiene campos de tipo command que indican el comando previo\n");
            printf("y el posterior (previous y next). Asi las operaciones d encadenado como && o ||\n");
            printf("pueden ser exresadas como comandos que toman por previous a la instruccion que esta\n");
            printf("antes del operador y por next al que esta despues. Esto nos permite representar sin\n");
            printf("mas parafernalia cadenas complejas de ands y ors de manera recursiva.\n");
            printf("Para el caso de las concatenaciones (;) decidi separar los comandos que intervienen\n");
            printf("en la concatenacion desde el mismo inicio en q la cadena es introducida, haciendo split\n");
            printf("a ella. Esta decision la tome dado que el ; tiene mayor precedencia en la estructura\n");
            printf("arborea con la q representamos los comandos\n");
        }
    }
    return 0;
}