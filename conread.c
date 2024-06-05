//
// Created by Lili on 14/11/2021.
//

#include "conread.h"

//X-ig olvasson, soronként;
Lista1Elem *beolvasas(Lista1Elem *where)
{
    printf("Irhatsz:\n");
    char c;
    scanf(" %c", &c);
    while(c!='X')
    {
        char *beolvasott=(char*)malloc(1 *sizeof(char));
        int i=1;
        beolvasott[0]='\0';
        while(c!='\n')
        {
            char *seged=(char*)malloc((i+1)*sizeof(char));
            seged[0]=c;
            for(int j=1; j<=i; j++)
            {
                seged[j]=beolvasott[j-1];
            }
            free(beolvasott);
            beolvasott=seged;
            i++;
            scanf("%c", &c);
        }
        //ember vagy kapcsolat-e?
        int szamlalo=0;
        for(int z=0; beolvasott[z]!='\0'; z++)
        {
            szamlalo++;
        }
        //ha ember
        if(beolvasott[szamlalo-1]=='e')
        {
            char *azonosito=szamjegykivalaszto(beolvasott, 0);
            int k=0;
            while(beolvasott[k]!=' ')
            {
                k++;
            }
            //ha hozzáad
            if(beolvasott[k+1]=='+')
            {
                Lista1Elem *uj;
                uj = (Lista1Elem*) malloc(sizeof(Lista1Elem));
                uj->person=azonosito;
                uj->connections=NULL;
                uj->kovetkezo=NULL;

                if (where==NULL)
                {
                    where=uj;
                }
                else
                {
                    Lista1Elem *kereso=where;
                    while (kereso->kovetkezo!=NULL)
                    {
                        kereso=kereso->kovetkezo;
                    }
                    kereso->kovetkezo=uj;
                }

            }
            //ha elvesz
            if(beolvasott[k+1]=='-')
            {
                Lista1Elem *kereso=where;
                Lista1Elem *lemarado=NULL;
                while(kereso!=NULL && !ugyanaz(kereso,azonosito))
                {
                    lemarado=kereso;
                    kereso=kereso->kovetkezo;
                }
                if (kereso==NULL)
                {

                }
                else if(lemarado==NULL)
                {
                    Lista1Elem *ujeleje=kereso->kovetkezo;
                    free(kereso->person);
                    free(kereso);
                    where=ujeleje;
                }
                else
                {
                    lemarado->kovetkezo=kereso->kovetkezo;
                    free(kereso->person);
                    free(kereso);
                }
                free(azonosito);
            }
            //ha nem jó
            if(beolvasott[k+1]!='+' && beolvasott[k+1]!='-')
            {
                printf("Nem jo a beiras!");
                free(azonosito);
            }

        }
        //ha kapcsolat
        if(beolvasott[szamlalo-1]=='k')
        {
            char *egyik=szamjegykivalaszto(beolvasott, 0);
            int k=0;
            while(beolvasott[k]!=' ')
            {
                k++;
            }
            char *masik=szamjegykivalaszto(beolvasott, k+1);
            int h=k+1;
            while(beolvasott[h]!=' ')
            {
                h++;
            }
            //ha hozzáad
            if (beolvasott[h+1]=='+')
            {
                Lista1Elem *elso= kereso(where, egyik);
                Lista1Elem *masodik= kereso(where, masik);
                if(elso==NULL || masodik==NULL)
                {
                    printf("Rossz a megadas");

                }
                else
                {
                    elso->connections= ujkapcsolat(elso->connections, masik);
                    masodik->connections= ujkapcsolat(masodik->connections, egyik);

                }


            }
            //ha elvesz
            if(beolvasott[h+1]=='-')
            {
                Lista1Elem *elso= kereso(where, egyik);
                Lista1Elem *masodik= kereso(where, masik);
                if(elso==NULL || masodik==NULL)
                {
                    printf("Rossz a megadas");
                }
                else
                {
                    elso->connections= torles(elso->connections, masik);
                    masodik->connections= torles(masodik->connections, egyik);
                }
            }
            //ha elrontotta
            if(beolvasott[h+1]!='+' && beolvasott[h+1]!='-')
            {
                printf("Nem jo!");
            }

        }
        //ha elrontotta
        if(beolvasott[szamlalo-1]!='e'&& beolvasott[szamlalo-1]!='k')
        {
            printf("Valami nem jo!");
        }
        free(beolvasott);

        scanf("%c", &c);

    }

    return where;
}