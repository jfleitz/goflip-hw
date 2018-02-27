/* ********************************************************
* File : scl_interrupt.h
* Description : Header files.  
* 
  Copyright 2004 ZiLOG Inc. ALL RIGHTS RESERVED.
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
**************************************************************/
/*
				
	1)	Project:   To create program to  emulate the I2C slave functionality
				   to Z8ENCORE  Microcontroller.
                  
    	IDE: Zilog ZDSII-Z8Encore version 4.2.1

		Date: 28-04-2003
************************************************************************** 
	2)  Strandard Include files :NIL
****************************************************************************
	3) Application Include files:NIL	
**************************************************************************
	4) Definitions :Listed below
************************************************************************
	5) Revisions: 0.00
**************************************************************************
*/


#define SEND_ACK					0xFE	// AND with PORT C to send ACK
#define SEND_NACK					0x01    //OR with PORT C  to send NACK

#define SDA_READ					0x01
#define SCL_READ					0x02

#define I2C_BUS_FREE				0x00
#define I2C_BUS_BUSY				0x01

#define I2C_ADDRESS_RECEIVE			0x00   // to select the slave address receive mode.
#define I2C_DATA_RECEIVE			0x01   // to select the slave data receive mode.	
#define I2C_DATA_TRANSMITTER 		0x02   // to select the slave transmitter mode.
#define I2C_ADDR_MISMATCH			0x03   // to select the Address mismatch mode.   

#define	SDA_INTR_ENABLE				0x01   // To OR with IRQ register to enable SDA interrupt
#define SDA_INTR_DISABLE			0XFE   // To AND with IRQ register to disable SDA interrupt

#define SDA_DIRECTION_OUT			0xFE
#define	SDA_DIRECTION_IN			0x01

#define SCL_DIRECTION_OUT			0xFD //AND with PC1 fd
#define SCL_DIRECTION_IN			0x02 //OR with PC1
#define RELEASE_SCL					0x02 //OR with PC1 to release SCL
										 //Holding the clock low.
#define HOLD_SCL_LOW				0xFD //AND with PC1 to hold clock low




void SCL_interrupt(void);		// Prototype declaration for SCL interrupt.
void SDA_interrupt(void);
void slave_address_receive(void);
void slave_data_receive(void);
void slave_transmitter(void);
void address_mismatch(void); 



