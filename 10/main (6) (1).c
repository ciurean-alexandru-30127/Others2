#include <stdio.h>
#include <stdlib.h>
#define INFINIT 0x7fffffff
#define NMAX 100
float parent[NMAX][NMAX], A[NMAX][NMAX];
int ** citire(int *n)
{
    int **cost;
    FILE *f=fopen ("graf.txt","r");
    if(f == NULL)
    {
        printf("NU s-a deschis fisierul graf.txt...");
        exit(1);
    }
    int i, j, c;
    fscanf(f,"%d",n);
    cost = (int **)malloc((*n+1)*sizeof(int));
    for(i=1; i<=*n; i++)
    {
        *(cost+i) = (int *)malloc((*n+1)*sizeof(int));
        for(j=1; j<=*n; j++)
        {
            cost[i][j] = INFINIT;
        }
    }
    while(!feof(f))
    {
        i = j = 0;
        fscanf(f,"%d%d%d", &i, &j, &c);
        if(i>0 && i<=*n && j>0 && j<=*n)
        {
            cost[i][j] = c;
            cost[j][i] = c;
        }
    }
    fclose(f);
    return cost;
}
void afisare(int **cost, int n)
{
    int i, j;
    for(i=1; i<=n; i++)
    {
        for(j=1; j<=n; j++)
        {
            if(cost[i][j] != INFINIT)
            {
                printf("%3d ", cost[i][j]);
            }
            else
            {
                printf("INF ");
            }
        }
        printf("\n");
    }
}
void  FLOYD(int n)
{
    int i,j,k;
    for(i = 1; i <= n; i++)
        A[i][i]=0;
    for(k = 1; k <= n; k++) /* iteraţiile */
        for(i = 1; i <= n; i++) /* pentru toate liniile */
            for(j = 1; j <= n; j++) /* pentru toate coloanele */
                if(A[i][k] + A[k][j] < A[i][j])
                {
                    A[i][j] = A[i][k] + A[k][j];
                    parent[i][j]=parent[k][j];
                }
}
void cale(int s,int d)
{
    if(s==d)
    {
        printf(" %d",s);
        return 0;
    }
    cale(s,parent[s][d]);
    printf("-> %d",d);
}
int citire_nod(int n, char *mesaj)
{
    int nod;
    do
    {
        printf("Introduceti nodul de %s = ", mesaj);
        scanf("%d", &nod);
    }
    while(nod<=0 || nod>n);   /* nodul trebuie sa aiba valoarea intre 1 și n */
    return nod;
}
void afisare_distante(int n, int s)
{
    char raspuns[2];
    int i, j, d;
    do
    {
        d = citire_nod(n, "sosire");
        printf("Distanta intre nodul %d si nodul %d este %0.0f\n",
               s, d, A[s][d]);
        printf("Drumul intre noduri este urmatorul: ");

        cale(s, d);
        printf("\n");
        printf("Doriti sa continuati? [DA/NU]\n");
        scanf("%s", &raspuns);
    }
    while(raspuns[0]=='d' || raspuns[0]=='D');
    printf("La revedere!\n");
}
int main()
{
    int n, **cost = citire(&n);
    int i, j, k;
    for(i = 1; i <= n; i++)
        for(j = 1; j <= n; j++)
            A[i][j] = cost[i][j]; /* iniţializare A */
    for(i = 1; i <= n; i++)
        for(j = 1; j <= n; j++)
            parent[i][j] = i;
    for(i = 1; i <= n; i++)
        A[i][i]=0;
    afisare(cost,n);
    FLOYD(n);
    int s = citire_nod(n, "plecare");
    afisare_distante(n,s);
    return 0;
}
