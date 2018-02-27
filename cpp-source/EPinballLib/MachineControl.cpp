/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   MachineControl.cpp
 * Author: drjones
 * 
 * Created on October 1, 2016, 10:56 PM
 */
#include <assert.h>
#include <wiringPi.h>
#include "MachineControl.h"

MachineControl::MachineControl() {
    assert(!(_state==NOT_CREATED));
    _state = CREATED;
}

MachineControl::~MachineControl() {
    _state = DESTROYED;
}

/*This is where we initialize the threads etc.
 */
bool MachineControl::Init(){
    //Set up Peripheral Queue
    
    /*JAF commenting out temporarily
    	pthread_rwlock_wrlock(&gameStatusLock);

	gameStatus = GAME_OVER;
	pthread_rwlock_unlock(&gameStatusLock);

	gameOverThreadRunning = false;*/
    _state = INITIALIZED;
}

bool MachineControl::Run(){
	_state = STARTING;
	//Peripheral Queue setup
	/*JAF commenting out temporarilypthread_rwlock_init(&peripheralInfoLock, NULL); //lock for shared resources (messageQueue))
	InitializePeripheralThread(&peripheralThread); //Create the peripheral thread
	
	printf("main: init lock for gameStatus\n");
	//GameStatus Lock
//	pthread_rwlock_init(&gameStatusLock, NULL); //lock for updating GameStatus)
//	printf("main: Call Start GameOverSeq\n");
//	StartGameOverSequence();
*/
	_state = RUNNING;
	return TRUE;
}

bool MachineControl::Stop(){
    	_state = STOPPING;
	//sleep(1);
	
	//StopAndWaitAllThreads();
	
	_state = STOPPED;
	return TRUE;
}