//
// Created by Lili on 22/11/2021.
//

#include "menu1_information.h"


void kiiras(Lista1Elem *Data)
{
    Lista1Elem *mozgo=Data;
    while(mozgo!=NULL)
    {
        printf("%s\t", mozgo->person);
        Lista2Elem *mozgo2=mozgo->connections;
        while(mozgo2!=NULL)
        {
            printf("%s ", mozgo2->connection);
            mozgo2=mozgo2->kovetkezo;
        }
        printf("\t");
        if(mozgo->information)
        {
            printf("1\n");
        }
        else
            printf("0\n");
        mozgo=mozgo->kovetkezo;
    }
    printf("\n\n");
}

bool ellenorzes(Lista1Elem *Data)
{
    Lista1Elem *mozgo=Data;
    while(mozgo!=NULL)
    {
        if(!(mozgo->information)&&mozgo->connections!=NULL)
        {
            return false;
        }
        mozgo=mozgo->kovetkezo;
    }
    return true;
}

Lista1Elem *valtoztato(Lista1Elem *Data, ListofChars *azonositokok)
{
    ListofChars *vizsgalando=azonositokok;
    while(vizsgalando!=NULL)
    {
        Lista1Elem *aki= kereso(Data, vizsgalando->azonositok);
        Lista2Elem *egyesevel=aki->connections;
        while(egyesevel!=NULL)
        {
            Lista1Elem *akinek=kereso(Data, egyesevel->connection);
            if(!akinek->information)
                akinek->information=true;
            egyesevel=egyesevel->kovetkezo;
        }
        vizsgalando=vizsgalando->next;
    }
    return Data;
}



ListofChars * vegerefuz(ListofChars *lista, char *mit)
{
    ListofChars *uj;
    uj=(ListofChars*)malloc(sizeof(ListofChars));
    uj->azonositok=mit;
    uj->next=NULL;
    if(lista==NULL)
    {
        lista=uj;
    }
    else
    {
        ListofChars *mozgo=lista;
        ListofChars *lemarado=NULL;
        while(mozgo!=NULL)
        {
            lemarado=mozgo;
            mozgo=mozgo->next;
        }
        lemarado->next=uj;
    }
    return lista;
}
ListofChars *kimarad(Lista1Elem *Data, ListofChars *ki)
{

    Lista1Elem *mozgo=Data;
    while(mozgo!=NULL)
    {
        if(!mozgo->information)
        {
            ki= vegerefuz(ki, mozgo->person);
        }
        mozgo=mozgo->kovetkezo;
    }
    if(ki==NULL)
        return NULL;
    return ki;
}
ListofChars *seged(ListofChars *mibennincs, Lista1Elem *Data)
{
    ListofChars *uj=NULL;
    if(mibennincs!=NULL) {
        Lista1Elem *mozgo = Data;
        while (mozgo != NULL) {
            if (mozgo->information) {
                ListofChars *segedmozgo = mibennincs;
                bool vane = false;
                while (segedmozgo != NULL) {
                    if (segedmozgo->azonositok == mozgo->person) {
                        vane = true;
                    }
                    segedmozgo = segedmozgo->next;
                }
                if (!vane)
                    uj = vegerefuz(uj, mozgo->person);
            }
            mozgo = mozgo->kovetkezo;
        }
    }
    return uj;
}

void listafelszab_LoC(ListofChars *lista)
{
    if(lista!=NULL)
    {
        ListofChars *iter = lista;
        while (iter != NULL)
        {
            ListofChars *kovetkezo = iter->next;
            free(iter);
            iter = kovetkezo;
        }
    }

}

Lista1Elem *information (Lista1Elem *Data)
{
    printf("Valami leiras mert miert ne\n");
    printf("Ki az informacio forrasa? (adj meg egy azonositot-azonosito\\n formaban)\n");
    Data=bool_initializer(Data);
    char *who;
    //char c;
    //scanf("%c\n", &c);

    who=beolvasas_seged();
    char *realid = szamjegykivalaszto(who, 0);
    Lista1Elem *ki;
    ki = kereso(Data, realid);
    ki->information = true;
    ListofChars *Lista = (ListofChars*)malloc(sizeof(ListofChars));
    Lista->azonositok = ki->person;
    Lista->next = NULL;
    kiiras(Data);
    ListofChars *Akik_Nem=NULL;
    bool konstans=true;
    while(konstans)
    {
        Data=valtoztato(Data, Lista);
        Akik_Nem=kimarad(Data, Akik_Nem);
        kiiras(Data);
        ListofChars *segito;
        segito=seged(Lista, Data);
        listafelszab_LoC(Lista);
        Lista=segito;
        if(!ellenorzes(Data))
        {
            listafelszab_LoC(Akik_Nem);
        }
        if(ellenorzes(Data))
        {
            konstans=false;

        }

    }
    free(who);
    //free(ki);
    free(Lista);
    free(realid);
    printf("\n Kiserlet vege.\n");
    return Data;
}