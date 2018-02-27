/*
********************************************************
* File : sda_interrupt.c
* Description : Codes for I2C slave functionality.  
* 
* Copyright 2004 ZiLOG Inc. ALL RIGHTS RESERVED.
*
* The source code in this file was written by an
* authorized ZiLOG employee or a licensed consultant.
* The source code has been verified to the fullest
* extent possible.
*
* Permission to use this code is granted on a royalty-free
* basis. However users are cautioned to authenticate the
* code contained herein.
*
* ZiLOG DOES NOT GUARANTEE THE VERACITY OF THE SOFTWARE.
*************************************************************
*/

#include <ez8.h>
#include "scl_interrupt.h"


extern unsigned char i2c_flag;
extern unsigned char bus_status;
extern unsigned char bit_counter;
extern unsigned char rising_edge_counter;  // Keeps counts of no 
										//of SCL rising edges 
unsigned char volatile edge_scl;	// To check SCL edge.
unsigned char  volatile edge1;		//To check SDA line
/************************************************************************************************
This is an interrupt service routine. The program jumps to this routine during both the 
rising and falling edges of SDA(on I2C bus). The SDA interrupts are disabled after 
detecting the start condition .The SDA is enabled only at the 10th SCL and after detecting 
the stop condition
************************************************************************************************/

#pragma interrupt
 void SDA_interrupt(void)
 {	
	SET_VECTOR(C0 ,SDA_interrupt);	
 	edge_scl = PCIN & SCL_READ;
	if (edge_scl != 0x02)  	// If SCL is LOW
	{	
		IRQ2 &= 0XFE; // DISABLE ANY INT REQUESTS OF SDA
		IRQ2ENH &= SDA_INTR_DISABLE;    // Disable SDA interrupt
  		IRQ2ENL &= SDA_INTR_DISABLE;    // Disable SDA interrupt
		return;	
	
	}
	else if (edge_scl == 0x02)				// If SCL is HIGH
	{
		edge1 = PCIN & SDA_READ;	//Read SDA when SCL is HIGH
		if(edge1 == 0x01)			//If SDA is HIGH, I2C STOP Condition
		  { 
		     bus_status = I2C_BUS_FREE;
		     i2c_flag = I2C_ADDRESS_RECEIVE;
			 IRQ2 &= 0XFE; // DISABLE ANY INT REQUESTS OF SDA
		     IRQ2ENH |= SDA_INTR_ENABLE;    // Enable SDA interrupt
  			 IRQ2ENL |= SDA_INTR_ENABLE;    // Enable SDA interrupt
			 return;
	 	  }
		 else if(edge1 == 0x00)		// If SDA is LOW ,when SCL is HIGH
		  {							// This is a Start OR Repeat Start Condition.
		        bus_status = I2C_BUS_BUSY;
	  			i2c_flag = I2C_ADDRESS_RECEIVE;
				IRQ2ENH &= SDA_INTR_DISABLE;    // Disable SDA interrupt
  				IRQ2ENL &= SDA_INTR_DISABLE;    // Disable SDA interrupt
			    bit_counter =0x00;				// Reset the bit counter to 0 
				rising_edge_counter =0x00;		//The bit counter to start from 0 during the Start
												// OR Repeat Starat condition and from 1 after 
												// receiving the first (address) byte
		  }
	   
    }

 }


