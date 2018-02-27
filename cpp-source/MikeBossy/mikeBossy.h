/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   mikeBossy.h
 * Author: drjones
 *
 * Created on May 8, 2016, 11:10 PM
 */

#ifndef MIKEBOSSY_H
#define MIKEBOSSY_H


#ifdef __cplusplus
extern "C" {
#endif

#include <pthread.h>
#include "messageQueue.h"


typedef enum {DIAGNOSTICS, GAME_OVER, GAME_START, PLAYER_1, PLAYER_2, BONUS_ROUND1, BONUS_ROUND2, TURN_OFF} status_type;


extern status_type gameStatus;
extern pthread_rwlock_t   gameStatusLock; 




//methods
void InitVariables();


#ifdef __cplusplus
}
#endif

#endif /* MIKEBOSSY_H */

