/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   BasePart.h
 * Author: Jeremy Fleitz
 *
 * Created on September 21, 2016, 11:50 PM
 */

#ifndef BASEPART_H
#define BASEPART_H

#include "MachineControl.h"


class BasePart {
public:
	BasePart();
	virtual ~BasePart();
	BasePart(const BasePart& orig);
	
	int getPoints(){
		return pointValue;
	}; //used to return the number of points that should be awarded to current player
	
	int getSolenoidID(){
		return solenoidID;
	}
	
	int getSwitchID(){
		return switchID;
	}
	
	void queueAction(){}; //enqueues the action that is to be performed when the switch is set
	
	void switchEventDown(){}; //will be called when the switch of switchID goes to a "down" state
	void switchEventUp(){}; //will be called when the switch of switchID goes to a "up" state
	
	
	void setValues(int solID, int swID, int points){
		solenoidID = solID;
		switchID = swID;
		pointValue = points;
	}
protected:
	int pointValue; //number of points that is awarded when the switch is depreessed
	int solenoidID; //the Solenoid ID that represents the special solenoid to be fired
	int switchID; //the ID of the switch that when depressed, queueAction() is called
	
private:

};

#endif /* BASEPART_H */

