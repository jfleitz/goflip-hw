/********************************************************************************************************
 * File: sysclk.c
 * Description:
 * 		This file implements the oscillator initialization. The inilization also
 * 		switches the oscialltor source if the seleted source does not match the runtime
 * 		clock source.
 *
 * Last modified: 21 Apr 2006
 ********************************************************************************************************
 * Copyright (C) 2008 by Zilog, Inc.  All Rights Reserved.
 ********************************************************************************************************/

/********************************************************************************************************
 *  header file includes
 ********************************************************************************************************/
#include <eZ8.h>
#include "sysclk.h"


/*********************************************************************************************************
 * local constant defintions
 *********************************************************************************************************
/*--------------------------------------------------------------------------------------
 *  System clock selection
 *
 *  Instructions for enabling the external clock:
 *      1. Select External clock and Frequency in the Debugger Setup Target dialog
 *      2. Uncomment the following line; "#define CLOCK_SOURCE    CLOCK_EXTERNAL"
 *--------------------------------------------------------------------------------------*/
//#define CLOCK_SOURCE    CLOCK_EXTERNAL        // external oscillator
#ifndef CLOCK_SOURCE
#define CLOCK_SOURCE    CLOCK_INTERNAL        // internal oscillator
#endif

#ifndef CLOCK_SOURCE
#define CLOCK_SOURCE    CLOCK_SOURCE_DEFAULT
#endif

/*--------------------------------------------------------------------------------------
 * The Osciallator control registers(OSCTL) is used to configure the clock source and select Internal 
 * Precision Frequency.
 *
 * +--------+-------+-------+-------+-------+-------+-------+---+---+---+
 * |        | BITS  |   7   |   6   |   5   |   4   |   3   | 2 | 1 | 0 |
 * | OSCTL  | ------+-------+-------+-------+-------+-------+---+---+---+
 * |        | FIELD | INTEN | XTLEN | WDTEN | POFEN | WDFEN |   SCKSEL  |
 * +--------+-------+-------+-------+-------+-------+-------+-----------+
 *                      |       |        |      |       |        |_ System clock oscillator select
 *                      |	    |		 |      |       |            000 = Internal precision oscillator 
 * 					    |	    |		 |	    |       |                  functions as system clock at 5.53MHz
 *                      |       |        |      |       |            001 = Internal precision oscillator functions
 *					    |	    |		 |	    |	    |  		          as system clock at 32KHz
 *                      |       |        |      |       |            010 = Crystal oscillator or external RC 
 *					    |	    |		 |	    |	    |	              oscillator functions as system clock
 *                      |       |        |      |       |            011 = Watchdog timer oscillator functions as 
 *    				    |	    |		 |	    |       | 		           system clock
 *                      |       |        |      |       |            100 = External clock signal on PB3 functions
 * 					    |	    |		 |	    |	    | 		          as system clock
 *                      |       |        |      |       |            101 = Reserved
 *                      |       |        |      |       |            110 = Reserved
 *                      |       |        |      |       |            111 = Reserved
 *                      |       |        |      |       |
 *                      |       |        |      |       |_ Watchdog timer oscillator failure detection enable
 *                      |       |        |      |          1 = Failure detection of Watchdog timer oscillator
 *                      |       |        |      |              is enabled
 *                      |       |        |      |          0 = Failure detection of Watchdog timer oscillator
 *                      |       |        |      |              is disabled          
 *                      |       |        |      |
 *                      |       |        |      |_ Primary oscillator failure detection enable
 *                      |       |        |         1 = Failure detection and recovery of primary oscillator 
 *                      |       |        |             is enabled
 *                      |       |        |         0 = Failure detection and recovery of primary oscillator 
 *                      |       |        |             is disabled 
 *                      |       |        |_ Watchdog timer oscillator enable
 *                      |       |           1 = Watchdog timer oscillator is enabled
 *                      |       |           0 = Watchdog timer oscillator is disabled
 *                      |       |
 *                      |       |_ Crystal oscillator enable * this setting overrides the GPIO register 
 *                      |          control for PA0 and PA1
 *                      |
 *                      |_ Internal precision oscillator enable
 *                         1 = Internal precision oscillator is enabled
 *                         0 = Internal precision oscillator is disabled
 *
 -----------------------------------------------------------------------------------------------------------*/
#if (CLOCK_SOURCE == CLOCK_EXTERNAL)
#define SCKSEL          SCK_XTAL
#define OSCEN           OSC_INTEN | OSC_XTLEN
#elif (CLOCK_SOURCE == CLOCK_INTERNAL)
/*--------------------------------------------------------------------------------------
 *  Instructions to use 32 KHz IPO supported only with USB/Ethernet SmartCable
 *      1. Enter 0.032 to Project settings->Debugger->Target\Setup->Internal\other
 *      2. Ensure to comment out the above statement; "#define CLOCK_SOURCE    CLOCK_EXTERNAL"
 *      3. Uncomment the following line ; "//#define SCKSEL          SCK_IPO_32K"
 *--------------------------------------------------------------------------------------*/
//#define SCKSEL          SCK_IPO_32K	// Select 32KHZ
#ifndef SCKSEL
#define SCKSEL          SCK_IPO			// Select 5.5926 MHZ
#endif
#define OSCEN           OSC_INTEN		// Enable IPO bit
#endif

/*********************************************************************************************************
 * Function: sysclk_init
 * Description: 
 *     Initialize system clock source 
 *
 **********************************************************************************************************/
void sysclk_init(void)
{
    /*******
	 * If clock source is selected as external, enable it
	 */
#if (SCKSEL & ~SCK_IPO_MASK) 
	unsigned long delay = 1000; 	// delay used for oscillator stabilization after enabled

    /******
	 *  Enable external source if not yet enabled
	 */
    if ((OSCCTL & 0x06) != SCKSEL)
    {

		/******
		 *  Enable external oscillator source
		 */
        OSCCTL = 0xE7;              // Unlock sequence for OSCTL write
        OSCCTL = 0x18;              //
        OSCCTL |= OSC_XTLEN;        // start external oscillator

        while(delay--);				// wait for clock to stabilize
	}
#endif
 	/******
	 *  Switch to selected oscillator source
	 */	
	OSCCTL = 0xE7;              // Unlock sequence for OSCTL write
    OSCCTL = 0x18;              //
    OSCCTL = OSCEN | SCKSEL;    // switch to other clock source
}

