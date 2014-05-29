/********************************************************************
 FileName:     	HardwareProfile - PIC18F87J94 PIM.h
 Dependencies:	See INCLUDES section
 Processor:	    PIC18 USB Microcontrollers
 Hardware:      PIC18F87J94 PIM
 Compiler:  	Microchip C18
 Company:		Microchip Technology, Inc.

 Software License Agreement:

 The software supplied herewith by Microchip Technology Incorporated
 (the "Company") for its PIC� Microcontroller is intended and
 supplied to you, the Company's customer, for use solely and
 exclusively on Microchip PIC Microcontroller products. The
 software is owned by the Company and/or its supplier, and is
 protected under applicable copyright laws. All rights are reserved.
 Any use in violation of the foregoing restrictions may subject the
 user to criminal sanctions under applicable laws, as well as to
 civil liability for the breach of the terms and conditions of this
 license.

 THIS SOFTWARE IS PROVIDED IN AN "AS IS" CONDITION. NO WARRANTIES,
 WHETHER EXPRESS, IMPLIED OR STATUTORY, INCLUDING, BUT NOT LIMITED
 TO, IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A
 PARTICULAR PURPOSE APPLY TO THIS SOFTWARE. THE COMPANY SHALL NOT,
 IN ANY CIRCUMSTANCES, BE LIABLE FOR SPECIAL, INCIDENTAL OR
 CONSEQUENTIAL DAMAGES, FOR ANY REASON WHATSOEVER.
********************************************************************/

#ifndef HARDWARE_PROFILE_PIC18F87J94_PIM_H
#define HARDWARE_PROFILE_PIC18F87J94_PIM_H

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

    /** USB ************************************************************/
    //The PIC18F87J94 FS USB Plug-In Module supports the USE_USB_BUS_SENSE_IO
    //feature.  The USE_SELF_POWER_SENSE_IO feature is not implemented on the
    //circuit board, so the USE_SELF_POWER_SENSE_IO define should always be
    //commented for this hardware platform.

    //#define USE_SELF_POWER_SENSE_IO
    #define tris_self_power     TRISAbits.TRISA2    // Input
    #if defined(USE_SELF_POWER_SENSE_IO)
    #define self_power          PORTAbits.RA2
    #else
    #define self_power          1
    #endif

    //#define USE_USB_BUS_SENSE_IO		//JP1 must be in R-U position to use this feature on this board	
    #define tris_usb_bus_sense  TRISBbits.TRISB5    // Input
    #if defined(USE_USB_BUS_SENSE_IO)
    #define USB_BUS_SENSE       PORTBbits.RB5
    #else
    #define USB_BUS_SENSE       1
    #endif


   
    //Uncomment this to make the output HEX of this project 
    //   to be able to be bootloaded using the HID bootloader
	#define PROGRAMMABLE_WITH_USB_HID_BOOTLOADER		

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
    //  the correct configuration bits as wells use the correct
    //  initialization functions for the board.  These defitions are only
    //  required in the stack provided demos.  They are not required in
    //  final application design.
    #define DEMO_BOARD PIC18F87J94_PIM
    #define PIC18F87J94_PIM
    #define PIC18F97J94_FAMILY
    #define CLOCK_FREQ 64000000
    #define GetSystemClock() CLOCK_FREQ
  
    /** LED ************************************************************/
    #define mInitAllLEDs()      {LATE &= 0xFC; TRISE &= 0xFC; LATD &= 0xF3; TRISD &= 0xF3;}
    
    #define mLED_1              LATEbits.LATE0
    #define mLED_2              LATEbits.LATE1
    #define mLED_3              LATDbits.LATD2
    #define mLED_4              LATDbits.LATD3
    
    #define mGetLED_1()         mLED_1
    #define mGetLED_2()         mLED_2
    #define mGetLED_3()         mLED_3
    #define mGetLED_4()         mLED_4

    #define mLED_1_On()         mLED_1 = 1;
    #define mLED_2_On()         mLED_2 = 1;
    #define mLED_3_On()         mLED_3 = 1;
    #define mLED_4_On()         mLED_4 = 1;
    
    #define mLED_1_Off()        mLED_1 = 0;
    #define mLED_2_Off()        mLED_2 = 0;
    #define mLED_3_Off()        mLED_3 = 0;
    #define mLED_4_Off()        mLED_4 = 0;
    
    #define mLED_1_Toggle()     mLED_1 = !mLED_1;
    #define mLED_2_Toggle()     mLED_2 = !mLED_2;
    #define mLED_3_Toggle()     mLED_3 = !mLED_3;
    #define mLED_4_Toggle()     mLED_4 = !mLED_4;
    
    /** SWITCH *********************************************************/
    #define mInitAllSwitches()  TRISBbits.TRISB4 = 1;
    #define mInitSwitch2()      TRISBbits.TRISB4 = 1;
    #define mInitSwitch3()      TRISBbits.TRISB4 = 1;
    #define sw2                 PORTBbits.RB4
    #define sw3                 PORTBbits.RB4

    /** RS 232 lines ****************************************************/
    #define UART_TRISTx   TRISCbits.TRISC6
    #define UART_TRISRx   TRISCbits.TRISC7
    #define UART_Tx       PORTCbits.RC6
    #define UART_Rx       PORTCbits.RC7
    #define UART_ENABLE	  RCSTAbits.SPEN

    /** Register/Bit Aliases ********************************************/
    #define TXREG         TXREG1
    #define RCREG         RCREG1
    #define RCSTA         RCSTA1
    #define RCSTAbits     RCSTA1bits
    #define TXSTA         TXSTA1
    #define TXSTAbits     TXSTA1bits
    #define SPBRG         SPBRG1
    #define SPBRGH        SPBRGH1
    #define BAUDCON       BAUDCON1
    #define RCIF          RC1IF
   
    /** I/O pin definitions ********************************************/
    #define INPUT_PIN 1
    #define OUTPUT_PIN 0

    //These definitions are only relevant if the respective functions are enabled
    //in the usb_config.h file.
    //Make sure these definitions match the GPIO pins being used for your hardware
    //setup.
    #define UART_DTS PORTBbits.RB0
    #define UART_DTR LATDbits.LATD7
    #define UART_RTS LATBbits.LATB2
    #define UART_CTS PORTBbits.RB1
    
    #define mInitRTSPin() {TRISBbits.TRISB2 = 0;}   //Configure RTS as a digital output.  
    #define mInitCTSPin() {TRISBbits.TRISB1 = 1;}   //Configure CTS as a digital input.  (Make sure pin is digital if ANxx functions is present on the pin)
    #define mInitDTSPin() {TRISBbits.TRISB0 = 1;}   //Configure DTS as a digital input.  (Make sure pin is digital if ANxx functions is present on the pin)
    #define mInitDTRPin() {TRISDbits.TRISD7 = 0;}   //Configure DTR as a digital output.
    

#endif  //HARDWARE_PROFILE_PIC18F87J94_PIM_H
