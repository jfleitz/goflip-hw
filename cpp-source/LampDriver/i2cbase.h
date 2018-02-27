#ifndef _I2CBASE_H_
#define _I2CBASE_H_


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

#define DEVICE_ADDRESS				0x0C //0000 1100 = address 06


void InitializeI2C(void); //call this in main.

void SCL_interrupt(void);		// Prototype declaration for SCL interrupt.
void SDA_interrupt(void);
void slave_address_receive(void);
void slave_data_receive(void);
void slave_transmitter(void);
void address_mismatch(void); 

#endif

