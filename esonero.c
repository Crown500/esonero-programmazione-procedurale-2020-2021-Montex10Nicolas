#include <stdio.h>
#include <time.h>
#include <string.h>
#include <stdlib.h>

void pulisci_input(void);

int main(void)
{
    // Prendo la stringa dall'utente
    const short DIMENSIONE = 128;
    char plaintext[DIMENSIONE];
    printf("Inserisci una stringa da cifrare (NON piu di %d caratteri)\n", DIMENSIONE);
    fgets(plaintext, DIMENSIONE, stdin);
    pulisci_input();

    // Faccio scegliere come decidere la key
    int scelta = 0;
    do
    {
        printf("Puoi scegliere tra:\n");
        printf("\t1) Inserire una stringa da utilizzare come chiave\n");
        printf("\t2) Generare casualmente una chiave\n");
        printf("Fai la tua scelta: ");
        scanf("%d", &scelta);
        pulisci_input();
    } while (scelta < 1 || scelta > 2);

    // Inizializzo tutti i valori che mi serviranno
    char key[DIMENSIONE];
    char criptata[DIMENSIONE];
    char plainCalcolata[DIMENSIONE];
    time_t t;
    srand((unsigned)time(&t));

    // Controllo come ha deciso di proseguire e genero/faccio inserire la key
    if (scelta == 1)
    {
        do
        {
            printf("Inserisci una stringa da usare come chiave lunga almeno %lx caratteri\n", strlen(plaintext));
            fgets(key, 128, stdin);
        } while (strlen(key) < strlen(plaintext));
    }

    else if (scelta == 2)
    {
        for (int i = 0; i < strlen(plaintext); i++)
        {
            key[i] = rand() % 128;
        }
    }
    else
    {
        return 1;
    }

    // La stringa viene cifrata
    for (int i = 0; i < strlen(key); i++)
    {
        criptata[i] = (char)(plaintext[i] ^ key[i]);
    }

    // La stringa viene decifrata
    for (int i = 0; i < strlen(key); i++)
    {
        plainCalcolata[i] = (char)(key[i] ^ criptata[i]);
    }

    printf("Plaintext inserita: %s", plaintext);
    printf("Key %s: %s", (scelta == 1 ? "inserita" : "generata"), key);
    printf("Cyper: %s\n", criptata);
    printf("Plain calcolata: %s\n", plainCalcolata);

    return 0;
}

// Sostituisce fflush che non funziona su linux, causa il problema di dover premere invio una volta di piu
void pulisci_input()
{
    int c;
    do
    {
        c = getchar();
    } while (c != '\n' && c != EOF);
}
