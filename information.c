//
// Created by Lili on 22/11/2021.
//

#include "information.h"
/*
 * Ez a függvény végigmegy a paraméterként megadott lista elemein és a boolean
 * típusú information-t mindenhol hamisra álltja.
 */
List1 *bool_initializer (List1 *Data)
{
    List1 *mover=Data;
    while(mover!=NULL)
    {
        mover->information=false;
        mover=mover->next;
    }
    return Data;
}

/*
 * Ez a függvény a paraméterként megadott lista minden elemének azonosítóját,
 * minden kapcsolatát, illetve ha az information true 1-est, ha false 2-est ír ki, soronként.
 */
void print_out(List1 *Data)
{
    List1 *mover=Data;
    while(mover!=NULL)
    {
        printf("%s\t", mover->person);
        List2 *mover2=mover->connections;
        while(mover2!=NULL)
        {
            printf("%s ", mover2->connection);
            mover2=mover2->next;
        }
        printf("\t");
        if(mover->information)
        {
            printf("1\n");
        }
        else
            printf("0\n");
        mover=mover->next;
    }
    printf("\n\n");
}

/*
 * Ez a függvény ellenőrzi, hogy van-e még olyan ember a List1 típusú, paraméterként átadott listában, a
 * ki még nem értesült az információról, viszont kapcsolatai alapján értesülhetne.
 */
bool check(List1 *Data)
{
    List1 *mover=Data;
    while(mover!=NULL)
    {
        if(!(mover->information)&&mover->connections!=NULL)
        {
            return false;
        }
        mover=mover->next;
    }
    return true;
}

/*
 * Ez a függvény paraméterként megkapja az adatokat tartalmazó List1 típusú listát, illetve az azoknak az azonosítóit
 * akik birtokában vannak az információknak. Az utóbbin végigmegy,az előbbiből kikeresi őket majd az ő connectionjeiket
 * - ha méhóg nem igazak - igazra változtatja. Visszatérési értéke a List1 lista első elemére mutató pointer.
 */
List1 *changer(List1 *Data, ListofChars *IDs, bool *n_c)
{
    ListofChars *to_check=IDs;

    while(to_check!=NULL)
    {
        List1 *who= search(Data, to_check->IDs);
        List2 *mover=who->connections;
        while(mover!=NULL)
        {
            List1 *who_to_change=search(Data, mover->connection);
            if(!who_to_change->information)
            {
                who_to_change->information=true;
                *n_c=false;
            }

            mover=mover->next;
        }
        to_check=to_check->next;
    }
    return Data;
}

/*
 * Ez a függvény a paraméterként megadott lista végére fűzi a paraméterként megadott sztringet. Külön kezeli
 * azt az esetet ha a lista üres, ekkor a lista elejére mutató pointer az új elemre mutat. Visszatérési
 * értéke a lista első elemére mutató pointer.
 */
ListofChars *add_char(ListofChars *where, char *what)
{
    ListofChars *new;
    new=(ListofChars*)malloc(sizeof(ListofChars));
    new->IDs=what;
    new->next=NULL;
    if(where==NULL)
    {
        where=new;
    }
    else
    {
        ListofChars *runner=where;
        ListofChars *walker=NULL;
        while(runner!=NULL)
        {
            walker=runner;
            runner=runner->next;
        }
        walker->next=new;
    }
    return where;
}

/*
 * Ez a függvény a paraméterként megadott ListofChars listához adja azokaz az azonosítókat/embereket, melyek még
 * nincsenek benne és a szintén paraméterként megadott List1 listában a hozzájuk tartozó information true.
 * Visszatérési értéke a ListofChars lista első elemére mutató pointer.
 */
ListofChars *adder(ListofChars *not_init, List1 *Data)
{
    if(not_init!=NULL)
    {
        List1 *mover = Data;
        while (mover != NULL)
        {
            if (mover->information)
            {
                ListofChars *mover2 = not_init;
                bool init = false;
                while (mover2 != NULL)
                {
                    if (mover2->IDs == mover->person)
                    {
                        init = true;
                    }
                    mover2 = mover2->next;
                }
                if (!init)
                    not_init = add_char(not_init, mover->person);
            }
            mover = mover->next;
        }
    }
    return not_init;
}

/*
 * Ez a függvény felszabadítja egy ListofChars típusú, paraméterként megadott lista minden elemét.
 */
void free_LoC(ListofChars *what)
{
    if(what!=NULL)
    {
        ListofChars *iter = what;
        while (iter != NULL)
        {
            ListofChars *next = iter->next;
            free(iter);
            iter = next;
        }
    }

}

/*
 * Ez a függvény felel az első kísérlet létrehozásáért és futtatásáért. Paraméterként a társaság adatait tartalmazó
 * listát kapja meg, az ennek a listának az első elemére mutató pointer a visszatérítési értéke.
 */
List1 *information (List1 *Data)
{
    printf(".-----------------------------------------------------------------------------------------------------.\n"
           "| This experiment models the spread of information. There is one person with some information,\n"
           "           who starts spreading it to their friends, who start spreading it to their friends, who... It's\n"
           "           only a matter of time before it reaches the majority of the society - through connections, or, in \n"
           "           other words, NETWORKS.                                                                            |\n"
           "'------------------------------------------------------------------------------------------------------------'\n");
    printf("Who is the source of information? (ID + ENTER)\n");
    Data=bool_initializer(Data);
    char *who;
    char c;
    scanf(" %c", &c);
    who= readin_one_row(c);
    char *realid = define_digits(who, 0);
    List1 *whos_ID;
    whos_ID = search(Data, realid);
    whos_ID->information = true;
    ListofChars *who_know = (ListofChars*)malloc(sizeof(ListofChars));
    who_know->IDs = whos_ID->person;
    who_know->next = NULL;
    print_out(Data);
    bool ready=true;
    while(ready)
    {
        bool nothing_changed=true;
        Data=changer(Data, who_know, &nothing_changed);
        print_out(Data);
        who_know=adder(who_know, Data);
        if(nothing_changed || check(Data))
        {
            ready=false;

        }

    }
    free(who);
    free_LoC(who_know);
    free(realid);
    printf("\n End of experiment.\n");
    return Data;
}