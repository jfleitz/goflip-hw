# -*- coding: utf-8 -*-
import time
import smbus

LAMP_LETTER_M = 1
LAMP_LETTER_I = 2
LAMP_LETTER_K = 3
LAMP_LETTER_E = 4
LAMP_LETTER_B = 5
LAMP_LETTER_O = 6
LAMP_LETTER_S = 7
LAMP_LETTER_SS = 8
LAMP_LETTER_Y = 9


def CycleAllLamps():
    for n in range(0, 64):
        print(("Lamp ", n))
        #output to I2C this lamp
        print("send i2c command to turn on lamp n")
        #and turn off the previous lamp
        if n == 0:
            #turn off 64
            print("replace with i2c off command for 64")
        else:
            #turn off n-1
            print("replace with i2c off command for n-1")
        time.sleep(0.5)  # sleeping for 500ms



