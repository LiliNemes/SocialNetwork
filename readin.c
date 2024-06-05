#include "readin.h"

/*
 * A függvény ea consoleról beolvas egy sort, azaz enterig. A függvénynek meg kell adni a sor már korábban
 * beolvasott első karakterét. A függvény létrehoz egy dinamikusan foglalt stringet melybe a sor kerül,
 * minden egyes beolvasott karakter után újraméretezi, majd lezáró nullával zárja és megadja visszatérési értékként.
 */
char *readin_one_row(char c)
{
    char *beolvasott=(char*)malloc(1 *sizeof(char));
    int i;
    for(i = 0; c!='\n'; i++)
    {

        beolvasott = realloc(beolvasott, sizeof(char)*(i+2));
        beolvasott[i] = c;
        scanf("%c", &c);
    }
    beolvasott[i] = '\0';
    return beolvasott;
}

/*
 * Ez a függvény egy paraméterként megadott azonosítójú embert hozzáfűz a paraméterként megadott List1
 * típusú listához. A függvény külön kezeli azt az esetet ha a lista üres és azt amikor nem. A függvény
 * visszatérési értéke a lista első elemére mutató pointer.
 */
List1 *add_new_person(List1 *where, char *who)
{
    List1 *new;
    new = (List1*) malloc(sizeof(List1));
    new->person=who;
    new->connections=NULL;
    new->next=NULL;
    new->percentage=0;
    new->characteristic=NULL;
    new->information=NULL;

    if (where==NULL)
    {
        where=new;
    }
    else
    {
        List1 *move=where;
        while (move->next!=NULL)
        {
            move=move->next;
        }
        move->next=new;
    }
    return where;

}

/*
 * Ez a függvény egy paraméterként megadott List1 típusú listából töröl egy szintén paraméterként megadott
 * azonosítójú elemet. A függvény külön kezeli azt az esetet ha a megadott lista üres (nem csinál semmit),
 * ha az első elemet kell törölni (a lista elejére mutató pointer változik), vagy ha nem az első elemet kell
 * törölni. A visszatérési értéke a lista elejére mutató pointer.
 */
List1 *remove_person(List1 *where, char *who)
{
    List1 *runner=where;
    List1 *walker=NULL;
    while(runner!=NULL && !compare(runner,who))
    {
        walker=runner;
        runner=runner->next;
    }
    if (runner==NULL)
    {
        //do nothing
    }
    else if(walker==NULL)
    {
        List1 *ujeleje=runner->next;
        free(runner->person);
        free(runner);
        where=ujeleje;
    }
    else
    {
        walker->next=runner->next;
        free(runner->person);
        free(runner);
    }
    free(who);
    return where;
}
/*
 * ez a függvény a paraméterként megadott lista két eleméhez, melyek azonosítói a szintén paraméterként megadott
 * sztringek, kapcsolatként hozzáfűzi a másikat. Visszatérési értéke a List1 lista első elemére mutató pointer.
 */
List1 *add_new_connection(List1 *where, char *one, char *two)
{
    List1 *first= search(where, one);
    List1 *second= search(where, two);
    if(first==NULL || second==NULL)
    {
        printf("Something is wrong!");

    }
    else
    {
        first->connections= new_connection_list2(first->connections, two);
        second->connections= new_connection_list2(second->connections, one);

    }
    return where;
}
/*
 * Ez a függvény a paraméterként megadott lista két elemének kapcsolataiból, melyek azonosítói a szintén paraméterként
 * megadott sztringek kölcsönösen törli a másik azonosítóját ezáltal törölve a köztük lévő kapcsolatot. Visszatérési
 * értéke a List1 lista első elemére mutató pointer.
 */
List1 *remove_connection (List1 *where, char *one, char *two)
{
    List1 *first= search(where, one);
    List1 *second= search(where, two);
    if(first==NULL || second==NULL)
    {
        printf("Rossz a megadas");
    }
    else
    {
        first->connections= delete(first->connections, two);
        second->connections= delete(second->connections, one);
    }
    return where;
}

/*
 * Ez a függvény a consoleról való beolvasásért felel. Addig olvas, amíg nagy X karaktert nem kap. A kapott
 * szöveg tárolásáért, feldolgozásáért más, általa meghívott függvények felelnek, itt csak az esetekre
 * bontás található. A függvény paraméterként az összes adatot tároló List1 típusú listát kapja,
 * visszatérési értéke ennek a listának az első elemére mutató pointer.
 */
List1 *readin(List1 *Data)
{
    printf("You can start writing:\n");
    char c;
    scanf(" %c", &c);
    while(c!='X')
    {
        char *readin= readin_one_row(c);
        //ha ember
        if(readin[0]=='e')
        {
            char *ID=define_digits(readin, 3);
            //ha hozzáad
            if(readin[1]=='+')
            {
                Data=add_new_person(Data, ID);
            }
            //ha töröl
            if(readin[1]=='-')
            {
                Data=remove_person(Data, ID);
            }
            //ha elrontotta
            if(readin[1]!='+' && readin[1]!='-')
            {
                printf("Something is wrong!");
                free(ID);
            }
        }
        //ha kapcsolat
        if(readin[0]=='k')
        {
            char *first=define_digits(readin, 3);
            int k=3;
            while(readin[k]!=' ')
            {
                k++;
            }
            char *second=define_digits(readin, ++k);
            //ha hozzáad
            if (readin[1]=='+')
            {
                Data= add_new_connection(Data, first, second);
            }
            //ha elvesz
            if(readin[1]=='-')
            {
                Data= remove_connection(Data, first, second);
                free(first);
                free(second);
            }
            //ha elrontotta
            if(readin[1]!='+' && readin[1]!='-')
            {
                printf("Something is wrong!");
                free(first);
                free(second);
            }

        }
        //ha elrontotta
        if(readin[0]!='e'&& readin[0]!='k')
        {
            printf("Something is wrong!");
        }
        free(readin);
        scanf("%c", &c);
    }
    return Data;
}

