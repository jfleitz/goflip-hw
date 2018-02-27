/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.cpp
 * Author: drjones
 *
 * Created on October 18, 2016, 11:03 PM
 */

#include <cstdlib>
#include "../EPinballLib/MachineControl.h"
#include "../EPinballLib/TimedMode.h"
#include "../EPinballLib/PopBumper.h"
using namespace std;

/*
 * 
 */
int main(int argc, char** argv) {
    MachineControl::instance().Init();
    TimedMode* t;
    t = new TimedMode();
    
    PopBumper* p;
    p = new PopBumper();
    p->setValues(0,1,200);
    return 0;
}

