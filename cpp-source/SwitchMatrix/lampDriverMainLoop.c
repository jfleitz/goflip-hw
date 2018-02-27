/*
********************************************************
* File : lampDriver.c
* Based on scl_interrupt.c (from AN0139-SC02)
* Description : Drives a lamp Driver board using i2c
*  PC0 and PC1 have to be used for the i2c pins, as these have interrupt triggering
**************************************************************
*/

#include <ez8.h>
#include <stdio.h>
#include "lampDriver.h"
#include "timer.h"
#include "sysclk.h"

unsigned char _ldu_map[64]= {0x10,0x11,0x12,0x13,0x14,0x15,0x16,0x17,0x18,0x19,
0x1A,0x1B,0x1C,0x1D,0x1E,0x1F,0x20,0x21,0x22,0x23,0x24,0x25,0x26,0x27,0x28,0x29,
0x2A,0x2B,0x2C,0x2D,0x2E,0x2F,0x40,0x41,0x42,0x43,0x44,0x45,0x46,0x47,0x48,0x49,
0x4A,0x4B,0x4C,0x4D,0x4E,0x4F,0x80,0x81,0x82,0x83,0x84,0x85,0x86,0x87,0x88,0x89,
0x8A,0x8B,0x8C,0x8D,0x8E,0x8F};

#define NOOUTPUT = 0x00


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


/*Lamp Specific Variables*/
unsigned char _lightControl[64];
unsigned char _slowBlink;
unsigned char _fastBlink;
unsigned char _strobe = 0;
unsigned char _lmp = 0;



INT8 _timerControl;
INT16 _delayCounter;

unsigned char _diagMode = 0;


unsigned char const BLINKON = 0x3f;
unsigned char const BLINKOFF =0x00;

void Initialize(void);
void InitLampArray(char);
void SetLampValue(unsigned char data);
void LampLoop(void);
void SetAllLamps(int value);

int ledIsOn;

//Initialization of  the function pointer
void (*function_ptr[4])(void) = { 
	slave_address_receive,
	slave_data_receive,
	slave_transmitter,
	address_mismatch }; 

/* *******************************************************************************
The main routine ,sets the Port pins PC0 and PC1 to work as either input or output
with open drain.The I2C bus status is set to free(No Transaction on the I2C bus).
Sets the interrupt PC0 and PC1 to highist priority.Enables the interrupt.
/*********************************************************************************/ 


void main()
{
  Initialize();
	
	/*
unsigned char timer_control = enable_disable|polarity|prescale|timer_mode;
// this information will go to
// timer control register
init_timer(timer_no, timer_control, start_high, start_low, reload_high,
reload_low, pwm_high, pwm_low);	
	*/
	
  PBOUT |= 0xF8; //set to zero
  LampLoop();
 }

void Initialize(void){
	_delayCounter = 0;
    DI();				// Globally disable all interrupts    
    sysclk_init();		// Initialize system clock per the selected clock source/frequency from project
	                    // setting and in the sysclk.c	
    timer_init();		// Intialize timer

	
  //PB0-3 are open drain for LED control
  PBADDR = 0x01; // Direction
  PBCTL = 0xE8; //1110 - 1000 all putputs are zeros
  PBADDR = 0x03; //output control
  PBCTL = 0x07;     //0000-0111 (open drain on PB0-PB3)
  PBADDR = 0x00;
	
  //PA0-7 should be TTL output
  PAADDR = 0x01; //Data Direction
  PACTL = 0x00; //0000 - 0000 all putputs are zeros
  PAADDR = 0x03;
  PACTL = 0x00; //TTL Output
  PAADDR = 0x00;
  
  PCADDR = 0x03 ; //For open drain mode.
  PCCTL |= 0x03; // Port pin PC0 to open drain mode.

  i2c_flag = I2C_ADDRESS_RECEIVE;	
  PCADDR = 0x01;				//Set the  Value to select DATA direction
  PCCTL  |= SDA_DIRECTION_IN;   // Change SDA to INPUT
  PCCTL  |=	SCL_DIRECTION_IN;   //OR with PC1
  //PC2-3 are input
  PCCTL |= 0x0C;

  bus_status = I2C_BUS_FREE;	// Indicates bus status is "FREE"
  IRQ2ENL = 0x03;
  IRQ2ENH = 0x03;    // Set SDA and SCL for Highist priority

  _slowBlink = BLINKOFF;
  _fastBlink = BLINKOFF;

  InitLampArray(0);
EI();				//Enable all interrupts
  
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
		    if(rising_edge_counter == 0x0A)  
			 {
				rising_edge_counter = 0x01;
				IRQ2 = IRQ2 & 0XFE;				//Disable pending interrupt requests of SDA
				IRQ2ENH |= SDA_INTR_ENABLE;    // Enable SDA interrupt
  				IRQ2ENL |= SDA_INTR_ENABLE;    // Enable SDA interrupt
					
		   }

			else
			 {
				IRQ2ENH &= SDA_INTR_DISABLE;    // Disable SDA interrupt
  				IRQ2ENL &= SDA_INTR_DISABLE;    // Disable SDA interrupt
				
			 }

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
  	  bit_counter++;  //Keep the count of no of bits received.
 	  if(bit_counter <=0x08)
		{
			return;
		}

	  if(bit_counter == 0x09)
		{
		data_byte = data_receive_byte;	// Store the data received.
		SetLampValue(data_byte);
		PCCTL  &= SDA_DIRECTION_OUT; // Change SDA to OUTPUT
		PCOUT &= SEND_ACK;			 //Send Ack or Nack 
		return;
		}
	 else if(bit_counter ==0x0A)
	   {
	   bit_counter = 0x01;			     // Reset the bit counter.
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

	

void SetLampAll(int value){
	int i;
	for(i=0;i<64;i++){
		_lightControl[i]=value;
		}
	}
	
void SetLamp(int lmp, unsigned char data){
	//00=off, 01=on, 10=slow blink, 11=fast blink
	_lightControl[lmp]=data;
}


void LampLoop(void){

	/*
porta bit:
0=lamp0
1=lamp1
2=lamp2
3=lamp3
4=str0
5=str1
6=str2
7=str3
*/	
	while(1){
		//just loop through each lamp value...
		int i;
		for(i=0;i<64;i++){
			switch(_lightControl[i]){
				case 1: //on
					PAOUT = _ldu_map[i];
					break;
				case 2: //slow blink
					if(_slowBlink)
						PAOUT = _ldu_map[i];
					else
						PAOUT = NOOUTPUT;
					break;
				case 3: //fast blink
					if(_fastBlink)
						PAOUT = _ldu_map[i];
					else
						PAOUT = NOOUTPUT;
					break;
				default:
					//off
					PAOUT = NOOUTPUT;
			}
			
			//pause here for some time.
			
		}
	}	
}

	/*
	bool_t DebounceSwitch2()
{
    static uint16_t State = 0; // Current debounce status
    State=(State<<1) | !RawKeyPressed() | 0xe000;
    if(State==0xf000)return TRUE;
    return FALSE; 
}
*/
bool RawUpSwitch(){
	char temp;
	temp = PCIN;
	return ((temp & 0x08) == 0x00);
}

bool DebounceUpSwitch(){
	static uint16 upState = 0; //current debounce status
	upState=(upState<<1) | !RawUpSwitch() | 0xe000;
	if(upState==0xf000) return TRUE;
	return FALSE;
}

void lampISR()
{
	if(DebounceUpSwitch()){
		//pressed, so increment where we are in the diagnosis
		if(_diagMode>4)
			_diagMode = 0;
		else
			_diagMode++;
		
		switch(_diagMode){
			case 1:
				SetAllLamps(1);
				break;
			case 2:
				SetAllLamps(2);
				break;
			case 3:
				SetAllLamps(3);
				break;
			default:
				SetAllLamps(0);
			}
	}
}
	
	


void blinkISR(){
	if(_timerControl>3){
		_timerControl = 0;
	}
	
	switch(_timerControl){
		case 0:
			_slowBlink=0x00;
			_fastBlink =0x00;
			break;
		case 1:
			_slowBlink = 0x00;
			_fastBlink=0x01;
			break;
		case 2:
			_slowBlink = 0x01;
			_fastBlink = 0x00;
			break;
		case 3:
			_slowBlink = 0x01;
			_fastBlink = 0x01;
			break;
		}
		
		_timerControl++;
	}