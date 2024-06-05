#include <stdio.h>
#include "debugmalloc.h"
#include "datamgmt.h"
#include "readin.h"
#include "menu.h"
#include "filemgmt.h"

int main() {

    printf("\n \n"
           " ^ ^                 \n"
           "(O,O)                \n"
           "(   ) SOCIAL NETWORKS    \n"
           "-\"-\"-----------------\n \n"
           ".-----------------------------------------------------------------------------------------------------------.\n"
           "| The core idea of network science is to explain sociological events based not on the \n"
           "           individual people but on the social connections between these individuals. The program models \n"
           "           three different experiments and tries to give an answer why networks are so important in society. |\n"
           "'-----------------------------------------------------------------------------------------------------------' "
           "\n \n"
           "Please select an option:\n"
           " ________________________________________________________________________ \n"
           "|  ____________________________________________________________________  |\n"
           "| | F - read in from previously made files.                            | |\n"
           "    C - read in from console window. \n"
           "| |____________________________________________________________________| |\n"
           "|________________________________________________________________________|"

           "\n \n");

    List1 *Data = NULL;

    char c;
    scanf(" %c", &c);

    if(c=='C')
    {
        Data = readin(Data);
        file_out(Data);
    }
    if(c=='F')
    {
        Data = freadin(Data);
    }
    read_menu(Data);
    Data = menu(Data);
    delete_all(Data);

    printf(".--------------------------------------------------------------------------------------------------------.\n"
                  "| Now you know how much our connections, or in other words, networks affect our day to day life,         |\n"
                  "| and what an important role they play in societies. Thank you for being here! :)                        |\n"
                  "'--------------------------------------------------------------------------------------------------------' \n\n");
    printf("Resources and special thanks to: InfoC, https://texteditor.com/ascii-frames/, https://ncase.me/crowds/ \n ");

    char o;
    scanf("%c\n", &o);
    return 0;
    }
