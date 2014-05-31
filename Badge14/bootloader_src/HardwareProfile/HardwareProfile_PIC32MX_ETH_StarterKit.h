// Copyright (c) 2002-2010,  Microchip Technology Inc.
//
// Microchip licenses this software to you solely for use with Microchip
// products.  The software is owned by Microchip and its licensors, and
// is protected under applicable copyright laws.  All rights reserved.
//
// SOFTWARE IS PROVIDED "AS IS."  MICROCHIP EXPRESSLY DISCLAIMS ANY
// WARRANTY OF ANY KIND, WHETHER EXPRESS OR IMPLIED, INCLUDING BUT
// NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY, FITNESS
// FOR A PARTICULAR PURPOSE, OR NON-INFRINGEMENT.  IN NO EVENT SHALL
// MICROCHIP BE LIABLE FOR ANY INCIDENTAL, SPECIAL, INDIRECT OR
// CONSEQUENTIAL DAMAGES, LOST PROFITS OR LOST DATA, HARM TO YOUR
// EQUIPMENT, COST OF PROCUREMENT OF SUBSTITUTE GOODS, TECHNOLOGY
// OR SERVICES, ANY CLAIMS BY THIRD PARTIES (INCLUDING BUT NOT LIMITED
// TO ANY DEFENSE THEREOF), ANY CLAIMS FOR INDEMNITY OR CONTRIBUTION,
// OR OTHER SIMILAR COSTS.
//
// To the fullest extent allowed by law, Microchip and its licensors
// liability shall not exceed the amount of fees, if any, that you
// have paid directly to Microchip to use this software.
//
// MICROCHIP PROVIDES THIS SOFTWARE CONDITIONALLY UPON YOUR ACCEPTANCE
// OF THESE TERMS.	


#ifndef __HARDWAREPROFILE_PIC32MX_ETH_STARTER_KIT_H__
#define __HARDWAREPROFILE_PIC32MX_ETH_STARTER_KIT_H__



 	/*******************************************************************/
    /******** USB stack hardware selection options *********************/
    /*******************************************************************/
    //This section is the set of definitions required by the MCHPFSUSB
    //  framework.  These definitions tell the firmware what mode it is
    //  running in, and where it can find the results to some information
    //  that the stack needs.
    //These definitions are required by every application developed with
    //  this revision of the MCHPFSUSB framework.  Please review each
    //  option carefully and determine which options are desired/required
    //  for your application.

    //#define USE_SELF_POWER_SENSE_IO
    #define tris_self_power     TRISAbits.TRISA2    // Input
    #define self_power          1

    //#define USE_USB_BUS_SENSE_IO
    #define tris_usb_bus_sense  TRISBbits.TRISB5    // Input
    #define USB_BUS_SENSE       1 

    /*******************************************************************/
    /*******************************************************************/
    /*******************************************************************/
    /******** Application specific definitions *************************/
    /*******************************************************************/
    /*******************************************************************/
    /*******************************************************************/

    /** Board definition ***********************************************/
    //These defintions will tell the main() function which board is
    //  currently selected.  This will allow the application to add
    //  the correct configuration bits as well use the correct
    //  initialization functions for the board.  These defitions are only
    //  required for this demo.  They are not required in
    //  final application design.


	
	#define mLED              LATDbits.LATD2
	// Blinks LED 1 on USB Starter kit
	#define BlinkLED() (mLED = ((ReadCoreTimer() & 0x0800000) != 0))
/*	#define InitLED() do{	\
							AD1PCFG = 0; \
							TRISDbits.TRISD2 = 0;  \
						}while(0)*/	
						
	#define InitLED() do{	\
							TRISDbits.TRISD2 = 0;  \
							TRISDbits.TRISD1 = 0;  \
							TRISDbits.TRISD0 = 0;  \
							LATDbits.LATD0 = 0; LATDbits.LATD1 = 0; LATDbits.LATD2 = 0;\
						}while(0)					
	
	// Switch S3 on USB Starter Kit.
	#define ReadSwitchStatus() (PORTReadBits(IOPORT_D, BIT_13) & BIT_13)
	


	// Error indication.	
	#define Error()   do{LATDbits.LATD0 = 1; LATDbits.LATD1 = 1; LATDbits.LATD2 = 1;} while(0);

	// External National PHY configuration
	#define	PHY_RMII				// external PHY runs in RMII mode
	#define	PHY_CONFIG_ALTERNATE	// alternate configuration used
	#define	PHY_ADDRESS			0x1	// the address of the National DP83848 PHY


#endif
