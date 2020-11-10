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
            printf("\n\nInserisci una stringa da usare come chiave lunga almeno %lx caratteri\n", strlen(plaintext));
            fgets(key, DIMENSIONE, stdin);
            pulisci_input();
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
        criptata[i] = plaintext[i] ^ key[i];
    }

    // La stringa viene decifrata
    for (int i = 0; i < strlen(key); i++)
    {
        plainCalcolata[i] = key[i] ^ criptata[i];
    }

    printf("\n\nPlaintext inserita: %s\n", plaintext);
    printf("Key %s: %s\n", (scelta == 1 ? "inserita" : "generata"), key);
    printf("Cyper: %s\n", criptata);
    printf("Plaintext calcolata: %s\n", plainCalcolata);

    return 0;
}

// Sostituisce fflush che non funziona con linux
void pulisci_input()
{
    while (getchar() != '\n' && getchar() != EOF);
}
