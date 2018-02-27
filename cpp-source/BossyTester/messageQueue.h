/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   messageQueue.h
 * Author: Jeremy Fleitz
 *
 * Created on May 10, 2016, 12:02 AM
 */

#ifndef MESSAGEQUEUE_H
#define MESSAGEQUEUE_H

#ifdef __cplusplus
extern "C" {
#endif

#define HIGHEST_PRIORITY 0
#define DEFAULT_PRIORITY 5
#define LOW_PRIORITY 9

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

	void InitializeQueue(struct message_struct **queue);
	struct message_struct PopHeadOff(struct message_struct **queue);
	int DeleteQueue(struct message_struct **queue);
	struct message_struct* AddToQueueWithPriority(struct message_struct **queue, message_type messageType, int commandID, int commandValue, int priority);
	int SomethingInQueue(struct message_struct *queue);

#ifdef __cplusplus
}
#endif

#endif /* MESSAGEQUEUE_H */

