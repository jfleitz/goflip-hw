/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   peripheralThread.h
 * Author: drjones
 *
 * Created on May 10, 2016, 9:12 PM
 */

#ifndef PERIPHERALTHREAD_H
#define PERIPHERALTHREAD_H

#include "messageQueue.h"

#ifdef __cplusplus
extern "C" {
#endif

#define I2C_LAMP_DRIVER_ADDRESS        0x04   //LDU
#define I2C_SOLENOID_DRIVER_ADDRESS 0x05 //SDU

	extern pthread_rwlock_t peripheralInfoLock;
	extern struct message_struct *peripheralMsgQueue_ptr; //Peripheral Queue to add commands to, to get marshalled out to the i2c connected devices etc.
	extern int exitPeripheralThread;
	extern pthread_t peripheralThread;



	void *PeripheralHandler(void *);
	void InitializePeripheralThread(pthread_t *);
	void PQSend(message_type , int, int, int);
	void StopPQThread();
	


#ifdef __cplusplus
}
#endif

#endif /* PERIPHERALTHREAD_H */

