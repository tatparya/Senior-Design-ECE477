#include "solution.h"
//#include "solHelper.h"

int solArray[500];
int arIndex = 0;
int arLength = 0;

void testSolution()
{
    int cube [6][3][3] = {
        {
            {0,0,0},
            {0,0,0},
            {0,0,0}
        },
        {
            {1,1,1},
            {1,1,1},
            {1,1,1}
        },
        {
            {2,2,2},
            {2,2,2},
            {2,2,2}
        },
        {
            {3,3,3},
            {3,3,3},
            {3,3,3}
        },
        {
            {4,4,4},
            {4,4,4},
            {4,4,4}
        },
        {
            {5,5,5},
            {5,5,5},
            {5,5,5}
        }
    };

    left( cube );
    up( cube );
    leftPrime( cube );
    right( cube );
    bottom( cube );

    solveCube( cube );

    //  Check solution
    printf( "Sol Array Len: %d\n", arLength );
}

int solveCube( int cube[6][3][3] )
{
    printf( "Starting Solving!\n" );
    int input;

    // //printf( "Setting Edges\n" );
    int * edges [3][4][2] = {
        {
            { &cube[4][1][0], &cube[0][0][1] },
            { &cube[4][2][1], &cube[1][0][1] },
            { &cube[4][1][2], &cube[2][0][1] },
            { &cube[4][0][1], &cube[3][0][1] }
        },
        {
            { &cube[0][1][0], &cube[3][1][2] },
            { &cube[1][1][0], &cube[0][1][2] },
            { &cube[2][1][0], &cube[1][1][2] },
            { &cube[3][1][0], &cube[2][1][2] }
        },
        {
            { &cube[5][1][0], &cube[0][2][1] },
            { &cube[5][0][1], &cube[1][2][1] },
            { &cube[5][1][2], &cube[2][2][1] },
            { &cube[5][2][1], &cube[3][2][1] }
        }
    };
    displayEdges( edges );

    // //printf( "Setting Corners\n" );
    int * corners[2][4][3] = {
        {
            { &cube[4][2][0],  &cube[0][0][2],  &cube[1][0][0] },
            { &cube[4][2][2],  &cube[1][0][2],  &cube[2][0][0] },
            { &cube[4][0][2],  &cube[2][0][2],  &cube[3][0][0] },
            { &cube[4][0][0],  &cube[3][0][2],  &cube[0][0][0] }
        },
        {
            { &cube[5][0][0],  &cube[0][2][2],  &cube[1][2][0] },
            { &cube[5][0][2],  &cube[1][2][2],  &cube[2][2][0] },
            { &cube[5][2][2],  &cube[2][2][2],  &cube[3][2][0] },
            { &cube[5][2][0],  &cube[3][2][2],  &cube[0][2][0] }
        }
    };
    // displayCorners( corners );

    //displayCube( cube );

    printf( "~~~~~~~~~  Solving White Cross ~~~~~~~~~\n" );
    if( solveWhiteCross( cube, edges ) != 0 )
        return -1;

    //displayCube( cube );

    printf( "~~~~~~~~~ Solving White Corners ~~~~~~~~~\n" );
    // scanf( "%d", &input );
    if( sovleWhiteCorners( cube, corners ) != 0 )
        return -1;

    //displayCube( cube );

    printf( "~~~~~~~~~ Solving Second Layer ~~~~~~~~~\n" );
    // scanf( "%d", &input );
    if( solveSecondLayer( cube, edges ) != 0 )
        return -1;

    //displayCube( cube );

    printf( "~~~~~~~~~ Solving Orange Cross ~~~~~~~~~\n" );
    // scanf( "%d", &input );
    if( solveOrangeCross( cube, edges ) != 0 )
        return -1;

    //displayCube( cube );

    printf( "~~~~~~~~~ Permuting Orange Cross ~~~~~~~~~\n" );
    // scanf( "%d", &input );
    if( permuteOrangeCross( cube, edges ) != 0 )
        return -1;

    //displayCube( cube );

    printf( "~~~~~~~~~ Solving Orange Corners ~~~~~~~~~\n" );
    // scanf( "%d", &input );
    if( solveOrangeCorners( cube, corners ) != 0 )
        return -1;

    //displayCube( cube );

    printf( "~~~~~~~~~ Permuting Orange Corners ~~~~~~~~~\n" );
    // scanf( "%d", &input );
    if( permuteOrangeCorners( cube, corners ) != 0 )
        return -1;

    //displayCube( cube );

    printf( "Solved!!\n" );

    return 0;
}

int checkSolved( int cube[6][3][3] )
{
    int solved = 1;

    int side, r, c;
    for( side = 0; side < 6; side++ )
    {
        for( r = 0; r < 3; r++ )
        {
            for( c = 0; c < 3; c++ )
            {
                if( cube[side][r][c] != side )
                {
                    solved = 0;
                }
            }
        }
    }

    return solved;
}

int solveWhiteCross( int cube [6][3][3], int * edges [3][4][2] )
{
    int count = 0;
    int dst = -1;
    int move = 0;
    int layer = -1;
    int found = 0;
    int side;

    while( count < 4 )
    {
        count = 0;
        //  Check if pieces in right place
        for( side = 0; side < 4; side++ )
        {
            if( *edges[0][side][0] == 4 )
            {
                dst = *edges[0][side][1];
                if( dst == side )
                {
                    count++;
                }
            }
        }

        //  Check if solved
        if( count == 4 )
        {
            continue;
        }

        //  Layer 2
        layer = 2;
        for( side = 0; side < 4; side++ )
        {
            found = 0;
            if( *edges[layer][side][0] == 4 )
            {
                //printf( "(Cross) White found at 0: Layer %d, Side %d\n", layer, side );
                //  Calculate dst and move
                dst = *edges[layer][side][1];
                found = 1;
            }
            else if( *edges[layer][side][1] == 4 )
            {
                //printf( "(Cross) White found at 1: Layer %d, Side %d\n", layer, side );
                //  Calculate dst and move
                dst = *edges[layer][side][0];
                found = 1;
            }

            if( found )
            {
                move = ( dst - side ) % 4;
                move = ( move == -3 ) ? 1 : move;
                move = ( move == 3 ) ? -1 : move;

                //printf( "M: %d, D: %d\n", move, dst );

                //  Get pieve below right spot
                if( move == -1 )
                {
                    calcMove( cube, 'D', side );
                }
                else if( move == 1 )
                {
                    calcMove( cube, 'd', side );
                }
                else if( move == -2 || move == 2 )
                {
                    calcMove( cube, 'd', side );
                    calcMove( cube, 'd', side );
                }

                //  Get into right spot
                if( *edges[layer][side][0] == 4 )
                {
                    calcMove( cube, 'f', dst );
                    calcMove( cube, 'f', dst );
                }
                else if( *edges[layer][side][1] == 4 )
                {
                    calcMove( cube, 'F', dst );
                    calcMove( cube, 'R', dst );
                    calcMove( cube, 'D', dst );
                    calcMove( cube, 'r', dst );
                    calcMove( cube, 'f', dst );
                    calcMove( cube, 'f', dst );
                }
            }
        }

        //  Layer 1
        layer = 1;
        for( side = 0; side < 4; side++ )
        {
            if( *edges[layer][side][0] == 4 )
            {
                calcMove( cube, 'l', side );
                calcMove( cube, 'd', side );
                calcMove( cube, 'L', side );
            }
            if( *edges[layer][side][1] == 4 )
            {
                calcMove( cube, 'F', side );
                calcMove( cube, 'd', side );
                calcMove( cube, 'f', side );
            }
        }

        //  Layer 0
        layer = 0;
        for( side = 0; side < 4; side++ )
        {
            if( *edges[layer][side][0] == 4 || *edges[layer][side][1] == 4 )
            {
                //  Check if in right spot
                if( *edges[0][side][0] == 4 )
                {
                    dst = *edges[0][side][1];
                    if( dst == side )
                    {
                        continue;
                    }
                }

                calcMove( cube, 'f', side );
                calcMove( cube, 'f', side );
            }
        }
    }

    return 0;
}

int sovleWhiteCorners( int cube [6][3][3], int * corners [2][4][3] )
{
    int done = 0;
    int count = 0;
    int dst = -1;
    int move = 0;
    int op = -1;
    int layer = 1;
    int side;

    while( count < 4 )
    {
        //  Check if corners solved
        count = 0;
        for( side = 0; side < 4; side++ )
        {
            //  Check if corners in place
            if( *corners[0][side][0] == 4 )
            {
                dst = * corners[0][side][1];
                if( dst == side )
                {
                    count++;
                }
            }
        }

        //  Break if done
        if( count == 4 )
        {
            continue;
        }

        //printf( "Done setting %d corners.", count );

        // Layer 1
        layer = 1;
        for( side = 0; side < 4; side++ )
        {
            //  White on orange face
            if( *corners[layer][side][0] == 4 )
            {
                //printf( "White found at 1: Layer %d, Side %d\n", layer, side );

                dst = *corners[layer][side][2];
                move = ( dst - side ) % 4;
                move = ( move == 3 ) ? -1 : move;
                move = ( move == -3 ) ? 1 : move;

                //printf( "M: %d, D: %d\n", move, dst );

                //  Set below right spot
                if( move == -1 )
                {
                    calcMove( cube, 'D', side );
                }
                else if( move == 1 )
                {
                    calcMove( cube, 'd', side );
                }
                else if( move == 2 || move == -2 )
                {
                    calcMove( cube, 'd', side );
                    calcMove( cube, 'd', side );
                }

                //  Get into right spot
                calcMove( cube, 'R', dst );
                calcMove( cube, 'd', dst );
                calcMove( cube, 'd', dst );
                calcMove( cube, 'r', dst );
                calcMove( cube, 'd', dst );
                calcMove( cube, 'R', dst );
                calcMove( cube, 'D', dst );
                calcMove( cube, 'r', dst );
            }

            else if( *corners[layer][side][1] == 4 )
            {
                //  White on left side
                //printf( "White found at 2: Layer %d, Side %d\n", layer, side );

                dst = *corners[layer][side][0];
                op = *corners[layer][side][2];
                move = ( dst - side ) % 4;
                move = ( move == 3 ) ? -1 : move;
                move = ( move == -3 ) ? 1 : move;

                //printf( "M: %d, D: %d OP: %d\n", move, dst, op );

                if( move == -1 )
                {
                    calcMove( cube, 'D', side );
                }
                else if( move == 1 )
                {
                    calcMove( cube, 'd', side );
                }
                else if( move == 2 || move == -2 )
                {
                    calcMove( cube, 'd', side );
                    calcMove( cube, 'd', side );
                }

                calcMove( cube, 'l', op );
                calcMove( cube, 'd', op );
                calcMove( cube, 'L', op );
            }
            else if( *corners[layer][side][2] == 4 )
            {
                //printf( "White found at 3: Layer %d, Side %d\n", layer, side );

                dst = *corners[layer][side][1];
                op = *corners[layer][side][0];
                move = ( dst - side ) % 4;
                move = ( move == 3 ) ? -1 : move;
                move = ( move == -3 ) ? 1 : move;

                //printf( "M: %d, D: %d\n", move, dst );

                if( move == -1 )
                {
                    calcMove( cube, 'D', side );
                }
                else if( move == 1 )
                {
                    calcMove( cube, 'd', side );
                }
                else if( move == 2 || move == -2 )
                {
                    calcMove( cube, 'd', side );
                    calcMove( cube, 'd', side );
                }

                calcMove( cube, 'F', op );
                calcMove( cube, 'D', op );
                calcMove( cube, 'f', op );
            }

        }

        //  Layer 0
        layer = 0;
        for( side = 0; side < 4; side++ )
        {
            //  Check if piece in place
            if( *corners[layer][side][0] == 4 )
            {
                dst = *corners[0][side][1];
                if( dst == side )
                {
                    continue;
                }
            }

            //  Bring piece to layer 1
            calcMove( cube, 'R', side );
            calcMove( cube, 'd', side );
            calcMove( cube, 'r', side );
        }
    }

    return 0;
}

int solveSecondLayer( int cube [6][3][3], int * edges [3][4][2] )
{
    int count = 0;
    int other = 0;
    int dst = 0;
    int layer = 0;
    int move = 0;
    int cornerCount = 0;
    int cur = 0;
    int side;


    while( count < 4 )
    {
        // //displayCube( cube );
        count = 0;
        //  Check if done
        for( side = 0; side < 4; side++ )
        {
            //  Check if edge in place
            if( *edges[1][side][0] == side )
            {
                other = *edges[1][side][1];
                dst = side - 1;
                dst = (dst == -1) ? 3 : dst;

                if( other == dst )
                {
                    count++;
                }
            }
        }

        //  Check if doen
        if( count == 4 )
        {
            continue;
        }

        //  Layer 2
        layer = 2;
        int side = 0;
        while( side < 4 )
        {
            //  Check if not orange
            if( *edges[layer][side][1] != 5 && *edges[layer][side][0] != 5 )
            {
                //printf( "~~~~~~~~~~~~~~~~~~\t");
                //printf( "Not orange found at layer 2 side %d", side );
                //printf( "\t~~~~~~~~~~~~~~~~~~\n");
                //printf( "Colors found : %d, %d\n", *edges[layer][side][1], *edges[layer][side][0] );
                //  Bring above spot
                cur = *edges[layer][side][0];
                dst = *edges[layer][side][1];

                //  Get into right spot
                move = ( dst - side ) % 4;
                move = ( move == -3 ) ? 1 : move;
                move = ( move == 3 ) ? -1 : move;

                //printf( "M: %d, D: %d\n", move, dst );

                //  Get piece below right spot
                if( move == -1 )
                {
                    calcMove( cube, 'D', side );
                }
                else if( move == 1 )
                {
                    calcMove( cube, 'd', side );
                }
                else if( move == -2 || move == 2 )
                {
                    calcMove( cube, 'd', side );
                    calcMove( cube, 'd', side );
                }

                //  SPECIAL CASE
                if( ( cur == 3 && dst == 0 ) )
                {
                    //printf( "~~~~~~~~~~~~~~~~~~\t");
                    //printf( "Moving to left" );
                    //printf( "\t~~~~~~~~~~~~~~~~~~\n");
                    calcMove( cube, 'd', dst );
                    calcMove( cube, 'l', dst );
                    calcMove( cube, 'D', dst );
                    calcMove( cube, 'L', dst );
                    calcMove( cube, 'D', dst );
                    calcMove( cube, 'F', dst );
                    calcMove( cube, 'd', dst );
                    calcMove( cube, 'f', dst );
                    side = 0;
                    continue;
                }
                //  SPECIAL CASE
                if( ( dst == 3 && cur == 0 ) )
                {
                    //printf( "~~~~~~~~~~~~~~~~~~\t");
                    //printf( "Moving to right" );
                    //printf( "\t~~~~~~~~~~~~~~~~~~\n");
                    calcMove( cube, 'D', dst );
                    calcMove( cube, 'R', dst );
                    calcMove( cube, 'd', dst );
                    calcMove( cube, 'r', dst );
                    calcMove( cube, 'd', dst );
                    calcMove( cube, 'f', dst );
                    calcMove( cube, 'D', dst );
                    calcMove( cube, 'F', dst );
                    side = 0;
                    continue;
                }

                //  LEFT
                if( cur < dst )
                {
                    //printf( "~~~~~~~~~~~~~~~~~~\t");
                    //printf( "Moving to left" );
                    //printf( "\t~~~~~~~~~~~~~~~~~~\n");
                    calcMove( cube, 'd', dst );
                    calcMove( cube, 'l', dst );
                    calcMove( cube, 'D', dst );
                    calcMove( cube, 'L', dst );
                    calcMove( cube, 'D', dst );
                    calcMove( cube, 'F', dst );
                    calcMove( cube, 'd', dst );
                    calcMove( cube, 'f', dst );
                    side = 0;
                    continue;
                }
                //  RIGHT
                else
                {
                    //printf( "~~~~~~~~~~~~~~~~~~\t");
                    //printf( "Moving to right" );
                    //printf( "\t~~~~~~~~~~~~~~~~~~\n");
                    calcMove( cube, 'D', dst );
                    calcMove( cube, 'R', dst );
                    calcMove( cube, 'd', dst );
                    calcMove( cube, 'r', dst );
                    calcMove( cube, 'd', dst );
                    calcMove( cube, 'f', dst );
                    calcMove( cube, 'D', dst );
                    calcMove( cube, 'F', dst );
                    side = 0;
                    continue;
                }
            }

            side++;
        }

        //  Layer 0
        layer = 1;
        for( side = 0; side < 4; side++ )
        {
            //  Check if edge is in right place
            if( *edges[1][side][0] == side )
            {
                other = *edges[1][side][1];
                dst = side - 1;
                dst = (dst == -1) ? 3 : dst;

                if( other == dst )
                {
                    //printf( "Edge on side %d in right place!\n", side );
                    continue;
                }
            }

            //  Check if edge is flipped
            if( *edges[1][side][1] == side )
            {
                other = *edges[1][side][0];
                dst = side - 1;
                dst = (dst == -1) ? 3 : dst;

                if( other == dst )
                {
                    //printf( "~~~~~~~~~~~~~~~~~~\t");
                    //printf( "Edge on side %d is flipped!", side );
                    //printf( "\t~~~~~~~~~~~~~~~~~~\n");
                    //  Move edge to layer 2
                    calcMove( cube, 'd', side );
                    calcMove( cube, 'l', side );
                    calcMove( cube, 'D', side );
                    calcMove( cube, 'L', side );
                    calcMove( cube, 'D', side );
                    calcMove( cube, 'F', side );
                    calcMove( cube, 'd', side );
                    calcMove( cube, 'f', side );
                }
            }

            //  Find not orange
            if( *edges[layer][side][1] != 5 && *edges[layer][side][0] != 5 )
            {
                //printf( "~~~~~~~~~~~~~~~~~~\t");
                //printf( "Edge on side %d needs to go to layer 2!", side );
                //printf( "\t~~~~~~~~~~~~~~~~~~\n");
                //  Move not orange out to layer 2
                calcMove( cube, 'd', side );
                calcMove( cube, 'l', side );
                calcMove( cube, 'D', side );
                calcMove( cube, 'L', side );
                calcMove( cube, 'D', side );
                calcMove( cube, 'F', side );
                calcMove( cube, 'd', side );
                calcMove( cube, 'f', side );
            }
        }
    }

    return 0;
}

int solveOrangeCross( int cube [6][3][3], int * edges [3][4][2]  )
{
    int count = 0;
    int opSide = -1;
    int side;

    while( count < 4 )
    {
        count = 0;
        //  Check if cross is in place
        for( side = 0; side < 4; side++ )
        {
            //printf( "Edge %d : %d\n", side, *edges[2][side][0] );
            if( *edges[2][side][0] == 5 )
            {
                count++;
            }
        }

        //  Display cube if count = 1
        if( count == 1 )
        {
            //printf( "THIS SHOULD NEVER HAPPEN!! FIRE!!\n" );
            //displayCube( cube );
            return -1;
        }

        //  Break if count 4
        if( count == 4 )
        {
            break;
        }

        //  Analyze and build cross
        //  Check if dot
        if( count == 0 )
        {
            calcMove( cube, 'f', 0 );
            calcMove( cube, 'l', 0 );
            calcMove( cube, 'd', 0 );
            calcMove( cube, 'L', 0 );
            calcMove( cube, 'D', 0 );
            calcMove( cube, 'F', 0 );
            calcMove( cube, 'f', 2 );
            calcMove( cube, 'l', 2 );
            calcMove( cube, 'd', 2 );
            calcMove( cube, 'L', 2 );
            calcMove( cube, 'D', 2 );
            calcMove( cube, 'l', 2 );
            calcMove( cube, 'd', 2 );
            calcMove( cube, 'L', 2 );
            calcMove( cube, 'D', 2 );
            calcMove( cube, 'F', 2 );
        }

        //  Check if 'L'
        if( count == 2 )
        {
            //  Find op side
            for( side = 0; side < 4; side++ )
            {
                //printf( "s1: %d, s2: %d\n", *edges[2][side][0],  *edges[2][ ( side + 1 ) % 4][0] );
                if( *edges[2][side][0] == 5 && *edges[2][ ( side + 1 ) % 4][0] == 5 )
                {
                    opSide = ( side + 3 ) % 4;
                }
            }

            //  Check if opSide found
            if( opSide != -1 )
            {
                //printf( "~~~~~~~~~~~~~~~~~~\t");
                //printf( "2) Op side found: %d", opSide );
                //printf( "\t~~~~~~~~~~~~~~~~~~\n");

                calcMove( cube, 'f', opSide );
                calcMove( cube, 'l', opSide );
                calcMove( cube, 'd', opSide );
                calcMove( cube, 'L', opSide );
                calcMove( cube, 'D', opSide );
                calcMove( cube, 'l', opSide );
                calcMove( cube, 'd', opSide );
                calcMove( cube, 'L', opSide );
                calcMove( cube, 'D', opSide );
                calcMove( cube, 'F', opSide );
            }
            //  Find straight opSide
            else
            {
                for( side = 0; side < 2; side++ )
                {
                    //printf( "s1: %d, s2: %d\n", *edges[2][side][0],  *edges[2][side + 2][0] );
                    if( *edges[2][side][0] == 5 && *edges[2][side + 2][0] == 5 )
                    {
                        opSide = side + 1;
                    }
                }

                //printf( "~~~~~~~~~~~~~~~~~~\t");
                //printf( "3) opSide found: %d", opSide );
                //printf( "\t~~~~~~~~~~~~~~~~~~\n");

                calcMove( cube, 'f', opSide );
                calcMove( cube, 'l', opSide );
                calcMove( cube, 'd', opSide );
                calcMove( cube, 'L', opSide );
                calcMove( cube, 'D', opSide );
                calcMove( cube, 'F', opSide );
            }

        }
    }

    return 0;
}

int permuteOrangeCross( int cube [6][3][3], int * edges [3][4][2] )
{
    int count = 0;
    int opSide = 0;
    int first = -1;
    int second = -1;
    int move = 0;
    int dst = -1;
    int side;

    while( count < 4 )
    {
        count = 0;
        //  Check if done
        for( side = 0; side < 4; side++ )
        {
            first = *edges[2][side][1];
            second = *edges[2][ ( side + 1 ) % 4 ][1] - 1;
            second = ( second == -1 ) ? 3 : second;

            if( first == second )
            {
                count++;
                opSide = side;
            }
        }

        //printf( "~~~~~~~~~ Count : %d ~~~~~~~~~\n", count );

        if( count == 4 || count == 3 )
        {
            break;
        }

        if( count == 0 )
        {
            calcMove( cube, 'l', 0 );
            calcMove( cube, 'd', 0 );
            calcMove( cube, 'L', 0 );
            calcMove( cube, 'd', 0 );
            calcMove( cube, 'l', 0 );
            calcMove( cube, 'd', 0 );
            calcMove( cube, 'd', 0 );
            calcMove( cube, 'L', 0 );
            calcMove( cube, 'd', 0 );
            calcMove( cube, 'l', 2 );
            calcMove( cube, 'd', 2 );
            calcMove( cube, 'L', 2 );
            calcMove( cube, 'd', 2 );
            calcMove( cube, 'l', 2 );
            calcMove( cube, 'd', 2 );
            calcMove( cube, 'd', 2 );
            calcMove( cube, 'L', 2 );
            calcMove( cube, 'd', 2 );
        }

        if( count == 1 )
        {
            opSide = ( opSide + 2 ) % 4;
            calcMove( cube, 'l', opSide );
            calcMove( cube, 'd', opSide );
            calcMove( cube, 'L', opSide );
            calcMove( cube, 'd', opSide );
            calcMove( cube, 'l', opSide );
            calcMove( cube, 'd', opSide );
            calcMove( cube, 'd', opSide );
            calcMove( cube, 'L', opSide );
            calcMove( cube, 'd', opSide );
        }
    }

    //  Place in right spot
    dst = *edges[2][0][1];
    if( dst == 1 )
    {
        calcMove( cube, 'd', 0 );
    }
    else if( dst == 2 )
    {
        calcMove( cube, 'd', 0 );
        calcMove( cube, 'd', 0 );
    }
    else if( dst == 3 )
    {
        calcMove( cube, 'D', 0 );
    }

    return 0;
}

int solveOrangeCorners( int cube [6][3][3], int * corners [2][4][3] )
{
    int count = 0;
    int opSide = 0;
    int first = -1;
    int second = -1;
    int third = -1;
    int move = 0;
    int dst = -1;
    int side;
    int face;

    while( count < 4 )
    {
        opSide = 0;
        count = 0;
        //  Check if done
        for( side = 0; side < 4; side++ )
        {

            //  Find dst
            for( face = 0; face < 3; face++ )
            {
                if( *corners[1][side][face] == 5 )
                {
                    dst = *corners[1][side][ ( face + 1 ) % 3 ];
                }
            }

            //printf( "side = %d\n", side );
            //printf( "dst = %d\n", dst );

            if( dst == side )
            {
                count++;
                opSide = side;
            }
        }

        //printf( "~~~~~~~~~ Count : %d ~~~~~~~~~\n", count );

        if( count == 4 )
        {
            break;
        }

        if( count == 1 || count == 0 )
        {
            opSide = ( opSide + 1 ) % 4;
            calcMove( cube, 'd', opSide );
            calcMove( cube, 'l', opSide );
            calcMove( cube, 'D', opSide );
            calcMove( cube, 'R', opSide );
            calcMove( cube, 'd', opSide );
            calcMove( cube, 'L', opSide );
            calcMove( cube, 'D', opSide );
            calcMove( cube, 'r', opSide );
        }
    }

    return 0;
}

int permuteOrangeCorners( int cube [6][3][3], int * corners [2][4][3] )
{
    int count = 0;
    int opSide = 0;
    int first = -1;
    int second = -1;
    int third = -1;
    int move = 0;
    int dst = -1;
    int stepCount = 0;
    int checkSide = -1;
    int side, i;

    while( count < 4 && stepCount < 6 )
    {
        opSide = 0;
        count = 0;
        //  Check if correct orientation
        //  Get corner to start algorithm at
        for( side = 3; side >= 0; side-- )
        {
            if( *corners[1][side][0] == 5 )
            {
                opSide = side;
                count++;
            }
        }

        //printf( "~~~~~~~~~ Count : %d ~~~~~~~~~\n", count );
        //printf( "Opside: %d\n", opSide );

        //  DONE
        if( count != 4 )
        {
            checkSide = ( opSide + 3 ) % 4;
            for( i = 0; i < 4 - count; i++ )
            {
                //printf( "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n" );
                //printf( "Working on side : %d of %d\n", i, 4 - count - 1 );
                //printf( "Check side %d: %d\n", checkSide, *corners[1][checkSide][0] );

                while( *corners[1][checkSide][0] != 5 )
                {
                    calcMove( cube, 'L', opSide );
                    calcMove( cube, 'u', opSide );
                    calcMove( cube, 'l', opSide );
                    calcMove( cube, 'U', opSide );
                    //printf( "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n" );
                }

                while( *corners[1][checkSide][0] == 5 && !orangeCornersDone( cube, corners ) )
                {
                    calcMove( cube, 'D', opSide );
                }
            }
        }
    }

    //  Place in right spot
    dst = *corners[1][0][1];
    //printf( "Dst: %d\n", dst );

    if( dst == 1 )
    {
        calcMove( cube, 'd', 0 );
    }
    else if( dst == 2 )
    {
        calcMove( cube, 'd', 0 );
        calcMove( cube, 'd', 0 );
    }
    else if( dst == 3 )
    {
        calcMove( cube, 'D', 0 );
    }

    if( !orangeCornersDone( cube, corners ) )
    {
        return -1;
    }

    return 0;
}

int orangeCornersDone( int cube [6][3][3], int * corners[2][4][3] )
{
    int count = 0;
    int side;
    for( side = 3; side >= 0; side-- )
    {
        if( *corners[1][side][0] == 5 )
        {
            count++;
        }
    }

    if( count == 4 )
    {
        return 1;
    }
    else
    {
        return 0;
    }
}
