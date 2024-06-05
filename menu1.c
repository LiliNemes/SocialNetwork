//
// Created by Lili on 20/11/2021.
//

#include "menu1.h"


void menu1(Lista1Elem *feladat, bool kilep)
{

    if (!kilep)
    {
        printf("1, ha irnal meg - 0, ha tovabb mennel\n");
        char c;
        scanf(" %c", &c);
        switch (c) {
            case '0':
                kilep=true;
                menu1(feladat, kilep);
                break;
            case '1':
                scanf(" %c", &c);
                feladat = beolvasas(feladat);
                menu1(feladat, kilep);
                break;
            default:
                printf("Nem jo!\n");
                menu1(feladat, kilep);
                break;
        }
    }
    else
        return;
}
void menu(Lista1Elem *f)
{
    Lista1Elem * feladat = f;
    bool kilep = false;
    while (!kilep)
    {
        printf("1 - elso kiserlet\n"
               "2 - masodik kiserlet\n"
               "3 - harmadik kiserlet\n"
               "4 - uj kozosseg letrehozasa\n"
               "5 - kilepes\n");
        char c;
        scanf(" %c", &c);
        switch (c) {
            case '1':
                feladat = menu_univerzalis(feladat, 1);

                break;
            case '2':
                feladat= menu_univerzalis(feladat, 2);
                break;
            case '3':
                feladat= menu_univerzalis(feladat, 3);
                break;
            case 4:
                printf("4");
                break;
            default:
                printf("5");
                kilep = true;
                break;
        }
    }

}

Lista1Elem *menu_univerzalis(Lista1Elem *f, int menuPont)
{
    bool kilep = false;
    Lista1Elem* feladat = f;
    while (!kilep){

        printf("1, ha kezdened a kiserletet - 0, ha visszamennel a menuhoz\n");
        char c;
        //scanf("%c", &c);
        scanf(" %c", &c);
        switch (c) {
            case '0':
                kilep=true;
                break;
            case '1':
                if(menuPont==1)
                    feladat = information(feladat);
                else if(menuPont==2)
                    feladat=misconceptions(feladat);
                if(menuPont==3)
                    feladat= spreading(feladat);
                break;
            default:
                printf("Nem jo!\n");
                break;
        }
    }

    return feladat;
}

