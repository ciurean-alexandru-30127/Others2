/*Se da un graf orientat cu n noduri, si m muchii, fara costuri citit prin
vectorul muchiilor din fisierul "GRAF.TXT".Fisierul contine pe prima linie numarul
de noduri urmat de numarul de muchii,iar pe fiecare din liniile urmatoare va
contine o pereche de numere ce reprezinta un arc prin varful de unde pleaca arcul
si varful unde ajunge arcul. Trebuie sa folosim algoritmul de explorare
in largime pt a verifica daca graful este conex sau nu. Datele de iesire vor fi
afisate pe ecran . In Programul principal vom citi datele de intrare si apoi va apela modulul
traversarii in largime.Cu ajutorul parcurgerii in largime vom putea stabili daca graful este conex , si vom afisa in acest caz un mesaj corespunzator. */
#include <stdio.h>
#include <stdlib.h>
typedef struct nod
{
    int cheie;
    struct nod *urm;
} NOD;




 int *vizitate;
void adauga( NOD **prim, NOD **ultim,int cheie)
{

    NOD *p = (NOD*)malloc(sizeof(NOD));
    p->cheie = cheie;
    p->urm = 0;
    if (*prim==0)
    {
        *prim = *ultim = p;
    }
    else
    {
        p = (*prim);
        (*prim)= p;
    }
}
int sterge(NOD **prim, NOD **ultim)
{
    /* sterge primul nod din lista */
    NOD *p;
    int cheie=0;
    if(*prim!=0)
    {
        p=*prim;
        *prim=(*prim)->urm;
        cheie = p->cheie;
        if(*prim==0)
        {
            *ultim=0;
        }
        free(p);
    }
    return cheie;
}
int ** citire(int *n,char * nume)
{
    int **a;
    FILE *f=fopen (nume,"r");
    if(f == NULL)

    {
        printf("NU s-a deschis fisierul %s...",nume);
        exit(1);
    }
    int i,j;
    fscanf(f,"%d",n);
    a = (int **)malloc((*n+1)*sizeof(int));
    for(i=1; i<=*n; i++)
    {
        *(a+i) = (int *)malloc((*n+1)*sizeof(int));
        for(j=1; j<=*n; j++)
        {
            a[i][j] = 0;
        }
    }
    while(!feof(f))
    {
        i = j = 0;
        fscanf(f,"%d%d", &i, &j);
        if(i>0 && i<=*n && j>0 && j<=*n)
        {
            a[i][j] = 1;
        }
    }
    fclose(f);
    return a;
}

void adauga_l( NOD **prim, NOD **ultim,int cheie)
{
    NOD *p = (NOD*)malloc(sizeof(NOD));
    p->cheie = cheie;
    p->urm = 0;
    if (*prim==0)
    {
        *prim = *ultim = p;
    }
    else
    {
        (*ultim)->urm = p;
        *ultim = p;
    }
}
void explorare_largime(int **a, int n, int s)
{
    /* s = nod de plecare */
    vizitate = (int *)malloc((n+1)*sizeof(int));
    NOD *prim = 0, *ultim = 0;
    int i, v, w;
    for (i=1; i<=n; i++)
    {


        vizitate[i] = 0;
    }
    adauga(&prim, &ultim, s);
    vizitate[s] = 1;
    printf("Explorarea în largime din nodul %d este:\n", s);
    while (prim)
    {
        v = sterge(&prim, &ultim);
        for (i=1; i<=n; i++)
        {
            if(a[v][i]==1 && (vizitate[i]==0))
            {
                w = i;
                adauga_l(&prim, &ultim, w);
                vizitate[w] = 1;
                printf("%d ", w);
            }
        }
    }
    printf("\n------------\n");
    free(vizitate);
}
int vizita(int n, int *vizitate)
{
    int i;
    for(i=1;i<=n;i++)
    {
        if(vizitate[i]==0)
        {
            return 0;
        }
    }
    return 1;
}
int main()
{int n, **g1 = citire(&n,"GRAF.txt");
    explorare_largime(g1,n,1);
   if(vizita(n,vizitate)==1)
   {
       printf("Este conex");
   }
   else
   {
       printf("Nu este conex");
   }
    return 0;
}
