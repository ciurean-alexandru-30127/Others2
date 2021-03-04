# include <stdlib.h>
# include <stdio.h>
# include <string.h>
typedef struct locomotiva
{
    int Id;
    char *Tip;
    float Greutate;
    struct locomotiva *urm;
} LOCOMOTIVA;
typedef struct
{
    LOCOMOTIVA *prim, *ultim, *crt;
    int dimensiune;
} DEPOU;
void Intrare(DEPOU *d);
void Iesire(DEPOU *d);
void Afisare(DEPOU *d);
void Populare(DEPOU **d);
void Salvare(DEPOU *d);
int main()
{
    int optiune;
    DEPOU *d;
    Populare(&d);
    while(1)
    {
        printf("1 Intrare, 2 Iesire, 3 Afisare, 4 Terminare ");
        scanf("%d", &optiune);
        switch(optiune)
        {
        case 1:
        {
            Intrare(d);
            break;
        }
        case 2:
        {
            Iesire(d);
            break;
        }
        case 3:
        {
            if(d->dimensiune == 0)
            {
                printf("Depoul este gol...\n");
            }
            else
            {
                Afisare(d);
            }
            break;
        }
        case 4:
        {
            printf("La revedere...");
            Salvare(d);
            return 0;
        }
        default:
        {
            printf("Optiune gresită...");
            break;
        }
        }
    }
    return 0;
}
void Intrare(DEPOU *d)
{
    char buf[100];
    d->crt = (LOCOMOTIVA *)malloc(sizeof(LOCOMOTIVA));
    /* citire date în nodul de adresă d->crt */
    printf("Introduceti Id = ");
    scanf("%d", &(d->crt->Id));
    printf("Introduceti Tip = ");
    scanf("%s", buf);
    d->crt->Tip = (char*)malloc((strlen(buf)+1)*sizeof(char));
    strcpy(d->crt->Tip, buf);
    printf("Introduceti Greutate = ");
    scanf("%f", &(d->crt->Greutate));
    d->dimensiune++;
    d->crt->urm = 0;
    if (d->prim == NULL)
    {

        d->prim = d->ultim = d->crt;
    }
    else
    {
        /* se inserează înainte de primul nod */
        d->ultim->urm = d->crt;
        d->ultim=d->crt;

    }
}
void Iesire(DEPOU *d)
{
    if(d->prim != NULL)
    {
        d->crt = d->prim;
        printf("Locomotiva care iese are urmatoarele detalii: Id = %d Tip = %s Greutate= %f\n", d->crt->Id, d->crt->Tip, d->crt->Greutate);
        d->prim = d->prim->urm;
        free(d->crt->Tip); /* eliberarea spațiului de memorie pentru șirul de caractere alocat dinamic */
        free(d->crt); /* eliberarea spațiului de memorie */
        d->dimensiune--;
        if(d->prim == NULL)
        {
            d->ultim = NULL; /* lista a devenit vidă */


        }
    }
    else
    {
        printf("Depoul este gol\n");
    }
}
void Afisare(DEPOU *d)
{
    int i = 0;
    d->crt = d->prim;
    while(d->crt)
    {
        i++;
        printf("Locomotiva %d are urmatoarele detalii: Id = %d Tip = %s Greutate =%f\n", i, d->crt->Id, d->crt->Tip, d->crt->Greutate);
        d->crt = d->crt->urm;
    }
}
void Populare(DEPOU **d)
{
    *d = (DEPOU*)malloc(sizeof(DEPOU*));
    (*d)->prim = (*d)->ultim = NULL;
    (*d)->dimensiune = 0;
    FILE *f = fopen("depou.txt", "r");
    if(!f)
        return;
    char buf[100];
    int id;
    float greutate;
    while(fscanf(f,"%d %s %f",&id,buf,&greutate)!=EOF)
    {
        (*d)->crt = (LOCOMOTIVA *)malloc(sizeof(LOCOMOTIVA));

        (*d)->crt->Id=id;
        (*d)->crt->Tip = (char*)malloc((strlen(buf)+1)*sizeof(char));
        strcpy((*d)->crt->Tip, buf);
        (*d)->crt->Greutate=greutate;
        (*d)->dimensiune++;
        (*d)->crt->urm = 0;
        if ((*d)->prim == NULL)
        {
            (*d)->prim = (*d)->ultim = (*d)->crt;
        }
        else
        {
            /* se adaugă după ultimul nod */
            (*d)->ultim->urm = (*d)->crt;
            (*d)->ultim = (*d)->crt;
        }
    }
    fclose(f);
}
void Salvare(DEPOU *d)
{
    FILE *f = fopen("depou.txt", "w");
    if(!f)
        return;
    d->crt = d->prim;
    d->dimensiune--;
    while(d->crt)
    {

        fprintf(f, "%d %s %f\n", d->crt->Id, d->crt->Tip, d->crt->Greutate);
        d->crt = d->crt->urm;
    }
    fclose(f);
}
