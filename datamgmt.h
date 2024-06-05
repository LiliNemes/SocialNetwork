//
// Created by Lili on 14/11/2021.
//

#ifndef NHF_DATAMGMT_H
#define NHF_DATAMGMT_H

#include <stdbool.h>
#include <stdlib.h>
#include "debugmalloc.h"

/*
 * Ez a struktúra két elemet tartalmaz: egy sztringet, mely egy embernek az azonosítóját
 * tartalmazza, illetve egy List2 típusú pointert, mely a lista következő elemére mutat.
 */
typedef struct List2{
    char *connection;
    struct List2 *next;
}List2;

/*
 * Ez a struktúra hat elemet tartalmaz: egy sztringet, mely egy embernek az azonosítóját tartalmazza,
 * egy List 2 típusú pointert, mely egy lista első elemére mutat, egy boolean típust mely azt mutatja meg, hogy az
 * adott személy birtokában van-e az információnak, egy boolean típust mely azt mutatja meg, hogy az adott emberre
 * egy bizonyos tulajdonság igaz-e, egy egész típusú számot mely azt mutatja meg, hogy az adott ember ismerőseinek
 * hány százalékára igaz a tulajdonság, illetve egy List1 típusú pointert, mely a lista következő elemére mutat.
 */
typedef struct List1{
    char *person;
    List2 *connections;
    bool information;
    bool characteristic;
    int percentage;
    struct List1 *next;

}List1;

char *define_digits(const char *source,  int start);

bool compare (const List1 *search, const char *ID);

bool compare2 (const List2 *search, const char *ID);

List1 *search(List1 *where, const char *what);

List2 *new_connection_list2(List2 *where, char *what);

List2 *delete(List2 *wherefrom, char *what);


#endif //NHF_DATAMGMT_H
