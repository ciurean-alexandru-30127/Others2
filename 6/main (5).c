#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct bin
{
    int ch;
    struct bin *st, *dr;
}BINAR;
BINAR *construire()
{
    BINAR *p = NULL;
    int c;
    scanf("%d", &c);
    if(c!=0)
    {
        p=(BINAR *)malloc(sizeof(BINAR));
        /* introducere de informație în nod */
        p->ch = c;
        p->st = construire();
        p->dr = construire();
    }
    return p;
}
BINAR *construire_echilibrat(int nr_noduri)
{
    BINAR *p = NULL;
    int n_stg, n_dr;
    if(nr_noduri != 0)
    {
        n_stg = nr_noduri/2; /* numărul nodurilor din subarborele stâng */
        n_dr = nr_noduri - n_stg - 1; /* ~ drept */
        p = (BINAR *)malloc(sizeof(BINAR));
        printf("\nIntroduceti informatia din nod in preordine ");
        scanf("%d", &(p->ch));
        p->st = construire_echilibrat(n_stg);
        p->dr = construire_echilibrat(n_dr);
    }
    return p;
}
void preordine(BINAR *p, int nivel)
{
    int i;
    if (p != 0)
    {
        /*tipărire spații variabile funcție de nivel, pentru indentare*/
        for(i = 0; i < nivel; i++)
            printf("    ");
        printf("%d\n", p->ch); /*prelucrare nod curent*/
        preordine(p->st, nivel+1);
        preordine(p->dr, nivel+1);
    }
}
int main()
{
    int o;
    BINAR *radacina;
        printf("1 Arbore binar 2 Arbore binar echilibrat ");
        scanf("%d",&o);
        switch(o)
        {
        case 1:
        {
            radacina = construire();
            preordine(radacina, 0);
            break;
        }
        case 2:
        {
            int n;
            printf("Numar de noduri: ");
            scanf("%d",&n);
            radacina = construire_echilibrat(n);
            preordine(radacina, 0);
            break;
        }
        default:
        {
            printf("Optiune gresita!");
            break;
        }

    }
    return 0;
}
