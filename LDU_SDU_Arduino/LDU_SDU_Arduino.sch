EESchema Schematic File Version 2
LIBS:LDU_SDU_Arduino-rescue
LIBS:power
LIBS:device
LIBS:transistors
LIBS:conn
LIBS:linear
LIBS:regul
LIBS:74xx
LIBS:cmos4000
LIBS:adc-dac
LIBS:memory
LIBS:xilinx
LIBS:microcontrollers
LIBS:dsp
LIBS:microchip
LIBS:analog_switches
LIBS:motorola
LIBS:texas
LIBS:intel
LIBS:audio
LIBS:interface
LIBS:digital-audio
LIBS:philips
LIBS:display
LIBS:cypress
LIBS:siliconi
LIBS:opto
LIBS:atmel
LIBS:contrib
LIBS:valves
LIBS:arduino_mini_pro
LIBS:LDU_SDU_Arduino-cache
EELAYER 25 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 1 1
Title "Arduino LDU/SDU Driver"
Date "2016-05-30"
Rev "1.0"
Comp "ePinball"
Comment1 "I2C Driver for LDU/SDU"
Comment2 "Arduino Mini Pro"
Comment3 ""
Comment4 ""
$EndDescr
$Comp
L Arduino_Mini_Pro-RESCUE-LDU_SDU_Arduino U1
U 1 1 574CFB27
P 7350 2800
F 0 "U1" H 7350 2800 60  0000 C CNN
F 1 "Arduino_Mini_Pro" V 7200 3000 60  0000 C CNN
F 2 "Arduino:MiniPro" H 7350 2800 60  0001 C CNN
F 3 "" H 7350 2800 60  0000 C CNN
	1    7350 2800
	1    0    0    -1  
$EndComp
$Comp
L CONN_01X09 P3
U 1 1 574CFD84
P 10100 1750
F 0 "P3" H 10100 2250 50  0000 C CNN
F 1 "LDU" V 10200 1750 50  0000 C CNN
F 2 "Pin_Headers:Pin_Header_Angled_1x09" H 10100 1750 50  0001 C CNN
F 3 "" H 10100 1750 50  0000 C CNN
	1    10100 1750
	1    0    0    -1  
$EndComp
$Comp
L CONN_01X09 P2
U 1 1 574CFE29
P 9500 3850
F 0 "P2" H 9500 4350 50  0000 C CNN
F 1 "SDU" V 9600 3850 50  0000 C CNN
F 2 "Pin_Headers:Pin_Header_Angled_1x09" H 9500 3850 50  0001 C CNN
F 3 "" H 9500 3850 50  0000 C CNN
	1    9500 3850
	1    0    0    -1  
$EndComp
$Comp
L CONN_01X04 P1
U 1 1 574CFE62
P 4400 2250
F 0 "P1" H 4400 2500 50  0000 C CNN
F 1 "CONN_01X04" V 4500 2250 50  0000 C CNN
F 2 "Connectors_Molex:Molex_KK_6410-04" H 4400 2250 50  0001 C CNN
F 3 "" H 4400 2250 50  0000 C CNN
	1    4400 2250
	-1   0    0    1   
$EndComp
Text Notes 10300 2100 0    60   ~ 0
1 - Enable 1\n2 - Enable 2\n3 - ADDR 4\n4 - ADDR 3\n5 - Enable 3\n6 - Key\n7 - Enable 4\n8 - ADDR 1\n9 - ADDR 2
Text Notes 9650 4250 0    60   ~ 0
1 - Relay (J3-12:J1-21)\n2 - Relay (J2-14/15:Sol Gnd)\n3 - Direct J2/10 \n4 - Direct J2/9\n5 - ADDR 1\n6 - ADDR 2\n7 - Key\n8 - ADDR 3\n9 - ADDR 4\n
Text Notes 3700 2400 0    60   ~ 0
4 - SDA\n3 - SCL\n2 - GND\n1 - +5V
$Comp
L Earth #PWR01
U 1 1 574D056B
P 4900 2550
F 0 "#PWR01" H 4900 2300 50  0001 C CNN
F 1 "Earth" H 4900 2400 50  0001 C CNN
F 2 "" H 4900 2550 50  0000 C CNN
F 3 "" H 4900 2550 50  0000 C CNN
	1    4900 2550
	1    0    0    -1  
$EndComp
$Comp
L Earth #PWR02
U 1 1 574D05A3
P 6000 2500
F 0 "#PWR02" H 6000 2250 50  0001 C CNN
F 1 "Earth" H 6000 2350 50  0001 C CNN
F 2 "" H 6000 2500 50  0000 C CNN
F 3 "" H 6000 2500 50  0000 C CNN
	1    6000 2500
	1    0    0    -1  
$EndComp
$Comp
L Earth #PWR03
U 1 1 574D0B0A
P 9250 2550
F 0 "#PWR03" H 9250 2300 50  0001 C CNN
F 1 "Earth" H 9250 2400 50  0001 C CNN
F 2 "" H 9250 2550 50  0000 C CNN
F 3 "" H 9250 2550 50  0000 C CNN
	1    9250 2550
	1    0    0    -1  
$EndComp
$Comp
L +5V #PWR04
U 1 1 574D0BF9
P 4750 1800
F 0 "#PWR04" H 4750 1650 50  0001 C CNN
F 1 "+5V" H 4750 1940 50  0000 C CNN
F 2 "" H 4750 1800 50  0000 C CNN
F 3 "" H 4750 1800 50  0000 C CNN
	1    4750 1800
	1    0    0    -1  
$EndComp
$Comp
L +5V #PWR05
U 1 1 574D0C15
P 8100 1250
F 0 "#PWR05" H 8100 1100 50  0001 C CNN
F 1 "+5V" H 8100 1390 50  0000 C CNN
F 2 "" H 8100 1250 50  0000 C CNN
F 3 "" H 8100 1250 50  0000 C CNN
	1    8100 1250
	1    0    0    -1  
$EndComp
Wire Wire Line
	7450 3500 7450 3650
Wire Wire Line
	7450 3650 5400 3650
Wire Wire Line
	5400 3650 5400 2200
Wire Wire Line
	5400 2200 4600 2200
Wire Wire Line
	4600 2100 5300 2100
Wire Wire Line
	5300 2100 5300 3750
Wire Wire Line
	5300 3750 7350 3750
Wire Wire Line
	7350 3750 7350 3500
Wire Wire Line
	6550 2400 6000 2400
Wire Wire Line
	6000 1400 6000 2500
Wire Wire Line
	4600 2300 4900 2300
Wire Wire Line
	4900 2300 4900 2600
Wire Wire Line
	7050 1600 7050 1400
Wire Wire Line
	6000 1400 7150 1400
Connection ~ 6000 2400
Wire Wire Line
	7150 1400 7150 1600
Connection ~ 7050 1400
Wire Wire Line
	6550 3100 6300 3100
Wire Wire Line
	6300 3100 6300 3850
Wire Wire Line
	6300 3850 9300 3850
Wire Wire Line
	6550 3200 6550 3950
Wire Wire Line
	6550 3950 9300 3950
Wire Wire Line
	8000 3200 8300 3200
Wire Wire Line
	8300 1650 8300 4150
Wire Wire Line
	8300 1650 9900 1650
Wire Wire Line
	8000 3100 8350 3100
Wire Wire Line
	8350 1550 8350 4250
Wire Wire Line
	8350 1550 9900 1550
Wire Wire Line
	8000 2800 8700 2800
Wire Wire Line
	8700 1350 8700 3450
Wire Wire Line
	8700 1350 9900 1350
Wire Wire Line
	8000 2700 8750 2700
Wire Wire Line
	8750 1450 8750 3550
Wire Wire Line
	8750 1450 9900 1450
Wire Wire Line
	8000 2600 8800 2600
Wire Wire Line
	8800 1750 8800 3650
Wire Wire Line
	8000 2500 8850 2500
Wire Wire Line
	8000 2200 9250 2200
Wire Wire Line
	9250 2200 9250 2550
Wire Wire Line
	8000 2400 8100 2400
Wire Wire Line
	8100 2400 8100 1250
Wire Wire Line
	4600 2400 4750 2400
Wire Wire Line
	4750 2400 4750 1800
Wire Wire Line
	7250 1600 7250 1400
Wire Wire Line
	7250 1400 8100 1400
Connection ~ 8100 1400
Connection ~ 8250 3850
Connection ~ 8200 3950
Wire Wire Line
	8300 4150 9300 4150
Connection ~ 8300 3200
Wire Wire Line
	8350 4250 9300 4250
Connection ~ 8350 3100
Wire Wire Line
	8700 3450 9300 3450
Connection ~ 8700 2800
Wire Wire Line
	8750 3550 9300 3550
Connection ~ 8750 2700
Wire Wire Line
	8800 3650 9300 3650
Connection ~ 8800 2600
Wire Wire Line
	8850 3750 9300 3750
Connection ~ 8850 2500
Wire Wire Line
	8800 1750 9900 1750
Wire Wire Line
	9900 2150 8200 2150
Wire Wire Line
	8200 2150 8200 3950
Wire Wire Line
	9900 2050 8250 2050
Wire Wire Line
	8250 2050 8250 3850
Wire Wire Line
	9900 1950 8850 1950
Connection ~ 8850 1950
Wire Wire Line
	8850 1950 8850 3750
$Comp
L CP C1
U 1 1 5754E591
P 4700 3200
F 0 "C1" H 4725 3300 50  0000 L CNN
F 1 "CP" H 4725 3100 50  0000 L CNN
F 2 "Capacitors_ThroughHole:C_Radial_D10_L13_P5" H 4738 3050 50  0001 C CNN
F 3 "" H 4700 3200 50  0000 C CNN
	1    4700 3200
	1    0    0    -1  
$EndComp
$Comp
L +5V #PWR06
U 1 1 5754E5F9
P 4700 2950
F 0 "#PWR06" H 4700 2800 50  0001 C CNN
F 1 "+5V" H 4700 3090 50  0000 C CNN
F 2 "" H 4700 2950 50  0000 C CNN
F 3 "" H 4700 2950 50  0000 C CNN
	1    4700 2950
	1    0    0    -1  
$EndComp
$Comp
L Earth #PWR07
U 1 1 5754E617
P 4700 3550
F 0 "#PWR07" H 4700 3300 50  0001 C CNN
F 1 "Earth" H 4700 3400 50  0001 C CNN
F 2 "" H 4700 3550 50  0000 C CNN
F 3 "" H 4700 3550 50  0000 C CNN
	1    4700 3550
	1    0    0    -1  
$EndComp
Wire Wire Line
	4700 3050 4700 2950
Wire Wire Line
	4700 3350 4700 3550
Connection ~ 4900 2550
$Comp
L PWR_FLAG #FLG08
U 1 1 5754F02A
P 4450 2950
F 0 "#FLG08" H 4450 3045 50  0001 C CNN
F 1 "PWR_FLAG" H 4450 3130 50  0000 C CNN
F 2 "" H 4450 2950 50  0000 C CNN
F 3 "" H 4450 2950 50  0000 C CNN
	1    4450 2950
	1    0    0    -1  
$EndComp
$Comp
L PWR_FLAG #FLG09
U 1 1 5754F048
P 4450 3350
F 0 "#FLG09" H 4450 3445 50  0001 C CNN
F 1 "PWR_FLAG" H 4450 3530 50  0000 C CNN
F 2 "" H 4450 3350 50  0000 C CNN
F 3 "" H 4450 3350 50  0000 C CNN
	1    4450 3350
	1    0    0    -1  
$EndComp
Wire Wire Line
	4700 2950 4450 2950
Wire Wire Line
	4450 3350 4700 3350
NoConn ~ 9900 1850
NoConn ~ 7350 1600
NoConn ~ 7450 1600
NoConn ~ 7550 1600
NoConn ~ 6550 2100
NoConn ~ 6550 2200
NoConn ~ 6550 2300
NoConn ~ 6550 2500
NoConn ~ 6550 2600
NoConn ~ 6550 2700
NoConn ~ 6550 2800
NoConn ~ 6550 2900
NoConn ~ 6550 3000
NoConn ~ 7150 3500
NoConn ~ 7250 3500
NoConn ~ 8000 2900
NoConn ~ 8000 3000
NoConn ~ 8000 2300
NoConn ~ 8000 2100
NoConn ~ 9300 4050
$EndSCHEMATC
