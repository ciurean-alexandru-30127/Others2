#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct
{
    char *nume;
    int cantitate;
    double pret;
    char *data_primirii;
    char *data_expirarii;
} Medicament;

typedef struct nod
{
    Medicament *med;
    struct nod* predecesor,*urmator;

} Nod;

typedef struct
{
    Nod *primul, *ultimul,*curent;
    int dimensiune;

} Lista;

Medicament *Alocare_Med(char *nume,int cantitate,double pret,char *d_p,char *d_e)
{
    Medicament *med=(Medicament*)malloc(sizeof(Medicament));
    med->nume=(char*)malloc((strlen(nume)+1)*sizeof(char));
    med->data_expirarii=(char*)malloc((strlen(d_e)+1)*sizeof(char));
    med->data_primirii=(char*)malloc((strlen(d_p)+1)*sizeof(char));
    strcpy(med->nume,nume);
    strcpy(med->data_expirarii,d_e);
    strcpy(med->data_primirii,d_p);
    med->pret=pret;
    med->cantitate=cantitate;

    return med;
}
Lista* Alocare_Lista()
{
    Lista *l=(Lista*)malloc(sizeof(Lista));
    l->primul=l->ultimul=NULL;
    return l;
}

Nod *Alocare_nod(Medicament *med)
{
    Nod *nod=(Nod*)malloc(sizeof(Nod));
    nod->predecesor=nod->urmator=NULL;
    nod->med=med;
    return nod;

}
void Cautare(Lista *l,Nod *nod)
{
    int r;
    l->curent=l->primul;
    while(l->curent)
    {
        r=strcmp(nod->med->nume,l->curent->med->nume);
        if(r==0)
        {
            if(nod->med->pret>l->curent->med->pret)
            {
                return;
            }
            else
            {
                l->curent=l->curent->urmator;
            }
        }else
        if(r<0)
        {
            return;
        }
        else
        {
            l->curent=l->curent->urmator;

        }
    }

}

void Adauga_ultimul(Lista *l,Nod *nod)
{


    l->dimensiune++;
    if(l->primul==NULL)
    {

        l->primul=l->ultimul=nod;

    }
    else
    {
        nod->predecesor=l->ultimul;
        l->ultimul->urmator=nod;
        l->ultimul=nod;
    }

}

void Adauga_primul(Lista *l,Nod *nod)
{
    l->dimensiune++;
    nod->urmator=l->primul;
    if(l->primul==NULL)
    {
        l->primul=l->ultimul=nod;

    }
    else
    {
        l->primul->predecesor=nod;

        l->primul=nod;

    }


}

void Afisare(Lista *m)
{
    if(m->primul!=NULL)
    {

        m->curent=m->primul;
        while(m->curent)
        {
            printf("Nume= %s pret= %lf  cantitate=%d Data_e=%s Data_p=%s\n",m->curent->med->nume,m->curent->med->pret,m->curent->med->cantitate,m->curent->med->data_expirarii,m->curent->med->data_primirii);

            m->curent=m->curent->urmator;

        }
    }
    else
    {
        printf("Lista este goala\n");
    }
}


void Inserare_nod(Lista *m,Nod *nod)
{
    m->dimensiune++;
    nod->predecesor=m->curent->predecesor;
    nod->urmator=m->curent;
    if(m->curent->predecesor!=0)
    {
        m->curent->predecesor->urmator=nod;

    }
    m->curent->predecesor=nod;

    if(m->curent==m->primul)
    {
        m->primul=nod;
    }

}
void Creare(Lista *m)
{
    Nod *nod=NULL;
    Medicament *med=NULL;
    char nume[100],d_e[100],d_p[100];
    printf("Nume medicament: ");
    fflush(stdin);
    gets(nume);
    printf("Pret medicament: ");
    double pret;
    scanf("%lf",&pret);
    printf("Catitate medicament: ");
    int cantitate;
    scanf("%d",&cantitate);
    printf("Data primirii medicament: ");
    scanf("%s",d_p);
    printf("Data expirarii medicament: ");
    scanf("%s",d_e);
    med=Alocare_Med(nume,cantitate,pret,d_p,d_e);
    nod=Alocare_nod(med);

    if(m->primul==NULL)
    {
        Adauga_ultimul(m,nod);
    }
    else
    {
        Cautare(m,nod);
        if(m->curent!=NULL)
        {
            Inserare_nod(m,nod);
        }
        else
        {
            Adauga_ultimul(m,nod);

        }
    }
}

void Stocare(Lista *m)
{
    m->curent=m->primul;
    FILE *f=fopen("medicamente.out","w");
    if(f==NULL)
    {
        printf("Fisierul nu se deschide!!\n");
        exit(1);
    }

    while(m->curent!=NULL)
    {

         if(m->curent->urmator!=NULL)
         {
             fprintf(f,"%s,%fl,%d,%s,%s\n",m->curent->med->nume,m->curent->med->pret,m->curent->med->cantitate,m->curent->med->data_primirii,m->curent->med->data_expirarii);
          }else
          {

                 fprintf(f,"%s,%fl,%d,%s,%s ",m->curent->med->nume,m->curent->med->pret,m->curent->med->cantitate,m->curent->med->data_primirii,m->curent->med->data_expirarii);
          }
         m->curent=m->curent->urmator;
    }
    fclose(f);
}

void Populare(Lista **m)
{
    FILE *f=fopen("medicamente.txt","r");

    if(f==NULL)
    {
        printf("Nu se poate deschide fisierul!!!\n");
        return;
    }
    char sir[500];
    while(!feof(f))
    {
        if(fgets(sir,500,f)!=NULL)
        {

            Medicament *med=NULL;
            char *nume=strtok(sir,",");
            char *pret=strtok(NULL,",");  //Am pus NULL intentionat acolo
            char *cantitate=strtok(NULL,",");
            char *d_p=strtok(NULL,",");
            char *d_e=strtok(NULL,",");

            d_e[strlen(d_e)-1]='\0';
            med=Alocare_Med(nume,atoi(cantitate),atof(pret),d_p,d_e);
            Nod *nod=Alocare_nod(med);
               if((*m)->primul==NULL)
    {
        Adauga_ultimul((*m),nod);
    }
    else
    {
        Cautare((*m),nod);
        if((*m)->curent!=NULL)
        {
            Inserare_nod((*m),nod);
        }
        else
        {
            Adauga_ultimul((*m),nod);

        }
    }
        }
    }

}

void Modificare_Med(Lista *l)
{
    printf("Introdu numele medicamentului: ");
    char med[100];
    fflush(stdin);
    gets(med);
    printf("Introdu pretul medicamentului: ");
    double pret;
    scanf("%lf",&pret);

    l->curent=l->primul;

    while(l->curent!=NULL)
    {

        if((strcmp(l->curent->med->nume,med)==0)&&l->curent->med->pret==pret)
        {
            printf("introdu noua valoare pentru cantitate: ");
            scanf("%d",&l->curent->med->cantitate);
            char d_p[100];
            char d_e[100];
            printf("Introdu noua data de primire: ");
            scanf("%s",d_p);
            printf("Introdu noua data de exprirare: ");
            scanf("%s",d_e);
            realloc(l->curent->med->data_primirii,(strlen(d_p)+1)*sizeof(char));
            realloc( l->curent->med->data_expirarii,(strlen(d_e)+1)*sizeof(char));

            strcpy(l->curent->med->data_primirii,d_p);
            strcpy(l->curent->med->data_expirarii,d_e);

        }
        l->curent=l->curent->urmator;

    }

}


void Stergere_nod(Lista *l)
{
    printf("Introdu numele medicamentului : ");
    char med[100];
    fflush(stdin);
    gets(med);
    printf("Introdu pretul medicamentului: ");
    double pret;
    scanf("%lf",&pret);

    l->curent =l->primul;
    while(l->curent!=NULL)
    {
        if((strcmp(l->curent->med->nume,med)==0)&&l->curent->med->pret==pret)
        {
           if((l->primul==l->curent)&&(l->ultimul==l->curent))
           {
               l->primul=l->ultimul=NULL;
               free(l->curent);
           }else
           {
              if(l->primul==l->curent)
              {
                  l->primul=l->primul->urmator;
                  l->primul->predecesor=NULL;
                  free(l->curent);

              }else
              {
                 if(l->ultimul==l->curent)
                 {
                     l->ultimul=l->ultimul->predecesor;
                     l->ultimul->urmator=NULL;
                     free(l->curent);

                 }
                 else
                 {
                     l->curent->urmator=l->curent->predecesor;
                     l->curent->predecesor->urmator=l->curent->urmator;
                     free(l->curent);
                 }
              }

           }
        }


       l->curent=l->curent->urmator;

    }

}
int main()
{
    Lista *m=NULL;
    m=Alocare_Lista();
    Populare(&m);
    int optiune;
    while(1)
    {
        printf(" 1:Adauga medicament  2:Afiseaza lista  3:Actualizeaza medicamentul  4:Iesire  5:Elimina medicament\n");
        printf("introdu optiunea: ");
        scanf("%d",&optiune);
        switch(optiune)
        {
        case 1:
        {
            Creare(m);
            break;
        };
        case 2:
        {
            Afisare(m);
            break;

        }
        case 3:
        {
            Modificare_Med(m);
            break;
        }
        case 4:
        {
            Stocare(m);
            printf("La revedere!!\n");
            return 0;
            break;
        }
        case 5:
            {
                Stergere_nod(m);
                break;
            }
        default:
        {
            printf("Introdu optiunea din nou! Ai ales optiune  gresita!!\n");
            break;
        }

        }
    }

    return 0;
}
