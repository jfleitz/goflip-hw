/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   PopBumper.cpp
 * Author: drjones
 * 
 * Created on September 22, 2016, 9:30 PM
 */

#include "PopBumper.h"
#include "MachineControl.h"

PopBumper::PopBumper() {
}

PopBumper::PopBumper(const PopBumper& orig) {
}

PopBumper::~PopBumper() {
}

void PopBumper::queueAction(){
    
    //sample of queuing some actions...
    MachineControl::instance().AudioPlayer(); //call whatever method for audio
    MachineControl::instance().AddScore(1000); //just pass in the point value here. AddScore() should keep track of what player gets the points
    MachineControl::instance().LampDriver(); //call the methods of the LampDriver here...blink fast/slow/on/off. Need to make it so that we can have a delayed event maybe?
    MachineControl::instance().SolenoidDriver(); //call methods of the solenoidDriver here.
    
    //Need to be able to add a Delay Event ? Such as I hit a target, and want to have a Hurry Up go for 30 secs. 
    
    return;
}
