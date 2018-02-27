/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   PeripheralThread.cpp
 * Author: drjones
 * 
 * Created on September 27, 2016, 9:05 PM
 */
#include<stdio.h>
#include<pthread.h>
#include "PeripheralThread.h"



pthread_rwlock_t peripheralInfoLock;
pthread_mutex_t pqsomethingToProcess; //locked means nothing new. unlocked means go for it.

struct message_struct *peripheralMsgQueue_ptr; //Peripheral Queue to add commands to, to get marshalled out to the i2c connected devices etc.

int exitPeripheralThread;
pthread_t peripheralThread;

pthread_cond_t newMessageCV = PTHREAD_COND_INITIALIZER;
pthread_mutex_t newMessageMutex = PTHREAD_MUTEX_INITIALIZER;



PeripheralThread::PeripheralThread() {
}

PeripheralThread::PeripheralThread(const PeripheralThread& orig) {
}

PeripheralThread::~PeripheralThread() {
}

