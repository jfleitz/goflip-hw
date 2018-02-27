/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   testThread.h
 * Author: drjones
 *
 * Created on May 16, 2016, 7:54 PM
 */

#ifndef TESTTHREAD_H
#define TESTTHREAD_H

#include <pthread.h>

#ifdef __cplusplus
extern "C" {
#endif

	extern pthread_rwlock_t   msgQueueLock;    
	extern struct message_struct *msgqueue_ptr;
	

	void *PeripheralThread(void *);
	void InitializeTestThread(pthread_t *);



#ifdef __cplusplus
}
#endif

#endif /* TESTTHREAD_H */

