/*
********************************************************
* File : switchMatrix.c
* Based on scl_interrupt.c (from AN0139-SC02 and LampDriver)
* Description : Drives a switch Matrix and reports back by SPI
*  PC0 and PC1 have to be used for the i2c pins, as these have interrupt triggering
**************************************************************
*/


/*From ~/DropBox/Bossy/Workspace/pinsupport.cpp (2012 ish?)
Description: Interrupt Timer handler that will take in the values from the input buffer, compare to the previous values. New values stored. Anything changed, then switch buffer will be added to.

explanation is at: http://www.compuphase.com/electronics/debouncing.htm
*/


#define PROTOTYPE_BOARD 1 //Define this for the proto board


#include <ez8.h>
#include <stdio.h>
#include "spibase.h"
#include "sysclk.h"
#include "timer.h"
#include "switchmatrix.h"
/*
PB0-PB2 = Strobe Select (outputs)
PA0-PA7 = Switch Inputs (inputs)
PB3, PB4 = LED indicators (outputs)

PC0, PC1 = Switch Inputs
PC2 = SS
PC3 = SCLK
PC4 = MOSI
PC5 = MISO
*/

unsigned char const NOOUTPUT = 0x00;
const int NUMBER_OF_SWITCH_SAMPLES = 1;


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


/*Switch Specific Variables*/
unsigned char _slowBlink;
unsigned char _fastBlink;
int  _timerControl;

unsigned char _swStrobe = 0;

unsigned char _downLED = 0; //0 = off, 1=turn on, 2=on (so turn off next time around) PB3
unsigned char _upLED = 0; //0 = off, 1=turn on, 2=on (so turn off next time around) PB4

unsigned char const PB_DOWN_LED = 0x08; //0000 1000
unsigned char const PB_UP_LED =0x10; //0001 0000

void Initialize(void);
void SwitchLoop(void);
void ReportSwitchChange(unsigned char, unsigned char, unsigned char);
int ledIsOn;


/* *******************************************************************************
The main routine ,sets the Port pins PC0 and PC1 to work as either input or output
with open drain.The I2C bus status is set to free(No Transaction on the I2C bus).
Sets the interrupt PC0 and PC1 to highist priority.Enables the interrupt.
/*********************************************************************************/ 


void main()
{
  Initialize();	
  SwitchLoop();
 }

void Initialize(void){
    DI();				// Globally disable all interrupts    
    sysclk_init();		// Initialize system clock per the selected clock source/frequency from project
	                    // setting and in the sysclk.c	
    timer_init();		// Intialize timer
	
	
	//JAF TEMPORARY InitializeSPI();	//initialize SPI routines
	
	/*
	PB0-PB2 = Strobe Select (outputs)
	PA0-PA7 = Switch Inputs (inputs)
	PB3, PB4 = LED indicators (outputs)

	PC0, PC1 = Switch Inputs (need to do this still)
	PC2 = SS
	PC3 = SCLK
	PC4 = MOSI
	PC5 = MISO
	*/
	
	
  //PB0-2 are TTL Output for Strobe control to the 74ls138
  //PB3-4 are open drain outputs for LEDs
  PBADDR = 0x01; // Direction
  PBCTL = 0xE0; //1110 - 0000 all putputs are zeros
  PBADDR = 0x03; //output control
  PBCTL = 0x18;     //0001-1000 (open drain on PB3-PB4 for the LEDs)
  PBADDR = 0x00;

  //PA0-7 are TTL input (from the 339 comparators)
  PAADDR = 0x01; //Data Direction
  PACTL = 0xFF; //1111 - 1111 all inputa
  PAADDR = 0x00;

  //SPI Setup
  PCADDR = 0x01;	//Set the  Value to select DATA direction
  PCCTL  = 0x1f;   // Change SDA to INPUT PC0-PC4 are all In, PC5 is an out, so 0x1f
  PCADDR = 0x00;

	

EI();				//Enable all interrupts
  
}
 


void SwitchStrobeIncAndSet()
{
    int outputValue = 0x00;

    if(_swStrobe>=8)
    {
        _swStrobe = 0;
    }

	//PBOUT |= _swStrobe & 0x07;
	//PBOUT |= 0x01; //setting bit 0
	PBOUT &= 0xF8; //clearing Bit 0, 1 and 2 
    _swStrobe++;
}



/*Switch Matrix Handling routines*/

/*
Description: Interrupt Timer handler that will take in the values from the input buffer, compare to the previous values. New values stored. Anything changed, then switch buffer will be added to.

explanation is at: http://www.compuphase.com/electronics/debouncing.htm

*/

//This will debounce the strobe sample passed in, as well as update the debounced state when necessary (after 4 vertical counter cycles)
//Needs to be called every 5 ms per strobe. Therefore 8 strobes = 5ms/8 = every 625uSec
//Returns changes after they have been debounced.
unsigned char debounce(unsigned char strobeSample, int strobe, unsigned char *toggle)
{
    static unsigned char debounced_state[8], clock_B[8],clock_A[8];
    unsigned char delta;
    \

    delta = strobeSample ^ debounced_state[strobe];
    clock_B[strobe] = (clock_B[strobe] ^ clock_A[strobe]) & delta;
    clock_A[strobe] = ~clock_A[strobe] & delta;

    *toggle = delta & ~(clock_A[strobe] | clock_B[strobe]);
    debounced_state[strobe] ^= *toggle;

    return debounced_state[strobe]; //debounced_state[strobe];
}



void SwitchLoop(void){
	int i;
	unsigned int count =60;
	//unsigned long int count = 60;  //about 86 clock cycles per while loop, so this should be 260 usec?  

	/*
	PB0-PB2 = Strobe Select (outputs)
	PA0-PA7 = Switch Inputs (inputs)
	PB3, PB4 = LED indicators (outputs)

	PC0, PC1 = Switch Inputs (need to do this still)
	PC2 = SS	
	PC3 = SCLK
	PC4 = MOSI
	PC5 = MISO
	
	What we will send:
	Bits 2-7 = Switch ID (64 switch combinations)
	Bits 0-1 = 
		00 = now open
		01 = now closed
		10 = 
		11 = 
	*/
	unsigned char sample;
	char curSwitches;
	unsigned char toggle;
	
	_upLED = 1;
	_downLED = 1;

	while(1){
		SwitchStrobeIncAndSet();
		

#if defined(PROTOTYPE_BOARD)		
		//need to set _reg3		
		//sample = PCIN&0x01; --This is for the hardwired button
		sample = PAIN & 0xC0; //PA6 and PA7 only for the demo board with the 64 sw tester.
								//C1, C2, C4 are on the 64 key
								//R1 and R2
		
#else
		sample = PAIN;
#endif
		
		
		
		curSwitches =debounce(sample, _swStrobe, &toggle);
		
		if(toggle!=0x00){
			//depending if anything changed, we need to notify the RaspPi, as well as do the diag leds
			//therefore previous prob needs to return changes so that we know we need to report.
			
			//this might not work since if the switch was just released, then it would 0
			ReportSwitchChange(_swStrobe,curSwitches, toggle);
			
		}
		while(count>0)
			count--;
		count=60;
	}
}

void ReportSwitchChange(unsigned char strobe, unsigned char switches, unsigned char toggle){
	int curBit = 1;
	int i;
	int report=0x00;
	
	for(i=0;i<8; i++){
		if(toggle&curBit!=0){
			//Report Strobe is Bits 7-5, Switches are Bits 4-2, Bits 0 and 1 are state of switch
			report = (((strobe<<4) & i)<<2);
			
			//switches&curBit = new state of the switch that we are looping on. (if 0 = false >0 = true
			//report last 2 bits as 1 = now high, and 0 = now low
			if(switches&curBit!=0){
				report &= 0xFE;
				_upLED = 1;
			}
			else{
				report &= 0xFD;
				_downLED =1;
			}			
		}
		curBit=curBit<<1;
	}
	
	SPI_Send(report);   // Exchange the data
}

/*
const char DataOut[] = "Hello ZiLOG!"; // Output Buffer

char DataIn[DATASIZE];                 // Input Buffer

void main()
{
   SPI_Init();       // Start the slave driver
   IdlePorts();      // Set port modes and conditions
   EI();

   SPI_SendReceiveBlock(DataOut, DataIn, strlen(DataOut));

   if (!strncmp(DataOut, DataIn, strlen(DataOut)))
   {
      T1PWM = 0;
   }

   while (ALWAYS)
   {
      T1PWM = SPI_SendReceive(0xAA);   // Exchange the data
   }
}*/


void blinkISR(){
	
	switch(_upLED){
		case 0:
			//no blink
			break;
		case 1: //turn on
			PBOUT &=~PB_UP_LED;
			_upLED = 2;
			break;
		case 2:
			//has been on, so turn off and reset
			PBOUT|=PB_UP_LED;
			_upLED = 0;
			break;
		}
	
	switch(_downLED){
		case 0:
			//no blink
			break;
		case 1: //turn on
			PBOUT &=~PB_DOWN_LED;
			_downLED = 2;
			break;
		case 2:
			//has been on, so turn off and reset
			PBOUT|=PB_DOWN_LED;
			_downLED = 0;
			break;
		}
		
	}
	