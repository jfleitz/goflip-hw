/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.c
 * Author: drjones
 *
 * Created on May 8, 2016, 10:26 PM
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include<pthread.h>
#include <unistd.h>
#include "mikeBossy.h"
#include "gameOver.h"
#include "peripheralThread.h"
#include "gameConstants.h"

/*
 * 
 */


int gameOverThreadRunning;

status_type gameStatus;
pthread_rwlock_t gameStatusLock;

void StartGameOverSequence();
void StopAndWaitAllThreads();

int main(int argc, char** argv) {
	InitVariables();

	//Peripheral Queue setup
	pthread_rwlock_init(&peripheralInfoLock, NULL); //lock for shared resources (messageQueue))
	InitializePeripheralThread(&peripheralThread); //Create the peripheral thread
	
	printf("main: init lock for gameStatus\n");
	//GameStatus Lock
	pthread_rwlock_init(&gameStatusLock, NULL); //lock for updating GameStatus)
	printf("main: Call Start GameOverSeq\n");
	StartGameOverSequence();

	//while (1) {
	//Basically we just process whatever our events are from the switches here. Keep track of the game progress too.
	getchar();
	//}


	gameStatus = TURN_OFF; //stops the game over thread
	sleep(1);
	
	
	StopAndWaitAllThreads();

	return (EXIT_SUCCESS);
}

void InitVariables() {
	pthread_rwlock_wrlock(&gameStatusLock);

	gameStatus = GAME_OVER;
	pthread_rwlock_unlock(&gameStatusLock);

	gameOverThreadRunning = false;
}

void StartGameOverSequence() {
	gameStatus = GAME_OVER;
	InitializeGameOverThread(&gameOverThread);
	gameOverThreadRunning = true;
}

void StopAndWaitAllThreads() {
	pthread_join(gameOverThread, NULL);
	
	//turn off all lamps
	AddToQueueWithPriority(&peripheralMsgQueue_ptr, MSG_LAMP,LAMPS_ALL,LAMP_CONTROL_OFF,DEFAULT_PRIORITY );		
	
	//sleep to wait for the above to happen
	sleep(1);
	StopPQThread();	
	pthread_join(peripheralThread, NULL);
}

