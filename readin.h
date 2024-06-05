//
// Created by Lili on 14/11/2021.
//

#ifndef NHF_READIN_H
#define NHF_READIN_H

#include "datamgmt.h"
#include "debugmalloc.h"


char *readin_one_row(char c);

List1 *add_new_person(List1 *where, char *who);

List1 *remove_person(List1 *where, char *who);

List1 *add_new_connection(List1 *where, char *one, char *two);

List1 *remove_connection (List1 *where, char *one, char *two);

List1 *readin(List1 *Data);


#endif //NHF_READIN_H
