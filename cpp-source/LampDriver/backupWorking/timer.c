/********************************************************************************************************
 * File: timer.c
 * Description:
 *   	This file include implementation of subroutines that do 
 *       o Timer 0 initialization
 *       o Interrupt handling for timer 0
 *		 
 *
 * Last modified: 21 Apr 2006
 ********************************************************************************************************
 * Copyright (C) 2008 by Zilog, Inc.  All Rights Reserved.
 ********************************************************************************************************/

 /********************************************************************************************************* 
 *  header file includes
 *********************************************************************************************************/
 #include <eZ8.h>
#include <sio.h>
#include "lampDriver.h"
#include "timer.h"

/********************************************************************************************************* 
 * constants defintion and global variables
 *********************************************************************************************************/

/*-------------------------------------------------------------------------------------
 * By default, LEDs are blinking at variable rates per selected frequency. The faster
 * the frequency is, the faster the blink rate is.
 * 
 * To flash LEDs at constant rate for all selected frequency, UNCOMMENT the following
 * line; "#define FIXED_BLINK_RATE	1"
 *-------------------------------------------------------------------------------------*/
#define STARTCOUNT 1
#define BLINK_RELOAD 0xffff
//#define LAMP_RELOAD 0xB400	//should be about 10msec
#define LAMP_RELOAD 0x3fff	//should be about 10msec

void setupBlinkInterruptTimer1();
void setupLampInterruptTimer0();



/********************************************************************************************************* 
 * Global variables
 *********************************************************************************************************/


/*********************************************************************************************************
 * Function: isr_timer
 * Description: 
 *    Interrupt occurs when timer timeouts and the interrupt handler updates the execution status to Run state
 *
 **********************************************************************************************************/
void interrupt lamp_timer(void) 
{
		lampISR();
}

void interrupt blink_timer(void) 
{
		blinkISR();
}

/*********************************************************************************************************
 * Function: timer_init
 * Description: 
 *    Intialize timer0 and  timer interrupt
 *
 **********************************************************************************************************/
void timer_init(void)
{

	/*--------------------------------------------------------------------------------------------------------
	 * The timer control registers(TxTCL0 and TxTCL1) are used to configure timer before the timer is started.
	 * 
	 * +--------+-------+-------+-----+-----+-----+---+---+---+------+
	 * |        | BITS  |   7   |  6  |  5  |  4  | 3 | 2 | 1 |   0  |
	 * | TxTCL0 | ------+-------+-----+-----+-----+---+---+---+------+
	 * |        | FIELD | TMODE | TICONFIG  | CSC |    PWMD   |INPCAP|
	 * +--------+-------+-------+-----------+-----+-----------+------+
	 *                      |         |        |        |         |_ Input Capture Event
	 *                      |         |        |        |            0 = Previous timer interrupt is not
	 *                      |         |        |        |                a result of Timer Input Capture Event
	 *                      |         |        |        |            1 = Previous timer interrupt is a result 
	 *                      |         |        |        |                of Timer Input Capture Event
	 *                      |         |        |        |_ PWM Delay Value
	 *                      |         |        |           000 = No delay
	 *                      |         |        |           001 = 2 cycles delay
	 *                      |         |        |           010 = 4 cycles delay
	 *                      |         |        |           011 = 8 cycles delay
	 *                      |         |        |           100 = 16 cycles delay
	 *                      |         |        |           101 = 32 cycles delay
	 *                      |         |        |           110 = 64 cycles delay
	 *                      |         |        |           111 = 128 cycles delay
	 *                      |         |        |_ Cascade Timers
	 *                      |         |           0 = Timer Input signal comes from the pin.
	 *                      |         |           1 = Input signal is connected to Timer  output.
	 *                      |         |
	 *                      |         |_ Timer Interrupt Configuration
	 *                      |            0x = Timer Interrupt occurs on all defined Reload, Compare and Input Events
	 *                      |            10 = Timer Interrupt only on defined Input Capture/Deassertion Events
	 *                      |            11 = Timer Interrupt only on defined Reload/Compare Events
	 *                      |
	 *                      |_ Timer Mode High Bit
	 *                         used along with the TMODE[2:0] field in TxCTL1 register determines the operating
	 *                         mode of the timer
	 *
	 * +--------+-------+-----+------+----+---+----+----+---+---+
	 * |        | BITS  |  7  |   6  |  5 | 4 | 3  |  2 | 1 | 0 |
	 * | TxTCL1 | ------+-----+------+----+---+----+----+-------|
	 * |        | FIELD | TEN | TPOL |    PRES     |    TMODE   |
	 * +--------+-------+-----+------+-------------+------------+
	 *                     |      |         |           |__ Timer mode
	 *                     |      |         |               TMODEHI-TMODE[2:0] selects among the following modes:
	 *                     |      |         |               0000 = One-Shot mode
	 *                     |      |         |               0001 = Continuous mode
	 *                     |      |         |               0010 = Counter mode
	 *                     |      |         |               0011 = PWM Single Output mode
	 *                     |      |         |               0100 = Capture mode
	 *                     |      |         |               0101 = Compare mode
	 *                     |      |         |               0110 = Gated mode
	 *                     |      |         |               0111 = Capture/Compare mode
	 *                     |      |         |               1000 = PWM Dual Output mode
	 *                     |      |         |               1001 = Capture Restart mode
	 *                     |      |         |               1010 = Comparator Counter mode
	 *                     |      |         |               1011 = Triggered One-Shot mode
	 *                     |      |         |
	 *                     |      |         |__ Prescale value
	 *                     |      |                         000 = Divide by 1
	 *                     |      |                         001 = Divide by 2
	 *                     |      |                         010 = Divide by 4
	 *                     |      |                         011 = Divide by 8
	 *                     |      |                         100 = Divide by 16
	 *                     |      |                         101 = Divide by 32
	 *                     |      |                         110 = Divide by 64
	 *                     |      |                         111 = Divide by 128                                                    
	 *                     |      |__ Timer Input/Output Polarity
	 *                     |          For Continuous mode
	 *                     |          When the timer is disabled, the Timer Output signal is set to the value of this bit.
	 *                     |          When the timer is enabled, the Timer Output signal is complemented upon timer Reload.
	 *                     |__ Timer Enable
	 *                         0 = Timer is disabled.
	 *                         1 = Timer enabled to count.
	 *
	 *
	 *
	 *------------------------------------------------------------------------------------------------------------*/


	/*---------------------------------------------------------------------------------------------
	 * Enable timer 0 interrupt via IRQ0ENH and IRQ0ENL. 
	 *
	 * +---------+-------+-------+-------+-------+--------+--------+--------+--------+--------+
	 * |         | BITS  |   7   |   6   |   5   |   4    |   3    |   2    |    1   |    0   |
	 * | IRQ0ENH | ------+-------+-------+------ +--------+--------+--------|--------+--------+
	 * |         | FIELD | T2ENH | T1ENH | T0ENH | U0RENH | U0TENH | I2CENH | SPIENH | ADCENH |
	 * +---------+-------+-------+-------+-------+--------+--------+--------+--------+--------+
	 *                                     |          
	 *                                     |__  T0ENH—Timer 0 Interrupt Request Enable High Bit       
	 *
	 * +---------+-------+-------+-------+-------+--------+--------+--------+--------+--------+
	 * |         | BITS  |   7   |   6   |   5   |   4    |   3    |   2    |    1   |    0   |
	 * | IRQ0ENL | ------+-------+-------+------ +--------+--------+--------|--------+--------+
	 * |         | FIELD | T2ENL | T1ENL | T0ENL | U0RENL | U0TENL | I2CENL | SPIENL | ADCENL |
	 * +---------+-------+-------+-------+-------+--------+--------+--------+--------+--------+
	 *                                     |          
	 *                                     |__  T0ENH—Timer 0 Interrupt Request Enable Low Bit    
	 *
	 *
	 *	IRQ0ENH[x] IRQ0ENL[x]    Priority Description
	 *	     0          0        Disabled Disabled
	 *	     0          1        Level 1 Low
	 * 	     1          0        Level 2 Nominal
	 *	     1          1        Level 3 High
	 *	where x indicates the register bits from 0–7.
	 *----------------------------------------------------------------------------------------------*/

	/*********
	 * enabled timer interrupts
	 */
	 
	setupBlinkInterruptTimer1();
	setupLampInterruptTimer0();
	
    IRQ0ENH |= 0x60;	    // Nominal priority, T0ENH(bit5), T1ENH(bit6) = 1 
    IRQ0ENL &= ~0x60;       // 					 T0ENL(bit5), T1ENH(bit6) = 0
}

	
void setupBlinkInterruptTimer1(){
		unsigned char timerPres;	
		timerPres = 7;
	
		SET_VECTOR(TIMER1, blink_timer);  

		//Reload value = (1 sec * system clock frequency) / prescalar
		//Reload value = (1 * 20000000) / 128 = 78125	(about 1/4 slower)
		T1CTL1 |= 0x1;  // CONTINUOUS mode
		T1CTL1 |= (timerPres<<3); //set the prescale
	
		T1H = (STARTCOUNT >> 8);
		T1L = (STARTCOUNT & 0x00FF);
		T1RH = (BLINK_RELOAD >> 8);
		T1RL = (BLINK_RELOAD & 0x00FF);
		
		T1CTL1 |= 0x80; // Enable timer
	}
	
void setupLampInterruptTimer0(){		
		unsigned char timerPres;
		SET_VECTOR(TIMER0, lamp_timer);  	
		timerPres = 4;
		//Reload value = (1 sec * system clock frequency) / prescalar
		//Reload value = (1 * 20000000) / 128 = 78125	(about 1/4 slower)
		T0CTL1 |= 0x1;  // CONTINUOUS mode
		T0CTL1 |= (timerPres<<3); //set the prescale
	
		T0H = (STARTCOUNT >> 8);
		T0L = (STARTCOUNT & 0x00FF);
		T0RH = (LAMP_RELOAD >> 8);
		T0RL = (LAMP_RELOAD & 0x00FF);
		
		T0CTL1 |= 0x80; // Enable timer
	}
