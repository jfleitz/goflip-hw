EESchema Schematic File Version 2
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
LIBS:pwmDriver
LIBS:rpi-interface-cache
EELAYER 25 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 1 1
Title "Raspberry PI GPIO - 4 Port and PWM Expansion"
Date ""
Rev ""
Comp ""
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
$Comp
L 74HC595 U2
U 1 1 5A40884B
P 5350 1600
F 0 "U2" H 5500 2200 50  0000 C CNN
F 1 "74HC595" H 5350 1000 50  0000 C CNN
F 2 "" H 5350 1600 50  0000 C CNN
F 3 "" H 5350 1600 50  0000 C CNN
	1    5350 1600
	1    0    0    -1  
$EndComp
$Comp
L 74HC595 U3
U 1 1 5A4088C0
P 5350 3150
F 0 "U3" H 5500 3750 50  0000 C CNN
F 1 "74HC595" H 5350 2550 50  0000 C CNN
F 2 "" H 5350 3150 50  0000 C CNN
F 3 "" H 5350 3150 50  0000 C CNN
	1    5350 3150
	1    0    0    -1  
$EndComp
$Comp
L 74HC595 U4
U 1 1 5A40890D
P 5350 4750
F 0 "U4" H 5500 5350 50  0000 C CNN
F 1 "74HC595" H 5350 4150 50  0000 C CNN
F 2 "" H 5350 4750 50  0000 C CNN
F 3 "" H 5350 4750 50  0000 C CNN
	1    5350 4750
	1    0    0    -1  
$EndComp
$Comp
L CONN_02X20 P6
U 1 1 5A40893E
P 2000 3350
F 0 "P6" H 2000 4400 50  0000 C CNN
F 1 "GPIO Connector" V 2000 3350 50  0000 C CNN
F 2 "" H 2000 2400 50  0000 C CNN
F 3 "" H 2000 2400 50  0000 C CNN
	1    2000 3350
	1    0    0    -1  
$EndComp
$Comp
L GNDREF #PWR01
U 1 1 5A408E52
P 4600 1900
F 0 "#PWR01" H 4600 1650 50  0001 C CNN
F 1 "GNDREF" H 4600 1750 50  0000 C CNN
F 2 "" H 4600 1900 50  0000 C CNN
F 3 "" H 4600 1900 50  0000 C CNN
	1    4600 1900
	1    0    0    -1  
$EndComp
$Comp
L GNDREF #PWR02
U 1 1 5A408E6E
P 4600 3450
F 0 "#PWR02" H 4600 3200 50  0001 C CNN
F 1 "GNDREF" H 4600 3300 50  0000 C CNN
F 2 "" H 4600 3450 50  0000 C CNN
F 3 "" H 4600 3450 50  0000 C CNN
	1    4600 3450
	1    0    0    -1  
$EndComp
$Comp
L GNDREF #PWR03
U 1 1 5A408EE6
P 4600 5000
F 0 "#PWR03" H 4600 4750 50  0001 C CNN
F 1 "GNDREF" H 4600 4850 50  0000 C CNN
F 2 "" H 4600 5000 50  0000 C CNN
F 3 "" H 4600 5000 50  0000 C CNN
	1    4600 5000
	1    0    0    -1  
$EndComp
$Comp
L +5V #PWR04
U 1 1 5A409078
P 4150 1100
F 0 "#PWR04" H 4150 950 50  0001 C CNN
F 1 "+5V" H 4150 1240 50  0000 C CNN
F 2 "" H 4150 1100 50  0000 C CNN
F 3 "" H 4150 1100 50  0000 C CNN
	1    4150 1100
	1    0    0    -1  
$EndComp
$Comp
L GNDREF #PWR05
U 1 1 5A409755
P 2800 2650
F 0 "#PWR05" H 2800 2400 50  0001 C CNN
F 1 "GNDREF" H 2800 2500 50  0000 C CNN
F 2 "" H 2800 2650 50  0000 C CNN
F 3 "" H 2800 2650 50  0000 C CNN
	1    2800 2650
	1    0    0    -1  
$EndComp
$Comp
L VCC #PWR06
U 1 1 5A409F31
P 3000 1100
F 0 "#PWR06" H 3000 950 50  0001 C CNN
F 1 "VCC" H 3000 1250 50  0000 C CNN
F 2 "" H 3000 1100 50  0000 C CNN
F 3 "" H 3000 1100 50  0000 C CNN
	1    3000 1100
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR07
U 1 1 5A409F4D
P 2400 1050
F 0 "#PWR07" H 2400 800 50  0001 C CNN
F 1 "GND" H 2400 900 50  0000 C CNN
F 2 "" H 2400 1050 50  0000 C CNN
F 3 "" H 2400 1050 50  0000 C CNN
	1    2400 1050
	1    0    0    -1  
$EndComp
$Comp
L GNDREF #PWR08
U 1 1 5A409F69
P 2050 1050
F 0 "#PWR08" H 2050 800 50  0001 C CNN
F 1 "GNDREF" H 2050 900 50  0000 C CNN
F 2 "" H 2050 1050 50  0000 C CNN
F 3 "" H 2050 1050 50  0000 C CNN
	1    2050 1050
	1    0    0    -1  
$EndComp
$Comp
L +5V #PWR09
U 1 1 5A409F85
P 3200 1100
F 0 "#PWR09" H 3200 950 50  0001 C CNN
F 1 "+5V" H 3200 1240 50  0000 C CNN
F 2 "" H 3200 1100 50  0000 C CNN
F 3 "" H 3200 1100 50  0000 C CNN
	1    3200 1100
	1    0    0    -1  
$EndComp
$Comp
L CONN_01X09 P7
U 1 1 5A454CDF
P 7150 1550
F 0 "P7" H 7150 2050 50  0000 C CNN
F 1 "Out A" V 7250 1550 50  0000 C CNN
F 2 "" H 7150 1550 50  0000 C CNN
F 3 "" H 7150 1550 50  0000 C CNN
	1    7150 1550
	1    0    0    -1  
$EndComp
$Comp
L CONN_01X09 P8
U 1 1 5A454DBA
P 7150 3100
F 0 "P8" H 7150 3600 50  0000 C CNN
F 1 "Out B" V 7250 3100 50  0000 C CNN
F 2 "" H 7150 3100 50  0000 C CNN
F 3 "" H 7150 3100 50  0000 C CNN
	1    7150 3100
	1    0    0    -1  
$EndComp
$Comp
L CONN_01X05 P9
U 1 1 5A454E1D
P 7150 4500
F 0 "P9" H 7150 4800 50  0000 C CNN
F 1 "Out C" V 7250 4500 50  0000 C CNN
F 2 "" H 7150 4500 50  0000 C CNN
F 3 "" H 7150 4500 50  0000 C CNN
	1    7150 4500
	1    0    0    -1  
$EndComp
$Comp
L CONN_01X05 P10
U 1 1 5A454E90
P 7150 5300
F 0 "P10" H 7150 5600 50  0000 C CNN
F 1 "Out D" V 7250 5300 50  0000 C CNN
F 2 "" H 7150 5300 50  0000 C CNN
F 3 "" H 7150 5300 50  0000 C CNN
	1    7150 5300
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR010
U 1 1 5A4551F8
P 6800 2000
F 0 "#PWR010" H 6800 1750 50  0001 C CNN
F 1 "GND" H 6800 1850 50  0000 C CNN
F 2 "" H 6800 2000 50  0000 C CNN
F 3 "" H 6800 2000 50  0000 C CNN
	1    6800 2000
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR011
U 1 1 5A455518
P 6800 3600
F 0 "#PWR011" H 6800 3350 50  0001 C CNN
F 1 "GND" H 6800 3450 50  0000 C CNN
F 2 "" H 6800 3600 50  0000 C CNN
F 3 "" H 6800 3600 50  0000 C CNN
	1    6800 3600
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR012
U 1 1 5A455770
P 6800 4800
F 0 "#PWR012" H 6800 4550 50  0001 C CNN
F 1 "GND" H 6800 4650 50  0000 C CNN
F 2 "" H 6800 4800 50  0000 C CNN
F 3 "" H 6800 4800 50  0000 C CNN
	1    6800 4800
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR013
U 1 1 5A455A0B
P 6800 5600
F 0 "#PWR013" H 6800 5350 50  0001 C CNN
F 1 "GND" H 6800 5450 50  0000 C CNN
F 2 "" H 6800 5600 50  0000 C CNN
F 3 "" H 6800 5600 50  0000 C CNN
	1    6800 5600
	1    0    0    -1  
$EndComp
NoConn ~ 1750 2700
NoConn ~ 1750 2800
NoConn ~ 1750 2900
NoConn ~ 2250 2500
NoConn ~ 2250 2700
NoConn ~ 2250 2800
NoConn ~ 2250 2900
NoConn ~ 2250 3000
NoConn ~ 2250 3200
NoConn ~ 2250 3300
NoConn ~ 2250 3400
NoConn ~ 2250 3500
NoConn ~ 2250 3600
NoConn ~ 2250 3700
NoConn ~ 2250 3800
NoConn ~ 2250 3900
NoConn ~ 2250 4000
NoConn ~ 2250 4100
NoConn ~ 2250 4200
NoConn ~ 2250 4300
NoConn ~ 1750 4300
NoConn ~ 1750 4200
NoConn ~ 1750 4100
NoConn ~ 1750 4000
NoConn ~ 1750 3900
NoConn ~ 1750 3800
NoConn ~ 1750 3700
NoConn ~ 1750 3600
NoConn ~ 1750 3500
NoConn ~ 1750 3400
NoConn ~ 1750 3300
NoConn ~ 1750 3200
NoConn ~ 6050 5200
$Comp
L PWR_FLAG #FLG014
U 1 1 5A456047
P 2200 900
F 0 "#FLG014" H 2200 995 50  0001 C CNN
F 1 "PWR_FLAG" H 2200 1080 50  0000 C CNN
F 2 "" H 2200 900 50  0000 C CNN
F 3 "" H 2200 900 50  0000 C CNN
	1    2200 900 
	1    0    0    -1  
$EndComp
$Comp
L PWR_FLAG #FLG015
U 1 1 5A456073
P 3100 900
F 0 "#FLG015" H 3100 995 50  0001 C CNN
F 1 "PWR_FLAG" H 3100 1080 50  0000 C CNN
F 2 "" H 3100 900 50  0000 C CNN
F 3 "" H 3100 900 50  0000 C CNN
	1    3100 900 
	1    0    0    -1  
$EndComp
$Comp
L PCA9685-TSSOP U1
U 1 1 5A456336
P 3450 6000
F 0 "U1" H 3450 5900 50  0000 C CNN
F 1 "PCA9685-TSSOP" H 3450 6100 50  0000 C CNN
F 2 "MODULE" H 3450 6000 50  0001 C CNN
F 3 "DOCUMENTATION" H 3450 6000 50  0001 C CNN
	1    3450 6000
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR016
U 1 1 5A456547
P 2250 7450
F 0 "#PWR016" H 2250 7200 50  0001 C CNN
F 1 "GND" H 2250 7300 50  0000 C CNN
F 2 "" H 2250 7450 50  0000 C CNN
F 3 "" H 2250 7450 50  0000 C CNN
	1    2250 7450
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR017
U 1 1 5A45689E
P 4300 7150
F 0 "#PWR017" H 4300 6900 50  0001 C CNN
F 1 "GND" H 4300 7000 50  0000 C CNN
F 2 "" H 4300 7150 50  0000 C CNN
F 3 "" H 4300 7150 50  0000 C CNN
	1    4300 7150
	1    0    0    -1  
$EndComp
$Comp
L Jumper_NO_Small A0
U 1 1 5A4569D7
P 2450 5350
F 0 "A0" H 2450 5430 50  0000 C CNN
F 1 "Jumper_NO_Small" H 2460 5290 50  0001 C CNN
F 2 "" H 2450 5350 50  0000 C CNN
F 3 "" H 2450 5350 50  0000 C CNN
	1    2450 5350
	1    0    0    -1  
$EndComp
$Comp
L Jumper_NO_Small A1
U 1 1 5A456A30
P 2250 5450
F 0 "A1" H 2250 5530 50  0000 C CNN
F 1 "Jumper_NO_Small" H 2260 5390 50  0001 C CNN
F 2 "" H 2250 5450 50  0000 C CNN
F 3 "" H 2250 5450 50  0000 C CNN
	1    2250 5450
	1    0    0    -1  
$EndComp
$Comp
L Jumper_NO_Small A2
U 1 1 5A456AB1
P 2050 5550
F 0 "A2" H 2050 5630 50  0000 C CNN
F 1 "Jumper_NO_Small" H 2060 5490 50  0001 C CNN
F 2 "" H 2050 5550 50  0000 C CNN
F 3 "" H 2050 5550 50  0000 C CNN
	1    2050 5550
	1    0    0    -1  
$EndComp
$Comp
L Jumper_NO_Small A3
U 1 1 5A456AE0
P 1850 5650
F 0 "A3" H 1850 5730 50  0000 C CNN
F 1 "Jumper_NO_Small" H 1860 5590 50  0001 C CNN
F 2 "" H 1850 5650 50  0000 C CNN
F 3 "" H 1850 5650 50  0000 C CNN
	1    1850 5650
	1    0    0    -1  
$EndComp
$Comp
L Jumper_NO_Small A4
U 1 1 5A456B0F
P 1650 5750
F 0 "A4" H 1650 5830 50  0000 C CNN
F 1 "Jumper_NO_Small" H 1660 5690 50  0001 C CNN
F 2 "" H 1650 5750 50  0000 C CNN
F 3 "" H 1650 5750 50  0000 C CNN
	1    1650 5750
	1    0    0    -1  
$EndComp
$Comp
L +3.3V #PWR018
U 1 1 5A457063
P 1200 2250
F 0 "#PWR018" H 1200 2100 50  0001 C CNN
F 1 "+3.3V" H 1200 2390 50  0000 C CNN
F 2 "" H 1200 2250 50  0000 C CNN
F 3 "" H 1200 2250 50  0000 C CNN
	1    1200 2250
	1    0    0    -1  
$EndComp
$Comp
L PWR_FLAG #FLG019
U 1 1 5A457093
P 850 2300
F 0 "#FLG019" H 850 2395 50  0001 C CNN
F 1 "PWR_FLAG" H 850 2480 50  0000 C CNN
F 2 "" H 850 2300 50  0000 C CNN
F 3 "" H 850 2300 50  0000 C CNN
	1    850  2300
	1    0    0    -1  
$EndComp
$Comp
L R R3
U 1 1 5A457C02
P 2300 7050
F 0 "R3" V 2380 7050 50  0000 C CNN
F 1 "1k" V 2300 7050 50  0000 C CNN
F 2 "" V 2230 7050 50  0000 C CNN
F 3 "" H 2300 7050 50  0000 C CNN
	1    2300 7050
	1    0    0    -1  
$EndComp
$Comp
L R R4
U 1 1 5A457C7E
P 2450 7050
F 0 "R4" V 2530 7050 50  0000 C CNN
F 1 "1k" V 2450 7050 50  0000 C CNN
F 2 "" V 2380 7050 50  0000 C CNN
F 3 "" H 2450 7050 50  0000 C CNN
	1    2450 7050
	1    0    0    -1  
$EndComp
$Comp
L R R2
U 1 1 5A457CBB
P 2150 7050
F 0 "R2" V 2230 7050 50  0000 C CNN
F 1 "1k" V 2150 7050 50  0000 C CNN
F 2 "" V 2080 7050 50  0000 C CNN
F 3 "" H 2150 7050 50  0000 C CNN
	1    2150 7050
	1    0    0    -1  
$EndComp
$Comp
L R R1
U 1 1 5A457D12
P 2000 7050
F 0 "R1" V 2080 7050 50  0000 C CNN
F 1 "1k" V 2000 7050 50  0000 C CNN
F 2 "" V 1930 7050 50  0000 C CNN
F 3 "" H 2000 7050 50  0000 C CNN
	1    2000 7050
	1    0    0    -1  
$EndComp
$Comp
L R R5
U 1 1 5A4584BC
P 2600 7050
F 0 "R5" V 2680 7050 50  0000 C CNN
F 1 "1k" V 2600 7050 50  0000 C CNN
F 2 "" V 2530 7050 50  0000 C CNN
F 3 "" H 2600 7050 50  0000 C CNN
	1    2600 7050
	1    0    0    -1  
$EndComp
$Comp
L Jumper_NO_Small A5
U 1 1 5A458C1B
P 4650 5750
F 0 "A5" H 4650 5830 50  0000 C CNN
F 1 "Jumper_NO_Small" H 4660 5690 50  0001 C CNN
F 2 "" H 4650 5750 50  0000 C CNN
F 3 "" H 4650 5750 50  0000 C CNN
	1    4650 5750
	1    0    0    -1  
$EndComp
$Comp
L +3.3V #PWR020
U 1 1 5A459AE3
P 1400 5100
F 0 "#PWR020" H 1400 4950 50  0001 C CNN
F 1 "+3.3V" H 1400 5240 50  0000 C CNN
F 2 "" H 1400 5100 50  0000 C CNN
F 3 "" H 1400 5100 50  0000 C CNN
	1    1400 5100
	1    0    0    -1  
$EndComp
Wire Wire Line
	6050 3600 6050 3950
Wire Wire Line
	6050 3950 4500 3950
Wire Wire Line
	4500 3950 4500 4300
Wire Wire Line
	4500 4300 4650 4300
Wire Wire Line
	6050 2050 6050 2350
Wire Wire Line
	6050 2350 4500 2350
Wire Wire Line
	4500 2350 4500 2700
Wire Wire Line
	4500 2700 4650 2700
Wire Wire Line
	4650 1350 4450 1350
Wire Wire Line
	4450 1350 4450 4500
Wire Wire Line
	4450 2900 4650 2900
Wire Wire Line
	4450 4500 4650 4500
Connection ~ 4450 2900
Wire Wire Line
	4400 4800 4650 4800
Wire Wire Line
	4400 1650 4400 4800
Wire Wire Line
	4400 3200 4650 3200
Wire Wire Line
	4650 1650 4400 1650
Connection ~ 4400 3200
Wire Wire Line
	4650 4900 4600 4900
Wire Wire Line
	4600 4900 4600 5000
Wire Wire Line
	4600 3450 4600 3300
Wire Wire Line
	4600 3300 4650 3300
Wire Wire Line
	4600 1900 4600 1750
Wire Wire Line
	4600 1750 4650 1750
Wire Wire Line
	4650 1450 4150 1450
Wire Wire Line
	4150 1100 4150 4600
Wire Wire Line
	4150 3000 4650 3000
Connection ~ 4150 1450
Wire Wire Line
	4150 4600 4650 4600
Connection ~ 4150 3000
Wire Wire Line
	4650 1150 4200 1150
Wire Wire Line
	4200 1150 4200 1350
Wire Wire Line
	4200 1350 1600 1350
Wire Wire Line
	1600 1350 1600 3000
Wire Wire Line
	1600 3000 1750 3000
Wire Wire Line
	1750 3100 1650 3100
Wire Wire Line
	1650 3100 1650 1550
Wire Wire Line
	1650 1550 4450 1550
Connection ~ 4450 1550
Wire Wire Line
	2250 3100 4400 3100
Connection ~ 4400 3100
Wire Wire Line
	2250 2400 4150 2400
Connection ~ 4150 2400
Wire Wire Line
	2250 2600 2800 2600
Wire Wire Line
	2800 2600 2800 2650
Wire Wire Line
	3000 1100 3000 1150
Wire Wire Line
	3000 1150 3200 1150
Wire Wire Line
	3200 1150 3200 1100
Wire Wire Line
	2050 1050 2050 1000
Wire Wire Line
	2050 1000 2400 1000
Wire Wire Line
	2400 1000 2400 1050
Wire Wire Line
	6050 1150 6950 1150
Wire Wire Line
	6050 1250 6950 1250
Wire Wire Line
	6050 1350 6950 1350
Wire Wire Line
	6050 1450 6950 1450
Wire Wire Line
	6050 1550 6950 1550
Wire Wire Line
	6050 1650 6950 1650
Wire Wire Line
	6050 1750 6950 1750
Wire Wire Line
	6050 1850 6950 1850
Wire Wire Line
	6800 2000 6800 1950
Wire Wire Line
	6800 1950 6950 1950
Wire Wire Line
	6050 2700 6950 2700
Wire Wire Line
	6050 2800 6950 2800
Wire Wire Line
	6050 2900 6950 2900
Wire Wire Line
	6050 3000 6950 3000
Wire Wire Line
	6050 3100 6950 3100
Wire Wire Line
	6050 3200 6950 3200
Wire Wire Line
	6050 3300 6950 3300
Wire Wire Line
	6050 3400 6950 3400
Wire Wire Line
	6050 4300 6950 4300
Wire Wire Line
	6050 4400 6950 4400
Wire Wire Line
	6050 4500 6950 4500
Wire Wire Line
	6050 4600 6950 4600
Wire Wire Line
	6800 4800 6800 4700
Wire Wire Line
	6800 4700 6950 4700
Wire Wire Line
	6050 4700 6650 4700
Wire Wire Line
	6650 4700 6650 5100
Wire Wire Line
	6650 5100 6950 5100
Wire Wire Line
	6050 4800 6600 4800
Wire Wire Line
	6600 4800 6600 5200
Wire Wire Line
	6600 5200 6950 5200
Wire Wire Line
	6050 4900 6550 4900
Wire Wire Line
	6550 4900 6550 5300
Wire Wire Line
	6550 5300 6950 5300
Wire Wire Line
	6050 5000 6500 5000
Wire Wire Line
	6500 5000 6500 5400
Wire Wire Line
	6500 5400 6950 5400
Wire Wire Line
	6800 5600 6800 5500
Wire Wire Line
	6800 5500 6950 5500
Wire Wire Line
	6800 3600 6800 3500
Wire Wire Line
	6800 3500 6950 3500
Wire Wire Line
	2200 900  2200 1000
Connection ~ 2200 1000
Wire Wire Line
	3100 900  3100 1150
Connection ~ 3100 1150
Wire Wire Line
	1750 2500 1500 2500
Wire Wire Line
	4200 5450 4400 5450
Wire Wire Line
	4200 5550 4300 5550
Wire Wire Line
	1450 2600 1750 2600
Wire Wire Line
	1200 2250 1200 2400
Wire Wire Line
	850  2400 1750 2400
Wire Wire Line
	850  2300 850  2400
Connection ~ 1200 2400
Wire Wire Line
	2350 5450 2700 5450
Wire Wire Line
	2150 5550 2700 5550
Wire Wire Line
	1950 5650 2700 5650
Wire Wire Line
	1750 5750 2700 5750
Wire Wire Line
	2550 5350 2700 5350
Wire Wire Line
	2600 6900 2600 5350
Connection ~ 2600 5350
Wire Wire Line
	2450 6900 2450 5450
Connection ~ 2450 5450
Wire Wire Line
	2300 6900 2300 5550
Connection ~ 2300 5550
Wire Wire Line
	2150 6900 2150 5650
Connection ~ 2150 5650
Wire Wire Line
	2000 6900 2000 5750
Connection ~ 2000 5750
Wire Wire Line
	2000 7200 2000 7350
Wire Wire Line
	2000 7350 2700 7350
Wire Wire Line
	2600 7350 2600 7200
Wire Wire Line
	2250 7450 2250 7350
Connection ~ 2250 7350
Wire Wire Line
	2150 7200 2150 7350
Connection ~ 2150 7350
Wire Wire Line
	2300 7200 2300 7350
Connection ~ 2300 7350
Wire Wire Line
	2450 7200 2450 7350
Connection ~ 2450 7350
Wire Wire Line
	1550 5750 1400 5750
Wire Wire Line
	1400 5750 1400 5100
Wire Wire Line
	1750 5650 1400 5650
Connection ~ 1400 5650
Wire Wire Line
	1950 5550 1400 5550
Connection ~ 1400 5550
Wire Wire Line
	2150 5450 1400 5450
Connection ~ 1400 5450
Wire Wire Line
	2350 5350 1400 5350
Connection ~ 1400 5350
$Comp
L R R6
U 1 1 5A45A268
P 4450 6950
F 0 "R6" V 4530 6950 50  0000 C CNN
F 1 "1k" V 4450 6950 50  0000 C CNN
F 2 "" V 4380 6950 50  0000 C CNN
F 3 "" H 4450 6950 50  0000 C CNN
	1    4450 6950
	1    0    0    -1  
$EndComp
Wire Wire Line
	4200 5750 4550 5750
Wire Wire Line
	4450 6800 4450 5750
Connection ~ 4450 5750
Wire Wire Line
	4200 5850 4300 5850
Wire Wire Line
	4300 5650 4300 7150
Wire Wire Line
	4200 5650 4300 5650
Connection ~ 4300 5850
Wire Wire Line
	4300 7100 4450 7100
Connection ~ 4300 7100
$Comp
L +3.3V #PWR021
U 1 1 5A45A7F2
P 4850 5500
F 0 "#PWR021" H 4850 5350 50  0001 C CNN
F 1 "+3.3V" H 4850 5640 50  0000 C CNN
F 2 "" H 4850 5500 50  0000 C CNN
F 3 "" H 4850 5500 50  0000 C CNN
	1    4850 5500
	1    0    0    -1  
$EndComp
Wire Wire Line
	4850 5750 4750 5750
Wire Wire Line
	2700 7350 2700 6650
Connection ~ 2600 7350
$Comp
L CONN_01X03 P1
U 1 1 5A45BBC9
P 700 4850
F 0 "P1" H 700 5050 50  0000 C CNN
F 1 "CONN_01X03" V 800 4850 50  0000 C CNN
F 2 "" H 700 4850 50  0000 C CNN
F 3 "" H 700 4850 50  0000 C CNN
	1    700  4850
	-1   0    0    1   
$EndComp
$Comp
L CONN_01X03 P2
U 1 1 5A45BCA4
P 700 5350
F 0 "P2" H 700 5550 50  0000 C CNN
F 1 "CONN_01X03" V 800 5350 50  0000 C CNN
F 2 "" H 700 5350 50  0000 C CNN
F 3 "" H 700 5350 50  0000 C CNN
	1    700  5350
	-1   0    0    1   
$EndComp
$Comp
L CONN_01X03 P3
U 1 1 5A45BCFD
P 700 5850
F 0 "P3" H 700 6050 50  0000 C CNN
F 1 "CONN_01X03" V 800 5850 50  0000 C CNN
F 2 "" H 700 5850 50  0000 C CNN
F 3 "" H 700 5850 50  0000 C CNN
	1    700  5850
	-1   0    0    1   
$EndComp
$Comp
L CONN_01X03 P4
U 1 1 5A45C135
P 700 6400
F 0 "P4" H 700 6600 50  0000 C CNN
F 1 "CONN_01X03" V 800 6400 50  0000 C CNN
F 2 "" H 700 6400 50  0000 C CNN
F 3 "" H 700 6400 50  0000 C CNN
	1    700  6400
	-1   0    0    1   
$EndComp
Wire Wire Line
	900  4750 1350 4750
Wire Wire Line
	900  5250 1250 5250
Wire Wire Line
	1250 5250 1250 5950
Wire Wire Line
	1250 5950 2700 5950
Wire Wire Line
	900  5750 1300 5750
Wire Wire Line
	1300 5750 1300 6050
Wire Wire Line
	1300 6050 2700 6050
Wire Wire Line
	1350 4750 1350 5850
Wire Wire Line
	1350 5850 2700 5850
Wire Wire Line
	900  6300 1300 6300
Wire Wire Line
	1300 6300 1300 6150
Wire Wire Line
	1300 6150 2700 6150
NoConn ~ 2700 6250
NoConn ~ 2700 6350
NoConn ~ 2700 6450
NoConn ~ 2700 6550
NoConn ~ 4200 5950
NoConn ~ 4200 6050
NoConn ~ 4200 6150
NoConn ~ 4200 6250
NoConn ~ 4200 6350
NoConn ~ 4200 6450
NoConn ~ 4200 6550
NoConn ~ 4200 6650
$Comp
L GND #PWR022
U 1 1 5A45CCD0
P 1000 6700
F 0 "#PWR022" H 1000 6450 50  0001 C CNN
F 1 "GND" H 1000 6550 50  0000 C CNN
F 2 "" H 1000 6700 50  0000 C CNN
F 3 "" H 1000 6700 50  0000 C CNN
	1    1000 6700
	1    0    0    -1  
$EndComp
Wire Wire Line
	900  4950 1000 4950
Wire Wire Line
	1000 4950 1000 6700
Wire Wire Line
	900  5450 1000 5450
Connection ~ 1000 5450
Wire Wire Line
	900  5950 1000 5950
Connection ~ 1000 5950
Wire Wire Line
	900  6500 1000 6500
Connection ~ 1000 6500
$Comp
L CONN_01X02 P5
U 1 1 5A45D082
P 700 7250
F 0 "P5" H 700 7400 50  0000 C CNN
F 1 "CONN_01X02" V 800 7250 50  0000 C CNN
F 2 "" H 700 7250 50  0000 C CNN
F 3 "" H 700 7250 50  0000 C CNN
	1    700  7250
	-1   0    0    1   
$EndComp
$Comp
L GND #PWR023
U 1 1 5A45D14F
P 1250 7600
F 0 "#PWR023" H 1250 7350 50  0001 C CNN
F 1 "GND" H 1250 7450 50  0000 C CNN
F 2 "" H 1250 7600 50  0000 C CNN
F 3 "" H 1250 7600 50  0000 C CNN
	1    1250 7600
	1    0    0    -1  
$EndComp
$Comp
L CP1 C1
U 1 1 5A45D197
P 1250 7350
F 0 "C1" H 1275 7450 50  0000 L CNN
F 1 "470uf" H 1275 7250 50  0000 L CNN
F 2 "" H 1250 7350 50  0000 C CNN
F 3 "" H 1250 7350 50  0000 C CNN
	1    1250 7350
	1    0    0    -1  
$EndComp
Wire Wire Line
	900  7200 1250 7200
Wire Wire Line
	900  7300 900  7600
Wire Wire Line
	900  7600 1250 7600
Wire Wire Line
	1250 7600 1250 7500
Wire Wire Line
	900  4850 1150 4850
Wire Wire Line
	1150 4850 1150 7200
Connection ~ 1150 7200
Wire Wire Line
	900  5350 1150 5350
Connection ~ 1150 5350
Wire Wire Line
	900  5850 1150 5850
Connection ~ 1150 5850
Wire Wire Line
	900  6400 1150 6400
Connection ~ 1150 6400
Wire Wire Line
	4200 5350 4700 5350
Wire Wire Line
	4700 5350 4700 5600
Wire Wire Line
	4700 5600 4850 5600
Wire Wire Line
	4850 5500 4850 5750
Connection ~ 4850 5600
Wire Wire Line
	4400 5450 4400 4900
Wire Wire Line
	4400 4900 1500 4900
Wire Wire Line
	1500 4900 1500 2500
Wire Wire Line
	1450 2600 1450 4850
Wire Wire Line
	1450 4850 4300 4850
Wire Wire Line
	4300 4850 4300 5550
$EndSCHEMATC