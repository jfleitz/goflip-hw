/*
********************************************************
* File : lampDriver.c
* Based on scl_interrupt.c (from AN0139-SC02)
* Description : Drives a lamp Driver board using i2c
*  PC0 and PC1 have to be used for the i2c pins, as these have interrupt triggering
*
*
* Drives 64 lamps
* Data Byte command: 0bAAAA AAcc
* Bits A (data bit 2-7) = Lamp Address
* Bits C:
*		00 = off
*		01 = on
*		10 = slow blink
*		11 = fast blink
*
*
*
*	Green = Lamp Adress 1 (8) = pin 9 = pa0
*	Blue = Lamp Address 2 (9) = pin 7 = pa1
*	Purple = Address 3 (4) = pin 5 = pa2
*	Gray = Address 4 (3) = pin 3 = pa3
*
*	Brown = Lamp En 1 (1)= pin 18 = pa4
*	Red =  Lamp En 2 (2) = pin 16 = pa5
*	Orange = Lamp En 3(5) = pin 14 = pa6
*	Yellow = Lamp En 4 (7) = pin 12 = pa7
*
*
*	Lamp En must be 0 for selecting.
*	Address is active high
*
*
**************************************************************
*/

#include <ez8.h>
#include <stdio.h>

#include "lampDriver.h"
#include "timer.h"
#include "sysclk.h"
#include "i2cbase.h"

unsigned char const _ldu_map[64]= {0xE0,0xE1,0xE2,0xE3,0xE4,0xE5,0xE6,0xE7,0xE8,0xE9,
0xEA,0xEB,0xEC,0xED,0xEE,0xEF,0xD0,0xD1,0xD2,0xD3,0xD4,0xD5,0xD6,0xD7,0xD8,0xD9,
0xDA,0xDB,0xDC,0xDD,0xDE,0xDF,0xB0,0xB1,0xB2,0xB3,0xB4,0xB5,0xB6,0xB7,0xB8,0xB9,
0xBA,0xBB,0xBC,0xBD,0xBE,0xBF,0x70,0x71,0x72,0x73,0x74,0x75,0x76,0x77,0x78,0x79,
0x7A,0x7B,0x7C,0x7D,0x7E,0x7F};


long _dataIn;

/*Lamp Specific Variables*/
unsigned char _lightControl[64];
unsigned char _slowBlink;
unsigned char _fastBlink;
unsigned char _strobe = 0;
unsigned char _lmp = 0;
unsigned char _diagMode = 0;

int  _timerControl;

int _lampCounter = 0;

unsigned char const BLINKON = 0x3f;
unsigned char const BLINKOFF =0x00;

void Initialize(void);
void LampLoop(void);
void SetLampAll(int value);
void SetLamp(int , unsigned char );
void DiagLEDControl(unsigned char);
static void pause( void );
int ledIsOn;


unsigned char lastDataReceived;


/* *******************************************************************************
The main routine ,sets the Port pins PC0 and PC1 to work as either input or output
with open drain.The I2C bus status is set to free(No Transaction on the I2C bus).
Sets the interrupt PC0 and PC1 to highist priority.Enables the interrupt.
/*********************************************************************************/ 
void main()
{
  lastDataReceived = 0x00;
  Initialize();
  LampLoop();
 }


 
 void Initialize(void){
	DI();				// Globally disable all interrupts    

	InitializeI2C();

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

	PCCTL |= 0x0C;	//PC2-3 are input
	_slowBlink = BLINKOFF;
	_fastBlink = BLINKOFF;

	SetLampAll(0);
	EI();				//Enable all interrupts
	PBOUT |= 0xF8; //set to zero
  
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
	int i;
	unsigned long int count;

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

portB:
0=LED1
1=LED2
2=LED3
3=n/a
4=Lamp Enable
*/	


	PBOUT &= 0xEF; //PB4 is lamp enable (active low)
	while(1){
		//just loop through each lamp value...
		for(i=0;i<64;i++){
			switch(_lightControl[i]){
				case 1: //on
					PAOUT = _ldu_map[i];
					pause();
					break;
				case 2: //slow blink
					if(_slowBlink==0x01){
						PAOUT = _ldu_map[i];
						pause();
					}
					else{
						PAOUT = 0x00;
					}
					break;
				case 3: //fast blink
					if(_fastBlink==0x01){
						PAOUT = _ldu_map[i];
						pause();
					}
					else{
						PAOUT = 0x00;
					}
					break;
			}
		}
		DiagLEDControl(_lightControl[22]); //calling every end of loop using lamp 22

	}	
}


void DiagLEDControl(unsigned char command){
	if(lastDataReceived!=0x00){
		lastDataReceived = 0x00;
	}
	
	switch(command){
		case 1:
			PBOUT &= 0xFD; //on  
			break;
		case 2:
			if(_slowBlink==0x01){
				PBOUT &= 0xFD;
				}
				else{
					PBOUT |= ~0xFD;
					}
			break;
		case 3:
			if(_fastBlink==0x01){
				PBOUT &= 0xFD;
				}
				else{
					PBOUT |= ~0xFD;
					}
			break;
		default:
			PBOUT |= ~0xFD; //off
		}
}


/*
			switch(_diagMode){
				case 1:
					PBOUT &= 0xED; //on  (JAF changed to E from F so that PB4 is off(active low)
					break;
				case 2:
					if(_slowBlink==0x01){
						PBOUT &= 0xED;
						}
						else{
							PBOUT |= ~0xED;
							}
					break;
				case 3:
					if(_fastBlink==0x01){
						PBOUT &= 0xED;
						}
						else{
							PBOUT |= ~0xED;
							}
					break;
				default:
					PBOUT |= ~0xED; //off
				}
*/


	/*
	bool_t DebounceSwitch2()
{
    static uint16_t State = 0; // Current debounce status
    State=(State<<1) | !RawKeyPressed() | 0xe000;
    if(State==0xf000)return TRUE;
    return FALSE; 
}
*/
BOOL RawUpSwitch(){
	char temp;
	temp = PCIN;
	return ((temp & 0x08) == 0x00);
}

BOOL DebounceUpSwitch(){
	static UINT16 upState = 0; //current debounce status
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
				SetLampAll(1);
				break;
			case 2:
				SetLampAll(2);
				break;
			case 3:
				SetLampAll(3);
				break;
			default:
				SetLampAll(0);
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
	
	
//Processes the I2C message
void processMessage(unsigned char data, long dataIn){
	//two 6 bits are the lamp
	int lampAddress = 0x3f & (data>>2);
	int lampValue = 0x03 & data;
		
	_dataIn = dataIn;
	_lightControl[lampAddress]=lampValue;
	lastDataReceived = data;
	return;
}

static void pause( void )
{
   unsigned long int count = 20;//60;//214 //53581;
   
   while ( count > 0 )
      count -= 1;
      
   return;
}
