/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include "mikeBossy.h"
#include "gameOver.h"
#include "gameConstants.h"
#include "peripheralThread.h"
#include "messageQueue.h"

#include <stdio.h>
#include <stdint.h>
#include <pthread.h>
#include <unistd.h>

pthread_t gameOverThread;

void InitializeGameOverThread(pthread_t *gameOverThread) {
	printf("Creating GameThread\n");
	pthread_create(gameOverThread, NULL, GameOverHandler, NULL);
	printf("GameThread created\n");
}

void *GameOverHandler(void *arg) {
	int bossyNameLoop[9] = {LAMP_LETTER_M, LAMP_LETTER_I, LAMP_LETTER_K, LAMP_LETTER_E, LAMP_LETTER_B, LAMP_LETTER_O, LAMP_LETTER_S, LAMP_LETTER_S2, LAMP_LETTER_Y};
	int retval;

	status_type curGameStatus;

	curGameStatus = GAME_OVER;
	printf("GameThread starting\n");
	int i;
	
	while (curGameStatus == GAME_OVER) {
		//looping till we are not in the game over state
		
		//Turn on each lamp above one at a time.
		for(i=0;i<9;i++){
			PQSend(MSG_LAMP, i, LAMP_CONTROL_ON, DEFAULT_PRIORITY);
			SLEEP_MS(100);
		}
		
		SLEEP_MS(500);
		
		//now turn off each one at a time.
		for(i=0;i<9;i++){
			PQSend(MSG_LAMP, i, LAMP_CONTROL_OFF, DEFAULT_PRIORITY);
			SLEEP_MS(100);
		}
		
		SLEEP_MS(500);
		
		//chase the light
		for(i=0;i<9;i++){
			PQSend(MSG_LAMP, i, LAMP_CONTROL_ON, DEFAULT_PRIORITY);
			
			//turn off previous
			PQSend(MSG_LAMP, (i>0?i-1:8), LAMP_CONTROL_OFF, DEFAULT_PRIORITY);

			SLEEP_MS(250);
		}

		SLEEP_MS(500);
		
		//slow blink all of them
		for(i=0;i<9;i++){
			PQSend(MSG_LAMP, i, LAMP_CONTROL_SLOW_BLINK, DEFAULT_PRIORITY);
		}
		
		sleep(3); //3 seconds
		
		//fast blink
		for(i=0;i<9;i++){
			PQSend(MSG_LAMP, i, LAMP_CONTROL_FAST_BLINK, DEFAULT_PRIORITY);
		}
		
		
		sleep(3); //3 seconds
		
		//all back off.
		for(i=0;i<9;i++){
			PQSend(MSG_LAMP, i, LAMP_CONTROL_OFF, DEFAULT_PRIORITY);
		}

		
		//Get the latest status
		pthread_rwlock_rdlock(&gameStatusLock);
		curGameStatus = gameStatus;
		pthread_rwlock_unlock(&gameStatusLock);
	}
	printf("GameThread exited\n");
	return NULL;
}