#include "misconceptions.h"
/*
 * Ez a függvény a paraméterként megadott List1 lista minden elemének soronként kiírja az azonosítóját,
 * a kapcsolatait, illetve itt kell a felhasználónak megadnia, hogy az adott emberre igaz-e a tulajdonság.
 * Ha 1-est ír a characteristic truera változik, ha 0-ást akkor falsera. A függvény visszatétési értéke a
 * List1 lista első elemére mutató pointer.
 */
List1 *give_characteristics(List1 *Data)
{
    List1 *mover = Data;
    while (mover != NULL)
    {
        printf("%s \t", mover->person);
        List2 *mover2 = mover->connections;
        while (mover2 != NULL)
        {
            printf("%s ", mover2->connection);
            mover2 = mover2->next;
        }
        printf("\t here: ");
        int tf;
        scanf("%d", &tf);

        if (tf == 1)
            mover->characteristic = true;
        if (tf == 0)
            mover->characteristic = false;

        printf("\n");

        mover = mover->next;
    }

        return Data;

}

/*
 * Ez a függvény a paraméterként megadott List1 lista minden elemére kiszámolja, hogy ismerőseinek hány
 * százalékára igaz a megadott tulajdonság, majd a tizedespont utáni tagokat elvágva egészként tárolja a
 * struktúra percentage elemében. A üggvény visszatérési értéke a lista első elemére mtató pointer.
 */
List1 *calculator(List1 *Data)
{
    List1 *mover=Data;
    while(mover!=NULL)
    {
        int yes=0;
        int no=0;
        List2 *mover2=mover->connections;
        while(mover2!=NULL)
        {
            List1 *who=search(Data, mover2->connection);
            if(who->characteristic)
            {
                yes++;
            }
            if(!who->characteristic)
            {
                no++;
            }
            mover2=mover2->next;
        }
        if(yes==0 && no==0)
        {
            mover->percentage=0;
        }
        else
            mover->percentage=(yes*100/(yes+no));
        mover=mover->next;
    }
    return Data;
}

/*
 * Ez a függvény a paraméterként megadott List1 lista minden elemének azonosítóját, kapcsolatait,
 * 1-et ha igaz rá a tulajdnság, 0-t ha nem, a százalékot kiírja soronként. Nincs visszatérési értéke.
 */
void write_out(List1 *Data)
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
        if(mover->characteristic)
            printf("1\t");
        else if(!mover->characteristic)
        {
            printf("0\t");
        }
        printf("%d %%\n", mover->percentage);
        mover=mover->next;
    }
}

/*
 * Ez a függvény a paraméterként megadott lista minden elemén végigmegy és megvizsgálja, hogy igaz-e rá a tulajdonság.
 * Viszatérési értéke az egeész közösségre jellemző valódi arány, egy egész típusú változóban.
 */
int average_of_sum(List1 *Data)
{
    List1 *mover=Data;
    int sum_yes=0;
    int sum_all=0;
    while(mover!=NULL)
    {
        if(mover->characteristic)
            sum_yes++;
        sum_all++;
        mover=mover->next;
    }
    int average=(sum_yes*100/sum_all);
    return average;
}

/*
 * Ez a függvény felel a paraméterként megadott List1 listában szereplő adatokon a második kísérlet végrehajtásáért.
 * visszatérési értéke a lista első elemére muattó pointer.
 */
List1 *misconceptions(List1 *Data)
{
    printf(".-------------------------------------------------------------------------------------------------------------.\n"
           "| This experiment is about the misconceptions individuals make base on networks. People tend \n"
           "           to look to their social connections to understand their world. For example\n"
           "           people look to their peers to find out what percentage of their friends (not counting themselves) are, \n"
           "           say, volunteering. However, these numbers can easily fool people. In this experiment you need to decide\n"
           "           for every person whether they're volunteering or not. You're going to see what percentage of society\n"
           "           volunteers according to every person and what is the truth.                                                |\n"
           "'---------------------------------------------------------------------------------------------------------------------'\n");
    printf("Are they volunteering (1) or not(0)?\n");
    Data=give_characteristics(Data);
    Data=calculator(Data);
    write_out(Data);
    int average= average_of_sum(Data);
    printf("The real rate: %d %% \n", average);
    return Data;

}