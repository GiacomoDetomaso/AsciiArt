#include <stdio.h>
#include <math.h>
#include <ctype.h>

#define C 50
#define R 50

/* indicate the state of some operations */
enum State
{
    TRUE = 'y',
    FALSE = 'n'
};

enum FigureType
{
    POINT = 2,
    LINE = 3,
    SQUARE = 4,
    RECTANGLE = 5,
    CIRCLE = 6,
    DELETE = 7
};

/* Set of functions to print the canvas */

void printMat(char mat[][C]);                                          // print the elements of the canvas
void init(char mat[][C]);                                             // init the matrix
void menu();                                                         // print the menu
int printLineO(char mat[][C], int l, int x, int y);                 // x row, y column (fixed)
int printtLineV(char mat[][C], int l, int x, int y);               // print line in the canvas
int printSquare(char mat[][C], int l, int x, int y);              // print squadre in the matrix
int printRectangle(char mat[][C], int l, int h, int x, int y);   // print rectangle in the matrix
void printCircle(char mat[][C], int r, int h, int k);           // print the circle in the matrix with its dimension (ray height and center)
