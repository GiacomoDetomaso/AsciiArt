#include "asciiartlib.h";

void printMat(char mat[][C])
{
    for (int i = 0; i < R; i++)
    {
        for (int j = 0; j < C; j++)
        {

            printf("%c ", mat[i][j]);
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
            mat[i][j] = ' '; 
        }
    }
}

void menu()
{
    printf(" ____________________________\n\n");
    printf("| 1) Print a dot             |\n");
    printf("| 2) Print a line            |\n");
    printf("| 3) Print a square          |\n");
    printf("| 4) Print a rectangle       |\n");
    printf("| 5) Print a cirmunference   |\n");
    printf("| 6) Delete canvas           |\n");
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
        return FALSE; // check the line's length

    for (i = y; i < dim; i++)
    {
        mat[i][x] = '*';
    }

    return TRUE;
}

int printSquare(char mat[][C], int l, int x, int y)
{
    int newY = y, newX = x;
    enum State s;

    s = printLineO(mat, l, x, y);

    if (s == FALSE)
        return FALSE;

    s = printLineV(mat, l, x, y);

    if (s == FALSE)
        return FALSE;

    newY = newY + (l - 1); // calculate new Y value as old Y + length - 1
    newX = newX + (l - 1); // same for the X

    s = printLineO(mat, l, x, newY);

    if (s == FALSE)
        return FALSE;

    s = printLineV(mat, l, newX, y);

    if (s == FALSE)
        return FALSE;

    return TRUE;
}

int printRectangle(char mat[][C], int l, int h, int x, int y)
{
    int newY = y, newX = x;
    enum State s;

    s = printLineO(mat, l, x, y);

    if (s == FALSE)
        return FALSE;

    s = printLineV(mat, h, x, y);

    if (s == FALSE)
        return FALSE;

    newY = newY + (h - 1); // calculate new Y value as old Y + length - 1
    newX = newX + (l - 1); // same for the X

    s = printLineO(mat, l, x, newY);

    if (s == FALSE)
        return FALSE;

    s = printLineV(mat, h, newX, y);

    if (s == FALSE)
        return FALSE;

    return TRUE;
}

void printCircle(char mat[][C], int r, int h, int k)
{
    int x, y; // using circumnference equation to print it
    float a, b, c, radDelta;

    /* Circumnference equation is:  (x - xC)^2 + (y - yC)^2 = r^2
        We know:    1) centre coordinates (xC,yC)
                    2) x and y are given by the loop */

    /* Position to start the loops*/

    int startX = h - r;
    int startY = k - r;

    /* Position to end the loops */

    int endX = h + r;
    int endY = k + r;

    /* First for loop to evaluate the x values of the equation
        We have to solve this equation ay^2 - by + c
        where:
            1)by = yC * y 
            2) b = -2 * yC
        and:
            1) c = x^2 - 2x * xC + xC^2 - r^2.

        The x values are given because we use x as counter in this first loop */

    int powR = r * r;  // square ray
    int powXc = h * h; // square xC
    int powYc = k * k;

    /*Equations coefficients*/

    a = 1;
    b = -2 * k;

    mat[k][h] = 'o'; // centre dot

    for (x = h - r; x <= h + r; x++)
    {
        c = x * x + powXc - 2 * h * x + powYc - powR;
        radDelta = pow(b * b - 4 * a * c, 0.5);
        y = round((-b + radDelta) / (2 * a));
        mat[y][x] = '*';
        y = round((-b - radDelta) / (2 * a));
        mat[y][x] = '*';
    }

    /*Second loop to evaluate the y values*/

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


int writePGM (unsigned char * fileName, unsigned char * canvas, int r, int c){
    FILE *fp;
    char buf [512];

    fp = fopen(fileName, "wb"); // open binary file

    if(fp == NULL)
        return FALSE;

    /* Header */
    strcpy(buf, "P5 50 50 255\n"); 
    fwrite(buf, sizeof(char), strlen(buf), fp);

    /* Payload */
    fwrite(canvas, sizeof(unsigned char), r * c, fp);
    fclose(fp);
	
    return TRUE;
}