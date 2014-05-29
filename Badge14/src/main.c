/** I N C L U D E S **********************************************************/
#include "./USB/usb.h"
#include "./USB/usb_function_cdc.h"
#include "Sound.h"
#include "HardwareProfile.h"
#include "GenericTypeDefs.h"
#include "./Common/Compiler.h"
#include "USB/usb_config.h"
#include "USB/usb_device.h"
#include "USB/usb.h"
#include "HardwareProfile.h"
#include "badge14.h"

#if defined (__C30__) || defined(__C32__) || defined __XC16__
    #include "uart2.h"
#endif

/** CONFIGURATION **************************************************/
#if defined(__32MX460F512L__) || defined(__32MX795F512L__)
        #pragma config UPLLEN   = ON        // USB PLL Enabled
// PEB    #pragma config FPLLMUL  = MUL_15        // PLL Multiplier
        #pragma config FPLLMUL  = MUL_20        // PLL Multiplier
// PEB        #pragma config UPLLIDIV = DIV_2         // USB PLL Input Divider
        #pragma config UPLLIDIV = DIV_1         // USB PLL Input Divider
        #pragma config FPLLIDIV = DIV_2         // PLL Input Divider
// PEB        #pragma config FPLLODIV = DIV_1         // PLL Output Divider
        #pragma config FPLLODIV = DIV_2         // PLL Output Divider
        #pragma config FPBDIV   = DIV_1         // Peripheral Clock divisor
        #pragma config FWDTEN   = OFF           // Watchdog Timer
        #pragma config WDTPS    = PS1           // Watchdog Timer Postscale
        #pragma config FCKSM    = CSDCMD        // Clock Switching & Fail Safe Clock Monitor
        #pragma config OSCIOFNC = OFF           // CLKO Enable
// PEB       #pragma config POSCMOD  = HS            // Primary Oscillator
        #pragma config POSCMOD  = XT            // Primary Oscillator
        #pragma config IESO     = OFF           // Internal/External Switch-over
        #pragma config FSOSCEN  = ON            // Secondary Oscillator Enable (KLO was off)
        #pragma config FNOSC    = PRIPLL        // Oscillator Selection
        #pragma config CP       = OFF           // Code Protect
        #pragma config BWP      = OFF           // Boot Flash Write Protect
        #pragma config PWP      = OFF           // Program Flash Write Protect
        #pragma config ICESEL   = ICS_PGx2      // ICE/ICD Comm Channel Select
        #pragma config JTAGEN = OFF             // JTAG Enable (JTAG Disabled)
#endif



/** V A R I A B L E S ********************************************************/
#if defined(__18CXX)
#pragma udata
#endif

unsigned char    NextUSBOut;
char USB_In_Buffer[CDC_DATA_IN_EP_SIZE];
char USB_Out_Buffer[CDC_DATA_OUT_EP_SIZE];

USB_HANDLE  lastTransmission;
unsigned int play_count = 0x8001;
//BOOL stringPrinted;

/** P R I V A T E  P R O T O T Y P E S ***************************************/
static void InitializeSystem(void);
void ProcessIO(void);
void USBDeviceTasks(void);
void YourHighPriorityISRCode();
void YourLowPriorityISRCode();
void USBCBSendResume(void);
void BlinkUSBStatus(void);
void UserInit(void);
void putcUSART(char c);
unsigned char getcUSART ();

/** VECTOR REMAPPING ***********************************************/

/******************************************************************************
 * - - - - - - - - - - - ENTRY POINT - - - - - - - - - - - - -
 *****************************************************************************/
#define GAME_MODE
int main(void)
{
    struct BadgeState *game_state;
    char sample_i = 0, sample_val = 0;

    InitializeSystem();

    #if defined(USB_INTERRUPT)
        USBDeviceAttach();
    #endif

    #if defined(GAME_MODE)
        game_state = Init_Game();
    #endif
    while(1)
    {
        if((play_count & 0x0fff) && play_count & 0x8000)
        {
            //LATBbits.LATB2 = 1;
            //LATBbits.LATB3 = 1;

            getNextSample( &sample_i, &sample_val);
            LATAbits.LATA9 = sample_val;
            play_count++;
        }
        else
            play_count = play_count & 0x8000;

        #if defined(USB_POLLING)
		// Check bus status and service USB interrupts.
        USBDeviceTasks(); // Interrupt or polling method.  If using polling, must call
        				  // this function periodically.  This function will take care
        				  // of processing and responding to SETUP transactions 
        				  // (such as during the enumeration process when you first
        				  // plug in).  USB hosts require that USB devices should accept
        				  // and process SETUP packets in a timely fashion.  Therefore,
        				  // when using polling, this function should be called 
        				  // regularly (such as once every 1.8ms or faster** [see 
        				  // inline code comments in usb_device.c for explanation when
        				  // "or faster" applies])  In most cases, the USBDeviceTasks() 
        				  // function does not take very long to execute (ex: <100 
        				  // instruction cycles) before it returns.
        #endif
    				  

		// Application-specific tasks.
		// Application related code may be added here, or in the ProcessIO() function.
        ProcessIO();
    #if defined(GAME_MODE)
         Run_Game(&game_state);
        //welcome(game_state);
    #endif
    }//end while
}//end main


/********************************************************************
 * Function:        static void InitializeSystem(void)
 * Overview:        InitializeSystem is a centralize initialization
 *                  routine. All required USB initialization routines
 *                  are called from here.
 *
 *                  User application initialization routine should
 *                  also be called from here.                  
 *******************************************************************/
static void InitializeSystem(void)
{
        ANSELA = 0x00;
        ANSELB = 0x00;
        ANSELC = 0x00;

        TRISA = 0; 
        LATA = 0; 

        TRISB = 0; 
        LATB = 0; 

        TRISC = 0; 
        LATC = 0; 

        LCDReset();

//	The USB specifications require that USB peripheral devices must never source
//	current onto the Vbus pin.  Additionally, USB peripherals should not source
//	current on D+ or D- when the host/hub is not actively powering the Vbus line.
//	When designing a self powered (as opposed to bus powered) USB peripheral
//	device, the firmware should make sure not to turn on the USB module and D+
//	or D- pull up resistor unless Vbus is actively powered.  Therefore, the
//	firmware needs some means to detect when Vbus is being powered by the host.
//	A 5V tolerant I/O pin can be connected to Vbus (through a resistor), and
// 	can be used to detect when Vbus is high (host actively powering), or low
//	(host is shut down or otherwise not supplying power).  The USB firmware
// 	can then periodically poll this I/O pin to know when it is okay to turn on
//	the USB module/D+/D- pull up resistor.  When designing a purely bus powered
//	peripheral device, it is not possible to source current on D+ or D- when the
//	host is not actively providing power on Vbus. Therefore, implementing this
//	bus sense feature is optional.  This firmware can be made to use this bus
//	sense feature by making sure "USE_USB_BUS_SENSE_IO" has been defined in the
//	HardwareProfile.h file.    
    #if defined(USE_USB_BUS_SENSE_IO)
        tris_usb_bus_sense = INPUT_PIN; // See HardwareProfile.h
    #endif
    
//	If the host PC sends a GetStatus (device) request, the firmware must respond
//	and let the host know if the USB peripheral device is currently bus powered
//	or self powered.  See chapter 9 in the official USB specifications for details
//	regarding this request.  If the peripheral device is capable of being both
//	self and bus powered, it should not return a hard coded value for this request.
//	Instead, firmware should check if it is currently self or bus powered, and
//	respond accordingly.  If the hardware has been configured like demonstrated
//	on the PICDEM FS USB Demo Board, an I/O pin can be polled to determine the
//	currently selected power source.  On the PICDEM FS USB Demo Board, "RA2" 
//	is used for	this purpose.  If using this feature, make sure "USE_SELF_POWER_SENSE_IO"
//	has been defined in HardwareProfile - (platform).h, and that an appropriate I/O pin 
//  has been mapped	to it.
    #if defined(USE_SELF_POWER_SENSE_IO)
    tris_self_power = INPUT_PIN;	// See HardwareProfile.h
    #endif
    
    UserInit();

    USBDeviceInit();	//usb_device.c.  Initializes USB module SFRs and firmware
    					//variables to known states.
}//end InitializeSystem



/******************************************************************************
 * Function:        void UserInit(void)
 *
 * Overview:        This routine should take care of all of the demo code
 *                  initialization that is required.
 *****************************************************************************/
void UserInit(void)
{
	unsigned char i;

    {
        unsigned char i;

        for (i=0; i<CDC_DATA_IN_EP_SIZE; i++) {
            USB_In_Buffer[i] = 0;
            USB_Out_Buffer[i] = 0;
        }
    }

    // RA8 == front/back sensor
    // config as input
    TRISAbits.TRISA8 = 1;
    // pull up on
    CNPUAbits.CNPUA8 = 1;

    // RB8 == shake sensor
    // config as input
    TRISBbits.TRISB8 = 1;
    // pull up off
    CNPUBbits.CNPUB8 = 0;

    mInitAllLEDs();
}//end UserInit


#if defined(__C30__) || defined(__C32__) || defined __XC16__
    #define mDataRdyUSART() UART2IsPressed()
    #define mTxRdyUSART()   U2STAbits.TRMT
#endif

/******************************************************************************
 * Function:        void mySetLineCodingHandler(void)
 *
 * PreCondition:    USB_CDC_SET_LINE_CODING_HANDLER is defined
 * Overview:        This function gets called when a SetLineCoding command
 *                  is sent on the bus.  This function will evaluate the request
 *                  and determine if the application should update the baudrate
 *                  or not.
 *****************************************************************************/
#if defined(USB_CDC_SET_LINE_CODING_HANDLER)
void mySetLineCodingHandler(void)
{
    //If the request is not in a valid range
    if(cdc_notice.GetLineCoding.dwDTERate.Val > 115200)
    {
        //NOTE: There are two ways that an unsupported baud rate could be
        //handled.  The first is just to ignore the request and don't change
        //the values.  That is what is currently implemented in this function.
        //The second possible method is to stall the STATUS stage of the request.
        //STALLing the STATUS stage will cause an exception to be thrown in the 
        //requesting application.  Some programs, like HyperTerminal, handle the
        //exception properly and give a pop-up box indicating that the request
        //settings are not valid.  Any application that does not handle the
        //exception correctly will likely crash when this requiest fails.  For
        //the sake of example the code required to STALL the status stage of the
        //request is provided below.  It has been left out so that this demo
        //does not cause applications without the required exception handling
        //to crash.
        //---------------------------------------
        //USBStallEndpoint(0,1);
    }
    else
    {
        //Update the baudrate info in the CDC driver
        CDCSetBaudRate(cdc_notice.GetLineCoding.dwDTERate.Val);
        
    }
}
#endif

/******************************************************************************
 * Function:        void putcUSART(char c)
 * Output:          unsigned char c - character to received on the UART
 *
 * Overview:        Print the input character to the UART
 *****************************************************************************/
unsigned char getcUSART ()
{
	char  c;

    #if defined(__C30__) || defined(__C32__) || defined __XC16__
        c = UART2GetChar();
    #endif

	return c;
}


#define INPUT_PIN 1
#define OUTPUT_PIN 0

// use port (not LAT/latch) for input
# define LOWERSLIDER_LEFT  PORTCbits.PORTC5
# define LOWERSLIDER_RIGHT PORTCbits.PORTC4
# define RIGHTSLIDER_UPPER PORTCbits.PORTC3
# define RIGHTSLIDER_LOWER PORTCbits.PORTC2

// Pull down register
// CNPD

// Pull up register
// CNPUC

// yummy globals
char G_lower_slider_left=0;

void doCapTouch1() {
   register char s0, s1, s2, s3, s4, s5, s6, s7;

   G_lower_slider_left = 0;

   // pulls up off
   CNPUCbits.CNPUC5 = 0;
   // set as output
   TRISCbits.TRISC5 = 0;
   // zero output. according to datasheet also writes latch bit
   PORTCbits.RC5  = 0;

   // config as input
   TRISCbits.TRISC5 = 1;
   // pull up on
   CNPUCbits.CNPUC5 = 1;
   // see when cap is charged

   s0 = PORTCbits.RC5;
   s1 = PORTCbits.RC5;
   s2 = PORTCbits.RC5;
   s3 = PORTCbits.RC5;
   s4 = PORTCbits.RC5;
   s5 = PORTCbits.RC5;
   s6 = PORTCbits.RC5;
   s7 = PORTCbits.RC5;

   G_lower_slider_left = s0 + s1 + s2 + s3 + s4 + s5 + s6 + s7;
}

char G_lower_slider_right=0;

char G_side_slider_right = 0;
char G_side_slider_left = 0;

void doCapTouch2() {
   register char s0, s1, s2, s3, s4, s5, s6, s7;

   G_lower_slider_right = 0;

   // pulls up off
   CNPUCbits.CNPUC4 = 0;
   // set as output
   TRISCbits.TRISC4 = 0;
   // zero output. according to datasheet also writes latch bit
   PORTCbits.RC4  = 0;

   // config as input
   TRISCbits.TRISC4 = 1;
   // pull up on
   CNPUCbits.CNPUC4 = 1;

   // wait for cap to charge
   s0 = PORTCbits.RC4;
   s1 = PORTCbits.RC4;
   s2 = PORTCbits.RC4;
   s3 = PORTCbits.RC4;
   s4 = PORTCbits.RC4;
   s5 = PORTCbits.RC4;
   s6 = PORTCbits.RC4;
   s7 = PORTCbits.RC4;

   G_lower_slider_right = s0 + s1 + s2 + s3 + s4 + s5 + s6 + s7;

}

/********************************************************************
 * Function:        void ProcessIO(void)
 *
 * Overview:        This function is a place holder for other user
 *                  routines. It is a mixture of both USB and
 *                  non-USB tasks.
 *******************************************************************/

extern int gDelay;
extern char gContrast;

//
void getTouchUL();
void getTouchUR();

//right Upper and lower
void  getTouchRU();
void  getTouchRL();

static unsigned char shake=0;
static unsigned char frontBack=0;

const char hextab[]={"0123456789ABCDEF"};

void ProcessIO(void)
{   
    //Blink the LEDs according to the USB device status
    //BlinkUSBStatus();

    //C short circuit makes this work
    if(PORTBbits.RB13 && button_pressed < 250)
    {
        button_pressed += 1;
    }
    else if (!PORTBbits.RB13)
    {
        button_cnt = 0;
        button_pressed = 0;
    }
    
    getTouchUL();
    getTouchUR();

    getTouchRU();
    getTouchRL();

    frontBack = PORTAbits.RA8 ;
    shake = PORTBbits.RB8 ;

    // User Application USB tasks
    if((USBDeviceState < CONFIGURED_STATE)||(USBSuspendControl==1)) return;

    {
        unsigned char nread=0, i;

        nread = getsUSBUSART(USB_In_Buffer,64); //until the buffer is free.
        if(nread > 0) {
            /* speaker */
            //LATAbits.LATA9 = !LATAbits.LATA9;
            if (USB_In_Buffer[0] == 92)
                play_count ^= 0x8000;

            play_count |= 0x0001;
            /* serial byte led */
            //LATBbits.LATB15 = !LATBbits.LATB15;
            //LATBbits.LATB1 = 1;//!LATBbits.LATB1;

            /* contrast byte */
            if (USB_In_Buffer[0] == '-') {
               char printme[8];

               gContrast--;

               printme[0] = 48 +  (unsigned char)gContrast / 100;
               printme[1] = 48 + ((unsigned char)gContrast % 100) / 10;
               printme[2] = 48 + ((unsigned char)gContrast % 100) % 10;
               printme[3] = 0;
               LCDString(printme);

               LCDInit(); //Init the LCD

               USB_In_Buffer[0] = 0;
               nread == 0;
            }

            if ((USB_In_Buffer[0] == '=') || (USB_In_Buffer[0] == '+')) {
               char printme[8];

               gContrast++;

               printme[0] = 48 +  (unsigned char)gContrast / 100;
               printme[1] = 48 + ((unsigned char)gContrast % 100) / 10;
               printme[2] = 48 + ((unsigned char)gContrast % 100) % 10;
               printme[3] = 0;
               LCDString(printme);

               LCDInit(); //Init the LCD

               USB_In_Buffer[0] = 0;
               nread == 0;
            }

            // special character that are not echoed to LCD
            if ((USB_In_Buffer[0] == 127) 
             |  (USB_In_Buffer[0] == 27)
             |  (USB_In_Buffer[0] == '[')) {
                void LCDLogo();

                /* backspace == clear screen */
                if (USB_In_Buffer[0] == 127) LCDClear();

                /* backlight byte */
                if (USB_In_Buffer[0] == 27) LATBbits.LATB7 = !LATBbits.LATB7;

                /* hackrva logo */
                if (USB_In_Buffer[0] == '[') LCDLogo();

               USB_In_Buffer[0] = 0;
               nread == 0;
            }

            if (USB_In_Buffer[0] == ',') {
                unsigned char printme[8];
                void gotoXY(int x, int y);

                char left = G_side_slider_left;
                char right = G_side_slider_right;

                gotoXY(0, 40);
                printme[0] = 'L';
                printme[1] = 48 +  (unsigned char)left / 100;
                printme[2] = 48 + ((unsigned char)left % 100) / 10;
                printme[3] = 48 + ((unsigned char)left % 100) % 10;
                printme[4] = 32;
                printme[5] = 0;
                LCDString(printme);

                for (i=0; printme[i] !=0 ; i++)
                    USB_Out_Buffer[NextUSBOut++] = printme[i];

                USB_Out_Buffer[NextUSBOut++] = ' ';

                gotoXY(42, 40);
                printme[0] = 'R';
                printme[1] = 48 +  (unsigned char)right / 100;
                printme[2] = 48 + ((unsigned char)right % 100) / 10;
                printme[3] = 48 + ((unsigned char)right % 100) % 10;
                printme[4] = 32;
                printme[5] = 0;
                LCDString(printme);

                for (i=0; printme[i] !=0 ; i++)
                    USB_Out_Buffer[NextUSBOut++] = printme[i];

                USB_Out_Buffer[NextUSBOut++] = '\r';
                USB_Out_Buffer[NextUSBOut++] = '\n';

                USB_In_Buffer[0] = 0;
                nread == 0;
            }

            if (USB_In_Buffer[0] == '.') {
               USB_In_Buffer[0] = 0;
               nread == 0;
            }

            if (USB_In_Buffer[0] == '/') {
                unsigned char printme[16];
                void gotoXY(int x, int y);
		int setupRTCC(void);


		// shake sensor
                gotoXY(0, 41);
                printme[0] = 'S';
                printme[1] = 48 +  (unsigned char)shake / 100;
                printme[2] = 48 + ((unsigned char)shake % 100) / 10;
                printme[3] = 48 + ((unsigned char)shake % 100) % 10;
                printme[4] = 32;
                printme[5] = 0;
                LCDString(printme);

                for (i=0; printme[i] !=0 ; i++)
                    USB_Out_Buffer[NextUSBOut++] = printme[i];

                USB_Out_Buffer[NextUSBOut++] = ' ';

		// front sensor
                gotoXY(42, 41);
                printme[0] = 'F';
                printme[1] = 48 +  (unsigned char)frontBack / 100;
                printme[2] = 48 + ((unsigned char)frontBack % 100) / 10;
                printme[3] = 48 + ((unsigned char)frontBack % 100) % 10;
                printme[4] = 32;
                printme[5] = 0;
                LCDString(printme);

                for (i=0; printme[i] !=0 ; i++)
                    USB_Out_Buffer[NextUSBOut++] = printme[i];

		// secondary clock running status
               	printme[0] = hextab[(OSCCON >> 28) & 0xF];
               	printme[1] = hextab[(OSCCON >> 24) & 0xF];
               	printme[2] = hextab[(OSCCON >> 20) & 0xF];
               	printme[3] = hextab[(OSCCON >> 16) & 0xF];
               	printme[4] = hextab[(OSCCON >> 12) & 0xF];
               	printme[5] = hextab[(OSCCON >>  8) & 0xF];
               	printme[6] = hextab[(OSCCON >>  4) & 0xF];
               	printme[7] = hextab[(OSCCON      ) & 0xF];
               	printme[7] = 0;
               	LCDString(printme);

                for (i=0; printme[i] !=0 ; i++)
                    USB_Out_Buffer[NextUSBOut++] = printme[i];


               	printme[0] = 'R';
               	printme[1] = 'T';
               	printme[2] = 'C';
               	printme[3] = 'C';
               	printme[4] = ':';
               	printme[5] = setupRTCC();
               	printme[6] = 0;
               	LCDString(printme);
                for (i=0; printme[i] !=0 ; i++)
                    USB_Out_Buffer[NextUSBOut++] = printme[i];


                USB_Out_Buffer[NextUSBOut++] = '\r';
                USB_Out_Buffer[NextUSBOut++] = '\n';

                USB_In_Buffer[0] = 0;
                nread == 0;
            }

            // IR xmit
            if (USB_In_Buffer[0] == '>') {
                LATCbits.LATC1 = !LATCbits.LATC1;

                USB_In_Buffer[0] = 0;
                nread == 0;
            }

//  IR recv
#define IR_RECV PORTCbits.RC1

	    // print anything not handled above
            if (USB_In_Buffer[0] != 0)  {
               char printme[32];

               for (i=0; i<nread; i++)
                    printme[i] = USB_In_Buffer[i];

               printme[i] = 0;

               LCDString(printme);

               LCDInit(); //Init the LCD
            }

            for (i=0; i<nread; i++,NextUSBOut++) {
                USB_Out_Buffer[NextUSBOut] = USB_In_Buffer[i];
            }

        }

        // echo back to USB
        if ((USBUSARTIsTxTrfReady()) && (NextUSBOut > 0)) {
            putUSBUSART(&USB_Out_Buffer[0], NextUSBOut);
		    NextUSBOut = 0;
        }
    }

    CDCTxService();
}//end ProcessIO

/********************************************************************
 * Function:        void BlinkUSBStatus(void)
 *
 * Overview:        BlinkUSBStatus turns on and off LEDs 
 *                  corresponding to the USB device state.
 *
 * Note:            mLED macros can be found in HardwareProfile.h
 *                  USBDeviceState is declared and updated in
 *                  usb_device.c.
 *******************************************************************/
void BlinkUSBStatus(void)
{
    static WORD led_count=0;
    
    if(led_count == 0)led_count = 10000U;
    led_count--;

    #define mLED_Both_Off()         {mLED_1_Off();mLED_2_Off();}
    #define mLED_Both_On()          {mLED_1_On();mLED_2_On();}
    #define mLED_Only_1_On()        {mLED_1_On();mLED_2_Off();}
    #define mLED_Only_2_On()        {mLED_1_Off();mLED_2_On();}

    if(USBSuspendControl == 1)
    {
        if(led_count==0)
        {
            mLED_1_On();
            mLED_2_On();

        }//end if
    }
    else
    {
        if(USBDeviceState == DETACHED_STATE)
        {
            mLED_Both_Off();
        }
        else if(USBDeviceState == ATTACHED_STATE)
        {
            mLED_Both_On();
        }
        else if(USBDeviceState == POWERED_STATE)
        {
            mLED_Only_1_On();
        }
        else if(USBDeviceState == DEFAULT_STATE)
        {
            mLED_Only_2_On();
        }
        else if(USBDeviceState == ADDRESS_STATE)
        {
            if(led_count == 0)
            {
                mLED_1_Toggle();
                mLED_2_Off();
            }//end if
        }
        else if(USBDeviceState == CONFIGURED_STATE)
        {
            if(led_count==0)
            {
                mLED_1_Toggle();
                if(mGetLED_1())
                {
                    mLED_2_Off();
                }
                else
                {
                    mLED_2_On();
                }
            }//end if
        }//end if(...)
    }//end if(UCONbits.SUSPND...)

}//end BlinkUSBStatus


// ******************************************************************************************************
// ************** USB Callback Functions ****************************************************************
// ******************************************************************************************************
// The USB firmware stack will call the callback functions USBCBxxx() in response to certain USB related
// events.  For example, if the host PC is powering down, it will stop sending out Start of Frame (SOF)
// packets to your device.  In response to this, all USB devices are supposed to decrease their power
// consumption from the USB Vbus to <2.5mA* each.  The USB module detects this condition (which according
// to the USB specifications is 3+ms of no bus activity/SOF packets) and then calls the USBCBSuspend()
// function.  You should modify these callback functions to take appropriate actions for each of these
// conditions.  For example, in the USBCBSuspend(), you may wish to add code that will decrease power
// consumption from Vbus to <2.5mA (such as by clock switching, turning off LEDs, putting the
// microcontroller to sleep, etc.).  Then, in the USBCBWakeFromSuspend() function, you may then wish to
// add code that undoes the power saving things done in the USBCBSuspend() function.

// The USBCBSendResume() function is special, in that the USB stack will not automatically call this
// function.  This function is meant to be called from the application firmware instead.  See the
// additional comments near the function.

// Note *: The "usb_20.pdf" specs indicate 500uA or 2.5mA, depending upon device classification. However,
// the USB-IF has officially issued an ECN (engineering change notice) changing this to 2.5mA for all 
// devices.  Make sure to re-download the latest specifications to get all of the newest ECNs.

/******************************************************************************
 * Function:        void USBCBSuspend(void)
 * Overview:        Call back that is invoked when a USB suspend is detected
 *****************************************************************************/
void USBCBSuspend(void)
{
	//Example power saving code.  Insert appropriate code here for the desired
	//application behavior.  If the microcontroller will be put to sleep, a
	//process similar to that shown below may be used:
	
	//ConfigureIOPinsForLowPower();
	//SaveStateOfAllInterruptEnableBits();
	//DisableAllInterruptEnableBits();
	//EnableOnlyTheInterruptsWhichWillBeUsedToWakeTheMicro();	//should enable at least USBActivityIF as a wake source
	//Sleep();
	//RestoreStateOfAllPreviouslySavedInterruptEnableBits();	//Preferrably, this should be done in the USBCBWakeFromSuspend() function instead.
	//RestoreIOPinsToNormal();									//Preferrably, this should be done in the USBCBWakeFromSuspend() function instead.

	//IMPORTANT NOTE: Do not clear the USBActivityIF (ACTVIF) bit here.  This bit is 
	//cleared inside the usb_device.c file.  Clearing USBActivityIF here will cause 
	//things to not work as intended.	
	 
}


/******************************************************************************
 * Function:        void USBCBWakeFromSuspend(void)
 * Overview:        The host may put USB peripheral devices in low power
 *					suspend mode (by "sending" 3+ms of idle).  Once in suspend
 *					mode, the host may wake the device back up by sending non-
 *					idle state signalling.
 *					
 *					This call back is invoked when a wakeup from USB suspend 
 *					is detected.
 *****************************************************************************/
void USBCBWakeFromSuspend(void)
{
	// If clock switching or other power savings measures were taken when
	// executing the USBCBSuspend() function, now would be a good time to
	// switch back to normal full power run mode conditions.  The host allows
	// 10+ milliseconds of wakeup time, after which the device must be 
	// fully back to normal, and capable of receiving and processing USB
	// packets.  In order to do this, the USB module must receive proper
	// clocking (IE: 48MHz clock must be available to SIE for full speed USB
	// operation).  
	// Make sure the selected oscillator settings are consistent with USB 
    // operation before returning from this function.
}

/********************************************************************
 * Function:        void USBCB_SOF_Handler(void)
 * Overview:        The USB host sends out a SOF packet to full-speed
 *                  devices every 1 ms. This interrupt may be useful
 *                  for isochronous pipes. End designers should
 *                  implement callback routine as necessary.
 *******************************************************************/
void USBCB_SOF_Handler(void)
{
    // No need to clear UIRbits.SOFIF to 0 here.
    // Callback caller is already doing that.
}

/*******************************************************************
 * Function:        void USBCBErrorHandler(void)
 * Overview:        The purpose of this callback is mainly for
 *                  debugging during development. Check UEIR to see
 *                  which error causes the interrupt.
 *******************************************************************/
void USBCBErrorHandler(void)
{
    // No need to clear UEIR to 0 here.
    // Callback caller is already doing that.

	// Typically, user firmware does not need to do anything special
	// if a USB error occurs.  For example, if the host sends an OUT
	// packet to your device, but the packet gets corrupted (ex:
	// because of a bad connection, or the user unplugs the
	// USB cable during the transmission) this will typically set
	// one or more USB error interrupt flags.  Nothing specific
	// needs to be done however, since the SIE will automatically
	// send a "NAK" packet to the host.  In response to this, the
	// host will normally retry to send the packet again, and no
	// data loss occurs.  The system will typically recover
	// automatically, without the need for application firmware
	// intervention.
	
	// Nevertheless, this callback function is provided, such as
	// for debugging purposes.
}


/*******************************************************************
 * Function:        void USBCBCheckOtherReq(void)
 * Overview:        When SETUP packets arrive from the host, some
 * 					firmware must process the request and respond
 *					appropriately to fulfill the request.  Some of
 *					the SETUP packets will be for standard
 *					USB "chapter 9" (as in, fulfilling chapter 9 of
 *					the official USB specifications) requests, while
 *					others may be specific to the USB device class
 *					that is being implemented.  For example, a HID
 *					class device needs to be able to respond to
 *					"GET REPORT" type of requests.  This
 *					is not a standard USB chapter 9 request, and 
 *					therefore not handled by usb_device.c.  Instead
 *					this request should be handled by class specific 
 *					firmware, such as that contained in usb_function_hid.c.
 *******************************************************************/
void USBCBCheckOtherReq(void)
{
    USBCheckCDCRequest();
}//end


/*******************************************************************
 * Function:        void USBCBStdSetDscHandler(void)
 * Overview:        The USBCBStdSetDscHandler() callback function is
 *					called when a SETUP, bRequest: SET_DESCRIPTOR request
 *					arrives.  Typically SET_DESCRIPTOR requests are
 *					not used in most applications, and it is
 *					optional to support this type of request.
 *******************************************************************/
void USBCBStdSetDscHandler(void)
{
    // Must claim session ownership if supporting this request
}//end


/*******************************************************************
 * Function:        void USBCBInitEP(void)
 * Overview:        This function is called when the device becomes
 *                  initialized, which occurs after the host sends a
 * 					SET_CONFIGURATION (wValue not = 0) request.  This 
 *					callback function should initialize the endpoints 
 *					for the device's usage according to the current 
 *					configuration.
 *******************************************************************/
void USBCBInitEP(void)
{
    //Enable the CDC data endpoints
    CDCInitEP();
}

/********************************************************************
 * Function:        void USBCBSendResume(void)
 * Overview:        The USB specifications allow some types of USB
 * 					peripheral devices to wake up a host PC (such
 *					as if it is in a low power suspend to RAM state).
 *					This can be a very useful feature in some
 *					USB applications, such as an Infrared remote
 *					control	receiver.  If a user presses the "power"
 *					button on a remote control, it is nice that the
 *					IR receiver can detect this signalling, and then
 *					send a USB "command" to the PC to wake up.
 *					
 *					The USBCBSendResume() "callback" function is used
 *					to send this special USB signalling which wakes 
 *					up the PC.  This function may be called by
 *					application firmware to wake up the PC.  This
 *					function will only be able to wake up the host if
 *                  all of the below are true:
 *					
 *					1.  The USB driver used on the host PC supports
 *						the remote wakeup capability.
 *					2.  The USB configuration descriptor indicates
 *						the device is remote wakeup capable in the
 *						bmAttributes field.
 *					3.  The USB host PC is currently sleeping,
 *						and has previously sent your device a SET 
 *						FEATURE setup packet which "armed" the
 *						remote wakeup capability.   
 *
 *                  If the host has not armed the device to perform remote wakeup,
 *                  then this function will return without actually performing a
 *                  remote wakeup sequence.  This is the required behavior, 
 *                  as a USB device that has not been armed to perform remote 
 *                  wakeup must not drive remote wakeup signalling onto the bus;
 *                  doing so will cause USB compliance testing failure.
 *                  
 *					This callback should send a RESUME signal that
 *                  has the period of 1-15ms.
 *
 * Note:            This function does nothing and returns quickly, if the USB
 *                  bus and host are not in a suspended condition, or are 
 *                  otherwise not in a remote wakeup ready state.  Therefore, it
 *                  is safe to optionally call this function regularly, ex: 
 *                  anytime application stimulus occurs, as the function will
 *                  have no effect, until the bus really is in a state ready
 *                  to accept remote wakeup. 
 *
 *                  When this function executes, it may perform clock switching,
 *                  depending upon the application specific code in 
 *                  USBCBWakeFromSuspend().  This is needed, since the USB
 *                  bus will no longer be suspended by the time this function
 *                  returns.  Therefore, the USB module will need to be ready
 *                  to receive traffic from the host.
 *
 *                  The modifiable section in this routine may be changed
 *                  to meet the application needs. Current implementation
 *                  temporary blocks other functions from executing for a
 *                  period of ~3-15 ms depending on the core frequency.
 *
 *                  According to USB 2.0 specification section 7.1.7.7,
 *                  "The remote wakeup device must hold the resume signaling
 *                  for at least 1 ms but for no more than 15 ms."
 *                  The idea here is to use a delay counter loop, using a
 *                  common value that would work over a wide range of core
 *                  frequencies.
 *                  That value selected is 1800. See table below:
 *                  ==========================================================
 *                  Core Freq(MHz)      MIP         RESUME Signal Period (ms)
 *                  ==========================================================
 *                      48              12          1.05
 *                       4              1           12.6
 *                  ==========================================================
 *                  * These timing could be incorrect when using code
 *                    optimization or extended instruction mode,
 *                    or when having other interrupts enabled.
 *                    Make sure to verify using the MPLAB SIM's Stopwatch
 *                    and verify the actual signal on an oscilloscope.
 *******************************************************************/
void USBCBSendResume(void)
{
    static WORD delay_count;
    
    //First verify that the host has armed us to perform remote wakeup.
    //It does this by sending a SET_FEATURE request to enable remote wakeup,
    //usually just before the host goes to standby mode (note: it will only
    //send this SET_FEATURE request if the configuration descriptor declares
    //the device as remote wakeup capable, AND, if the feature is enabled
    //on the host (ex: on Windows based hosts, in the device manager 
    //properties page for the USB device, power management tab, the 
    //"Allow this device to bring the computer out of standby." checkbox 
    //should be checked).
    if(USBGetRemoteWakeupStatus() == TRUE) 
    {
        //Verify that the USB bus is in fact suspended, before we send
        //remote wakeup signalling.
        if(USBIsBusSuspended() == TRUE)
        {
            USBMaskInterrupts();
            
            //Clock switch to settings consistent with normal USB operation.
            USBCBWakeFromSuspend();
            USBSuspendControl = 0; 
            USBBusIsSuspended = FALSE;  //So we don't execute this code again, 
                                        //until a new suspend condition is detected.

            //Section 7.1.7.7 of the USB 2.0 specifications indicates a USB
            //device must continuously see 5ms+ of idle on the bus, before it sends
            //remote wakeup signalling.  One way to be certain that this parameter
            //gets met, is to add a 2ms+ blocking delay here (2ms plus at 
            //least 3ms from bus idle to USBIsBusSuspended() == TRUE, yeilds
            //5ms+ total delay since start of idle).
            delay_count = 3600U;        
            do
            {
                delay_count--;
            }while(delay_count);
            
            //Now drive the resume K-state signalling onto the USB bus.
            USBResumeControl = 1;       // Start RESUME signaling
            delay_count = 1800U;        // Set RESUME line for 1-13 ms
            do
            {
                delay_count--;
            }while(delay_count);
            USBResumeControl = 0;       //Finished driving resume signalling

            USBUnmaskInterrupts();
        }
    }
}

/*******************************************************************
 * Function:        void USBCBEP0DataReceived(void)
 *
 * PreCondition:    ENABLE_EP0_DATA_RECEIVED_CALLBACK must be
 *                  defined already (in usb_config.h)
 * Overview:        This function is called whenever a EP0 data
 *                  packet is received.  This gives the user (and
 *                  thus the various class examples a way to get
 *                  data that is received via the control endpoint.
 *                  This function needs to be used in conjunction
 *                  with the USBCBCheckOtherReq() function since 
 *                  the USBCBCheckOtherReq() function is the apps
 *                  method for getting the initial control transfer
 *                  before the data arrives.
 *
 * Note:            None
 *******************************************************************/
#if defined(ENABLE_EP0_DATA_RECEIVED_CALLBACK)
void USBCBEP0DataReceived(void)
{
}
#endif

/*******************************************************************
 * Function:        BOOL USER_USB_CALLBACK_EVENT_HANDLER(
 *                        USB_EVENT event, void *pdata, WORD size)

 * Input:           USB_EVENT event - the type of event
 *                  void *pdata - pointer to the event data
 *                  WORD size - size of the event data

 * Overview:        This function is called from the USB stack to
 *                  notify a user application that a USB event
 *                  occured.  This callback is in interrupt context
 *                  when the USB_INTERRUPT option is selected.

 *******************************************************************/
BOOL USER_USB_CALLBACK_EVENT_HANDLER(int event, void *pdata, WORD size)
{
    switch(event)
    {
        case EVENT_TRANSFER:
            //Add application specific callback task or callback function here if desired.
            break;
        case EVENT_SOF:
            USBCB_SOF_Handler();
            break;
        case EVENT_SUSPEND:
            USBCBSuspend();
            break;
        case EVENT_RESUME:
            USBCBWakeFromSuspend();
            break;
        case EVENT_CONFIGURED: 
            USBCBInitEP();
            break;
        case EVENT_SET_DESCRIPTOR:
            USBCBStdSetDscHandler();
            break;
        case EVENT_EP0_REQUEST:
            USBCBCheckOtherReq();
            break;
        case EVENT_BUS_ERROR:
            USBCBErrorHandler();
            break;
        case EVENT_TRANSFER_TERMINATED:
            //Add application specific callback task or callback function here if desired.
            //The EVENT_TRANSFER_TERMINATED event occurs when the host performs a CLEAR
            //FEATURE (endpoint halt) request on an application endpoint which was 
            //previously armed (UOWN was = 1).  Here would be a good place to:
            //1.  Determine which endpoint the transaction that just got terminated was 
            //      on, by checking the handle value in the *pdata.
            //2.  Re-arm the endpoint if desired (typically would be the case for OUT 
            //      endpoints).
            break;
        default:
            break;
    }      
    return TRUE; 
}

/** EOF main.c *************************************************/
