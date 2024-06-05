#include "menu.h"
#include "filemgmt.h"

/*
 * Ez a függvény hozza létre az első menüt. 1 esetén újból meghívja a beolvasást, 0 esetén kilép
 * a ciklusból, a program tovább halad. A függvény addig ismétlődik amíg a felhasználó
 * 0-val ki nem lép.
 */
void read_menu(List1 *Data)
{
    bool exit = false;
    while (!exit)
    {
        printf("Press 1 if you would like to add more people or connections.\n"
               "Press 0 if you would like to continue with the experiments.\n");
        char c;
        scanf(" %c", &c);
        switch (c) {
            case '0':
                exit=true;
                break;
            case '1':

                Data = readin(Data);
                break;
            default:
                printf("Something is wrong!\n");
                break;
        }
    }

}

/*
 * Ez a menü jelenik meg minden kísérlet elején. Itt döntheti el a felhasználó, hogy kezdi a kísérletet
 * (vagy megismétli), vagy visszatér a főmenübe. Paraméterként meg kell adni egy intet is, ennek a segítségével
 * dönti el a program, hogy melyik kísérletet kell az 1-es gomb lenyomása esetén elindítani.
 */
List1 *menu_universal(List1 *Data, int menuPoint)
{
    bool exit = false;
    List1 * copy = Data;
    while (!exit){

        printf("Press 1 to start the experiment \n Press 0 to go back to the menu.\n");
        char c;
        scanf(" %c", &c);
        switch (c) {
            case '0':
                exit=true;
                break;
            case '1':
                if(menuPoint==1)
                    copy = information(copy);
                else if(menuPoint==2)
                    copy = misconceptions(copy);
                if(menuPoint==3)
                    copy = spreading(copy);
                break;
            default:
                printf("Something is wrong!\n");
                break;
        }
    }

    return Data;
}

/*
 * Ez a függvény felel a főmenü meghívásáért. Segítségével a felhasználó 5 menüpontból választhat.
 */
List1 *menu(List1 *Data)
{
    List1 *copy = Data;
    bool exit = false;
    while (!exit)
    {
        printf(
               " __| |____________________________________________________________________________________________| |__ \n"
               "(__| |____________________________________________________________________________________________| |__)\n"
               "   | |  1 - first experiment\n"
               "        2 - second experiment\n"
               "        3 - third experiment\n"
               "        4 - new society\n"
               "        5 - exit                                                                                  | |   \n"
               " __| |____________________________________________________________________________________________| |__ \n"
               "(__|_|____________________________________________________________________________________________|_|__)\n"
               );
        char c;
        scanf(" %c", &c);
        switch (c) {
            case '1':
                copy = menu_universal(copy, 1);
                break;
            case '2':
                copy= menu_universal(copy, 2);
                break;
            case '3':
                copy= menu_universal(copy, 3);
                break;
            case '4':
                delete_all(Data);
                Data = NULL;
                Data = readin(Data);
                read_menu(Data);
                file_out(Data);

                copy = Data;
                break;
            case'5':
                exit = true;
                break;
            default:
                printf("Something is wrong!");
                break;
        }
    }
    return Data;
}

