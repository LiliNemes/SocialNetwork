//
// Created by Lili on 22/11/2021.
//

#include "bool_initalizer.h"

Lista1Elem *bool_initializer (Lista1Elem *Data)
{
    Lista1Elem *mozgo=Data;
    while(mozgo!=NULL)
    {
        mozgo->information=false;
        mozgo=mozgo->kovetkezo;
    }
    return Data;
}