#include "delete_society.h"
/*
 * Ez a függvény elemenként felszabadít egy List1 típusú listát.
 */

void clear_list1(List1 *list)
{
    List1 *iter=list;
    while(iter!=NULL)
    {
        List1 *next=iter->next;
        free(iter);
        iter=next;
    }
}

/*
 * Ez a függvény elemenként felszabadít egy List2 típusú listát.
 */

void clear_list2(List2 *list)
{
    List2 *iter=list;
    while(iter!=NULL)
    {
        List2 *kovetkezo=iter->next;
        free(iter);
        iter=kovetkezo;
    }
}

/*
 * Ez a függvény felszabadítja az egész adatszerkezet alapját adó lisákat és a bennük szereplő
 * dinamikus sztringeket. Továbi magyarzat a függvényben kommentelve.
 */
void delete_all(List1 *Data)
{
    //1. lépés - felszabadítjuk minden List1-ben található List2 char *connection elemét.
    List1 *v = Data;
    while (v != NULL)
    {
        List2 *w = v->connections;
        while (w != NULL)
        {
            free(w->connection);
            w = w->next;
        }
        v = v->next;
    }

    //2. lépés - felszabadítjuk minden List1-ben található List2-t.
    List1 *l = Data;
    while (l != NULL)
    {
        clear_list2(l->connections);
        l = l->next;

    }

    //3. lépés - felszabadítjuk List1 minden elemének char *komponensét.
    List1 *b = Data;
    while (b != NULL)
    {
        free(b->person);
        b = b->next;
    }

    //4. lépés - flszabadítjuk List1-et.
    clear_list1(Data);
}