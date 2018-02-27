/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   MessageBase.h
 * Author: drjones
 *
 * Created on September 27, 2016, 8:26 PM
 */

#ifndef MESSAGEBASE_H
#define MESSAGEBASE_H

#include "PeripheralThread.h"

#define HIGHEST_PRIORITY 0
#define DEFAULT_PRIORITY 5
#define LOW_PRIORITY 9


class MessageBase {
public:
	MessageBase();
	MessageBase(const MessageBase& orig);
	virtual ~MessageBase();
private:
	struct message_struct* AddToQueueWithPriority(struct message_struct **queue, message_type messageType, int commandID, int commandValue, int priority);
	void  PQSend(message_type messageType, int commandID, int commandValue, int priority);
};

#endif /* MESSAGEBASE_H */

