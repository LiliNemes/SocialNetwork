//
// Created by Lili on 20/11/2021.
//

#ifndef NHF_MENU_H
#define NHF_MENU_H

#include <stdbool.h>
#include "readin.h"
#include "datamgmt.h"
#include "information.h"
#include "debugmalloc.h"
#include "misconceptions.h"
#include "spreading.h"
void read_menu(List1 *Data);

List1 *menu_universal(List1 *Data, int menuPoint);

List1* menu(List1 *Data);

#endif //NHF_MENU_H
