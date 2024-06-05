#include "filemgmt.h"

/*
 * Ez a függvény az adatszerkezet elemeit két különböző .txt fájlba írja ki.
 */
void file_out(List1 *Data)
{
    FILE *fp;
    fp = fopen("connections.txt", "wt");
    FILE *fa;
    fa = fopen("IDs.txt", "wt");
    if (fa == NULL)
    {
    perror(("File doesn't exist"));
    }
    if (fp == NULL)
    {
    perror("File doesn't exist");
    }
    List1 *m = Data;
    while (m != NULL)
    {
        fprintf(fp,"%s ", m->person);
        fprintf(fa,"%s\n", m->person);
        List2 *p = m->connections;
        while (p != NULL)
        {
            fprintf(fp,"%s ", p->connection);
            p = p->next;
}


        fprintf(fp,"\n");
        m = m->next;

    }
    fprintf(fa,"X");
    fprintf(fp,"X");
    fclose(fp);
    fclose(fa);
}

/*
 * A függvény egy megadott fileból beolvas egy sort, azaz enterig. A függvénynek meg kell adni a filet
 * amiből be kell olvasson illetve a sor már korábban beolvasott első karakterét. A függvény létrehoz
 * egy dinamikusan foglalt stringet melybe a sor kerül, minden egyes beolvasott karakter után újraméretezi,
 * majd lezáró nullával zárja és megadja visszatérési értékként.
 */
char *readin_one_row_file(FILE *fp, char c)
{
    char *readin=(char*)malloc(1 *sizeof(char));
    int i;
    for(i = 0; c!='\n' ; i++)
    {
        readin = realloc(readin, sizeof(char)*(i+2));
        readin[i] = c;
        fscanf(fp,"%c", &c);
    }
    readin[i] = '\0';
    return readin;
}

/*
 * Ez a függvény fileból való beolvasás során a második, kiiras.txt fájlból egy beolvasott sor feldolgozásával
 * létrehozza a megadott azonosítójú ember kapcsolatait. a define_digits segédfüggvény segítségével kiválasztja
 * az azonosítókat, a sor elején lévő azonosítójú embert megkeresi az adatokat tároló listában, az ő kapcsolatait
 * tároló listához fűzi a sorban szereplő többi azonosítót.
 */
List1 *add_connection_file(List1 *where, char *source)
{
    char *to_who = define_digits(source, 0);
    List1 *source_ID = search(where, to_who);
    int num_of_digits = 0;
    int t;
    for (t = 0; source[t] != ' '; t++)
    {
        num_of_digits++;
    }
    for (int v = num_of_digits; source[v + 1] != '\0'; v = num_of_digits)
    {
        char *connection = define_digits(source, v + 1);
        source_ID->connections = new_connection_list2(source_ID->connections, connection);
        for (int w = v + 1; source[w] != ' ' && source[w + 1] != '\0'; w++)
        {
            num_of_digits++;
        }
        num_of_digits++;
    }
    free(source);
    free(to_who);

    return where;
}

/*
 * Ez a függvény a fileból (2 .txt fileból) való beolvasásért felel. Addig olvas, amíg nagy X karaktert nem kap. A kapott
 * szöveg tárolásáért, feldolgozásáért más, általa meghívott függvények felelnek, itt csak az esetekre
 * bontás található. A függvény paraméterként az összes adatot tároló List1 típusú listát kapja,
 * visszatérési értéke ennek a listának az első elemére mutató pointer.
 */
List1* freadin(List1 *Data)
{
    FILE *first;
    first = fopen("C:IDs.txt", "r");
    if(first!=NULL)
    {
        char r;
        fscanf(first, " %c", &r);
        while (r != 'X')
        {
            char *readin = readin_one_row_file(first, r);
            Data = add_new_person(Data, readin);
            fscanf(first, " %c", &r);

        }
        fclose(first);
    }
    else
    {
        printf("The file doesn't exist.\n");
    }
    FILE *second;
    second=fopen("connections.txt", "r");
    if(second != NULL)
    {
        char z;
        fscanf(second, " %c", &z);
        while (z != 'X')
        {
            char *readin2=readin_one_row_file(second, z);
            Data=add_connection_file(Data, readin2);
            fscanf(second, "%c", &z);
        }
        fclose(second);
    }
    else
    {
        printf("The file doesn't exist\n");
    }
    return Data;
}