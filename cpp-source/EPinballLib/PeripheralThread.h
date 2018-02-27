/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   PeripheralThread.h
 * Author: drjones
 *
 * Created on September 27, 2016, 9:05 PM
 */

#ifndef PERIPHERALTHREAD_H
#define PERIPHERALTHREAD_H
#include <pthread.h>

typedef enum {
	MSG_LAMP, MSG_SOLENOID, MSG_SOUND, MSG_DISPLAY, MSG_EVENT
} message_type;


struct message_struct {
	int commandID;
	int commandValue;
	int priority;
	message_type messageType;

	struct message_struct *next;
};


//we should have our global accessible variables here (that would be used by MessageBase)
#define I2C_LAMP_DRIVER_ADDRESS        0x04   //LDU
#define I2C_SOLENOID_DRIVER_ADDRESS 0x05 //SDU

#define I2C_LAMP_DRIVER_ADDRESS        0x04   //LDU
#define I2C_SOLENOID_DRIVER_ADDRESS 0x05 //SDU

extern pthread_rwlock_t peripheralInfoLock;
extern struct message_struct *peripheralMsgQueue_ptr; //Peripheral Queue to add commands to, to get marshalled out to the i2c connected devices etc.
extern int exitPeripheralThread;
extern pthread_t peripheralThread;


extern pthread_cond_t newMessageCV ;
extern pthread_mutex_t newMessageMutex;



class PeripheralThread {
public:
	PeripheralThread();
	PeripheralThread(const PeripheralThread& orig);
	virtual ~PeripheralThread();
	
	
private:

};

#endif /* PERIPHERALTHREAD_H */

