#include "datamgmt.h"
/*
 * Ez a függvény egy karaktertömb és egy egész típusú szám megadásának segítségével kivág egy részletet
 * a karaktertömbből és visszaadja ezt a dinamikusan foglalt sztringet. Az azonosítók kivágásakor
 * használom, azon az elven működik, hogy egy azonosító mindig két space vagy egy space és egy lezáró
 * nulla között helyezkedik el.
 */
char *define_digits(const char *source, const int start)
{
    int num_of_digits=0;
    int t=start;
    while(source[t]!=' ' && source[t]!='\0')
    {
        num_of_digits++;
        t++;
    }
    num_of_digits++;
    char *ID=(char*)malloc(num_of_digits * sizeof(char));

    int z=0;
    for(int u=start; u < start + num_of_digits - 1; u++)
    {
        ID[z]=source[u];
        z++;
    }
    ID[num_of_digits - 1]='\0';
    return ID;
}

/*
 * Ez a függvény összehasonlítja a paraméterként átadott Lista1 elem személyazonosítóját és egy
 * sztring tömbként megadott másik értéket. Célja, hogy meghatározza, a két karakterazonosító megegyezik-e.
 * Ha igen akkor a visszatérési érték igaz, ha nem, akkor hamis.
 */
bool compare (const List1 *search, const char *ID)
{
    for(int i=0; ID[i]!='\0'; i++)
    {
        if(search->person[i]!=ID[i])
        {
            return false;
        }

    }
    return true;
}
/*
 * A függény pontosan úgy müködik, mint a compare függvény, csak List1 helyett List2 azonosítókat
 * hasonlít össze a megadott karaktertömbbel.
 */
bool compare2 (const List2 *search, const char *ID)
{
    for(int i=0; ID[i]!='\0'; i++)
    {
        if(search->connection[i]!=ID[i])
        {
            return false;
        }

    }
    return true;
}

/*
 * Ez a függvény végigmegy a List 1-en és megkeresi benne a paraméterként megadott sztringet.
 * Minden list1 elemre elvégzi a compare függvényt, ha egyezést talál egy, a sztringgel megegyező
 * azonosítójú Lista1 elemre mutató pointerrel tér vissza. Amennyiben nincs egyezés a visszatérési
 * érték NULL pointer.
 */

List1 *search(List1 *where, const char *what)
{
    List1 *found;
    List1 *move=where;
    while(move!=NULL)
    {
        if(compare(move, what))
        {
            found=move;
            return found;
        }
        move=move->next;
    }
    return NULL;
}
/*
 * Ez a függvény egy új elemet (char *what) fűz hozzá a paraméterként megadott List2 lista végére
 * (List 2*where). Külön kezeli az a helyzetet is, mikor a megadott lista üres és így az újonnan
 * hozzáfűzött elem lesz az első. A kibővített lsita elejére mutató pointerrel tér vissza.
 */
List2 *new_connection_list2(List2 *where, char *what)
{
    List2 *new;
    new = (List2 *) malloc(sizeof(List2));
    new->connection=what;
    new->next=NULL;

    if (where==NULL)
    {
        where=new;
    }
    else
    {
        List2 *mover=where;
        while (mover->next!=NULL && mover->connection!=what)
        {
            mover=mover->next;
        }
        if(mover->connection==what)
        {
            //do nothing
        }
        else
        {
            mover->next = new;
        }
    }
    return where;
}

/*
 * Ez a függvény egy paraméterként megadott List2 típusú listából törli a szintén paraméterként
 * megadott sztringet. A compare 2 függvény segítségével előbb megkeresi a listában, majd törli.
 * Külön kezeli azt az esetet, ha a lista üres (ne csináljon semmit), ha az első elemet kell törölni
 * (a listára mutató pointer változik), illetve ha nem az első elemet kell törölni. A visszatérési
 * értéke a lista első elemére mutató pointer.
 */

List2 *delete(List2 *wherefrom, char *what)
{
    List2 *runner=wherefrom;
    List2 *walker=NULL;
    while(runner != NULL && !compare2(runner, what))
    {
        walker=runner;
        runner=runner->next;
    }
    if (runner == NULL)
    {
        //do nothing
    }
    else if(walker == NULL)
    {
        List2 *new_beginning=runner->next;
        free(runner->connection);
        free(runner);
        wherefrom=new_beginning;
    }
    else
    {
        walker->next=runner->next;
        free(runner->connection);
        free(runner);
    }
    return wherefrom;
}

