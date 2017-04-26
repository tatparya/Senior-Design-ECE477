#include "cube.h"
#include <stdlib.h>
#include <time.h>
#include "solHelper.h"

int motorIndices[6] = { 0, 0, 0, 0, 0, 0 };

void displayCorners( int * corners [2][4][3] )
{
    int i, j;
    printf( "Displaying Corners\n" );
    for( i = 0; i < 2; i++ )
    {
        printf( "Layer %d:\n", i + 1 );
        for( j = 0; j < 4; j++ )
        {
            printf( "%d, %d, %d\n", *corners[i][j][0], *corners[i][j][1], *corners[i][j][2] );
        }
    }
}

void displayEdges( int * edges [3][4][2] )
{
    int i, j;
    printf( "Displaying Edges\n" );
    for( i = 0; i < 3; i++ )
    {
        printf( "Layer %d:\n", i + 1 );
        for( j = 0; j < 4; j++ )
        {
            printf( "%d, %d\n", *edges[i][j][0], *edges[i][j][1] );
        }
    }
}

void displayCube( int cube[6][3][3] )
{ int i,j;
    int r,c;

    r = 0;
    c = 0;

    printf( "Cube:\n");

    for( i = 0; i < 3; i++ )
    {
        for( r = 0; r < 3; r++ )
        {
            for( j = 0; j < 4; j++ )
            {
                if( i == 0 && j == 1 )
                {
                    //  Print side 5
                    displayCubeRow( cube, r, 4 );
                }

                else if( i == 1 && j == 0 )
                {
                    // Print side 1
                    displayCubeRow( cube, r, 0 );
                }

                else if( i == 1 && j == 1 )
                {
                    // Print side 2
                    displayCubeRow( cube, r, 1 );
                }

                else if( i == 1 && j == 2 )
                {
                    // Print side 3
                    displayCubeRow( cube, r, 2 );
                }

                else if( i == 1 && j == 3 )
                {
                    // Print side 4
                    displayCubeRow( cube, r, 3 );
                }

                else if( i == 2 && j == 1 )
                {
                    // Print side 6
                    displayCubeRow( cube, r, 5 );
                }

                else
                {
                    //  Print blanks
                    displayCubeRow( cube, r, -1 );
                }
            }

            printf( "\n\n" );
        }
    }
}

void displayCubeRow( int cube[6][3][3], int row, int side )
{
    int col;
    for( col = 0; col < 3; col++ )
    {
        //  Check if blank or not
        if( side == -1 )
        {
            printf( "   " );
        }
        else
        {
            printf( " %d ", cube[side][row][col] );
        }
    }
}

void rotate( int side[3][3] )
{
    int i;
    for( i = 0; i < 2; i++ )
    {
        int temp = side[0][i];
        side[0][i] = side[2-i][0];
        side[2-i][0] = side[2][2-i];
        side[2][2-i] = side[i][2];
        side[i][2] = temp;
    }
}

void rotatePrime( int side[3][3] )
{
    int i;
    for( i = 0; i < 2; i++ )
    {
        int temp = side[0][i];
        side[0][i] = side[i][2];
        side[i][2] = side[2][2-i];
        side[2][2-i] = side[2-i][0];
        side[2-i][0] = temp;
    }
}

void up( int cube [6][3][3] )
{
    int t1, t2, t3;
    t1 = cube[0][0][0];
    t2 = cube[0][0][1];
    t3 = cube[0][0][2];

    cube[0][0][0] = cube[1][0][0];
    cube[0][0][1] = cube[1][0][1];
    cube[0][0][2] = cube[1][0][2];

    cube[1][0][0] = cube[2][0][0];
    cube[1][0][1] = cube[2][0][1];
    cube[1][0][2] = cube[2][0][2];

    cube[2][0][0] = cube[3][0][0];
    cube[2][0][1] = cube[3][0][1];
    cube[2][0][2] = cube[3][0][2];

    cube[3][0][0] = t1;
    cube[3][0][1] = t2;
    cube[3][0][2] = t3;

    rotate( cube[4] );

    //  Rotate motor
    solArray[arIndex] = 4;
    arIndex++;
    arLength++;

    //printf( "Up / White\n" );

    //rotato_potato( 4, 1, &motorIndices[4], 1 );
}

void upPrime( int cube [6][3][3] )
{
    int t1, t2, t3;
    t1 = cube[3][0][0];
    t2 = cube[3][0][1];
    t3 = cube[3][0][2];

    cube[3][0][0] = cube[2][0][0];
    cube[3][0][1] = cube[2][0][1];
    cube[3][0][2] = cube[2][0][2];

    cube[2][0][0] = cube[1][0][0];
    cube[2][0][1] = cube[1][0][1];
    cube[2][0][2] = cube[1][0][2];

    cube[1][0][0] = cube[0][0][0];
    cube[1][0][1] = cube[0][0][1];
    cube[1][0][2] = cube[0][0][2];

    cube[0][0][0] = t1;
    cube[0][0][1] = t2;
    cube[0][0][2] = t3;

    rotatePrime( cube[4] );

    //  Rotate motor
    solArray[arIndex] = 10;
    arIndex++;
    arLength++;

    //printf( "Up Prime / White\n" );

    //rotato_potato( 4, -1, &motorIndices[3], 1 );
}

void down( int cube [6][3][3] )
{
    int t1, t2, t3;
    t1 = cube[3][2][0];
    t2 = cube[3][2][1];
    t3 = cube[3][2][2];

    cube[3][2][0] = cube[2][2][0];
    cube[3][2][1] = cube[2][2][1];
    cube[3][2][2] = cube[2][2][2];

    cube[2][2][0] = cube[1][2][0];
    cube[2][2][1] = cube[1][2][1];
    cube[2][2][2] = cube[1][2][2];

    cube[1][2][0] = cube[0][2][0];
    cube[1][2][1] = cube[0][2][1];
    cube[1][2][2] = cube[0][2][2];

    cube[0][2][0] = t1;
    cube[0][2][1] = t2;
    cube[0][2][2] = t3;

    rotate( cube[5] );

    //  Rotate motor
    solArray[arIndex] = 5;
    arIndex++;
    arLength++;

    //printf( "Down / Yellow\n" );

    //rotato_potato( 5, 1, &motorIndices[5], 1 );
}

void downPrime( int cube [6][3][3] )
{
    int t1, t2, t3;
    t1 = cube[0][2][0];
    t2 = cube[0][2][1];
    t3 = cube[0][2][2];

    cube[0][2][0] = cube[1][2][0];
    cube[0][2][1] = cube[1][2][1];
    cube[0][2][2] = cube[1][2][2];

    cube[1][2][0] = cube[2][2][0];
    cube[1][2][1] = cube[2][2][1];
    cube[1][2][2] = cube[2][2][2];

    cube[2][2][0] = cube[3][2][0];
    cube[2][2][1] = cube[3][2][1];
    cube[2][2][2] = cube[3][2][2];

    cube[3][2][0] = t1;
    cube[3][2][1] = t2;
    cube[3][2][2] = t3;

    rotatePrime( cube[5] );

    //  Rotate motor
    solArray[arIndex] = 11;
    arIndex++;
    arLength++;

    //printf( "Down Prime / Yellow\n" );

    //rotato_potato( 5, -1, &motorIndices[5], 1 );
}

void left( int cube [6][3][3] )
{
    int t1, t2, t3;
    t1 = cube[1][0][0];
    t2 = cube[1][1][0];
    t3 = cube[1][2][0];

    cube[1][0][0] = cube[4][0][0];
    cube[1][1][0] = cube[4][1][0];
    cube[1][2][0] = cube[4][2][0];

    cube[4][0][0] = cube[3][2][2];
    cube[4][1][0] = cube[3][1][2];
    cube[4][2][0] = cube[3][0][2];

    cube[3][2][2] = cube[5][0][0];
    cube[3][1][2] = cube[5][1][0];
    cube[3][0][2] = cube[5][2][0];

    cube[5][0][0] = t1;
    cube[5][1][0] = t2;
    cube[5][2][0] = t3;

    rotate( cube[0] );

    //  Rotate motor
    solArray[arIndex] = 0;
    arIndex++;
    arLength++;

    //printf( "Left / Blue\n" );

    //rotato_potato( 0, 1, &motorIndices[0], 1 );
}

void leftPrime( int cube [6][3][3] )
{
    int t1, t2, t3;
    t1 = cube[1][0][0];
    t2 = cube[1][1][0];
    t3 = cube[1][2][0];

    cube[1][0][0] = cube[5][0][0];
    cube[1][1][0] = cube[5][1][0];
    cube[1][2][0] = cube[5][2][0];

    cube[5][0][0] = cube[3][2][2];
    cube[5][1][0] = cube[3][1][2];
    cube[5][2][0] = cube[3][0][2];

    cube[3][2][2] = cube[4][0][0];
    cube[3][1][2] = cube[4][1][0];
    cube[3][0][2] = cube[4][2][0];

    cube[4][0][0] = t1;
    cube[4][1][0] = t2;
    cube[4][2][0] = t3;

    rotatePrime( cube[0] );

    //  Rotate motor
    solArray[arIndex] = 6;
    arIndex++;
    arLength++;

    //printf( "Left Prime / Blue\n" );

    //rotato_potato( 0, -1, &motorIndices[0], 1 );
}

void right( int cube [6][3][3] )
{
    int t1, t2, t3;
    t1 = cube[1][0][2];
    t2 = cube[1][1][2];
    t3 = cube[1][2][2];

    cube[1][0][2] = cube[5][0][2];
    cube[1][1][2] = cube[5][1][2];
    cube[1][2][2] = cube[5][2][2];

    cube[5][0][2] = cube[3][2][0];
    cube[5][1][2] = cube[3][1][0];
    cube[5][2][2] = cube[3][0][0];

    cube[3][2][0] = cube[4][0][2];
    cube[3][1][0] = cube[4][1][2];
    cube[3][0][0] = cube[4][2][2];

    cube[4][0][2] = t1;
    cube[4][1][2] = t2;
    cube[4][2][2] = t3;

    rotate( cube[2] );

    //  Rotate motor
    solArray[arIndex] = 2;
    arIndex++;
    arLength++;

    //printf( "Right / Green\n" );

    //rotato_potato( 2, 1, &motorIndices[2], 1 );

}

void rightPrime( int cube [6][3][3] )
{
    int t1, t2, t3;
    t1 = cube[1][0][2];
    t2 = cube[1][1][2];
    t3 = cube[1][2][2];

    cube[1][0][2] = cube[4][0][2];
    cube[1][1][2] = cube[4][1][2];
    cube[1][2][2] = cube[4][2][2];

    cube[4][0][2] = cube[3][2][0];
    cube[4][1][2] = cube[3][1][0];
    cube[4][2][2] = cube[3][0][0];

    cube[3][2][0] = cube[5][0][2];
    cube[3][1][0] = cube[5][1][2];
    cube[3][0][0] = cube[5][2][2];

    cube[5][0][2] = t1;
    cube[5][1][2] = t2;
    cube[5][2][2] = t3;

    rotatePrime( cube[2] );

    //  Rotate motor
    solArray[arIndex] = 8;
    arIndex++;
    arLength++;

    //printf( "Right Prime / Green\n" );

    //rotato_potato( 2, -1, &motorIndices[2], 1 );
}

void face( int cube [6][3][3] )
{
    int t1, t2, t3;
    t1 = cube[0][0][2];
    t2 = cube[0][1][2];
    t3 = cube[0][2][2];

    cube[0][0][2] = cube[5][0][0];
    cube[0][1][2] = cube[5][0][1];
    cube[0][2][2] = cube[5][0][2];

    cube[5][0][0] = cube[2][2][0];
    cube[5][0][1] = cube[2][1][0];
    cube[5][0][2] = cube[2][0][0];

    cube[2][2][0] = cube[4][2][2];
    cube[2][1][0] = cube[4][2][1];
    cube[2][0][0] = cube[4][2][0];

    cube[4][2][2] = t1;
    cube[4][2][1] = t2;
    cube[4][2][0] = t3;

    rotate( cube[1] );

    //  Rotate motor
    solArray[arIndex] = 1;
    arIndex++;
    arLength++;

    //printf( "Face / Orange\n" );

    //rotato_potato( 1, 1, &motorIndices[1], 1 );
}

void facePrime( int cube [6][3][3] )
{
    int t1, t2, t3;
    t1 = cube[0][0][2];
    t2 = cube[0][1][2];
    t3 = cube[0][2][2];

    cube[0][0][2] = cube[4][2][2];
    cube[0][1][2] = cube[4][2][1];
    cube[0][2][2] = cube[4][2][0];

    cube[4][2][2] = cube[2][2][0];
    cube[4][2][1] = cube[2][1][0];
    cube[4][2][0] = cube[2][0][0];

    cube[2][2][0] = cube[5][0][0];
    cube[2][1][0] = cube[5][0][1];
    cube[2][0][0] = cube[5][0][2];

    cube[5][0][0] = t1;
    cube[5][0][1] = t2;
    cube[5][0][2] = t3;

    rotatePrime( cube[1] );

    //  Rotate motor
    solArray[arIndex] = 7;
    arIndex++;
    arLength++;

    //printf( "Face Prime / Orange\n" );

    //rotato_potato( 1, -1, &motorIndices[0], 1 );
}

void bottom( int cube [6][3][3] )
{
    int t1, t2, t3;
    t1 = cube[0][0][0];
    t2 = cube[0][1][0];
    t3 = cube[0][2][0];

    cube[0][0][0] = cube[4][0][2];
    cube[0][1][0] = cube[4][0][1];
    cube[0][2][0] = cube[4][0][0];

    cube[4][0][2] = cube[2][2][2];
    cube[4][0][1] = cube[2][1][2];
    cube[4][0][0] = cube[2][0][2];

    cube[2][2][2] = cube[5][2][0];
    cube[2][1][2] = cube[5][2][1];
    cube[2][0][2] = cube[5][2][2];

    cube[5][2][0] = t1;
    cube[5][2][1] = t2;
    cube[5][2][2] = t3;

    rotate( cube[3] );

    //  Rotate motor
    solArray[arIndex] = 3;
    arIndex++;
    arLength++;

    //printf( "Bottom / Red\n" );

    //rotato_potato( 3, 1, &motorIndices[3], 1 );
}

void bottomPrime( int cube [6][3][3] )
{
    int t1, t2, t3;
    t1 = cube[0][0][0];
    t2 = cube[0][1][0];
    t3 = cube[0][2][0];

    cube[0][0][0] = cube[5][2][0];
    cube[0][1][0] = cube[5][2][1];
    cube[0][2][0] = cube[5][2][2];

    cube[5][2][0] = cube[2][2][2];
    cube[5][2][1] = cube[2][1][2];
    cube[5][2][2] = cube[2][0][2];

    cube[2][2][2] = cube[4][0][2];
    cube[2][1][2] = cube[4][0][1];
    cube[2][0][2] = cube[4][0][0];

    cube[4][0][2] = t1;
    cube[4][0][1] = t2;
    cube[4][0][0] = t3;

    rotatePrime( cube[3] );

    //  Rotate motor
    solArray[arIndex] = 9;
    arIndex++;
    arLength++;

    //printf( "Bottom Prime / Red\n" );

    //rotato_potato( 3, -1, &motorIndices[3], 1 );
}

void calcMove( int cube [6][3][3], char move, int side )
{
    //printf( "\nCube before \n" );
    //printf( "Move : %c, on side %d\n", move, side );
    //displayCube( cube );

    switch ( move ) {
        case 'u':
            switch ( side ) {
                case 0:
                    up( cube );
                    break;
                case 1:
                    up( cube );
                    break;
                case 2:
                    up( cube );
                    break;
                case 3:
                    up( cube );
                    break;
                case 4:
                    bottom( cube );
                    break;
                case 5:
                    face( cube );
                    break;
            }
            break;
        case 'U':
            switch ( side ) {
                case 0:
                    upPrime( cube );
                    break;
                case 1:
                    upPrime( cube );
                    break;
                case 2:
                    upPrime( cube );
                    break;
                case 3:
                    upPrime( cube );
                    break;
                case 4:
                    bottomPrime( cube );
                    break;
                case 5:
                    facePrime( cube );
                    break;
            }
            break;
        case 'd':
            switch ( side ) {
                case 0:
                    down( cube );
                    break;
                case 1:
                    down( cube );
                    break;
                case 2:
                    down( cube );
                    break;
                case 3:
                    down( cube );
                    break;
                case 4:
                    face( cube );
                    break;
                case 5:
                    bottom( cube );
                    break;
            }
            break;
        case 'D':
            switch ( side ) {
                case 0:
                    downPrime( cube );
                    break;
                case 1:
                    downPrime( cube );
                    break;
                case 2:
                    downPrime( cube );
                    break;
                case 3:
                    downPrime( cube );
                    break;
                case 4:
                    facePrime( cube );
                    break;
                case 5:
                    bottomPrime( cube );
                    break;
            }
            break;
        case 'l':
            switch ( side ) {
                case 0:
                    bottom( cube );
                    break;
                case 1:
                    left( cube );
                    break;
                case 2:
                    face( cube );
                    break;
                case 3:
                    right( cube );
                    break;
                case 4:
                    left( cube );
                    break;
                case 5:
                    left( cube );
                    break;
            }
            break;
        case 'L':
            switch ( side ) {
                case 0:
                    bottomPrime( cube );
                    break;
                case 1:
                    leftPrime( cube );
                    break;
                case 2:
                    facePrime( cube );
                    break;
                case 3:
                    rightPrime( cube );
                    break;
                case 4:
                    leftPrime( cube );
                    break;
                case 5:
                    leftPrime( cube );
                    break;
            }
            break;
        case 'r':
            switch ( side ) {
                case 0:
                    face( cube );
                    break;
                case 1:
                    right( cube );
                    break;
                case 2:
                    bottom( cube );
                    break;
                case 3:
                    left( cube );
                    break;
                case 4:
                    right( cube );
                    break;
                case 5:
                    right( cube );
                    break;
            }
            break;
        case 'R':
            switch ( side ) {
                case 0:
                    facePrime( cube );
                    break;
                case 1:
                    rightPrime( cube );
                    break;
                case 2:
                    bottomPrime( cube );
                    break;
                case 3:
                    leftPrime( cube );
                    break;
                case 4:
                    rightPrime( cube );
                    break;
                case 5:
                    rightPrime( cube );
                    break;
            }
            break;
        case 'f':
            switch ( side ) {
                case 0:
                    left( cube );
                    break;
                case 1:
                    face( cube );
                    break;
                case 2:
                    right( cube );
                    break;
                case 3:
                    bottom( cube );
                    break;
                case 4:
                    up( cube );
                    break;
                case 5:
                    down( cube );
                    break;
            }
            break;
        case 'F':
            switch ( side ) {
                case 0:
                    leftPrime( cube );
                    break;
                case 1:
                    facePrime( cube );
                    break;
                case 2:
                    rightPrime( cube );
                    break;
                case 3:
                    bottomPrime( cube );
                    break;
                case 4:
                    upPrime( cube );
                    break;
                case 5:
                    downPrime( cube );
                    break;
            }
            break;
        case 'b':
            switch ( side ) {
                case 0:
                    right( cube );
                    break;
                case 1:
                    bottom( cube );
                    break;
                case 2:
                    left( cube );
                    break;
                case 3:
                    face( cube );
                    break;
                case 4:
                    down( cube );
                    break;
                case 5:
                    up( cube );
                    break;
            }
            break;
        case 'B':
            switch ( side ) {
                case 0:
                    rightPrime( cube );
                    break;
                case 1:
                    bottomPrime( cube );
                    break;
                case 2:
                    leftPrime( cube );
                    break;
                case 3:
                    facePrime( cube );
                    break;
                case 4:
                    downPrime( cube );
                    break;
                case 5:
                    upPrime( cube );
                    break;
            }
            break;
    }
    //displayCube( cube );
}

void scrambleCube( int cube [6][3][3], int numMoves )
{
    time_t t;
    srand((unsigned) time(&t));
    int i;
    for( i = 0; i < numMoves; i++ )
    {
        int n;
        n = ( rand() + 1 ) % 6;
        switch ( n ) {
            case 0:
                left( cube );
                break;
            case 1:
                right( cube );
                break;
            case 2:
                up( cube );
                break;
            case 3:
                down( cube );
                break;
            case 4:
                face( cube );
                break;
            case 5:
                bottom( cube );
                break;
        }
        //displayCube( cube );
    }
}
