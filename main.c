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
        figure++; // numeric costants in asciiartlib.c starts from 2

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
                    1) top left point (x,y) of the canvas
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
                    1) top left point (x,y) of the canvas
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
            do
            {
                printf("Insert centre (xC, yX) of the circle and his ray\n");

                printf("-xC: ");
                scanf("%d", &x);

                printf("\n-yC: ");
                scanf("%d", &y);

                printf("\n-Ray:");
                scanf("%d", &ray);

                if (ray >= x || ray >= y)
                    printf("\nRay to big, out of bound error!\nThe ray must be lower than the centre's coordinates!\n\n");

            } while (ray >= x || ray >= y); // cicle to avoid the circumference to be out of the canvas's bounds

            puts("\n\n");
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

    } while (choose != FALSE);

    printf("\n\nDo you want to save the canvas on a file? (Y/N)");
    fflush(stdin);
    choose = getchar();

    if (choose == TRUE)
        writePGM("canvas.pgm", canvas, R, C);
    else
        printf("Closing the canvas...");

    //return 0;
}
