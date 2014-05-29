/********************************************************************
 FileName:     	HardwareProfile - PIC24FJ256DA210 Development Board.h
 Dependencies:  See INCLUDES section
 Processor:     PIC24FJ256GB110
 Hardware:      PIC24FJ256GB110 PIM
 Compiler:      Microchip C30
 Company:       Microchip Technology, Inc.

 Software License Agreement:

 The software supplied herewith by Microchip Technology Incorporated
 (the �Company�) for its PIC� Microcontroller is intended and
 supplied to you, the Company�s customer, for use solely and
 exclusively on Microchip PIC Microcontroller products. The
 software is owned by the Company and/or its supplier, and is
 protected under applicable copyright laws. All rights are reserved.
 Any use in violation of the foregoing restrictions may subject the
 user to criminal sanctions under applicable laws, as well as to
 civil liability for the breach of the terms and conditions of this
 license.

 THIS SOFTWARE IS PROVIDED IN AN �AS IS� CONDITION. NO WARRANTIES,
 WHETHER EXPRESS, IMPLIED OR STATUTORY, INCLUDING, BUT NOT LIMITED
 TO, IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A
 PARTICULAR PURPOSE APPLY TO THIS SOFTWARE. THE COMPANY SHALL NOT,
 IN ANY CIRCUMSTANCES, BE LIABLE FOR SPECIAL, INCIDENTAL OR
 CONSEQUENTIAL DAMAGES, FOR ANY REASON WHATSOEVER.

********************************************************************
 File Description:

 Change History:
  Rev   Date         Description
  ?.?   09/15/2008   Initial revision
********************************************************************/

#ifndef HARDWARE_PROFILE_PIC24FJ256DA210_DEV_BOARD_H
#define HARDWARE_PROFILE_PIC24FJ256DA210_DEV_BOARD_H

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
    #define USB_BUS_SENSE       U1OTGSTATbits.SESVD // Special considerations required if using SESVD for this purpose.  See documentation.
   
    //Uncomment this to make the output HEX of this project 
    //   to be able to be bootloaded using the HID bootloader
    //#define PROGRAMMABLE_WITH_USB_HID_BOOTLOADER	

    //If the application is going to be used with the HID bootloader
    //  then this will provide a function for the application to 
    //  enter the bootloader from the application (optional)
    #if defined(PROGRAMMABLE_WITH_USB_HID_BOOTLOADER)
        #define EnterBootloader() __asm__("goto 0x400")
    #endif   

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
    #define DEMO_BOARD PIC24FJ256DA210_DEV_BOARD
    #define PIC24FJ256DA210_DEV_BOARD
    #define CLOCK_FREQ 32000000
    #define GetSystemClock() CLOCK_FREQ
    #define GetPeripheralClock() CLOCK_FREQ
    
    /** LED ************************************************************/
    #define mInitAllLEDs()      LATE &= 0xFDFF; TRISE &= 0xFDFF; LATG &= 0xFEFF; TRISG &= 0xFEFF;
    
    #define mLED_1              LATGbits.LATG8
    #define mLED_2              LATEbits.LATE9
    #define mLED_3              LATGbits.LATG8
    #define mLED_4              LATEbits.LATE9

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
    #define mInitSwitch2()      {TRISBbits.TRISB5=1; ANSBbits.ANSB5 = 0;}
    #define mInitSwitch3()      {TRISBbits.TRISB5=1; ANSBbits.ANSB5 = 0;}
    #define mInitAllSwitches()  mInitSwitch2();mInitSwitch3();
    #define sw2                 PORTBbits.RB5
    #define sw3                 PORTBbits.RB5

    /** UART ***********************************************************/
    #define BAUDRATE2       57600UL
    #define BRG_DIV2        4 
    #define BRGH2           1 

    /** I/O pin definitions ********************************************/
    #define INPUT_PIN 1
    #define OUTPUT_PIN 0

    //These definitions are only relevant if the respective functions are enabled
    //in the usb_config.h file.
    //Make sure these definitions match the GPIO pins being used for your hardware
    //setup.  Replace X and Y values with appropriate values based on your board.
    #define UART_DTS PORTXbits.RXY
    #define UART_DTR LATXbits.LATXY
    #define UART_RTS LATXbits.LATXY
    #define UART_CTS PORTXbits.RXY
    
    #define mInitRTSPin() {TRISXbits.TRISXY = 0;}   //Configure RTS as a digital output.  
    #define mInitCTSPin() {TRISXbits.TRISXY = 1;}   //Configure CTS as a digital input.  (Make sure pin is digital if ANxx functions is present on the pin)
    #define mInitDTSPin() {TRISXbits.TRISXY = 1;}   //Configure DTS as a digital input.  (Make sure pin is digital if ANxx functions is present on the pin)
    #define mInitDTRPin() {TRISXbits.TRISXY = 0;}   //Configure DTR as a digital output.
#endif  //HARDWARE_PROFILE_PIC24FJ256DA210_DEV_BOARD_H
