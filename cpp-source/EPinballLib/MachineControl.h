/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   MachineControl.h
 * Author: drjones
 *
 * Created on October 1, 2016, 10:56 PM
 * 
 * List of things todo..
 * Add the thread initialization stuff for the peripheral control
 * Add States for the machine itself
 * Add initialization routine for the switch matrix
 * 
 */

#ifndef MACHINECONTROL_H
#define MACHINECONTROL_H

#include "BasePart.h"


class MachineControl {
	enum MachineState {NOT_CREATED,CREATED,INITIALIZED,STARTING,RUNNING,HALT, STOPPING,STOPPED,DESTROYED};
	
public:
	static MachineControl &instance(){static MachineControl instance; return instance; }
	MachineControl();
	virtual ~MachineControl();

	void AudioPlayer(){};
	void Scoring(){};
	void LampDriver(){};
	void SolenoidDriver(){};
	void DisplayControl(){};

//These are methods that can be used to simplify calls elsewhere	
	void AddScore(int points){ 
		//Todo: just call Scoring()..whatever to add points. this is just to make it simpler to read )
	}

	void SetLamp(int lampID, int lampState){
		//Todo: just call LampDriver()..whatever to control the lamp. this is just to make it simpler to read )
	}
	
	void SetSolenoid(int solenoidID, int solState){
		//Todo: just call SolenoidDriver()..whatever to control the solenoid. this is just to make it simpler to read )		
	}
	
//The following are for actually controlling the state of the machine itself
	bool Init(); //initializes peripheral queue thread etc.
	bool Run(); //starts the threads. 
	bool Stop(); 
	
private:
	BasePart *_parts;
	MachineState _state;
};

#endif /* MACHINECONTROL_H */

