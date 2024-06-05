//
// Created by Lili on 23/11/2021.
//

#ifndef NHF_SPREADING_H
#define NHF_SPREADING_H

#include "debugmalloc.h"
#include "datamgmt.h"
#include "menu.h"
#include "stdio.h"
#include "stdlib.h"
#include "stdbool.h"
#include "misconceptions.h"
#include "information.h"

ListofChars *who_are_1(List1 *Data, ListofChars *where_to);

void print_out_3(List1 *Data);

List1 *transformer(List1 *Data, ListofChars *are_true, bool *n_c, int percentage);

ListofChars *adder_3(ListofChars *not_init, List1 *Data);

bool check_3(List1 *Data);

bool all_is_false(List1 *Data);

List1 *make_it_false(List1 *Data);

List1 *spreading(List1 *Data);

#endif //NHF_SPREADING_H
