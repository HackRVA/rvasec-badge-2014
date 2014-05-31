/*********************************************************************
 *
 *	Hardware specific definitions for:
 *    - PIC32 USB Starter Kit II
 *    - PIC32MX795F512L
 *    - Ethernet PICtail Plus (ENC28J60)
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
 *
 * Author               Date		Comment
 *~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * Howard Schlunder		09/16/2010	Regenerated for specific boards
 ********************************************************************/
#ifndef __HARDWARE_PROFILE_PIC32MX_ENC28J60_H__
#define __HARDWARE_PROFILE_PIC32MX_ENC28J60_H__


// Specify which SPI to use for the ENC28J60 or ENC624J600.  SPI1 is 
// the topmost slot with pin 1 on it.  SPI2 is the middle slot 
// starting on pin 33.
#define ENC_IN_SPI1
//#define ENC_IN_SPI2

#if defined(DEMO_BOARD_USB_STARTER_KIT)
	#if defined(ENC_IN_SPI1)
		#error "SPI1 is not supported for PIC32 USB Starter Kit. Enable macro ENC_IN_SPI2"
	#endif
#endif

#if   (((__PIC32_FEATURE_SET__ >= 100) && (__PIC32_FEATURE_SET__ <= 299)))
		#error("TODO: For PIC32MX1xx/PIC32MX2xx devices, user has to take care of mapping the ports to required pins using PPS");
#endif

// ENC28J60 I/O pins
#if defined ENC_IN_SPI1
	#define ENC_CS_TRIS			(TRISDbits.TRISD14)
	#define ENC_CS_IO			(PORTDbits.RD14)
	//#define ENC_RST_TRIS		(TRISDbits.TRISD15)	// Not connected by default.  It is okay to leave this pin completely unconnected, in which case this macro should simply be left undefined.
	//#define ENC_RST_IO		(PORTDbits.RD15)

	// SPI SCK, SDI, SDO pins are automatically controlled by the 
	#define ENC_SPI_IF			(IFS0bits.SPI1RXIF)
	#define ENC_SSPBUF			(SPI1BUF)
	#define ENC_SPICON1			(SPI1CON)
	#define ENC_SPICON1bits		(SPI1CONbits)
	#define ENC_SPIBRG			(SPI1BRG)
	#define ENC_SPISTATbits		(SPI1STATbits)
#elif defined ENC_IN_SPI2
	#define ENC_CS_TRIS			(TRISFbits.TRISF12)
	#define ENC_CS_IO			(PORTFbits.RF12)
	//#define ENC_RST_TRIS		(TRISFbits.TRISF13)	// Not connected by default.  It is okay to leave this pin completely unconnected, in which case this macro should simply be left undefined.
	//#define ENC_RST_IO		(PORTFbits.RF13)

	// SPI SCK, SDI, SDO pins are automatically controlled by the 
	// PIC32 SPI module 
	#define ENC_SPI_IF			(IFS1bits.SPI2RXIF)
	#define ENC_SSPBUF			(SPI2BUF)
	#define ENC_SPICON1			(SPI2CON)
	#define ENC_SPISTATbits		(SPI2STATbits)
	#define ENC_SPICON1bits		(SPI2CONbits)
	#define ENC_SPIBRG			(SPI2BRG)
#endif

#endif
