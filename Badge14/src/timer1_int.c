/*********************************************************************
 *
 *      PIC32MX Timer1 API Example Code
 *
 *********************************************************************
 * FileName:        timer1_int.c
 * Dependencies:	plib.h
 *
 * Processor:       PIC32MX
 *
 * Compiler:        MPLAB XC32
 *                  MPLAB IDE
 * Company:         Microchip Technology Inc.
 *
 * Software License Agreement
 *
 * The software supplied herewith by Microchip Technology Incorporated
 * (the “Company”) for its PIC32MX Microcontroller is intended
 * and supplied to you, the Company’s customer, for use solely and
 * exclusively on Microchip Microcontroller products.
 * The software is owned by the Company and/or its supplier, and is
 * protected under applicable copyright laws. All rights are reserved.
 * Any use in violation of the foregoing restrictions may subject the
 * user to criminal sanctions under applicable laws, as well as to
 * civil liability for the breach of the terms and conditions of this
 * license.
 *
 * THIS SOFTWARE IS PROVIDED IN AN “AS IS” CONDITION. NO WARRANTIES,
 * WHETHER EXPRESS, IMPLIED OR STATUTORY, INCLUDING, BUT NOT LIMITED
 * TO, IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A
 * PARTICULAR PURPOSE APPLY TO THIS SOFTWARE. THE COMPANY SHALL NOT,
 * IN ANY CIRCUMSTANCES, BE LIABLE FOR SPECIAL, INCIDENTAL OR
 * CONSEQUENTIAL DAMAGES, FOR ANY REASON WHATSOEVER.
 *
 *********************************************************************
 * $Id: timer1_int.c 9390 2008-06-16 23:43:04Z rajbhartin $
 *
 * $Name:  $
 *********************************************************************
 * The purpose of this example code is to demonstrate the use of
 * peripheral library macros and functions supporting the PIC32MX
 * General Purpose Timer1.
 *
 * Platform: 	PIC32MX Starter Kit
 *
 * Features demonstrated:
 *      - Timer configuration
 *      - Interrupt configuration
 *      - ISR syntax
 *
 * Description:
 * 		- This example toggles PORTD<0> once every second
 *
 * Oscillator Configuration Bit Settings:
 * 		- Oscillator Selection Bits = 	Primary Osc w/PLL (XT+HS+EC+PLL)
 *		- Primary Oscillator Config = 	HS osc mode
 *		- PLL Input Divider			=	2x Divider
 *		- PLL Multiplier			=	18x Multiplier
 *
 * Notes:
 *		- Set PBCLK divisor = 1:8 to achieve slower timer clock
 *		- Timer1 clock 		= FOSC/PB_DIV/PRESCALE
 *							= 72E6/8/256 = 35.156KHz
 *		- To toggle led once every second, PR1 is loaded with 35156
 *
 ********************************************************************/
#include <plib.h>

// Configuration Bit settings
// SYSCLK = 80 MHz (8MHz Crystal/ FPLLIDIV * FPLLMUL / FPLLODIV)
// PBCLK = 40 MHz
// Primary Osc w/PLL (XT+,HS+,EC+PLL)
// WDT OFF
// Other options are don't care
//
//#pragma config FPLLMUL = MUL_20, FPLLIDIV = DIV_2, FPLLODIV = DIV_1, FWDTEN = OFF
//#pragma config POSCMOD = HS, FNOSC = PRIPLL, FPBDIV = DIV_8


// Let compile time pre-processor calculate the PR1 (period)
#define SYS_FREQ 			(20000000L)
//#define TOGGLES_PER_SEC		(38000*4)
#define TOGGLES_PER_SEC		38000
#define T2_TICK       		(SYS_FREQ/TOGGLES_PER_SEC)
#define T2_TICK_DIV2       	(SYS_FREQ/TOGGLES_PER_SEC/2)

int TimerInit(void)
{
    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    //STEP 1. Configure cache, wait states and peripheral bus clock
	// Configure the device for maximum performance but do not change the PBDIV
	// Given the options, this function will change the flash wait states, RAM
	// wait state and enable prefetch cache but will not change the PBDIV.
	// The PBDIV value is already set via the pragma FPBDIV option above..
//	SYSTEMConfig(SYS_FREQ, SYS_CFG_WAIT_STATES | SYS_CFG_PCACHE);

    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    // STEP 2. configure Timer 1 using internal clock, 1:256 prescale

    //OpenTimer2(T2_ON | T2_SOURCE_INT | T2_PS_1_256, T2_TICK);
    OpenTimer2(T2_ON | T2_SOURCE_INT, T2_TICK);

    // set up the timer interrupt with a priority of 2
    ConfigIntTimer2(T2_INT_ON | T2_INT_PRIOR_2);

    // enable multi-vector interrupts
    INTEnableSystemMultiVectoredInt();

    // shake sensor debug pin
    TRISBbits.TRISB8 = 0;

    IEC0bits.INT4IE=0; // disable this interrupt

    // AN6/RPC0/RC0 == IR recv
    // config as input
    TRISCbits.TRISC0 = 1;

    SYSKEY = 0x0;
    SYSKEY = 0xAA996655;
    SYSKEY = 0x556699AA;

    CFGCONbits.IOLOCK = 0; // unlock configuration

    INT4Rbits.INT4R = 0b0110; // map RPC0 

    CFGCONbits.IOLOCK = 1; // relock configuration

    SYSKEY = 0x0;

    INTCONbits.INT4EP=0; // edge polarity  FALLING EDGE
    IPC4bits.INT4IP=1; // interrupt priority
    IPC4bits.INT4IS=1; // interrupt sub priority
    IEC0bits.INT4IE=1; // enable this interrupt

    IEC0bits.T2IE=1;
}

// EXT4 int enabled when IR recv is 0 otherwise 1+
unsigned char G_IRrecv = 0;
unsigned char G_IRsend = 0;
unsigned char G_IRsendVal = 0;
unsigned char G_IRrecvVal = 0;
unsigned char G_bitCnt = 0;
unsigned char G_firstHalf = 0;
unsigned char G_lastHalf = 0;
unsigned char G_halfCount = 0;


void __ISR(_TIMER_2_VECTOR, IPL2SOFT) Timer2Handler(void)
{
   static unsigned char sendOne = 0;
   static unsigned char sendZero = 0;
   static unsigned char lowHalf = 1;
   static unsigned char highHalf = 1;

   // clear the interrupt flag
   mT2ClearIntFlag();

   // LATBbits.LATB8 == DBG pin shake sensor near LCD pins
   // each timer interrupt is 1/38khz
   if (G_IRrecv) {
	if (G_bitCnt > 7) {
	   G_IRrecv = 0;
	   G_bitCnt = 0;
	   G_halfCount = 0;
	}
	else {
	   G_halfCount++;
	   // 32 interrupts for each half of bit send
	   // for 64 total per bit
	   if (G_halfCount == 16) G_firstHalf = !PORTCbits.RC0; 
	   if (G_halfCount == 48) G_lastHalf = !PORTCbits.RC0;
	   if (G_halfCount > 63) {
	      G_IRrecvVal <<= 1 ;
	      G_IRrecvVal |= G_lastHalf; // should check proper manchester low->high, high->low
	      LATBbits.LATB8 = G_lastHalf; // DBG output
	      G_bitCnt++;
	      G_halfCount = 0;
	   }
	}
	return;
   }

   if (G_IRsend) {
        // 3 sections for IR send:
        // -init and looping vars
        // -send a zero
        // -send a one

        // break byte into bits to send
	// init, and looping. is the one or zero is done?
	if ((sendOne == 0) && (sendZero == 0)) {
	   if (G_bitCnt < 8) {
		// high order bit first
		sendOne = (G_IRsendVal & (0b10000000 >> G_bitCnt));
		sendZero = (sendOne == 0);
		G_bitCnt++;
	   }
	   else {
		G_IRsend = 0;
		G_bitCnt = 0;

	   }
	}


      // ;    A "1" in Manchester goes from Low-High over the bit period
      // ;    cycle. During the pulsing period, the carrier frequency should
      // ;    be 38kHz, and the duty cycle of the carrier should be about 1/4.
      // ;------------------------------------------------------------------

      //      ; LOW HALF 889us
      // 32 cycles off

      //      ; HIGH HALF (889us)
      //      ; Toggle 7us on, 21us off for 38kHz for the duration
      //      ; Pulsing 7 on, 21 off yields a 1/4 time duty cycle for carrier.
      //      ; Has 32 pulses of these periods 32*28us
      //      ;

      // each timer interrupt is 1/38khz
      if (sendOne) {
	 G_halfCount++;

	 if (lowHalf) {
	    // this is off for 32 counts
	    LATCbits.LATC1 = 0;

	    if (G_halfCount > 31) {
	      lowHalf = 0;
	      G_halfCount = 0;
	    }
	 }
	 else { 
	   // this is on for 7us (1/4 duty cycle) in each 
	   // 32 count 1/38khz interrupt

	   // high half
	   // 4 assignments is about 1us
	   // so 7us is about 4 * 7 assignments

	   LATCbits.LATC1 = 1;
	   LATCbits.LATC1 = 1;
	   LATCbits.LATC1 = 1;
	   LATCbits.LATC1 = 1;

	   LATCbits.LATC1 = 1;
	   LATCbits.LATC1 = 1;
	   LATCbits.LATC1 = 1;
	   LATCbits.LATC1 = 1;

	   LATCbits.LATC1 = 1;
	   LATCbits.LATC1 = 1;
	   LATCbits.LATC1 = 1;
	   LATCbits.LATC1 = 1;

	   LATCbits.LATC1 = 1;
	   LATCbits.LATC1 = 1;
	   LATCbits.LATC1 = 1;
	   LATCbits.LATC1 = 1;

	   LATCbits.LATC1 = 1;
	   LATCbits.LATC1 = 1;
	   LATCbits.LATC1 = 1;
	   LATCbits.LATC1 = 1;

	   LATCbits.LATC1 = 1;
	   LATCbits.LATC1 = 1;
	   LATCbits.LATC1 = 1;
	   LATCbits.LATC1 = 1;

	   LATCbits.LATC1 = 1;
	   LATCbits.LATC1 = 1;
	   LATCbits.LATC1 = 1;
	   LATCbits.LATC1 = 1;

	   LATCbits.LATC1 = 0;

	    if (G_halfCount > 31) {
	      lowHalf = 1;
	      G_halfCount = 0;
	      sendOne = 0;
	    }
	 }
      }

      // ;------------------------------------------------------------------
      // ;  SendZero
      // ;
      // ;            A "0" in Manchester goes from High-Low over the bit period.
      // ;    The high period is a series of pulses of duty cycle 1/4 at a
      // ;    frequency of 36kHz.  This implementation yields 35.71kHz.
      // ;------------------------------------------------------------------
      // 
      //      ; HIGH HALF (889us)
      //      ; Toggle 7us on, 21us off for 35.7kHz (~36kHz) for the duration
      //      ; Pulsing 7 on, 21 off yields a 1/4 time duty cycle for carrier.
      //      ; Has 32 pulses of these periods 32*28us = 896us (~889us)
      //
      if (sendZero) {
	 G_halfCount++;
	 if (highHalf) {
	   // high half
	   // 4 assignments is about 1us
	   // so 7us is about 4 * 7 assignments

	   LATCbits.LATC1 = 1;
	   LATCbits.LATC1 = 1;
	   LATCbits.LATC1 = 1;
	   LATCbits.LATC1 = 1;

	   LATCbits.LATC1 = 1;
	   LATCbits.LATC1 = 1;
	   LATCbits.LATC1 = 1;
	   LATCbits.LATC1 = 1;

	   LATCbits.LATC1 = 1;
	   LATCbits.LATC1 = 1;
	   LATCbits.LATC1 = 1;
	   LATCbits.LATC1 = 1;

	   LATCbits.LATC1 = 1;
	   LATCbits.LATC1 = 1;
	   LATCbits.LATC1 = 1;
	   LATCbits.LATC1 = 1;

	   LATCbits.LATC1 = 1;
	   LATCbits.LATC1 = 1;
	   LATCbits.LATC1 = 1;
	   LATCbits.LATC1 = 1;

	   LATCbits.LATC1 = 1;
	   LATCbits.LATC1 = 1;
	   LATCbits.LATC1 = 1;
	   LATCbits.LATC1 = 1;

	   LATCbits.LATC1 = 1;
	   LATCbits.LATC1 = 1;
	   LATCbits.LATC1 = 1;
	   LATCbits.LATC1 = 1;

	   LATCbits.LATC1 = 0;

	   if (G_halfCount > 31) {
	     highHalf = 0;
	     G_halfCount = 0;
	   }
	 }
	 else {
	   //      ; LOW HALF (889us = 889 instr cycles)
	   LATCbits.LATC1 = 0;

	   if (G_halfCount > 31) {
	      highHalf = 1;
	      G_halfCount = 0;
	      sendZero = 0;
	   }
	 }
      }
   }
}

void __ISR( _EXTERNAL_4_VECTOR, ipl1) Int4Interrupt(void)
{ 
   // clear flag
   IFS0bits.INT4IF = 0;

   // if not sending, signal in receive
   if ((G_IRsend == 0) & (G_IRrecv == 0)) {
	G_IRrecv = 1;

	// firstHalf was zero, this is one, so bit is 1
	G_firstHalf = 0; // inverted from what it was
	G_halfCount = 32;
	G_IRrecvVal = 0;

   }
}
