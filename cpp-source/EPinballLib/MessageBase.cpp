/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   MessageBase.cpp
 * Author: drjones
 * 
 * Created on September 27, 2016, 8:26 PM
 */

#include "MessageBase.h"
#include<stdio.h>
#include<stdlib.h>

MessageBase::MessageBase() {
}

MessageBase::MessageBase(const MessageBase& orig) {
}

MessageBase::~MessageBase() {
}


struct message_struct* MessageBase::AddToQueueWithPriority(struct message_struct **queue, message_type messageType, int commandID, int commandValue, int priority) {
	//where the magic is. Basically this is a prioritized queue based on the time passed in priority. 
	//would do a ring buffer, but there is enough memory to not worry about it..so linked list it is.
	//messageType is either Lamp, Display, Sound or Solenoid
	//commandID is such as the LampID, SolenoidID or SoundID
	//commandValue is the argument (such as LampOn, LampOFF, etc.)
	//priority is where in the queue to insert. This should be default to 5. 
	//add_to_list(message_type messageType, int commandID, int commandValue, int priority)

	int found = 0;
	struct message_struct *seekptr = *queue;
	struct message_struct *lastptr = NULL;

	struct message_struct *ptr = (struct message_struct*) malloc(sizeof (struct message_struct));
	if (NULL == ptr) {
		return NULL;
	}

	ptr->commandID = commandID;
	ptr->commandValue = commandValue;
	ptr->priority = priority;
	ptr->messageType = messageType;
	ptr->next = NULL;


	if(seekptr==NULL){
		//set queue to the ptr;
		*queue = ptr;
		return ptr;
	}
	
	//check to see if we need to add this to the beginning of the list.
	if(seekptr->priority > priority){
		ptr->next = seekptr;
		*queue = ptr;
		return ptr;
	}
	
	while (seekptr != NULL) {
		if ((seekptr->priority <= priority) && (seekptr->next == NULL || seekptr->next->priority > priority)) //if the current value is before or equal to the priority value 
			//and the next value in line (if there is one) is greater.
		{
			//we need to add the new value right after seek ptr.
			ptr->next = seekptr->next;
			seekptr->next = ptr;
			found = 1;
			break;
		} else {
			lastptr = seekptr;
			seekptr = seekptr->next;
		}
	}

	if (found == 0) { //insert location not found, so add to the end.
		lastptr->next = ptr;
	}


	return ptr;
}

void MessageBase::PQSend(message_type messageType, int commandID, int commandValue, int priority) {
	pthread_rwlock_wrlock(&peripheralInfoLock);
	AddToQueueWithPriority(&peripheralMsgQueue_ptr, messageType, commandID, commandValue, priority);
	pthread_rwlock_unlock(&peripheralInfoLock);

	//signal we have a new message.
	pthread_mutex_lock(&newMessageMutex);
	pthread_cond_signal(&newMessageCV); 	    
	pthread_mutex_unlock(&newMessageMutex);
}
