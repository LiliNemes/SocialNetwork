//
// Created by Lili on 20/11/2021.
//

#ifndef NHF_MENU1_H
#define NHF_MENU1_H

#include <stdbool.h>
#include "conread.h"
#include "datamgmt.h"
#include "menu1_information.h"
#include "bool_initalizer.h"
#include "debugmalloc.h"
#include "misconceptions.h"
#include "spreading.h"
void menu1(Lista1Elem *feladat, bool kilep);
void menu(Lista1Elem *feladat);
Lista1Elem *menu_univerzalis(Lista1Elem *feladat, int menuPont);

#endif //NHF_MENU1_H
