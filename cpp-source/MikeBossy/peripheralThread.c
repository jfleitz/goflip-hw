/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
#include<stdio.h>
#include<pthread.h>
#include "wiringPi.h"
#include "wiringPiI2C.h"
#include "peripheralThread.h"
#include "messageQueue.h"


pthread_rwlock_t peripheralInfoLock;
pthread_mutex_t pqsomethingToProcess; //locked means nothing new. unlocked means go for it.

struct message_struct *peripheralMsgQueue_ptr; //Peripheral Queue to add commands to, to get marshalled out to the i2c connected devices etc.
int exitPeripheralThread;
pthread_t peripheralThread;

pthread_cond_t newMessageCV = PTHREAD_COND_INITIALIZER;
pthread_mutex_t newMessageMutex = PTHREAD_MUTEX_INITIALIZER;

void PQSend(message_type messageType, int commandID, int commandValue, int priority) {
	pthread_rwlock_wrlock(&peripheralInfoLock);
	AddToQueueWithPriority(&peripheralMsgQueue_ptr, messageType, commandID, commandValue, priority);
	pthread_rwlock_unlock(&peripheralInfoLock);

	//signal we have a new message.
	pthread_mutex_lock(&newMessageMutex);
	pthread_cond_signal(&newMessageCV); 	    
	pthread_mutex_unlock(&newMessageMutex);
}

void StopPQThread() {
	pthread_rwlock_rdlock(&peripheralInfoLock);
	exitPeripheralThread = 1;
	pthread_rwlock_unlock(&peripheralInfoLock);

	pthread_mutex_lock(&newMessageMutex);
	pthread_cond_signal(&newMessageCV); 	    
	pthread_mutex_unlock(&newMessageMutex);	
}

void InitializePeripheralThread(pthread_t *testThread) {
	//peripheralInfoLock
	printf("Initializing PeripheralThread\n");
	pthread_rwlock_wrlock(&peripheralInfoLock);
	exitPeripheralThread = 0;
	pthread_rwlock_unlock(&peripheralInfoLock);
	InitializeQueue(&peripheralMsgQueue_ptr); //get the messageQueue setup
	printf("PeripheralThread being made\n");
	pthread_create(testThread, NULL, PeripheralHandler, NULL);
	printf("PeripheralThread created\n");
}

void DisplayTestMessage(struct message_struct disp) {
	printf("*******\n");
	printf("Priority: %d\n", disp.priority);
	printf("CommandID: %d\n", disp.commandID);
	printf("CommandValue: %d\n", disp.commandValue);
}

void *PeripheralHandler(void *arg) {
	int i2cLampFD; //i2c file descriptor for Lamp
	int i2cSolenoidFD;

	int inQueue;
	int threadExitStatus = 0;
	struct message_struct value;


	i2cLampFD = wiringPiI2CSetup(I2C_LAMP_DRIVER_ADDRESS);
	i2cSolenoidFD = wiringPiI2CSetup(I2C_SOLENOID_DRIVER_ADDRESS);

	if (i2cLampFD == -1) {
		printf("WiringPi failed for Lamp Driver\n");
		return 0;
	}

	printf("i2c initialized\n");

	inQueue = 1; //just setting to enter the loop the first time

	while (threadExitStatus == 0) {
		//pause here and wait till we need to process something (set when adding a message to queue)

		pthread_mutex_lock(&newMessageMutex);
		pthread_cond_wait(&newMessageCV, &newMessageMutex);
		pthread_mutex_unlock(&newMessageMutex);

		//unlock the variable above (so that something else other than this thread owns the locking)
		//process everything in the queue.
		pthread_rwlock_rdlock(&peripheralInfoLock);
		inQueue = SomethingInQueue(peripheralMsgQueue_ptr);
		threadExitStatus = exitPeripheralThread; //see if we should exit out on the next go around.
		pthread_rwlock_unlock(&peripheralInfoLock);

		while (inQueue) {
			printf("Sending Peripheral Message\n");
			//do something..but we need to pop off message too, so writelock.
			pthread_rwlock_wrlock(&peripheralInfoLock);
			value = PopHeadOff(&peripheralMsgQueue_ptr);
			pthread_rwlock_unlock(&peripheralInfoLock);
			//DisplayTestMessage(value);
			switch (value.messageType) {
				case MSG_LAMP:
					wiringPiI2CWriteReg8(i2cLampFD, value.commandValue, value.commandID);
					break;
				case MSG_SOLENOID:
					wiringPiI2CWriteReg8(i2cSolenoidFD, value.commandValue, value.commandID);
					break;

			}

			pthread_rwlock_rdlock(&peripheralInfoLock);
			inQueue = SomethingInQueue(peripheralMsgQueue_ptr);
			pthread_rwlock_unlock(&peripheralInfoLock);

		}
	}
	printf("Peripheral Thread Exited\n");
}
