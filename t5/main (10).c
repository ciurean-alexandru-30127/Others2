/*input:5 24 12 15 15 19
output:3 12 15 19
Vom determina un subsir ordonat strict crescator de lungime maxima.
Astfel am declarat un vector cu N elemente si un subsir al vectorului declarat care este tot un vector,\
Primul element din fisierul de intrare reprezinta numarul de elemente ale vectorului, pe linia a doua
se afla elementele vectorului declarat. Vom afisa in fisierul de iesire pe prima linie lungimea celui mai
lung subsir crescator al sirului, iar pe linia a doua se va afisa cel mai lung subsir crescator al vectorului.*/

#include <stdio.h>
#define N 100001
long pnivmax[N],sir[N],tata[N]  ;
int main ()
{long n,i,j,nmax;
 FILE *fin=fopen("intrare.txt","r");
 fscanf(fin,"%ld",&n)      ;
 for (i=1;i<=n;i++)
 {fscanf(fin,"%ld",&sir[i]);}
 pnivmax[1]=1;nmax=1;
 tata[1]=0 ;

 for (i=2;i<=n;i++)
 {for (j=nmax;j>=1;j--)
  {if(sir[pnivmax[j]]<sir[i])
   {tata[i]=pnivmax[j];
    pnivmax[j+1]=i;
    if(j+1>nmax)
    {nmax=j+1;}
    break;
   }
  }
  if(j==0)
  {pnivmax[1]=i;tata[i]=0;
  }
 }
 for (j=nmax,i=pnivmax[nmax];i;i=tata[i],j--)
 {pnivmax[j]=sir[i];}
 FILE *fout=fopen("iesire.txt","w");
 fprintf(fout,"%ld\n",nmax);
 for (i=1;i<=nmax;i++)
 {fprintf(fout,"%ld ",pnivmax[i]);
 }
 return 0;
}
