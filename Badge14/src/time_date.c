/*********************************************************************
 *
 *                  RTCC API Example
 *
 *********************************************************************
 * FileName:        time_date.c
 * Dependencies:	Rtcc.h
 *
 *
 * Processor:       PIC32
 *
 * Complier:        MPLAB Cxx
 *                  MPLAB IDE vxx
 * Company:         Microchip Technology Inc.
 *
 * Software License Agreement
 *
 * The software supplied herewith by Microchip Technology Incorporated
 * (the �Company�) for its PIC32 Microcontroller is intended
 * and supplied to you, the Company�s customer, for use solely and
 * exclusively on Microchip PIC32 Microcontroller products.
 * The software is owned by the Company and/or its supplier, and is
 * protected under applicable copyright laws. All rights are reserved.
 * Any use in violation of the foregoing restrictions may subject the
 * user to criminal sanctions under applicable laws, as well as to
 * civil liability for the breach of the terms and conditions of this
 * license.
 *
 * THIS SOFTWARE IS PROVIDED IN AN �AS IS� CONDITION. NO WARRANTIES,
 * WHETHER EXPRESS, IMPLIED OR STATUTORY, INCLUDING, BUT NOT LIMITED
 * TO, IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A
 * PARTICULAR PURPOSE APPLY TO THIS SOFTWARE. THE COMPANY SHALL NOT,
 * IN ANY CIRCUMSTANCES, BE LIABLE FOR SPECIAL, INCIDENTAL OR
 * CONSEQUENTIAL DAMAGES, FOR ANY REASON WHATSOEVER.
 *
 *
 * Author               Date        Comment
 *~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * $Id: rtcc_api_example.c 4288 2007-08-22 23:00:56Z aura $
 *
 ********************************************************************/


// Master header file for all peripheral library includes
#include <plib.h>


//	local function prototypes

int CheckRtccRunning(int secWait);


// Configuration Bit settings
// SYSCLK = 80 MHz (8MHz Crystal/ FPLLIDIV * FPLLMUL / FPLLODIV)
// PBCLK = 40 MHz
// Primary Osc w/PLL (XT+,HS+,EC+PLL)
// WDT OFF
// Other options are don't care
//

#ifdef FOR_REFERENCE_ONLY

//#pragma config FPLLMUL = MUL_20, FPLLIDIV = DIV_2, FPLLODIV = DIV_1, FWDTEN = OFF
//#pragma config POSCMOD = HS, FNOSC = PRIPLL, FPBDIV = DIV_1

#endif

#define SYS_FREQ 		(20000000L)

/*********************************************************************
 * Function:        int main(void)
 *
 * PreCondition:    None
 *
 * Input:           None
 *
 * Output:          1 if everything went on ok, 0 if failed
 *
 * Side Effects:    None
 *
 * Overview:        The function is an example of using the RTCC device.

 * Note:            None
 ********************************************************************/
int setupRTCC(void)
{
	rtccTime	tm, tm1;			// time structure
	rtccDate	dt, dt1;			// date structure

	// Configure the device for maximum performance but do not change the PBDIV
	// Given the options, this function will change the flash wait states, RAM
	// wait state and enable prefetch cache but will not change the PBDIV.
	// The PBDIV value is already set via the pragma FPBDIV option above..

	// SYSTEMConfig(SYS_FREQ, SYS_CFG_WAIT_STATES | SYS_CFG_PCACHE);

	RtccInit();			// init the RTCC
	while(RtccGetClkStat()!=RTCC_CLK_ON);	// wait for the SOSC to be actually running and RTCC to have its clock source
							// could wait here at most 32ms

		tm.l=0;
		tm.sec=0x30;
		tm.min=0x07;
		tm.hour=0x10;

		dt.wday=2;
		dt.mday=0x02;
		dt.mon=0x06;
		dt.year=0x14;
		RtccSetTimeDate(tm.l, dt.l);

	//RtccSetTimeDate(0x21140000, 0x14060201);	// time is MSb: hour, min, sec, rsvd. date is MSb: year, mon, mday, wday.
												// please note that the rsvd field has to be 0 in the time field!
	RtccSetCalibration(0);	// value to calibrate with at each minute

	//tm1.l=RtccGetTime();
	//dt1.l=RtccGetDate();
	//RtccGetTimeDate(&tm1, &dt1);

	// now that we know the RTCC clock is up and running, it's easier to start from fresh:
	//RtccOpen(tm.l, dt.l, 0);	// set time, date and calibration in a single operation

	// check that the RTCC is running
	//if(!CheckRtccRunning(3))
	//{
		//return 0;
	//}

	// another way to see the RTCC is tunning: check the SYNC bit
	while(RtccGetSync());	// wait sync to be low
	while(!RtccGetSync());	// wait to be high
	while(RtccGetSync());	// wait sync to be low again


	// other RTCC operations

	// adjust the RTCC timing

	// enabling the RTCC output pin
	//RtccSelectPulseOutput(1);		// select the seconds clock pulse as the function of the RTCC output pin
	//RtccSelectPulseOutput(0);		// select the alarm pulse as the function of the RTCC output pin
	//RtccOutputEnable(1);			// enable the Output pin of the RTCC


	return 1;
}



/*********************************************************************
 * Function:        int CheckRtccRunning(int secWait)
 *
 * PreCondition:    None
 *
 * Input:           None
 *
 * Output:          1(true) if test succeeded, 0(FALSE) otherwise
 *
 * Side Effects:    None
 *
 * Overview:        The function checks that the RTCC has the clock enabled and counts the time.
 *
 * Note:            None
 ********************************************************************/
int CheckRtccRunning(int secWait)
{
	#define	WAIT_FOR_SEC_TMO	1100			// how many ms to wait for the RTCC seconds count to change

	rtccTime	t0, t1;
	int		fail;
	int		secCnt;
	unsigned int	tStart;


	
	for(secCnt=0, fail=0; secCnt<secWait; secCnt++)
	{
		tStart=ReadCoreTimer();
		t0.l=RtccGetTime();
		do
		{
			t1.l=RtccGetTime();
		}while((t1.sec==t0.sec) && (ReadCoreTimer()-tStart)<(SYS_FREQ/2000)*WAIT_FOR_SEC_TMO);	// wait seconds change

		if(t1.sec==t0.sec)
		{
			fail=1;
			break;	// failed
		}
	}
	
	return !fail;
}

 

