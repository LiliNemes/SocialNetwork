//
// Created by Lili on 22/11/2021.
//

#ifndef NHF_INFORMATION_H
#define NHF_INFORMATION_H

#include "readin.h"
#include "datamgmt.h"
#include "stdlib.h"
#include "delete_society.h"
#include "debugmalloc.h"


typedef struct ListofChars
{
    char *IDs;
    struct ListofChars *next;
}ListofChars;

List1 *bool_initializer (List1 *Data);

void print_out(List1 *Data);

bool check(List1 *Data);

List1 *changer(List1 *Data, ListofChars *IDs, bool *n_c);

ListofChars *add_char(ListofChars *where, char *what);

ListofChars *adder(ListofChars *not_init, List1 *Data);

void free_LoC(ListofChars *what);

List1 *information (List1 *Data);

#endif //NHF_INFORMATION_H
