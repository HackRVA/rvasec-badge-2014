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


#ifndef __HARDWARE_PROFILE_PIC32_ENC624J600_H__
#define __HARDWARE_PROFILE_PIC32_ENC624J600_H__

	#if   (((__PIC32_FEATURE_SET__ >= 100) && (__PIC32_FEATURE_SET__ <= 299)))
		#warning("TODO: For PIC32MX1xx/PIC32MX2xx devices, user must map the ports to required pins");
	#endif

	
		// Specify which SPI to use for the ENC28J60 or ENC624J600.  SPI1 is 
		// the topmost slot with pin 1 on it.  SPI2 is the middle slot 
		// starting on pin 33.
	
		#define ENC_IN_SPI1     // Use SPI1 with Ex-16 and PIM
		//#define ENC_IN_SPI2  // Use SPI2 with USB starterkit + IO expansion board.
		
	#if defined(DEMO_BOARD_USB_STARTER_KIT)
		#if defined(ENC_IN_SPI1)
			#error "SPI1 is not supported for PIC32 USB Starter Kit. Enable macro ENC_IN_SPI2"
		#endif
	#endif
	

		
		// ENC624J600 Interface Configuration
		// Comment out ENC100_INTERFACE_MODE if you don't have an ENC624J600 or 
		// ENC424J600.  Otherwise, choose the correct setting for the interface you 
		// are using.  Legal values are:
		//  - Commented out: No ENC424J600/624J600 present or used.  All other 
		//                   ENC100_* macros are ignored.
		//  - 0: SPI mode using CS, SCK, SI, and SO pins
		//  - 1: 8-bit demultiplexed PSP Mode 1 with RD and WR pins
		//  - 2: 8-bit demultiplexed PSP Mode 2 with R/Wbar and EN pins
		//  - 3: 16-bit demultiplexed PSP Mode 3 with RD, WRL, and WRH pins
		//  - 4: 16-bit demultiplexed PSP Mode 4 with R/Wbar, B0SEL, and B1SEL pins
		//  - 5: 8-bit multiplexed PSP Mode 5 with RD and WR pins
		//  - 6: 8-bit multiplexed PSP Mode 6 with R/Wbar and EN pins
		//  - 9: 16-bit multiplexed PSP Mode 9 with AL, RD, WRL, and WRH pins
		//  - 10: 16-bit multiplexed PSP Mode 10 with AL, R/Wbar, B0SEL, and B1SEL 
		//        pins
		#define ENC100_INTERFACE_MODE			0
		
		// If using a parallel interface, direct RAM addressing can be used (if all 
		// addresses wires are connected), or a reduced number of pins can be used 
		// for indirect addressing.  If using an SPI interface or PSP Mode 9 or 10 
		// (multiplexed 16-bit modes), which require all address lines to always be 
		// connected, then this option is ignored. Comment out or uncomment this 
		// macro to match your hardware connections.
		#define ENC100_PSP_USE_INDIRECT_RAM_ADDRESSING
		
		// ENC424J600/624J600 parallel indirect address remapping macro function.
		// This section translates SFR and RAM addresses presented to the 
		// ReadMemory() and WriteMemory() APIs in ENCX24J600.c to the actual 
		// addresses that must be presented on the parallel interface.  This macro 
		// must be modified to match your hardware if you are using an indirect PSP 
		// addressing mode (ENC100_PSP_USE_INDIRECT_RAM_ADDRESSING is defined) and 
		// have some of your address lines tied off to Vdd.  If you are using the 
		// SPI interface, then this section can be ignored or deleted.
		#if (ENC100_INTERFACE_MODE == 1) || (ENC100_INTERFACE_MODE == 2) || (ENC100_INTERFACE_MODE == 5) || (ENC100_INTERFACE_MODE == 6) // 8-bit PSP
			#define ENC100_TRANSLATE_TO_PIN_ADDR(a)		((((a)&0x0100)<<6) | ((a)&0x00FF))
		#elif (ENC100_INTERFACE_MODE == 3) || (ENC100_INTERFACE_MODE == 4) // 16-bit PSP
			#define ENC100_TRANSLATE_TO_PIN_ADDR(a)		(a)
		#endif
		
		// Auto-crossover pins on Fast 100Mbps Ethernet PICtail/PICtail Plus.  If 
		// your circuit doesn't have such a feature, delete these two defines.
		#define ENC100_MDIX_TRIS				(TRISBbits.TRISB3)
		#define ENC100_MDIX_IO					(LATBbits.LATB3)
		
		// ENC624J600 I/O control and status pins
		// If a pin is not required for your selected ENC100_INTERFACE_MODE 
		// interface selection (ex: WRH/B1SEL for PSP modes 1, 2, 5, and 6), then 
		// you can ignore, delete, or put anything for the pin definition.  Also, 
		// the INT and POR pins are entirely optional.  If not connected, comment 
		// them out.
		#define ENC100_INT_TRIS					(TRISEbits.TRISE9)		// INT signal is optional and currently unused in the Microchip TCP/IP Stack.  Leave this pin disconnected and comment out this pin definition if you don't want it.
		#define ENC100_INT_IO					(PORTEbits.RE9)
		#if (ENC100_INTERFACE_MODE >= 1)	// Parallel mode
			// PSP control signal pinout
			#define ENC100_CS_TRIS					(TRISAbits.TRISA5)	// CS is optional in PSP mode.  If you are not sharing the parallel bus with another device, tie CS to Vdd and comment out this pin definition.
			#define ENC100_CS_IO					(LATAbits.LATA5)
			#define ENC100_POR_TRIS					(TRISCbits.TRISC1)	// POR signal is optional.  If your application doesn't have a power disconnect feature, comment out this pin definition.
			#define ENC100_POR_IO					(LATCbits.LATC1)
			#define ENC100_SO_WR_B0SEL_EN_TRIS		(TRISDbits.TRISD4)
			#define ENC100_SO_WR_B0SEL_EN_IO		(LATDbits.LATD4)
			#define ENC100_SI_RD_RW_TRIS			(TRISDbits.TRISD5)
			#define ENC100_SI_RD_RW_IO				(LATDbits.LATD5)
			#define ENC100_SCK_AL_TRIS				(TRISBbits.TRISB15)
			#define ENC100_SCK_AL_IO				(LATBbits.LATB15)
		#else
			// SPI pinout
			#if defined ENC_IN_SPI1
				#define ENC100_CS_TRIS					(TRISDbits.TRISD14)	// CS is mandatory when using the SPI interface
				#define ENC100_CS_IO					(LATDbits.LATD14)
				#define ENC100_POR_TRIS					(TRISDbits.TRISD15)	// POR signal is optional.  If your application doesn't have a power disconnect feature, comment out this pin definition.
				#define ENC100_POR_IO					(LATDbits.LATD15)
			#elif defined ENC_IN_SPI2
				#define ENC100_CS_TRIS					(TRISFbits.TRISF12)
				#define ENC100_CS_IO					(LATFbits.LATF12)
				#define ENC100_POR_TRIS					(TRISFbits.TRISF13)
				#define ENC100_POR_IO					(LATFbits.LATF13)
			#endif
		#endif


		// ENC624J600 SPI SFR register selection (controls which SPI peripheral to 
		// use on PICs with multiple SPI peripherals).  If a parallel interface is 
		// used (ENC100_INTERFACE_MODE is >= 1), then the SPI is not used and this 
		// section can be ignored or deleted.
		#if defined ENC_IN_SPI1
			#define ENC100_ISR_ENABLE		(IEC0bits.INT2IE)
			#define ENC100_ISR_FLAG			(IFS0bits.INT2IF)
			#define ENC100_ISR_POLARITY		(INTCONbits.INT2EP)
			#define ENC100_ISR_PRIORITY		(IPC2bits.INT2IP)
			#define ENC100_SPI_ENABLE		(ENC100_SPICON1bits.ON)
			#define ENC100_SPI_IF			(IFS0bits.SPI1RXIF)
			#define ENC100_SSPBUF			(SPI1BUF)
			#define ENC100_SPICON1			(SPI1CON)
			#define ENC100_SPISTATbits		(SPI1STATbits)
			#define ENC100_SPICON1bits		(SPI1CONbits)
			#define ENC100_SPIBRG			(SPI1BRG)
		#elif defined ENC_IN_SPI2
			#define ENC100_ISR_ENABLE		(IEC0bits.INT4IE)
			#define ENC100_ISR_FLAG			(IFS0bits.INT4IF)
			#define ENC100_ISR_POLARITY		(INTCONbits.INT4EP)
			#define ENC100_ISR_PRIORITY		(IPC2bits.INT4IP)
			#define ENC100_SPI_ENABLE		(ENC100_SPICON1bits.ON)
			#define ENC100_SPI_IF			(IFS1bits.SPI2RXIF)
			#define ENC100_SSPBUF			(SPI2BUF)
			#define ENC100_SPICON1			(SPI2CON)
			#define ENC100_SPISTATbits		(SPI2STATbits)
			#define ENC100_SPICON1bits		(SPI2CONbits)
			#define ENC100_SPIBRG			(SPI2BRG)
		#endif
#endif
