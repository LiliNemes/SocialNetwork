//
// Created by Lili on 22/11/2021.
//

#ifndef NHF_MENU1_INFORMATION_H
#define NHF_MENU1_INFORMATION_H

#include "conread.h"
#include "datamgmt.h"
#include "stdlib.h"
#include "readin.h"
#include "bool_initalizer.h"
#include "debugmalloc.h"


typedef struct ListofChars
{
    char *azonositok;
    struct ListofChars *next;
}ListofChars;

void kiiras(Lista1Elem *Data);

bool ellenorzes(Lista1Elem *Data);

Lista1Elem *valtoztato(Lista1Elem *Data, ListofChars *azonositokok);

ListofChars * vegerefuz(ListofChars *lista, char *mit);

ListofChars *kimarad(Lista1Elem *Data, ListofChars *ki);

ListofChars *seged(ListofChars *mibennincs, Lista1Elem *Data);

void listafelszab_LoC(ListofChars *lista);

Lista1Elem* information (Lista1Elem *Data);


#endif //NHF_MENU1_INFORMATION_H
