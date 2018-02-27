#include <ez8.h>
#include <stdio.h>
#include "i2cbase.h"
#include "sysclk.h"
#include "timer.h"
#include "lampdriver.h"
/*i2cBase.c - Written by Jeremy Fleitz
Based on Application Note 0139 from ZiLog for implementing I2C
Also based on the documentation found at:
http://www.best-microcontroller-projects.com/i2c-tutorial.html

The original application note lacks some base functionality to make the Z8 encore a true slave for Raspberry PI applications
*/


/* JAF 05/24 - curious to see if we reset bit_counter = 1 every time, will that work


/*i2c variables*/ 

unsigned char  i2c_flag;		// To hold the Different status of I2C

unsigned char bit_counter;	// To keep count of no of bits received 
							// This counter will reset when the count ==9
unsigned char data_receive_byte; // To store the data byte received.

unsigned char data_transmit_byte; // To store the data to be transmitted

unsigned char volatile sda_bit;	 //Read the SDA bit
unsigned char bus_status; // To set bus busy or free flag
unsigned char rising_edge_counter;  // Keeps counts of no of SCL rising edges 
									// in a byte.
unsigned char volatile address_received;		//Store the address received
unsigned char volatile data_byte;        	// Store the data received.
unsigned char volatile edge;
unsigned char volatile temp1;
unsigned char volatile send_bit;  // Stores the MSB to be transmitted
unsigned char byte_count; // Count no of bytes received.

//For the SDA interrupt
unsigned char volatile edge_scl;	// To check SCL edge.
unsigned char  volatile edge1;		//To check SDA line

long dataIn;


//Initialization of  the function pointer
void (*function_ptr[4])(void) = { 
	slave_address_receive,
	slave_data_receive,
	slave_transmitter,
	address_mismatch }; 

void InitializeI2C(void){
	dataIn = 0;
	PCADDR = 0x03 ; //For open drain mode.
	PCCTL |= 0x03; // Port pin PC0 to open drain mode.

	i2c_flag = I2C_ADDRESS_RECEIVE;	
	PCADDR = 0x01;				//Set the  Value to select DATA direction
	PCCTL  |= SDA_DIRECTION_IN;   // Change SDA to INPUT
	PCCTL  |=	SCL_DIRECTION_IN;   //OR with PC1

	bus_status = I2C_BUS_FREE;	// Indicates bus status is "FREE"
	IRQ2ENL = 0x03;
	IRQ2ENH = 0x03;    // Set SDA and SCL for Highist priority
	
    sysclk_init();		// Initialize system clock per the selected clock source/frequency from project
	                    // setting and in the sysclk.c	
    timer_init();		// Intialize timer
}


#pragma interrupt
 void SDA_interrupt(void)
 {	
	SET_VECTOR(C0 ,SDA_interrupt);	
 	edge_scl = PCIN & SCL_READ;
	if (edge_scl != 0x02)  	// SCL/Clock = 0
	{	
		//Disabling since we don't care of any SDA changes while Clock is low
		IRQ2 &= 0XFE; // DISABLE ANY INT REQUESTS OF SDA
		IRQ2ENH &= SDA_INTR_DISABLE;    // Disable SDA interrupt
  		IRQ2ENL &= SDA_INTR_DISABLE;    // Disable SDA interrupt
		return;	
	
	}
	else if (edge_scl == 0x02)				// SCL/Clock = 1
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
			    bit_counter =0x00;
				data_receive_byte = 0x00;	//reinitialize, since we are restarting.
				rising_edge_counter =0x00;		//The bit counter to start from 0 during the Start
												// OR Repeat Starat condition and from 1 after 
												// receiving the first (address) byte
		  }
	   
    }

 }

/* ******************************************************************************************
This is an interrupt service routine. The program jumps to this routine during both the 
rising and falling edges of SCL(on I2C bus). During the rising edge of the clock,a counter
"rising_edge_counter" is incremented to keep track the number of SCL and to take appropriate
decisions. This routine reads the data on the SDA line during the High level of SCL. This 
data is shifted(MSB is received or transmitted first) and a byte of data is formed after all
8 bits are received.During the low edge of SCL, this function invoke calls to different 
functions based on the I2C flag status.
******************************************************************************************* */

#pragma interrupt
 void SCL_interrupt(void)
 {
    edge = PCIN & SCL_READ;
 	SET_VECTOR(C1 ,SCL_interrupt);
	 if (edge == 0x02)  		// Rising edge detected.
		{	
			rising_edge_counter++;

			//always re-enabling if we are making the clock high, so that we can detect Stop and Start signals
			IRQ2 = IRQ2 & 0XFE;				//Disable pending interrupt requests of SDA
			IRQ2ENH |= SDA_INTR_ENABLE;    // Enable SDA interrupt
			IRQ2ENL |= SDA_INTR_ENABLE;    // Enable SDA interrupt

			dataIn |= sda_bit;
			dataIn <<= 1;
			
		    if(rising_edge_counter <= 0x07)
			{
				sda_bit = PCIN & SDA_READ;	
   				data_receive_byte |= sda_bit;	//Store the received data in 
   				data_receive_byte <<= 0x01;		//"receive_byte" register.
				
			}
			if(rising_edge_counter == 0x08)
			{
				sda_bit = PCIN & SDA_READ;		// Read the last bit of data and
   				data_receive_byte |= sda_bit;	// store as LSB without shifting. 
			}
		}
	else		// Falling edge detected
	{
		IRQ2ENH &= SDA_INTR_DISABLE;    // Disable SDA interrupt
	  	IRQ2ENL &= SDA_INTR_DISABLE;    // Disable SDA interrupt
				
		PCCTL  &= SCL_DIRECTION_OUT; 	// Change SDA to OUTPUT
	  	PCOUT  &= HOLD_SCL_LOW;		 	// Hold	SCL low	to add wait states
		(*function_ptr[i2c_flag])(); 	//Call the relevent functions using Function Pointer.
		PCCTL |= SCL_DIRECTION_IN;   	// Change SDA to INPUT

	}	 
}
/* ******************************************************************************************
This fuction, after receiving the address on the I2C bus , compares with the device address.
Sends Acknowledge if the Address received matches with the device address(AE in this example)
otherwise it sets the address mismatch flag. This function also checks if the  master wants to read from the 
slave or write to slave and accordingly sets the slave to either read or write mode.
******************************************************************************************* */


void slave_address_receive(void)

{
 

		bit_counter++; 
		if(bit_counter <= 0x08)					//The data of SDA is read in the rising edge 
			{									// of SCL.In the low level of clock data
				return;							//data is not read.
			}								
		if(bit_counter == 0x09)
			{
				address_received = data_receive_byte;   // Store the address received 
				temp1 = (data_receive_byte & 0xFE);		//Extaract only 7 bit address information.
				if(temp1 == DEVICE_ADDRESS) 
					{
 	 				   	PCCTL  &= SDA_DIRECTION_OUT;   // Change SDA to OUTPUT
						PCOUT &= SEND_ACK;			   //Send Acknowledgement 
	    				return;
				   	}
  				else 
   				 {
					i2c_flag = I2C_ADDR_MISMATCH;	// Set the address mismatch condition.
					return; 
				}	
			}
          if(bit_counter == 0x0A)
			{
				bit_counter = 0x01;		//Initialise the bit counter.
				rising_edge_counter = 0x00;
				temp1 = data_receive_byte;
				temp1 &= 0x01;
		    	if(temp1 == 0x01) 			// Check if slave in read
    		     	{						// OR Slave Transmit mode.
					//	send_bit = 	data_transmit_byte;
						send_bit = data_byte;
						send_bit &= 0x80;
						send_bit = send_bit >> 0x07;	// Extract MSB of data_transmit_byte
						PCCTL  &= SDA_DIRECTION_OUT; // Change SDA to OUTPUT
						PCOUT |= send_bit;		// Send the MSB of data byte on SDA 	
						i2c_flag = I2C_DATA_TRANSMITTER;  // Set the slave to slave transmit mode
						return;
					}
       			else
					{
						i2c_flag = I2C_DATA_RECEIVE;  // Set the flag to data receive mode.
						PCCTL  |= SDA_DIRECTION_IN;		 //Chanege SDA to INPUT
				 	}							      
			}	
	}
/* ****************************************************************************************
This function is  sends an acknowledge after a complete data byte is received.
Stores the received byte in a buffer.
*******************************************************************************************/

void slave_data_receive(void)
{	
	int lamp = 0;
	int value = 0;
	
		
  	  bit_counter++;  //Keep the count of no of bits received.
 	  if(bit_counter <=0x08)
		{
			return;
		}

	  if(bit_counter == 0x09)
		{
		data_byte = data_receive_byte;	// Store the data received.

/*Call the function for processing I2C Data
		switch(data_byte){
			case 0x13:
				_diagMode = 2;
				break;
			case 0x38:
				_diagMode = 3;
				break;
			case 0x22:
				_diagMode = 0;
				break;
			default:
				_diagMode = 1;
			}
			*/
		processMessage(data_byte, dataIn);

		PCCTL  &= SDA_DIRECTION_OUT; // Change SDA to OUTPUT
		PCOUT &= SEND_ACK;			 //Send Ack or Nack 
		return;
		}
	 else if(bit_counter ==0x0A)
	   {
	   bit_counter = 0x00;			     // Reset the bit counter.  (changed to 0 from 1)
       PCCTL  |= SDA_DIRECTION_IN;		 //Chanege SDA to INPUT
	   }
  }

/*****************************************************************************************
This function shifts the data in the transmit_data_byte and shifts the appropriate bit
on SDA line during the low period of SCL. After sending a byte of data it checks for 
acknowledge from the master. If master sends NACK(No-Acknowledgement), then slave stops
sending another byte of data. If it receives acknowledgement from the master ,it stars
sending the next data byte.However in this case the implementation is done for one byte
transfer and hence no code is written for transmitting multiple byts.
****************************************************************************************** */


void slave_transmitter(void)
{
			bit_counter++;  //Keep the count of no of bits transmitted.
			if(bit_counter <= 0x08)
		    {
			//	send_bit=data_transmit_byte;
				send_bit = data_byte;
				send_bit = (send_bit >>(8-bit_counter));
				send_bit &= 0x01;
				if(send_bit == 0x01)
				{
				PCOUT |= send_bit; 			//Send data on SDA line.
				
				}
				else
				{
				PCOUT &= 0xFE;
				
				}
	
				return; 
			}
		 	if(bit_counter == 0x09)
			{
				PCCTL  |= SDA_DIRECTION_IN;  // Change SDA to INPUT
				return;
			}

    	    if(bit_counter == 0X0A)
    		{
				if(sda_bit ==0x01)
	 				{
					  return; //Do not send next byte.
				   }
				else  
					{
						bit_counter = 0x01;
						//Prepare to  send the next byte; // Not implemented
				
				}
			}

	 }


/*************************************************************************************
This function is called when the received address do not match with the slave address.
Resets the bit counter to "0".
***************************************************************************************/

 void  address_mismatch(void)
 {
	
	bit_counter++;
	if(bit_counter == 0x0A)
		{
		 bit_counter = 0x00; 
		}
 }


