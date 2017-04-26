/*****************************************************************************
*
* Copyright (C) 2013 - 2016 Texas Instruments Incorporated - http://www.ti.com/
*
* Redistribution and use in source and binary forms, with or without
* modification, are permitted provided that the following conditions
* are met:
*
* * Redistributions of source code must retain the above copyright
*   notice, this list of conditions and the following disclaimer.
*
* * Redistributions in binary form must reproduce the above copyright
*   notice, this list of conditions and the following disclaimer in the
*   documentation and/or other materials provided with the
*   distribution.
*
* * Neither the name of Texas Instruments Incorporated nor the names of
*   its contributors may be used to endorse or promote products derived
*   from this software without specific prior written permission.
*
* THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
* "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
* LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
* A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
* OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
* SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
* LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
* DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
* THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
* (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
* OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*
****************************************************************************
*
* MSP432 blink.c template - P1.0 port toggle
*
* Classic coding
*
****************************************************************************/

#include "msp.h"
#include "blink.h"
//#include "source/motorDriver.h"
#include "motorDriver.h"
#include "driverlib.h"
#include "msp432p401r.h"
#include "msp_compatibility.h"
#include "solHelper.h"

#include <stdint.h>
#include <stdio.h>
#include <stdbool.h>

//Function Prototypes
void setup();
void SMCLKSetUp(const uint8_t);
void UARTA2Init(int);

void UARTA2SendByte(uint8_t);
void UARTA2SendString(unsigned char*);

void CreateArray();

//Global Variables
uint16_t rxA2;
int counter=0;

uint8_t rx_buffer[54];
uint16_t bufferIndex = 0;
bool data_rx_done = 0;
bool data_array_created = 0;
int ***data;
size_t xlen = 6;
size_t ylen = 3;
size_t zlen = 3;
int kocLen = 0;
int godMode = 0;
int seqDone = 0;

int cubeData [6][3][3] = {
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

int startSolving = 0;
int mot = 0;
int passindx[6] = {0, 0, 0, 0, 0, 0};

//timer function bs
int count = 0;
int tatparya = 0;
int step = -1;

void main(void)
{
    //  Init
    initMotors();
    initLEDs();

    //  UART Setup
    setup();

    printf("Starting\n");

    //  RUN TESTS
    testRobot();
    //  testUART();
    //  testKoc();
}

void createSolArray()
{
    int i;
    printf("Starting to create the solution array\n");

    //  Set array elements
    int buff_count=0;
    for (i=1; i <= kocLen; ++i)
    {
        solArray[i-1] = rx_buffer[ i ];
    }

    arLength = kocLen;

    printf("Array created\n");
}

void createArray()
{
    int i, j, k;
    printf("Starting to create the array\n");

    //  Allocate array space
    // if ((data = alloc_data(xlen, ylen, zlen)) == NULL)
    // {
    //     printf("FAILURE IN MALLOCING THE ARRAY");
    //     //return 0;
    // }

    printf("Finally the array is here\n");

    //  Set array elements
    int buff_count=0;
    for (i=0; i < xlen; ++i)
    {
        for (j=0; j < ylen; ++j)
        {
            for (k=0; k < zlen; ++k)
            {
                cubeData[i][j][k] = rx_buffer[buff_count];
                buff_count++;
                printf("%d, ", cubeData[i][j][k]);
            }
            printf("\n");
        }
        printf("\n");
    }

    printf("Array created\n");
}

void buttonpressed(){
    int del;
    int ar = 0;
    int d;
    int blah;

    printf( "Button pressed!\n Step count: %d\n\n", step );

    if( step == -1 )
    {
        printf( "testing cube!\n" );
        for( blah = 0; blah < 6; blah++ )
        {
            rotato_potato(blah, -1, &passindx[blah], 1);
            //for( del = 0; del < 5000; del++ );
            rotato_potato(blah, 1, &passindx[blah], 1);
            //for( del = 0; del < 5000; del++ );
        }

        step++;
    }
    else if( step == 0 )
    {

        //scramble

        step++;
    }
    else if( step == 1 )
    {
        step++;
        testSolution();
    }
    else if( step == 2 )
    {
        step++;
        outputMotorSteps();
    }


    //printf("Rotating motor: %d\n", mot);
    //rotato_potato(mot, 1, &passindx[mot],1);
    //mot += 1;
    //mot = mot % 6;

}

void outputMotorSteps()
{
    int ar = 0;
    int direction = 0;

    for( ar = 0; ar < arLength; ar++ )
    {
        if( solArray[ar] > 5 )
        {
            direction = -1;
        }
        else
        {
            direction = 1;
        }

        printf( "Rotating %d in direction %d\n", solArray[ar]%6, direction);
        rotato_potato(solArray[ar] % 6, direction, &passindx[ solArray[ar] % 6 ],1);

        //for( del = 0; del < 2500; del++ );
    }
}

void testRobot()
{
    int ig = 0;

    while(1)
    {
        printf( "Testing Robot!! %d\n", ++ig );
        //rotato_potato(1, 1, &passindx[1],1);
        MAP_PCM_gotoLPM0();

        //  Wait for button press
        while(tatparya == 0){}
        tatparya = 0;

        buttonpressed();
    }
}

void testKoc()
{
    while( 1 )
    {
        //  Check if seq received
        if( seqDone )
        {
            seqDone = 0;

            //  Get solution steps from rx_buf
            createSolArray();

            //  Solve Cube
            printf("Generated solution, starting solving!\n");

            //  Wait for button press
            while( !startSolving )
            {
                //printf( "Starting to solve : %d\n", startSolving );
            }

            //  Output solution steps on motor
            outputMotorSteps();
        }
    }
}

void testUART()
{
    while( 1 )
    {
        //  Check if cube received
        if(bufferIndex == 55)
        {
            // Cube Data Received from Pi
            printf("Cube orientation data received\n");
            data_rx_done = 1;
            bufferIndex = 0;
        }

        if (data_rx_done)
        {
            // Array finally created
            createArray();

            data_rx_done = 0;

            printf("Starting to generate solution!\n");

            //  Generate Solution
            solveCube( cubeData );

            //  Check solution
            printf( "Sol Array Len: %d\n", arLength );

            //  Solve Cube
            printf("Generated solution, starting solving!\n");

            //  Wait for button press
            while( !startSolving )
            {
                //printf( "Starting to solve : %d\n", startSolving );
            }

            //  Output solution steps
            outputMotorSteps();
        }
    }
}

void initMotors()
{
    //  Motor Port Initializations
    P10DIR |= 0xFF;
    P4DIR |= 0xFF;
    P7DIR |= 0xFF;
    P8DIR |= 0xFF;
    P9DIR |= 0xFF;
}

void initLEDs()
{
    //led initialization
    P2DIR |= 0xFF; // Comment for dev
    /*
     *  LED 1
     *  P2OUT = 0x10
     *  LED 2
     *  P2OUT = 0x20
     *  LED 3
     *  P2OUT = 0x40
     *  LED 4
     *  P2OUT = 0x80
     *
     */
}

// UART2 interrupt service routine
void eUSCIA2IsrHandler(void) {
    // RX interrupt
    printf( "Rcvd data!!" );
    if (UCA2IFG & UCRXIFG)
    {
        if( bufferIndex == 0 )
        {
            //  Check if God mode or regular mode
            if( (int) (rxA2 - '0') == 0 )
            {
                //  God mode
                godMode = 1;
                seqDone = 0;
            }
            else
            {
                //  Teaching mode
                godMode = 0;
            }
        }

        else
        {
            if( godMode )
            {
                rxA2 = UCA2RXBUF;
                rx_buffer[bufferIndex] = rxA2-'0';

                //  Check if seq received
                if( rx_buffer[ bufferIndex ] == -1 )
                {
                    seqDone = 1;
                    kocLen = bufferIndex - 2;
                }

                printf( "|   INDEX = %d : %d \n", bufferIndex, rx_buffer[ bufferIndex ] );
                bufferIndex++;
            }
            else
            {
                rxA2 = UCA2RXBUF;
                rx_buffer[bufferIndex] = rxA2-'0';

                printf( "|   INDEX = %d : %d \n", bufferIndex, rx_buffer[ bufferIndex ] );
                bufferIndex++;
            }

        }
    }
}

/* GPIO ISR */
void PORT1_IRQHandler(void)
{

    printf( "Button Pressed!\n" );

    startSolving = !startSolving;

    uint32_t status = MAP_GPIO_getEnabledInterruptStatus(GPIO_PORT_P1);
    MAP_GPIO_clearInterruptFlag(GPIO_PORT_P1,status);

    if (GPIO_PIN1 & status)
    {
        tatparya = 1;
    }
}

/* Timer32 ISR */
void T32_INT1_IRQHandler(void)
{
    //printf( "Fired timer interrupt\n" );
    popo = 1;
    MAP_Timer32_clearInterruptFlag(TIMER32_BASE);
    MAP_GPIO_setOutputLowOnPin(GPIO_PORT_P1, GPIO_PIN0);
    MAP_GPIO_enableInterrupt(GPIO_PORT_P1, GPIO_PIN1);
}

void setup() {

    //  watch dog timer
    WDTCTL = WDTPW | WDTHOLD;

    /* Setting MCLK to REFO at 128Khz for LF mode */
    MAP_CS_setReferenceOscillatorFrequency(CS_REFO_128KHZ);
    MAP_CS_initClockSignal(CS_MCLK, CS_REFOCLK_SELECT, CS_CLOCK_DIVIDER_1);
    MAP_PCM_setPowerState(PCM_AM_LF_VCORE0);

    /* Configuring GPIO */
    MAP_GPIO_setAsOutputPin(GPIO_PORT_P1, GPIO_PIN0);
    MAP_GPIO_setOutputLowOnPin(GPIO_PORT_P1, GPIO_PIN0);
    MAP_GPIO_setAsInputPinWithPullUpResistor(GPIO_PORT_P1, GPIO_PIN1);
    MAP_GPIO_clearInterruptFlag(GPIO_PORT_P1, GPIO_PIN1);
    MAP_GPIO_enableInterrupt(GPIO_PORT_P1, GPIO_PIN1);

    /* Configuring Timer32 to 128000 (1s) of MCLK in periodic mode */
    MAP_Timer32_initModule(TIMER32_BASE, TIMER32_PRESCALER_256, TIMER32_32BIT,
    TIMER32_PERIODIC_MODE);

    /* Enabling interrupts */
    MAP_Interrupt_enableInterrupt(INT_PORT1);
    MAP_Interrupt_enableInterrupt(INT_T32_INT1);
    MAP_Interrupt_enableMaster();

    //  UART stuff
    WDTCTL = WDTPW | WDTHOLD;       // Stop WDT

    SMCLKSetUp(24);                 //set system clock

    //setup for both uart ports
    UARTA2Init(115200);
}

// Set a system clock SMCLK of 3,6,12,24, and 48 (MHz)
void SMCLKSetUp(const uint8_t freq) {
    CS->KEY = 0x695A;      // Unlock Clock Select Register
    CS->CTL0 = 0;
    // Frequency in MHz
    switch(freq) {
        case 3:
            CS->CTL0 = CS_CTL0_DCORSEL_1;
            break;
        case 6:
            CS->CTL0 = CS_CTL0_DCORSEL_2;
            break;
        case 12:
            CS->CTL0 = CS_CTL0_DCORSEL_3;
            break;
        case 24:
            CS->CTL0 = CS_CTL0_DCORSEL_4;
            break;
        case 48:
            CS->CTL0 = CS_CTL0_DCORSEL_5;
            break;
        default:
            CS->CTL0 = CS_CTL0_DCORSEL_1;
            break;
    }
    // ACLK = REFO, SMCLK = MCLK = DCO
    CS->CTL1 = CS_CTL1_SELA_3 | CS_CTL1_SELS_3 | CS_CTL1_SELM_3;
    CS->KEY = 0;              // Lock Clock Select Register
}

// UARTA2 Initialization
void UARTA2Init(int baud_rate) {
    // 3.2 RX, 3.3 TX
    P3SEL0 |= (BIT3 | BIT2);
    P3SEL1 &= ~(BIT3 | BIT2);

    NVIC->ISER[0] = 1 << ((INT_EUSCIA2 - 16) & 31);    // Enable EUSCIA2 interrupt in NVIC module

    // Configuring UARTA2
    UCA2CTLW0 |= UCSWRST;
    UCA2CTLW0 |= UCSSEL__SMCLK;             // Put eUSCI in reset
    // Baud Rate calculation
    switch(baud_rate) {
        case 115200:
            UCA2BR0 = 13;                       // 24000000/16/115200 -> 13.0283
            UCA2BR1 = 0x00;                     // Fractional portion = 0.0283
            UCA2MCTLW = 0x0000 | UCOS16;        // User's Guide Table 21-4: UCBRSx = 0x00
            break;                              // UCBRFx = int((13.0283-13)*16) = 0
        case 9600:
            UCA2BR0 = 156;                          // 24000000/16/9600 -> 156.25
            UCA2BR1 = 0x00;                         // Fractional portion = 0.25
            UCA2MCTLW = 0x4400 | UCOS16 | 0x0040;   // User's Guide Table 21-4: UCBRSx = 0x44
            break;                                  // UCBRFx = int ( (156.25-156)*16) = 4
        default:
            UCA2BR0 = 13;                       // 24000000/16/115200 -> 13.0283
            UCA2BR1 = 0x00;                     // Fractional portion = 0.0283
            UCA2MCTLW = 0x0000 | UCOS16;        // User's Guide Table 21-4: UCBRSx = 0x00
            break;                              // UCBRFx = int((13.0283-13)*16) = 0
    }

    UCA2CTLW0 &= ~UCSWRST;                  // Initialize eUSCI
    UCA2IE |= UCRXIE;                       // Enable USCI_A2 RX interrupt
}

// UARTA2 Sending 1 string
void UARTA2SendString(unsigned char* string) {
    while(*string) {
        UARTA2SendByte(*string++);
    }
}

// UARTA2 Sending 1 byte
void UARTA2SendByte(uint8_t byte) {
    while(!(UCA2IFG & UCTXIFG));
    UCA2TXBUF = byte;
}
