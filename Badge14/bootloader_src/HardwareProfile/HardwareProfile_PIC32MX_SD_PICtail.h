/*********************************************************************
 *
 *	Hardware specific definitions for:
	SD/MMC PICtail card
 *
 *********************************************************************
 * FileName:        HardwareProfile.h
 * Dependencies:    Compiler.h
 * Processor:       PIC32
 * Compiler:        Microchip C32 v1.11 or higher
 * Company:         Microchip Technology, Inc.
 *
 * Software License Agreement
 *
 * Copyright (C) 2002-2010 Microchip Technology Inc.  All rights
 * reserved.
 *
 * Microchip licenses to you the right to use, modify, copy, and
 * distribute:
 * (i)  the Software when embedded on a Microchip microcontroller or
 *      digital signal controller product ("Device") which is
 *      integrated into Licensee's product; or
 * (ii) ONLY the Software driver source files ENC28J60.c, ENC28J60.h,
 *		ENCX24J600.c and ENCX24J600.h ported to a non-Microchip device
 *		used in conjunction with a Microchip ethernet controller for
 *		the sole purpose of interfacing with the ethernet controller.
 *
 * You should refer to the license agreement accompanying this
 * Software for additional information regarding your rights and
 * obligations.
 *
 * THE SOFTWARE AND DOCUMENTATION ARE PROVIDED "AS IS" WITHOUT
 * WARRANTY OF ANY KIND, EITHER EXPRESS OR IMPLIED, INCLUDING WITHOUT
 * LIMITATION, ANY WARRANTY OF MERCHANTABILITY, FITNESS FOR A
 * PARTICULAR PURPOSE, TITLE AND NON-INFRINGEMENT. IN NO EVENT SHALL
 * MICROCHIP BE LIABLE FOR ANY INCIDENTAL, SPECIAL, INDIRECT OR
 * CONSEQUENTIAL DAMAGES, LOST PROFITS OR LOST DATA, COST OF
 * PROCUREMENT OF SUBSTITUTE GOODS, TECHNOLOGY OR SERVICES, ANY CLAIMS
 * BY THIRD PARTIES (INCLUDING BUT NOT LIMITED TO ANY DEFENSE
 * THEREOF), ANY CLAIMS FOR INDEMNITY OR CONTRIBUTION, OR OTHER
 * SIMILAR COSTS, WHETHER ASSERTED ON THE BASIS OF CONTRACT, TORT
 * (INCLUDING NEGLIGENCE), BREACH OF WARRANTY, OR OTHERWISE.
 *
 ************************************************************************************************/
 
#ifndef _HARDWAREPROFILE_PIC32MX_SD_PICTAIL_H_
#define _HARDWAREPROFILE_PIC32MX_SD_PICTAIL_H_


// Description: Macro used to enable the SD-SPI physical layer (SD-SPI.c and .h)
#define USE_SD_INTERFACE_WITH_SPI

#if   (((__PIC32_FEATURE_SET__ >= 100) && (__PIC32_FEATURE_SET__ <= 299)))
		#error("TODO: For PIC32MX1xx/PIC32MX2xx devices, user must map the SPI ports to required I/Os");
#endif



/*********************************************************************/
/******************* Pin and Register Definitions ********************/
/*********************************************************************/

/* SD Card definitions: Change these to fit your application when using
   an SD-card-based physical layer                                   */

// Registers for the SPI module you want to use
#define MDD_USE_SPI_1
//#define MDD_USE_SPI_2

//SPI Configuration
#define SPI_START_CFG_1     (PRI_PRESCAL_64_1 | SEC_PRESCAL_8_1 | MASTER_ENABLE_ON | SPI_CKE_ON | SPI_SMP_ON)
#define SPI_START_CFG_2     (SPI_ENABLE)

 // Define the SPI frequency
 #define SPI_FREQUENCY			(10000000)
   
       #if defined MDD_USE_SPI_1
           	// Description: SD-SPI Chip Select Output bit
       		#define SD_CS               LATBbits.LATB1
       		// Description: SD-SPI Chip Select TRIS bit
           	#define SD_CS_TRIS          TRISBbits.TRISB1
           
           // Description: SD-SPI Card Detect Input bit
           #define SD_CD               PORTFbits.RF0
           // Description: SD-SPI Card Detect TRIS bit
           #define SD_CD_TRIS          TRISFbits.TRISF0

           // Description: SD-SPI Write Protect Check Input bit
           #define SD_WE               PORTFbits.RF1
           // Description: SD-SPI Write Protect Check TRIS bit
           #define SD_WE_TRIS          TRISFbits.TRISF1
                  
           // Description: The main SPI control register
           #define SPICON1             SPI1CON
           // Description: The SPI status register
           #define SPISTAT             SPI1STAT
           // Description: The SPI Buffer
           #define SPIBUF              SPI1BUF
           // Description: The receive buffer full bit in the SPI status register
           #define SPISTAT_RBF         SPI1STATbits.SPIRBF
           // Description: The bitwise define for the SPI control register (i.e. _____bits)
           #define SPICON1bits         SPI1CONbits
           // Description: The bitwise define for the SPI status register (i.e. _____bits)
           #define SPISTATbits         SPI1STATbits
           // Description: The enable bit for the SPI module
           #define SPIENABLE           SPICON1bits.ON
           // Description: The definition for the SPI baud rate generator register (PIC32)
           #define SPIBRG			    SPI1BRG

	        // Tris pins for SCK/SDI/SDO lines
			#if defined(__32MX360F512L__) // All PIC32MX3XX 
				// Description: The TRIS bit for the SCK pin
            	#define SPICLOCK            TRISFbits.TRISF6
            	// Description: The TRIS bit for the SDI pin
            	#define SPIIN               TRISFbits.TRISF7
            	// Description: The TRIS bit for the SDO pin
            	#define SPIOUT              TRISFbits.TRISF8
			#else	// example: PIC32MX360F512L
            	// Description: The TRIS bit for the SCK pin
            	#define SPICLOCK            TRISDbits.TRISD10
            	// Description: The TRIS bit for the SDI pin
            	#define SPIIN               TRISCbits.TRISC4
            	// Description: The TRIS bit for the SDO pin
            	#define SPIOUT              TRISDbits.TRISD0
			#endif

            	//SPI library functions
            #define putcSPI             putcSPI1
            #define getcSPI             getcSPI1
            #define OpenSPI(config1, config2)   OpenSPI1(config1, config2)
            
        #elif defined MDD_USE_SPI_2
            // Description: SD-SPI Chip Select Output bit
            #define SD_CS               LATBbits.LATB9
            // Description: SD-SPI Chip Select TRIS bit
            #define SD_CS_TRIS          TRISBbits.TRISB9
            
            // Description: SD-SPI Card Detect Input bit
            #define SD_CD               PORTGbits.RG0
            // Description: SD-SPI Card Detect TRIS bit
            #define SD_CD_TRIS          TRISGbits.TRISG0

            // Description: SD-SPI Write Protect Check Input bit
            #define SD_WE               PORTGbits.RG1
            // Description: SD-SPI Write Protect Check TRIS bit
            #define SD_WE_TRIS          TRISGbits.TRISG1
            
            // Description: The main SPI control register
            #define SPICON1             SPI2CON
            // Description: The SPI status register
            #define SPISTAT             SPI2STAT
            // Description: The SPI Buffer
            #define SPIBUF              SPI2BUF
            // Description: The receive buffer full bit in the SPI status register
            #define SPISTAT_RBF         SPI2STATbits.SPIRBF
            // Description: The bitwise define for the SPI control register (i.e. _____bits)
            #define SPICON1bits         SPI2CONbits
            // Description: The bitwise define for the SPI status register (i.e. _____bits)
            #define SPISTATbits         SPI2STATbits
            // Description: The enable bit for the SPI module
            #define SPIENABLE           SPI2CONbits.ON
            // Description: The definition for the SPI baud rate generator register (PIC32)
            #define SPIBRG			    SPI2BRG

            // Tris pins for SCK/SDI/SDO lines

            // Description: The TRIS bit for the SCK pin
            #define SPICLOCK            TRISGbits.TRISG6
            // Description: The TRIS bit for the SDI pin
            #define SPIIN               TRISGbits.TRISG7
            // Description: The TRIS bit for the SDO pin
            #define SPIOUT              TRISGbits.TRISG8
            //SPI library functions
            #define putcSPI             putcSPI2
            #define getcSPI             getcSPI2
            #define OpenSPI(config1, config2)   OpenSPI2(config1, config2)
        #endif       
        // Will generate an error if the clock speed is too low to interface to the card
        #if (GetSystemClock() < 100000)
            #error Clock speed must exceed 100 kHz
        #endif    
    
 
#endif
