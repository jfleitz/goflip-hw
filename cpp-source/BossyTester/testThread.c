/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
#include "testThread.h"
#include "messageQueue.h"
#include "main.h"
#include <stdio.h>

pthread_rwlock_t msgQueueLock;
struct message_struct *msgqueue_ptr;

void InitializeTestThread(pthread_t *testThread) {
	pthread_create(testThread, NULL, PeripheralThread, NULL);
}

void DisplayTestMessage(struct message_struct disp) {
	printf("*******\n");
	printf("Priority: %d\n", disp.priority);
	printf("CommandID: %d\n", disp.commandID);
	printf("CommandValue: %d\n", disp.commandValue);
}

void *PeripheralThread(void *arg) {
	//initialize i2c
	//int i2cLampFD; //i2c file descriptor for Lamp
	//i2cLampFD = wiringPiI2CSetup(I2C_LAMP_DRIVER_ADDRESS); //JAF TODO..move this to its own peripheralControl thread (which will process the peripheral queue).
	/*
		if (i2cLampFD == -1) {
			printf("WiringPi failed for Lamp Driver\n");
			return 0;
		}
	 */
	int inQueue;
	int threadExitStatus = 0;
	struct message_struct value;

	while (threadExitStatus == 0) {
		pthread_rwlock_rdlock(&msgQueueLock);
		inQueue = SomethingInQueue(msgqueue_ptr);
		threadExitStatus = exitStatus; //see if we should exit out on the next go around.
		pthread_rwlock_unlock(&msgQueueLock);
		if (inQueue) {
			//do something..but we need to pop off message too, so writelock.
			pthread_rwlock_wrlock(&msgQueueLock);
			value = PopHeadOff(&msgqueue_ptr);
			pthread_rwlock_unlock(&msgQueueLock);
			DisplayTestMessage(value);
		}
	}
}
