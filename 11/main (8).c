#include <stdio.h>
#include <stdlib.h>
#include  <string.h>
#define M 32

typedef struct
{
    char *nume;
    char *prenume;
    int media;
} Date;


typedef struct tip_nod
{
    Date *date;
    struct tip_nod *urm;
} Tip_nod;
Tip_nod *HT[M];

int f_d(char *cheie)
{
    int i,suma;
    suma=0;
    for(i=0; i<strlen(cheie); i++)
        suma+=*(cheie+1);
    return suma & (M-1);
}

Date *aloca_date(char *nume,char *prenume,int media)
{
    Date *date=(Date*)malloc(sizeof(Date));
    date->nume=(char*)malloc((strlen(nume)+1)*sizeof(char));
    date->prenume=(char*)malloc((strlen(prenume)+1)*sizeof(char));
    strcpy(date->nume,nume);
    strcpy(date->prenume,prenume);
    date->media=media;
    return date;
}
Tip_nod* cautare(char *nume,char *prenume)
{
    char *k=(char*)malloc((strlen(nume)+strlen(prenume)+1)*sizeof(char));
    strcpy(k,nume);
    strcat(k,prenume);
    int h=f_d(k);
    Tip_nod * p=HT[h];
    while(p)
    {
        if(strcmp(nume,p->date->nume)==0 && strcmp(prenume,p->date->prenume)==0)
            return p;
        p=p->urm;
    }
    return 0;
}

void citire()
{
    FILE *f=fopen("date.txt","r");
    if(!f)
    {
        exit(1);
    }
    int i;
    for(i=0; i<M; i++)
        HT[i]=0;
    char sir[500];

    while(!feof(f))
    {
        if(fgets(sir,500,f)!=NULL)
        {
            char *nume=strtok(sir,",");
            char *prenume=strtok(NULL,",");
            int media=atoi(strtok(NULL,","));
            Date *date=aloca_date(nume,prenume,media);

            Tip_nod *  p=(Tip_nod*)malloc(sizeof(Tip_nod));
            p->date=date;
            char *k=(char*)malloc((strlen(nume)+strlen(prenume)+1)*sizeof(char));
            strcpy(k,p->date->nume);
            strcat(k,p->date->prenume);
            int h=f_d(k);
            if(HT[h]==0)
            {
                HT[h]=p;
                p->urm=0;
            }
            else
            {
                p->urm=HT[h];
                HT[h]=p;

            }

        }
    }

}

void Afisare()
{
    int i;
    for(i=0; i<M; i++)
    {
        if(HT[i]!=0)
        {
            Tip_nod*  p=HT[i];
            while(p!=0)
            {
                printf("Nume: %s Prenume: %s Medie: %d \n",p->date->nume,p->date->prenume,p->date->media);
                p=p->urm;
            }

        }

    }

}

void inserare()
{
    Tip_nod * p=(Tip_nod*)malloc(sizeof(Tip_nod));
    char nume[100],prenume[100];
    int media;
    printf("Se introduce Elevul!!!\n\n");
    printf("Nume: ");
    scanf("%s",nume);
    printf("Prenume: ");
    scanf("%s",prenume);
    printf("Media: ");
    scanf("%d",&media);
    Date *date=aloca_date(nume,prenume,media);
    p->date=date;
    char *k=(char*)malloc((strlen(nume)+strlen(prenume)+1)*sizeof(char));
    strcpy(k,nume);
    strcat(k,prenume);

    int h=f_d(k);
    if(HT[h]==0)
    {
        HT[h]=p;
        p->urm=0;
    }
    else
    {
        p->urm=HT[h];
        HT[h]=p;

    }

}


void Modifica()
{
    char nume[50],prenume[50];
    printf("Nume: ");
    scanf("%s",nume);
    printf("Prenume: ");
    scanf("%s",prenume);
    char *k=(char*)malloc((strlen(nume)+strlen(prenume)+1)*sizeof(char));
    strcpy(k,nume);
    strcat(k,prenume);

    int h=f_d(k);
    Tip_nod * p=HT[h];
    while(p)
    {
        if(strcmp(nume,p->date->nume)==0 && strcmp(prenume,p->date->prenume)==0)
        {
            int med;
            printf("Introduce noua medie: ");
            scanf("%d",&med);
            p->date->media=med;
            break;
        }
        p=p->urm;
    }

    if(p==0)
    {
        printf("Nu se regaseste Elevul in tabel");
    }
}

void Sterge()
{
    char nume[50],prenume[50];
    printf("Nume: ");
    scanf("%s",nume);
    printf("Prenume: ");
    scanf("%s",prenume);
    char *k=(char*)malloc((strlen(nume)+strlen(prenume)+1)*sizeof(char));
    strcpy(k,nume);
    strcat(k,prenume);

    int h=f_d(k);
    Tip_nod * p=HT[h];

    while(p)
    {
        if(strcmp(nume,p->date->nume)==0 && strcmp(prenume,p->date->prenume)==0)
        {

            free(p);
            HT[h]=0;
                        break;
        }

        p=p->urm;
    }

    if(p==0)
    {
        printf("Nu se regaseste Elevul in tabel");
    }
}


void Write_File()
{

    FILE *f=fopen("date.txt","w");
    if(!f)
    {
        exit(1);
    }


    int i;
    for(i=0; i<M; i++)
    {
        if(HT[i]!=0)
        {
            Tip_nod*  p=HT[i];
            while(p!=0)
            {
                fprintf(f,"%s,%s,%d \n",p->date->nume,p->date->prenume,p->date->media);
                p=p->urm;
            }

        }

    }

}

int main()
{
    int optiune;
    citire();
    while(1)
    {
        printf("Optiunii: \n 1 Adauga \n 2 Modifica \n 3 Sterge \n 4 Afisare \n 5. Exit ");
        scanf("%d",&optiune);

        switch(optiune)
        {

        case 1:
        {
            inserare();
            break;
        }
        case 2:
        {
            Modifica();
            break;
        }
        case 3:
        {
            Sterge();
            break;
        }
        case 4:
        {
            //Afisare
            Afisare();
            break;
        }
        case 5:
        {
            Write_File();
            return 0;
            break;
        }
        default:
        {

            break;
        }
        }
    }
    return 0;
}
