//
// Created by Lili on 22/11/2021.
//

#ifndef NHF_FILEMGMT_H
#define NHF_FILEMGMT_H
#include "stdbool.h"
#include "datamgmt.h"
#include "debugmalloc.h"
#include "readin.h"

void file_out(List1 *Data);

char *readin_one_row_file(FILE *fp, char c);

List1 *add_connection_file(List1 *where, char *source);

List1 *freadin(List1 *Data);

#endif //NHF_FILEMGMT_H
