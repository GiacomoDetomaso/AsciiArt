#include "asciiartlib.c";

int main()
{
    char canvas[R][C];

    enum State choose;
    enum FigureType figure;

    int length, height, ray, x, y, dir;

    init(canvas); // init the canvas

    printf("Ascii Art Paint Jak\n");

    do
    {
        menu();
        
        printf("\nInsert choice: ");
        scanf("%d", &figure);
        figure++;

        switch (figure)
        {

        case POINT:

            printf("Insert coordinates:\n");

            printf("- x: ");
            scanf("%d", &x);

            printf("\n- y: ");
            scanf("%d", &y);

            /*Control if the dot has been printed correctly*/

            if (x > R || y > C || x < 0 || y < 0)
                printf("Cannot design dot!\n ");
            else
            {
                canvas[x][y] = '*';
                printMat(canvas);
            }

            break;

        case LINE:
            printf("Insert the coordinates and the length:\n");

            printf("-x: ");
            scanf("%d", &x);

            printf("\n-y: ");
            scanf("%d", &y);

            printf("\n-Length: ");
            scanf("%d", &length);

            printf("\n1) Vertical line 0) Horizontal line\n");
            scanf("%d", &dir);

            /* Control on the line */

            if (dir == 0)
                choose = printLineO(canvas, length, x, y);
            else
                choose = printLineV(canvas, length, x, y);

            if (choose == TRUE)
                printMat(canvas);
            else
                printf("Too big!");

            break;

        case SQUARE:
            printf("Insert  top - left coordinates:\n");

            /*  Square data acquisition
                    1) top left point (x,y) della matrice
                    2) side's length*/

            printf("-x: ");
            scanf("%d", &x);

            printf("\n-y: ");
            scanf("%d", &y);

            printf("\n-Side's length: ");
            scanf("%d", &length);

            choose = printSquare(canvas, length, x, y); // print the square in the matrix

            if (choose == TRUE)
                printMat(canvas); // stampa a video il risultato
            else
                printf("Cannot design square!\n");

            break;

        case RECTANGLE:
            printf("Insert top - left coordinates:\n");

            /*Rectangle data acquisition
                    1) top left point (x,y) della matrice
                    2) side's length
                    3) height */

            printf("-x: ");
            scanf("%d", &x);

            printf("\n-y: ");
            scanf("%d", &y);

            printf("\n-Side's length: ");
            scanf("%d", &length);

            printf("\n-Height: ");
            scanf("%d", &height);

            printRectangle(canvas, length, height, x, y);
            printMat(canvas); 

            break;

        case CIRCLE:
            printf("Insert centre (xC, yX) of the circle and his ray\n");

            printf("-xC: ");
            scanf("%d", &x);

            printf("\n-yC: ");
            scanf("%d", &y);

            printf("\n-Ray:");
            scanf("%d", &ray);

            printCircle(canvas, ray, x, y);
            printMat(canvas);

            break;

        case DELETE:
            printf("Delete...\n");
            init(canvas);
            break;

        default:
            printf("Wrong choice\n");
            break;
        }

        printf("\nContinue? Y/N:");
        fflush(stdin); // clean buffer
        choose = getchar();
        tolower(choose);

    }
    while (choose != FALSE);

    //return 0;
}



