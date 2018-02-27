/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   gameOver.h
 * Author: drjones
 *
 * Created on May 8, 2016, 10:29 PM
 */

#ifndef GAMEOVER_H
#define GAMEOVER_H

#ifdef __cplusplus
extern "C" {
#endif

	void *GameOverHandler(void *);
	extern pthread_t gameOverThread;
	void InitializeGameOverThread(pthread_t *);


#ifdef __cplusplus
}
#endif

#endif /* GAMEOVER_H */

