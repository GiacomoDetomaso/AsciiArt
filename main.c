#include <stdio.h>
#include <math.h>
#define C 30
#define R 30

/* Funzioni di disegno e di stampa */

void printMat(char mat[][C]);                                   // stampa gli elementi della matrice
void init(char mat[][C]);                                       // inizializza la matrice
void menu();                                                    // stampa del menù
int printLineO(char mat[][C], int l, int x, int y);             // x riga, y colonna (fissa)
int printtLineV(char mat[][C], int l, int x, int y);            // disegna una linea verticale
int printQuadrato(char mat[][C], int l, int x, int y);          // disegna il quadrato nella matrice
int printRettangolo(char mat[][C], int l, int h, int x, int y); // disegna il rettangolo nella matrice
void printCirconferenza(char mat[][C], int r, int h, int k);  // disegna la circonferenza nella matrice xC e yC sono le coordinate del centro

/* enumerazione per stato e tipo della figura da scegliere nel menù*/
enum Stato
{
    TRUE = 0,
    FALSE = 1
};
enum TipoFigura
{
    PUNTO = 2,
    LINEA = 3,
    QUADRATO = 4,
    RETTANGOLO = 5,
    CERCHIO = 6,
    CANCELLA = 7
};

int main()
{
    char canvas[R][C];

    enum Stato scelta;
    enum TipoFigura figura;

    int lunghezza, altezza, raggio, x, y;

    init(canvas); // inizializza la matrice

    printf("Paint Jak\n");

    do
    {
        menu();
        scanf("%d", &figura);
        figura++;

        switch (figura)
        {

        case PUNTO:

            printf("Inserisci le cordinate:\n");

            printf("- x: ");
            scanf("%d", &x);

            printf("\n- y: ");
            scanf("%d", &y);

            /*Controllo sul corretto disegno del punto*/

            if (x > R || y > C || x < 0 || y < 0)
                printf("Impossibile disegnare il punto!\n ");
            else
            {
                canvas[x][y] = '*';
                printMat(canvas);
            }

            break;

        case LINEA:
            printf("Inserire lunghezza e coordinate:\n");

            printf("-x: ");
            scanf("%d", &x);

            printf("\n-y: ");
            scanf("%d", &y);

            printf("\n-Lunghezza: ");
            scanf("%d", &lunghezza);

            printf("\n1) Linea  verticale 0) Linea orizzontale\n");
            scanf("%d", &scelta);

            /* Controllo sul corretto disegno della linea */

            if (scelta == TRUE)
                scelta = printLineO(canvas, lunghezza, x, y);
            else
                scelta = printLineV(canvas, lunghezza, x, y);

            if (scelta == TRUE)
                printMat(canvas);
            else
                printf("Linea troppo grande!");

            break;

        case QUADRATO:
            printf("Inserire lunghezza e coordinate top-left:\n");

            /*Acquisizione dei dati necessari per costruire il quadrato
                    1) posizione iniziale top-left punto (x,y) della matrice
                    2) lunghezza del lato*/

            printf("-x: ");
            scanf("%d", &x);

            printf("\n-y: ");
            scanf("%d", &y);

            printf("\n-Lunghezza lato: ");
            scanf("%d", &lunghezza);

            scelta = printQuadrato(canvas, lunghezza, x, y); // disegna il quadrato nella matrice

            if (scelta == TRUE)
                printMat(canvas); // stampa a video il risultato
            else
                printf("Impossibile disegnare la figura!\n");

            break;

        case RETTANGOLO:
            printf("Inserire lunghezza, altezza e coordinate top-left:\n");

            /*Acquisizione dei dati necessari per costruire il rettangolo
                    1) posizione iniziale top-left punto (x,y) della matrice
                    2) lunghezza del lato
                    3) altezza */

            printf("-x: ");
            scanf("%d", &x);

            printf("\n-y: ");
            scanf("%d", &y);

            printf("\n-Lunghezza lato: ");
            scanf("%d", &lunghezza);

            printf("\n-Altezza: ");
            scanf("%d", &altezza);

            printRettangolo(canvas, lunghezza, altezza, x, y);
            printMat(canvas); // stampa della matrice

            break;

        case CERCHIO:
            printf("Inserire centro (xC, yX) della circonferenza e il suo raggio\n");

            printf("-xC: ");
            scanf("%d", &x);

            printf("\n-yC: ");
            scanf("%d", &y);

            printf("\n-Raggio:");
            scanf("%d", &raggio);

            printCirconferenza(canvas, raggio, x, y);
            printMat(canvas);

            break;

        case CANCELLA:
            printf("Cancellazione in corso...\n");
            init(canvas);
            break;

        default:
            printf("Scelta errata\n");
            break;
        }

        printf("\nProseguire nel disegno? (1 = NO, 0 = SI)");
        scanf("%d", &scelta);

    }
    while (scelta != FALSE);
}

void printMat(char mat[][C])
{
    for (int i = 0; i < R; i++)
    {
        for (int j = 0; j < C; j++)
        {

            printf("%c ", mat[i][j]); // stampa il contenuto della matrice
        }
        puts("");
    }
}

void init(char mat[][C])
{
    for (int i = 0; i < R; i++)
    {
        for (int j = 0; j < C; j++)
        {
            mat[i][j] = ' '; // inizializza la matrice con spazi
        }
    }
}

void menu()
{
    printf(" ____________________________\n\n");
    printf("| 1) Disegna un punto        |\n");
    printf("| 2) Disegna una linea       |\n");
    printf("| 3) Disegna un quadrato     |\n");
    printf("| 4) Disegna un rettangolo   |  \n");
    printf("| 5) Disegna un cerchio      |  \n");
    printf("| 6) Cancella tutto          |\n");
    printf(" ____________________________\n");
}

int printLineO(char mat[][C], int l, int x, int y)
{
    int i;
    int dim = x + l;

    if (dim > R)
        return FALSE;

    for (i = x; i < dim; i++)
    {
        mat[y][i] = '*';
    }

    return TRUE;
}

int printLineV(char mat[][C], int l, int x, int y)
{
    int i;
    int dim = y + l;

    if (dim > C)
        return FALSE; // controllo sulla lunghezza della linea

    for (i = y; i < dim; i++)
    {
        mat[i][x] = '*';
    }

    return TRUE;
}

int printQuadrato(char mat[][C], int l, int x, int y)
{
    int newY = y, newX = x;
    enum Stato s;

    s = printLineO(mat, l, x, y);

    if (s == FALSE)
        return FALSE;

    s = printLineV(mat, l, x, y);

    if (s == FALSE)
        return FALSE;

    newY = newY + (l - 1); // calcola il nuovo valore di Y come valore di Y + lunghezza - 1
    newX = newX + (l - 1); // calcola il nuovo valore di X come valore di X + lunghezza - 1

    s = printLineO(mat, l, x, newY);

    if (s == FALSE)
        return FALSE;

    s = printLineV(mat, l, newX, y);

    if (s == FALSE)
        return FALSE;

    return TRUE;
}

int printRettangolo(char mat[][C], int l, int h, int x, int y)
{
    int newY = y, newX = x;
    enum Stato s;

    s = printLineO(mat, l, x, y);

    if (s == FALSE)
        return FALSE;

    s = printLineV(mat, h, x, y);

    if (s == FALSE)
        return FALSE;

    newY = newY + (h - 1); // calcola il nuovo valore di Y come valore di Y + lunghezza - 1
    newX = newX + (l - 1); // calcola il nuovo valore di X come valore di X + lunghezza - 1

    s = printLineO(mat, l, x, newY);

    if (s == FALSE)
        return FALSE;

    s = printLineV(mat, h, newX, y);

    if (s == FALSE)
        return FALSE;

    return TRUE;
}

void printCirconferenza(char mat[][C], int r, int h, int k)
{
    int x, y; // utilizzati per realizzare l'equazione caratteristica della circonfereza
    float a, b, c, radDelta;

    /* La circonferenza ha un equazione del tipo (x - xC)^2 + (y - yC)^2 = r^2
        Conosciamo: 1) coordinate del centro (xC,yC)
                    2) valori di x o y a seconda del ciclo*/

    /* Posizione da cui iniziare i rispettivi cicli*/

    int startX = h - r;
    int startY = k - r;

    /* Posizione di fine dei rispettivi cicli*/

    int endX = h + r;
    int endY = k + r;

    /* primo ciclo per valutare le y, i valori della x sono dati dal ciclo for
        si tratta di risolvere un'equazione del tipo ay^2 - by + c
        dove by = yC * y con b = -2 * yC
        e dove c = x^2 - 2x * xC + xC^2 - r^2.
        Siccome x è contatore del ciclo i valori di c è possibile calcolari da subito */

    int powR = r * r;    // raggio al quadrato
    int powXc = h * h; // quadrato di xC
    int powYc = k * k;

    a = 1;       // termine della y^2 (è sempre uno)
    b = -2 * k; // termine b di by

    mat[h][k] = 'o'; // disegno del centro

    for (x = h - r; x <= h + r; x++)
    {
        c = x * x + powXc - 2 * h * x + powYc - powR;
        radDelta = pow(b * b - 4 * a * c, 0.5);
        y = round((-b + radDelta) / (2 * a));
        mat[y][x] = '*';
        y = round((-b - radDelta) / (2 * a));
        mat[y][x] = '*';
    }

    a = 1;
    b = -2 * h;
    for (y = k - r; y <= k + r; y++)
    {
        c = y * y + powXc - 2 * k * y + powYc - powR;
        radDelta = pow(b * b - 4 * a * c, 0.5);
        x = round((-b + radDelta) / (2 * a));
        mat[y][x] = '*';
        x = round((-b - radDelta) / (2 * a));
        mat[y][x] = '*';
    }
}

