#include <stdio.h>
#include <time.h>
#include <string.h>
#include <stdlib.h>

void pulisci_input(void);

int main(void)
{
    const short DIMENSIONE = 128;
    char plaintext[DIMENSIONE];

    do
    {
        printf("Inserisci una stringa da cifrare (NON piu di %d caratteri)\n", DIMENSIONE);
        fgets(plaintext, DIMENSIONE, stdin);
	if (strlen(plaintext) == DIMENSIONE - 1) 
		pulisci_input();
        int scelta = 0;

        do
        {
            printf("Puoi scegliere tra:\n");
            printf("\t1) Inserire una stringa da utilizzare come chiave\n");
            printf("\t2) Generare casualmente una chiave\n");
            printf("\t3) Termina il programma\n");
            printf("Fai la tua scelta: ");
            scanf("%d", &scelta);
	    pulisci_input();
        } while (scelta != 1 && scelta != 2 && scelta != 3);

        // Inizializzo tutti i valori che mi serviranno
        char key[DIMENSIONE];
        char criptata[DIMENSIONE];
        char plainCalcolata[DIMENSIONE];
        time_t t;
        srand((unsigned)time(&t));

	// Faccio scegliere la key
        if (scelta == 1)
        {
            do
            {
                printf("\n\nInserisci una stringa da usare come chiave lunga almeno %lx caratteri\n", strlen(plaintext) - 1);
                fgets(key, DIMENSIONE, stdin);
		if (strlen(key) >= DIMENSIONE - 1)
			pulisci_input();
            } while (strlen(key) < strlen(plaintext));
        }

	// Genero la key
        else if (scelta == 2)
        {
            for (int i = 0; i < strlen(plaintext) - 1; i++)
            {
                key[i] = rand() % 128;
            }
	    key[strlen(plaintext)] = '\0';
        }

        else
            return 0;

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
    } while (1);
}

// Sostituisce fflush che non funziona con linux
void pulisci_input()
{
    while (getchar() != '\n');
}
