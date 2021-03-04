#include <stdio.h>
#include <stdlib.h>
# define NMAX 100

typedef struct locomotiva
{
    int Id;
    char Tip[21];
    float Greutate;
} LOCOMOTIVA;
int main()
{
    int varf = 0, optiune;
    LOCOMOTIVA DEPOU[NMAX];
    while (1)
    {
        printf("1 Intrare, 2 Iesire, 3 Afisare, 4 Terminare"); //afisare meniu cu optiunile :1 Intrare , 2 Iesire , 3 Afisare , 4 Terminare
       scanf("%d", &optiune);
        switch (optiune)
        {
        case 1:
        {
            if (varf == NMAX)
            {
                printf("Depoul este plin...\n");
            }
            else               // adauga locomotiva
            {
                printf("Introduceti Id = ");
                scanf("%d", &DEPOU[varf].Id);
                printf("Introduceti Tip = ");
                scanf("%s", DEPOU[varf].Tip);
                printf("Introduceti Greutate = ");
                scanf("%f", &DEPOU[varf].Greutate);
                varf++;
            }
            break;
        }
        case 2:
        {
            // modulul Ieșire;
            if (varf == 0)    //verificare daca depoul este gol si in caz afirmativ afiseaza mesaj corespunzator
            {
                printf("Depoul este gol...\n");
            }
            else         //afiseaza pe ecran detaliile pentru prima locomotiva
            {
                int i;

                printf("Locomotiva care iese are urmatoarele detalii : Id = % d Tip = % s Greutate = % f\n", DEPOU[0].Id, DEPOU[0].Tip, DEPOU[0].Greutate);
                for (i = 0; i < varf-1; i++)
                {
                    DEPOU[i].Greutate = DEPOU[i + 1].Greutate;
                    DEPOU[i].Id = DEPOU[i + 1].Id;
                    strcpy(DEPOU[i].Tip , DEPOU[i + 1].Tip);
                }
                varf--;
            }
            break;
        }
        case 3:
        {
            // modulul Afișare;
            if (varf == 0)
            {
                printf("Depoul este gol...\n");
            }
            else
            {
                int i;
                for (i = varf - 1; i >= 0; i--)
                {
                    printf("Locomotiva %d are urmatoarele detalii : Id = % d Tip = % s Greutate = % f\n", i + 1, DEPOU[i].Id, DEPOU[i].Tip, DEPOU[i].Greutate);   //afiseaza pe ecran detaliile pentru elementul curent din colectia DEPOU
                }
            }
            break;
        }
        case 4:
        {
            printf("La revedere...");
            return 0;
        }
        default:
        {
            printf("Optiune gresita...");
            break;
        }
        }
    }
}
