/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   gameConstants.h
 * Author: Jeremy Fleitz
 *
 * Created on May 8, 2016, 10:30 PM
 */

#ifndef GAMECONSTANTS_H
#define GAMECONSTANTS_H

#ifdef __cplusplus
extern "C" {
#endif

//0 means undefined below
	
#define LAMP_CONTROL_ON 1
#define LAMP_CONTROL_OFF 0
#define LAMP_CONTROL_SLOW_BLINK 2
#define LAMP_CONTROL_FAST_BLINK 3

#define LAMPS_ALL 65
	
#define LAMP_GAME_OVER 0
#define LAMP_HIGH_SCORE 0
#define LAMP_MATCH 0
#define LAMP_BALL_IN_PLAY 0

#define LAMP_GOAL 45
#define LAMP_LANE_TOP_LEFT 24
#define LAMP_LANE_TOP_MIDDLE 25
#define LAMP_LANE_TOP_RIGHT 30
#define LAMP_OVERTIME_TOP 16
#define LAMP_ARCH_TOP_LEFT_SPOT 49
#define LAMP_ACCESS_LANE_1000 17
#define LAMP_OVERTIME_ACCESS_LANE 11
#define LAMP_TARGET_LEFT 27
#define LAMP_LANE_MIDDLE_LEFT_SPECIAL 21
#define LAMP_LANE_MIDDLE_LEFT_WHITE 13
#define LAMP_TARGET_RIGHT_TOP 14
#define LAMP_TARGET_RIGHT_MIDDLE 28
#define LAMP_TARGET_RIGHT_BOTTOM 31
#define LAMP_OVERTIME_TARGETS_RIGHT 18
	
#define LAMP_LETTER_M 1
#define LAMP_LETTER_I 2
#define LAMP_LETTER_K 3
#define LAMP_LETTER_E 4
#define LAMP_LETTER_B 5
#define LAMP_LETTER_O 6
#define LAMP_LETTER_S 7
#define LAMP_LETTER_S2 8
#define LAMP_LETTER_Y 9

#define LAMP_OVERTIME_BOTTOM_LEFT_LANE 19
#define LAMP_OVERTIME_BOTTOM_RIGHT_LANE 20
#define LAMP_SCORES_GOAL_BOTTOM 38
#define LAMP_SPECIAL_BOTTOM_LEFT 22
#define LAMP_SPECIAL_BOTTOM_RIGHT 23
	
#define LAMP_BONUS_25000 44
#define LAMP_BONUS_5000_1 32
#define LAMP_BONUS_5000_2 47
#define LAMP_BONUS_5000_3 34
#define LAMP_BONUS_5000_4 35
#define LAMP_OVERTIME_CENTER 51
#define LAMP_BONUS_1000_1 0
#define LAMP_BONUS_1000_2 36
	
	
#define LAMP_SCORE_DISPLAY_1 0
#define LAMP_SCORE_DISPLAY_2 61
#define LAMP_SCORE_DISPLAY_3 0
#define LAMP_SCORE_DISPLAY_4 63

#define SLEEP_MS(x) usleep(x * 1000)

#ifdef __cplusplus
}
#endif

#endif /* GAMECONSTANTS_H */

