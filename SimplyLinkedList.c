#include <stdio.h>
#include <stdlib.h>

typedef int L_datentyp;

typedef struct l_knoten
{
    L_datentyp l_daten;
    struct l_knoten *next;
}L_knoten;

typedef struct liste
{
    L_knoten *anf;
    L_knoten *pos;
    L_knoten *pos_vorg;
}Liste;

void l_create(Liste *l)
{
    l->anf=NULL;
    l->pos=NULL;
    l->pos_vorg=NULL;
    printf("Liste wurde erzeugt\n");
}

int l_empty(Liste* l){return l->anf==NULL;}

void L_datentyp_eingeben(L_datentyp *e)
{
    printf("Geben sie Bitte die einzufuegende Ganzezahl ein:\t");
    scanf("%d", e);

}

//Element immer vor pos einfuegen
void l_insert(L_datentyp* e, Liste *l)
{
    L_knoten *neu = NULL;

    if( (neu = (L_knoten*)malloc(sizeof(L_knoten))) == NULL )
    {
        printf("Kein Speicher mehr verfuegbar!\n");
        return EXIT_FAILURE;
    }
    neu->l_daten = *e;//Element speichern
    neu->next = l->pos;//vor pos tun



    if(l->pos_vorg !=NULL)//wird ausgefuehrt ab dem zweiten Element
        l->pos_vorg->next=neu;//Ich verkette die Liste

    if(l->anf==l->pos)//Da ich immer vor pos einfügen, setze anf erneut falls ein Element eingefuegt ist wenn pos gerade an anfang der list steht
        l->anf = neu;

    l->pos_vorg = neu;//weil ich immer vor pos einfuege
}

L_datentyp l_delete_data(Liste *l, L_datentyp e)
{
    if(l_empty(l))//Ist liste leer?
    {
        printf("Liste ist gerade gerade leer, Es wird empfohlen i dann einzugeben");
        return -111;
    }

    printf("Element bitte eingeben:\t");//gewuenschtes Element eingeben
    scanf("%d", &e);

    L_datentyp d;
    int weiter = 1;
    if(l->anf!=l->pos)
        l_reset2(l);

    while(weiter&&l->pos!=NULL)
    {
        if(l->pos->l_daten!=e)
        {
            l->pos_vorg = l->pos;
            l->pos = l->pos->next;
        }
        else//Element gefunden
        {
            d = l_delete(l);//pos zeigt jetzt darauf, ich nutze l_delete aus
            weiter = 0;     //danach zeigt pos auf dem naechsten Element in der Liste
        }

        if(l->pos==NULL&&weiter)//Nict gefunden
        {
            printf("Element ist nicht in der Liste vorhanden\nDas ist die Liste, ein Element auswaehlen und eingeben wenn Sie es loeschen wollen\n");
            l_print(l);
            return -111;
        }
    }
    return d;//Mit d sehe ich ob e geloescht wurde
}

L_datentyp l_delete(Liste *l)
{
    //Ich loesche immer wo pos gerade zeigt
    L_datentyp e=0;
    if(l_empty(l))
    {
        printf("Liste ist gerade gerade leer, Es wird empfohlen i dann einzugeben");
        return -111;
    }
    else if(l->pos==NULL)
    {
        printf("Es kann gerade nicht geloescht werden, Es wird empfohlen s dann einzugeben");
        return -111;
    }

    if(l->pos==l->anf&&l->pos->next==NULL)//Nur ein Datum ist in der Liste gespeichert
    {
        e = l->pos->l_daten;
        free(l->pos);
        l->anf=NULL;
        l->pos=NULL;
        l->pos_vorg=NULL;
        printf("ACHTUNG: Liste ist jetzt LEER\n");
        return e;
    }

    L_knoten *a = l->pos;
    e = a->l_daten;
    printf("%d\n", e);
    if(l->anf==l->pos)//Es wird am Anfang geloescht
    {
        //next speichert die Adresse des naechsten Element und ist somit mit ihm verkettet
        //next=NULL besagt er ist nicht mit ihm verkettet
        l->anf = l->pos->next;//Ich gehe einen Schritt nach vorne biem Loeschen
        l->pos->next = NULL;//Geloeschtes Element aus der Liste entfernen
        l->pos = l->anf;

    }
    else if(l->pos->next==NULL)//Das letzte Element der Liste wird geloescht
    {
        l->pos = NULL;
        l->pos_vorg->next = l->pos;
    }
    else
    {
        l->pos = l->pos->next;//Einen Schritt nach vorne
        l->pos_vorg->next = l->pos;//Neu verketten
        l->pos_vorg->next->next=NULL;//Geloeschtes Element aus der Liste entfernen
    }

    free(a);//Speicherplatz des geloeschten Element freigeben
    return e;
}

void l_reset(Liste *l)
{
    if(l_empty(l))
    {
        printf("Liste ist gerade gerade leer, Es wird empfohlen i dann einzugeben");
        return;
    }

    if(l->pos==NULL)//pos Zeigt nicht auf der Liste, also er zeigt am Ende
    {
        l->pos_vorg->next = NULL;//Das letzte Element zeigt nicht mehr auf pos
    }
    l->pos = l->anf;
    l->pos_vorg = NULL;
    printf("Wurde erfolgreich reset\n");
}


void l_reset2(Liste *l)//wird nur vom write benutzt
{
    if(l->pos==NULL)//pos Zeigt nicht auf der Liste, also er zeigt am Ende
    {
        l->pos_vorg->next = NULL;//Das letzte Element zeigt nicht mehr auf pos
    }
    l->pos = l->anf;
    l->pos_vorg = NULL;

}

void l_advance(Liste *l)
{
    if(l_empty(l))
    {
        printf("Liste ist gerade gerade leer, Es wird empfohlen i dann einzugeben");
        return;
    }

    if(l->pos==NULL)
        printf("Wir sind schon am Ende, Reset wird empholen");
    else if(l->pos->next==NULL)
        printf("Wir sind schon auf das lezte Element, Reset wird empholen");
    else
    {
        l->pos_vorg = l->pos;
        l->pos = l->pos->next;
    }
}

L_datentyp l_out_of_list(Liste *l)
{
    return (l->pos==NULL);
}

void l_write(Liste *l)
{
    L_knoten *a = l->pos;//Aktuelle Position speichern
    L_knoten *b = l->pos_vorg;

    if(l->anf!=l->pos)
        l_reset2(l);

    int i=1;
    while(!l_out_of_list(l))
    {
        if(l->anf==l->pos)
        {
            printf("Das Erste Element der Liste: %d\n", l->pos->l_daten);
            i++;
        }
        else if(l->pos->next==NULL)
        {
            printf("Das lezte bzw %d. Element der Liste: %d\n", i, l->pos->l_daten);
            //return;
        }
        else
            printf("Das %d. Element der Liste: %d\n", i++, l->pos->l_daten);

        l->pos_vorg=l->pos;
        l->pos=l->pos->next;
    }

    l->pos = a;//Vorherige Position wieder geben
    l->pos_vorg = b;
}


void l_print(Liste *l)
{
    if(l_empty(l))
    {
        printf("Liste ist gerade gerade leer, Es wird empfohlen i dann einzugeben");
        return;
    }

    L_knoten *a = l->anf;
    printf("Liste:(");
    while(a->next!=NULL)
    {
        printf("%d ", a->l_daten);
        a = a->next;
    }
    printf("%d)\n", a->l_daten);
}

void l_show(Liste* l)
{
    if(l_empty(l))
    {
        printf("Liste ist gerade gerade leer, Es wird empfohlen i dann einzugeben");
        return;
    }
    else if(l->pos==NULL)
    {
        printf("Element ist gerade nicht definiert, Operationen wie reset wird empfohlen\n");
        return;
    }

    printf("Aktuelles Element: %d\n", l->pos->l_daten);

}



int main()
{
    Liste l;
    L_datentyp e=0;
    int weiter=1, erzeugt=0;
    char c;

    printf("Umgeben mit einfacher Liste:\n\n");
    while(weiter)
    {
        printf("c [create] Liste erzeugen\n");
        printf("i [insert] Element einfuegen\n");
        printf("s [show] Das aktuelle Element ansehen\n");
        printf("d [delete] Element entfernen\n");
        printf("e [delete this data] dieses Element entfernen\n");
        printf("p [print] liste ausgeben\n");
        printf("r [reset] pos-Zeiger\n");
        printf("a [advance] pos-Zeiger\n");
        printf("q [quit] Programm verlassen\n\n");

        c = getchar();
        if(erzeugt==0&&c!='q')
        {
            if(c!='c')
            {
                c='x';
            }
            else
                erzeugt = 1;
        }

        switch(c)
        {
        case 'x':
            printf("Sie muessen entweder c, um die Liste zu erzeugen, oder q zum Beeden, als erste Eingabe. Danke\n");
            break;
        case 'c':
            if(erzeugt==1)
            {
                l_create(&l);
                erzeugt=2;
            }
            else if(erzeugt==2)
            {
                printf("Liste wurde schon erzeugt und ");
                if(l.anf==NULL)
                    printf("ist noch leer, mit i koennen Sie Element hinzufuegen.");
                else
                {
                    printf("sieht so aus:\n\t");
                    l_print(&l);
                }
            }
            break;
        case 'i':
            L_datentyp_eingeben(&e);
            l_insert(&e,&l);
            break;
        case 's':
            l_show(&l);
            break;
        case 'd':
            e=l_delete(&l);
            if(e!=-111)
                printf("Gerade eben wurde %d geloescht\n",e);
            break;
        case 'e':
            e=l_delete_data(&l, e);
            if(e!=-111)
                printf("Gerade eben wurde die gewuenschte data %d geloescht\n",e);
            break;
        case 'p':
            l_print(&l);
            break;
        case 'r':
            l_reset(&l);
            break;
        case 'a':
            l_advance(&l);
            break;
        case 'q':
            if(erzeugt&&l.anf!=NULL)
                l_print(&l);
            weiter = 0;
            break;
        default:
            printf("Eingabe nicht definiert, Wiederholen Bitte\n");
            break;
        }
        if(c=='i')
        {
            l_write(&l);

        }
        getchar();
        printf("\n\n");
    }

    return 0;
}
