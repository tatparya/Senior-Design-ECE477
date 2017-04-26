#include "msp.h"
#include "driverlib.h"
#include "blink.h"

// change this to the number of steps on your motor
#define pin1 P4.6
#define pin2 P1.5
#define pin3 P4.3
// create an instance of the stepper class, specifying
// the number of steps of the motor and the pins it's
// attached to
//Stepper stepper(STEPS, 4, 5, 6, 7);
char motors[2][4] = {{0xa0, 0x60, 0x50, 0x90},{0x0a, 0x06, 0x05, 0x09}};

/*
 * side: which side you are rotation
 * direction: left or right 1 or -1
 * indx: just pass this variable dont bitch about it, set to 0 at beginning
 * amount: how many turns do you want
 */

void testMotors( )
{
    int ig = 0;
    int ij = 0;
    int passindx[6] = {0, 0, 0, 0, 0, 0};
    int dummy = 0;

    while(1)
    {
        P1OUT ^= 0xFF;                           /* Toggle P1.0 */

        for(ig = 0; ig <6; ig++){
            //rotato_potato(ig, 1, &passindx[ig],1);
            printf( "Rotating motor: %d\n", ig );

            printf( "Motor %d index : %d\n", ig, passindx[ig] );

            dummy = 0;
            for(ij = 0; ij<1000; ij++)
            {
                dummy += 1;
            }
        }

    }
}

void customDelay()
{
    int i = 0;
    MAP_GPIO_disableInterrupt(GPIO_PORT_P1, GPIO_PIN1);
    MAP_GPIO_setOutputHighOnPin(GPIO_PORT_P1, GPIO_PIN0);

    MAP_Timer32_setCount(TIMER32_BASE,180);
    MAP_Timer32_enableInterrupt(TIMER32_BASE);
    MAP_Timer32_startTimer(TIMER32_BASE, true);
    //while(popo == 0){}
    popo = 0;
    //printf( "Custom delay\n" );
}

void rotato_potato ( int side, int direction, int * indx, int amount )
{
    int stepCount = 0;
    int i = 0;
    int k = 0;
    int dummy = 0;
    if(side == 0 || side == 1 || side == 3 || side == 5|| side == 4)
    {
        direction = direction * -1;
    }

    if( side == 0 || side == 4 || side == 3 )
    {
        stepCount = 51;
    }
    else if( side == 1 || side == 2 )
    {
        stepCount = 51;
    }
    else
    {
        stepCount = 51;
    }

    //printf( "Rotating! step count: %d\n", stepCount );

    //  Rotate cube
    while( amount > 0 )
    {
        //  200 steps total (360 deg), 50 steps for 90 deg
        for( i = 0; i < stepCount; i++ )
        {
            //  Update index
            *indx += direction;
            *indx = * indx % 4;

            if( *indx == -1 )
            {
                *indx = 3;
            }

            switch( side )
            {
                case 0:
                    //mtr1
                    P8OUT = motors[0][*indx];
                    break;
                case 1:
                    //mtr2
                    P4OUT = motors[0][*indx];
                    break;
                case 2:
                    //mtr3
                    P7OUT = motors[1][*indx];
                    break;
                case 3:
                    //mtr4
                    P9OUT = motors[0][*indx];
                    break;
                case 4:
                    //mtr5
                    P10OUT = motors[1][*indx];
                    break;
                case 5:
                    //mtr6
                    P7OUT = motors[0][*indx];
                    break;
                default:
                    break;
            }

            customDelay();
            while( popo == 0){}
            popo = 0;

            //printf( "Step: %d\n", i );

        }
        amount--;
    }//end while

    P4OUT = 0x00;
    P8OUT = 0x00;
    P7OUT = 0x00;
    P10OUT = 0x00;
    P9OUT = 0x00;

    /*
    P2OUT = 0x00;
    P4OUT = 0x00;
    P5OUT = 0x00;
    P6OUT = 0x00;
    P10OUT = 0x00;
    */

    //printf( "Done Rotating\n" );

}//end function
