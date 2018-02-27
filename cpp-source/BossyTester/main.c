/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.c
 * Author: drjones
 *
 * Created on May 14, 2016, 9:57 PM
 */

#include <stdio.h>
#include <stdlib.h>
#include "testThread.h"
#include "messageQueue.h"
#include "main.h"
#include <pthread.h>

/*
 * 
 */

pthread_t testThread;
int exitStatus;


void TestQueue();
void TestWithThread();



void DisplayMessage(struct message_struct disp) {
	printf("*******\n");
	printf("Priority: %d\n", disp.priority);
	printf("CommandID: %d\n", disp.commandID);
	printf("CommandValue: %d\n", disp.commandValue);
}

int main(int argc, char** argv) {
	exitStatus = 0;
	
	//Initializing lock
	pthread_rwlock_init(&msgQueueLock, NULL);
	
	printf("Initializing Queue \n");
	InitializeQueue(&msgqueue_ptr);
	
	//Create a Thread to just pop off of the queue.
	
	
	printf("Calling TestQueueWithThread");
	//TestQueue();
	TestWithThread();
	
	return (EXIT_SUCCESS);
}


void TestQueue(){
	
	
	printf("Adding to Queue\n");
	AddToQueueWithPriority(&msgqueue_ptr, MSG_DISPLAY, 1, 2, 5); //prority 5
	
	if (SomethingInQueue(msgqueue_ptr))
		printf("Something in Queue after first message inserted \n");

	AddToQueueWithPriority(&msgqueue_ptr, MSG_LAMP, 2, 2, 3); //priority 3
	if (SomethingInQueue(msgqueue_ptr))
		printf("Still something in queue after 2nd message\n");


	AddToQueueWithPriority(&msgqueue_ptr, MSG_SOLENOID, 3, 2, 7); //priority 7
	AddToQueueWithPriority(&msgqueue_ptr, MSG_SOUND, 4, 2, 4); //priotity 4
	AddToQueueWithPriority(&msgqueue_ptr, MSG_SOUND, 4, 2, 8); //priotity 8

	//pop off
	struct message_struct value;
	int i = 1;
	while (SomethingInQueue(msgqueue_ptr)) {
		printf("Something is in Queue. Popping off %d\n", i);
		value = PopHeadOff(&msgqueue_ptr);
		DisplayMessage(value);
		i++;
	}


	
}

void TestWithThread(){
	printf("Initializing peripheralThread\n");
	//pthread_create(&testThread, NULL, PeripheralThread, NULL);
	InitializeTestThread(&testThread);
			
	printf("Adding to Queue\n");
	pthread_rwlock_wrlock(&msgQueueLock); 
	AddToQueueWithPriority(&msgqueue_ptr, MSG_DISPLAY, 1, 2, 5); //prority 5
//	pthread_rwlock_unlock(&msgQueueLock); 
	getchar();
	
	
	printf("Adding to Queue\n");
//	pthread_rwlock_wrlock(&msgQueueLock); 
	AddToQueueWithPriority(&msgqueue_ptr, MSG_LAMP, 2, 2, 3); //priority 3
//	pthread_rwlock_unlock(&msgQueueLock); 
	getchar();


	printf("Adding to Queue\n");
//	pthread_rwlock_wrlock(&msgQueueLock); 
	AddToQueueWithPriority(&msgqueue_ptr, MSG_SOLENOID, 3, 2, 7); //priority 7
//	pthread_rwlock_unlock(&msgQueueLock); 
	getchar();

	printf("Adding to Queue\n");
//	pthread_rwlock_wrlock(&msgQueueLock); 
	AddToQueueWithPriority(&msgqueue_ptr, MSG_SOUND, 4, 2, 4); //priotity 4
//	pthread_rwlock_unlock(&msgQueueLock); 
	getchar();

	printf("Adding to Queue\n");
//	pthread_rwlock_wrlock(&msgQueueLock); 
	AddToQueueWithPriority(&msgqueue_ptr, MSG_SOUND, 4, 2, 8); //priotity 8
	pthread_rwlock_unlock(&msgQueueLock); 
	
	getchar();

	printf("Setting ExitStatus after key pressed\n");
	getchar();

	exitStatus = 1;	
	pthread_join(testThread, NULL);
	
	
}



