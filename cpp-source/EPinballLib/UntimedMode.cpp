/*
 * The UntimedMode class is basically a hurry up that doesn't expire on time. 
 * It keeps going till the ball drains (or if the objective is complete)
 * 
 * To determine if complete, a counter is used to decrement. Once the counter reaches zero, the mode 
 * is considered to be complete (in which the completed Method is called)
 */

/* 
 * File:   UntimedMode.cpp
 * Author: drjones
 * 
 * Created on October 18, 2016, 9:21 PM
 */

#include "UntimedMode.h"

UntimedMode::UntimedMode() {
}

UntimedMode::UntimedMode(const UntimedMode& orig) {
}

UntimedMode::~UntimedMode() {
}

