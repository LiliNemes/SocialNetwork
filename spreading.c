#include "spreading.h"

/*
 * Ez a függvény a paraméterként megadott ListofChars lista végére fűzi azokat az azonosítókat, amikhez a paraméterként
 * megadottList1 listában tartozó characteristics érték igaz.
 */
ListofChars *who_are_1(List1 *Data, ListofChars *where_to)
{
    List1 *mover=Data;
    while(mover!=NULL)
    {
        if(mover->characteristic)
        {
            where_to=add_char(where_to, mover->person);
        }
        mover=mover->next;
    }

    return where_to;
}

/*
 * Ez a függvény a paraméterként megadott List1 lista minden elemének soronként kiírja az azonosítóját, kapcsolatait,
 * a hozzátartozó százalékot, illetve 1-et ha igaz a characteristics, 0-át ha nem. Nincs visszatérési értéke.
 */
void print_out_3(List1 *Data)
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
        printf("%d %%\t", mover->percentage);
        if(mover->characteristic)
            printf("1\n");
        else if(!mover->characteristic)
            printf("0\n");
        mover=mover->next;
    }
}

/*
 * Ez a függvény végigmegy a paraméterként kapott ListofChars lista minden elemén, majd miután kikereste a szintén
 * paraméterként megadott List1 listából az azonosítót végigmegy minden kapcsolatán, és akire a characteristics false
 * de a percentage (ismerőseinek igaz százaléka)>=50 azoknak a characteristicét igazra változtatja. Visszatérési értéke
 * a List1 lista első elemére mutató pointer.
 */
List1 *transformer(List1 *Data, ListofChars *are_true,  bool *n_c, int percentage)
{
    ListofChars *mover = are_true;
    while (mover != NULL)
    {
        List1 *whos_ID = search(Data, mover->IDs);
        List2 *mover2 = whos_ID->connections;
        while (mover2 != NULL)
        {
            List1 *akinek = search(Data, mover2->connection);
            if (!akinek->characteristic && akinek->percentage>=percentage)
            {
                akinek->characteristic = true;
                *n_c=false;
            }
            mover2 = mover2->next;
        }
        mover = mover->next;
    }
    return Data;
}

/*
 * Ez a függvény a paraméterként megadott ListofChars listához adja azokaz az azonosítókat/embereket, melyek még
 * nincsenek benne és a szintén paraméterként megadott List1 listában a hozzájuk tartozó characteristics true.
 * Visszatérési értéke a ListofChars lista első elemére mutató pointer.
 */
ListofChars *adder_3(ListofChars *not_init, List1 *Data)
{

    if(not_init!=NULL)
    {
        List1 *mover = Data;
        while (mover != NULL)
        {
            if (mover->characteristic)
            {
                ListofChars *mover2 = not_init;
                bool is_in = false;
                while (mover2 != NULL)
                {
                    if (mover2->IDs == mover->person)
                    {
                        is_in = true;
                    }
                    mover2 = mover2->next;
                }
                if (!is_in)
                    not_init = add_char(not_init, mover->person);
            }
            mover = mover->next;
        }
    }
    return not_init;
}

/*
Ez a függvény ellenőrzi, hogy van-e még olyan ember a List1 típusú, paraméterként átadott listában, akire még nem
 igaz a characteristic, de kapcsolatai alapján lehetne az.
 */
bool check_3(List1 *Data)
{
    List1 *mover=Data;
    while(mover!=NULL)
    {
        if(!(mover->characteristic)&&(mover->percentage>=50))
        {
            return false;
        }
        mover=mover->next;
    }
    return true;
}

/*
 * Ez a függvény ellenőrzi, hogy a paraméterként megadott List1 lista minden elemének characteristic komponense
 * hamis-e. Ha igen, a visszatérési érték igaz, ha nem, hamis.
 */
bool all_is_false(List1 *Data)
{
    List1 *mover=Data;
    int all=0;
    int no=0;
    while(mover!=NULL)
    {
        all++;
        if(!mover->characteristic)
            no++;
        mover=mover->next;
    }
    if(all==no)
        return true;
    else
        return false;
}

/*
 * Ez a függvény a paraméterként megadott lista minden elemének characteristicét false-ra változtatja.
 * Visszatérési értéke a lista első tagjára mutató pointer.
 */
List1 *make_it_false(List1 *Data)
{
    List1 *mover=Data;
    while(mover!=NULL)
    {
        if(mover->characteristic)
            mover->characteristic=false;
        mover=mover->next;
    }
    return Data;
}

/*
 * Ez a függvény felelős a harmadik kísérlet végrehajtásáért. Paraméterként egy list1 listát kap, benne a szükséges
 * adatokkal. Visszatérési értéke a lista elejére mutató pointer.
 */
List1 *spreading(List1 *Data)
{
    printf(".-------------------------------------------------------------------------------------------------------------.\n"
           "| Just like information, behavioral patterns can spread, too. For example, people are more\n"
           "           likely to volunteer if the majority of their friends does. In this experiment you will see how much\n"
           "           our friends behaviours and characteristics affect ours. If 50%% of one's friends volunteers, they \n"
           "           will volunteer too - spreading this amongst their friends.                                                |\n"
           "'--------------------------------------------------------------------------------------------------------------------'\n");
    if(Data->characteristic!=false && Data->characteristic!=true || all_is_false(Data))
    {

        printf("This happens if you play the third experiment before the second. But no problem -"
               "you can give the characteristics here as well. Write 1 if someone volunteers and 0 if they don't.\n");
        Data=give_characteristics(Data);
    }
    printf("From what %% is someone 'converted'?\n");
    int given_percentage;
    scanf("%d", &given_percentage);
    bool in=true;
    ListofChars *is_true=NULL;
    is_true=who_are_1(Data, is_true);
    Data=calculator(Data);
    print_out_3(Data);
    printf("\n");
    while(in)
    {
        bool nothing_changed=true;
        Data=transformer(Data, is_true, &nothing_changed, given_percentage);
        Data=calculator(Data);
        print_out_3(Data);
        printf("\n");
        is_true=adder_3(is_true, Data);
        if(check_3(Data)||nothing_changed)
        {
            in=false;

        }
    }
    free_LoC(is_true);
    Data=make_it_false(Data);
    printf("\nEnd of experiment.\n");
    return Data;

}