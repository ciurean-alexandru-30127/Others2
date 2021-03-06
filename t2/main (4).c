/* Datele de intrare vor fi intr-un fisier text denumit: "AVION.TXT". Acestea vor fi inregistrari de forma: id(%s), nume(%s),TIP(%s), Gama_croaziera(%d), data_verificare(%s).
Datele vor fi citite din fisier si prin crearea unei structuri de date de tip arbore binar de cautare  se va afisa un meniu care sa permita : afisarea unei liste ordonata crescator dupa id
cu proiectele din colectie , cautarea unui avion dupa id si alt meniu cu stergerea unui avion .
Se va creea tipul de data Avion, ce va avea ca elemente date despre avion, tipul de data Nod ce va contine avionul si va face legatura catre avionul stang si drept,
 fiind astfel o structura de date de tip arbore binar.Vom folosi traversarea inordine pentru sortarea crescatoare .*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct
{
    char *ID,*nume,*tip;
    int Gama_croaziera;
    char *data_verificare;
} Avion;
typedef struct av
{
    Avion info; /**< cheia pentru fiecare nod */
    struct r *st,*dr;
} NOD;
Avion initAvion(char* buf)
{
    int i=0;
    char sep[]=",";
    char *result = strtok(buf,sep);
    Avion m;
    while(result != NULL) /**< se tratează fiecare componentă */
    {
        /** pentru o instanță, prima componentă este ID*/
        switch(i)
        {
        case 0:
        {
            m.ID = (char *)malloc((strlen(result)+1)*sizeof(char));
            strcpy(m.ID,result);
            break;
        }
        case 1:
        {
            m.nume = (char *)malloc((strlen(result)+1)*sizeof(char));
            strcpy(m.nume,result);
            break;
        }
        case 2:
        {
            m.tip = (char *)malloc((strlen(result)+1)*sizeof(char));
            strcpy(m.tip,result);
            break;
        }
        case 3:
        {
            m.Gama_croaziera=atoi(result); /** conversie sir caractere in număr intreg*/
            break;


        }

        case 4:
        {
            m.data_verificare= (char *)malloc((strlen(result)+1)*sizeof(char));
            strcpy(m.data_verificare,result);
            break;
        }
        }
        i++;
        result=strtok(NULL,sep);
    }
    return m; /**< returnam proiectul cu toate specificatiile */
}

NOD *inserareAvion(NOD* rad,Avion m)
{
    if(rad) /**< daca nodul exista */
    {
        int fan=strcmp(rad->info.ID,m.ID);/**< in ordine lexicografica */
        if(fan>0)
        {
            rad->st=inserareAvion(rad->st,m);/**< introducem pe ramura stanga noul nod */
        }
        else
        {
            rad->dr=inserareAvion(rad->dr,m);/**< introducem pe ramura dreapta noul nod */
        }
        return rad;
    }
    else    /**< daca nu exista nodul */
    {
        NOD* nou = (NOD*)malloc(sizeof(NOD));
        nou->info=m;
        nou->dr=nou->st=NULL;
        return nou;
    }
}
void afisare(Avion m)
{
    printf("ID = %s Nume = %s tip=%s Gama_croaziera = %d data_verificare %s", m.ID, m.nume, m.tip,m.Gama_croaziera,m.data_verificare);
}
void inordine(NOD *rad)/**< la traversarea Inordine a unui arbore binar de căutare cheile apar sortate crescător */
{
    if(rad)
    {
        inordine(rad->st);
        afisare(rad->info);
        inordine(rad->dr);
    }
}
void cautaNOD(NOD* rad,char m[100])
{
    /**< se parcurge arborele in ordine si se cauta nodul care are ca informatie utila
    ID-ul egal cu cel transmis prin parametru - daca se gaseste nodul, cautarea se opreste*/
    if(rad)
    {
        int fan=strcmp(rad->info.ID,m);
        if(fan==0)
        {
            afisare(rad->info);
            return rad;
        }
        else if(fan>0)
        {
            cautaNOD(rad->st,m);
        }
        else
        {
            cautaNOD(rad->dr,m);
        }
    }
}
NOD *stergere_nod(NOD *rad,char key[100])
{
    NOD *p,*tata_p;/* p este nodul de sters, iar tata_p este tatal lui */
    NOD *nod_inlocuire,*tata_nod_inlocuire;/*nodul care il va inlocui pe p si tatal sau */
    int directie; /*stg=1;dr=2*/
    if(rad==0)
        return 0; /*arborele este vid */
    p=rad;
    tata_p=0;
    /* cautare nod cu cheia key */
    while(p!=0 && strcmp(p->info.ID,key)!=0)
    {
        if (strcmp(p->info.ID,key)>0)      /*cautare in stanga */
        {
            tata_p=p;
            p=p->st;
            directie=1;
        }
        else      /*cautare in dreapta */
        {
            tata_p=p;
            p=p->dr;
            directie=2;
        }
    }
    if(p==0)
    {
        printf("NU EXISTA Avionul: %s\n",key);
        return rad;
    }
    /* s-a gasit nodul p de cheie key */
    if(p->st==0)
        nod_inlocuire=p->dr; /* nodul de sters p nu are fiu sting */
    else if(p->dr==0)
        nod_inlocuire=p->st;	/*nodul de sters p  nu are fiu drept*/
    else    /* nodul de sters p are fiu stang si fiu drept */
    {
        tata_nod_inlocuire=p;
        nod_inlocuire=p->dr;        /* se cauta in subarborele drept*/
        while(nod_inlocuire->st!=0)
        {
            tata_nod_inlocuire=nod_inlocuire;
            nod_inlocuire=nod_inlocuire->st;
        }
        if(tata_nod_inlocuire!=p)
        {
            tata_nod_inlocuire->st=nod_inlocuire->dr;
            nod_inlocuire->dr=p->dr;
        }
        nod_inlocuire->st=p->st;
    }
    free(p);
    printf("Avionul %s a fost sters!\n",key);
    if(tata_p==0)
        return nod_inlocuire; /*s-a sters chiar radacina initiala */
    else
    {
        if (directie==1)
            tata_p->st=nod_inlocuire;
        else
            tata_p->dr=nod_inlocuire;
        return rad;
    }
}
void sterge_arbore(NOD* rad)
{
    if(rad)
    {
        sterge_arbore(rad->st);
        sterge_arbore(rad->dr);
        free(rad);
    }
}
int main()
{
    int o;
    char buf[100];
    FILE* f = fopen("AVION.TXT","r");
    if(!f)
        return;
    NOD* rad = NULL;
    while(!feof(f))
    {
        buf[0]='\0';
        fflush(stdin);
        fgets(buf, 100, f);
        if(strlen(buf)>0) // validare date de intrare
            rad = inserareAvion(rad,initAvion(buf));/**< se insereaza cate un produs de pe fiecare linie din fisier */
    }
    fclose(f);
    while(1)
    {
        printf("1 Afisare crescator 2 Cautare dupa id 3 Sterge avion 4 Terminare proces: ");
        scanf("%d",&o);
        switch(o)
        {
        case 1:
        {
            inordine(rad);
            break;
        }
        case 2:
        {
            char m[100],buff;
            printf("Avion-ID: ");
            scanf("%c",&buff);
            gets(m);
            cautaNOD(rad,m);
            break;
        }
        case 3:
        {
            char med[100],buff;
            printf("Avion-ID: ");
            scanf("%c",&buff);
            gets(med);
            rad = stergere_nod(rad,med);
            break;
        }

        case 4:
        {
            printf("La revedere!");
            sterge_arbore(rad); /**< eliberare memorie */
            return 0;
        }
        default:
        {
            printf("Optiune gresita!\n");
            break;
        }
        }
    }
    return 0;
}
