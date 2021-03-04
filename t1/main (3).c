#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//Input: Se citesc dintr-un fisier id,nume,tip,data verificare.
//Output: Se afiseaza lista care a fost citita precedent, ordonata crescator dupa gama_croaziera, iar pentru aceeasi gama se va afisa crescator dupa nume.

typedef struct
{
    int id;
    char nume[11];
    int gama_croaziera;
    int tip;
    char data_verificare;
} DATE;

typedef struct nod
{
    DATE *date;
    struct nod *prec,*urm;
}  NOD;

typedef struct
{
    NOD *prim,*ultim,*crt;
} LISTA;

void init_Lista(LISTA **l) //se aloca memorie si se initializeaza lista
{
    *l=(LISTA*)malloc(sizeof(LISTA));
    (*l)->prim=(*l)->ultim=0;
}

void inser_Nod(LISTA **l,char sir[])
{
    char *cuv=strtok(sir,",");
    int i=0;

    DATE *d=(DATE*)malloc(sizeof(DATE));

    while(cuv)
    {
        switch(i)
        {
        case 0:
            d->id=atoi(cuv);//int-atoi
            break;
        case 1:
            strcpy(d->nume,cuv);//char-strcpy
            break;
        case 2:
            d->gama_croaziera=atoi(cuv);
            break;

        case 3:
            d->tip=atoi(cuv);//
            break;
        case 4:
            strcpy(d->data_verificare,cuv);
            break;
        }
		i++;
        cuv=strtok(NULL,",");
    }

    NOD *n=(NOD*)malloc(sizeof(NOD));
    n->date=d;

    (*l)->crt=(*l)->prim;

    while((*l)->crt)
    {
        if(strcmp((*l)->crt->date->gama_croaziera,n->date->gama_croaziera)<0)//descrescator
            (*l)->crt=(*l)->crt->urm;
        else
        {
            if(strcmp((*l)->crt->date->gama_croaziera,n->date->gama_croaziera)==0)
                if((*l)->crt->date->nume<n->date->nume)//cresccator
                    (*l)->crt=(*l)->crt->urm;
                else
                    break;
            else
                break;
        }
    }

    if((*l)->crt==0)
    {
        //Caz 1: lista vida
        if((*l)->prim==0)
        {
            n->urm=0;
            n->prec=0;
            (*l)->prim=(*l)->ultim=n;

        }
        else
        {
            //Caz 2: inseram dupa ultimul nod
            (*l)->ultim->urm=n;
            n->prec=(*l)->ultim;
            n->urm=0;
            (*l)->ultim=n;
        }
    }
    else
    {
        if((*l)->crt==(*l)->prim) //Caz 3: inseram inainte de primul nod
        {
            (*l)->prim->prec=n;
            n->prec=0;
            n->urm=(*l)->prim;
            (*l)->prim=n;
        }
        else
        {
            //Caz 4: inseram intre 2 noduri
            (*l)->crt->prec->urm=n;
            n->prec=(*l)->crt->prec;
            n->urm=(*l)->crt;
            (*l)->crt->prec=n;
        }
    }


}

void Afisare(LISTA *l)
{
    l->crt=l->prim;
    while(l->crt)
    {
        printf("%d, %s, %d, %d, %s\n", l->crt->date->id,l->crt->date->nume,l->crt->date->gama_croaziera,l->crt->date->tip,l->crt->date->data_verificare);
        l->crt=l->crt->urm;
    }
}

int main()
{
    LISTA *l;
    init_Lista(&l);

    char sir[50];

    FILE *f=fopen("Avion.txt","r");

    if(!f) //Verificam daca fisierul dat exista
    {
        printf("Eroare"); //Daca nu, se iese din program
        exit(1);
    }
    else
    {
        while(!feof(f))
        {
            strcpy(sir,"NULL");
            fgets(sir,50,f);
            if(strcmp(sir,"NULL")!=0)
                inser_Nod(&l,sir);
        }
        Afisare(l);

    }

    return 0;
}
