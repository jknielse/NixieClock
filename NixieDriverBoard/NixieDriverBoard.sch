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
LIBS:NixieComponentLibrary
LIBS:russian-nixies
LIBS:NixieDriverBoard-cache
EELAYER 25 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 1 1
Title ""
Date ""
Rev ""
Comp ""
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
$Comp
L K155ID1 K155ID2
U 1 1 5637AE09
P 7800 4450
F 0 "K155ID2" H 7800 4450 60  0000 C CNN
F 1 "K155ID1" H 7750 4150 60  0000 C CNN
F 2 "Housings_DIP:DIP-16_W7.62mm_LongPads" H 7800 4450 60  0001 C CNN
F 3 "" H 7800 4450 60  0000 C CNN
	1    7800 4450
	1    0    0    -1  
$EndComp
$Comp
L K155ID1 K155ID1
U 1 1 5637AF66
P 7800 2900
F 0 "K155ID1" H 7800 2900 60  0000 C CNN
F 1 "K155ID1" H 7750 2600 60  0000 C CNN
F 2 "Housings_DIP:DIP-16_W7.62mm_LongPads" H 7800 2900 60  0001 C CNN
F 3 "" H 7800 2900 60  0000 C CNN
	1    7800 2900
	1    0    0    -1  
$EndComp
$Comp
L 74HC595 74HC1
U 1 1 5637B051
P 5600 3650
F 0 "74HC1" H 5750 4250 70  0000 C CNN
F 1 "74HC595" H 5600 3050 70  0000 C CNN
F 2 "Housings_DIP:DIP-16_W7.62mm_LongPads" H 5600 3650 60  0001 C CNN
F 3 "" H 5600 3650 60  0000 C CNN
	1    5600 3650
	1    0    0    -1  
$EndComp
$Comp
L CONN_01X12 NIXIE1
U 1 1 5637B08A
P 9500 2900
F 0 "NIXIE1" H 9500 3550 50  0000 C CNN
F 1 "NIXIE (1)" V 9600 2900 50  0000 C CNN
F 2 "Socket_Strips:Socket_Strip_Straight_1x12" H 9500 2900 60  0001 C CNN
F 3 "" H 9500 2900 60  0000 C CNN
	1    9500 2900
	1    0    0    -1  
$EndComp
$Comp
L CONN_01X12 NIXIE2
U 1 1 5637B112
P 9500 4450
F 0 "NIXIE2" H 9500 5100 50  0000 C CNN
F 1 "NIXIE (2)" V 9600 4450 50  0000 C CNN
F 2 "Socket_Strips:Socket_Strip_Straight_1x12" H 9500 4450 60  0001 C CNN
F 3 "" H 9500 4450 60  0000 C CNN
	1    9500 4450
	1    0    0    -1  
$EndComp
$Comp
L CONN_01X06 CONN1
U 1 1 5637B173
P 3200 5000
F 0 "CONN1" H 3200 5350 50  0000 C CNN
F 1 "CONN_01X06" V 3300 5000 50  0000 C CNN
F 2 "Socket_Strips:Socket_Strip_Angled_1x06" H 3200 5000 60  0001 C CNN
F 3 "" H 3200 5000 60  0000 C CNN
	1    3200 5000
	-1   0    0    1   
$EndComp
$Comp
L CONN_01X06 CONN2
U 1 1 5637B2FA
P 4400 5000
F 0 "CONN2" H 4400 5350 50  0000 C CNN
F 1 "CONN_01X06" V 4500 5000 50  0000 C CNN
F 2 "Socket_Strips:Socket_Strip_Angled_1x06" H 4400 5000 60  0001 C CNN
F 3 "" H 4400 5000 60  0000 C CNN
	1    4400 5000
	1    0    0    1   
$EndComp
Text Label 2500 2900 0    60   ~ 0
VCC
Text Label 2500 2750 0    60   ~ 0
VDD
Text Label 2500 2600 0    60   ~ 0
GND
Text Label 2500 2450 0    60   ~ 0
DATA
Text Label 2500 2300 0    60   ~ 0
CLK
Text Label 2500 2150 0    60   ~ 0
PROP
NoConn ~ 9300 3450
NoConn ~ 9300 5000
$Comp
L VCC #PWR01
U 1 1 5639017D
P 3300 3200
F 0 "#PWR01" H 3300 3050 50  0001 C CNN
F 1 "VCC" H 3300 3350 50  0000 C CNN
F 2 "" H 3300 3200 60  0000 C CNN
F 3 "" H 3300 3200 60  0000 C CNN
	1    3300 3200
	-1   0    0    1   
$EndComp
$Comp
L VDD #PWR02
U 1 1 563901A6
P 3100 3200
F 0 "#PWR02" H 3100 3050 50  0001 C CNN
F 1 "VDD" H 3100 3350 50  0000 C CNN
F 2 "" H 3100 3200 60  0000 C CNN
F 3 "" H 3100 3200 60  0000 C CNN
	1    3100 3200
	-1   0    0    1   
$EndComp
$Comp
L GND #PWR03
U 1 1 563901EB
P 2900 3200
F 0 "#PWR03" H 2900 2950 50  0001 C CNN
F 1 "GND" H 2900 3050 50  0000 C CNN
F 2 "" H 2900 3200 60  0000 C CNN
F 3 "" H 2900 3200 60  0000 C CNN
	1    2900 3200
	1    0    0    -1  
$EndComp
$Comp
L R R1
U 1 1 56390499
P 8900 2350
F 0 "R1" V 8980 2350 50  0000 C CNN
F 1 "R" V 8900 2350 50  0000 C CNN
F 2 "Resistors_ThroughHole:Resistor_Horizontal_RM15mm" V 8830 2350 30  0001 C CNN
F 3 "" H 8900 2350 30  0000 C CNN
	1    8900 2350
	0    1    1    0   
$EndComp
$Comp
L R R2
U 1 1 563904EC
P 8900 3900
F 0 "R2" V 8980 3900 50  0000 C CNN
F 1 "R" V 8900 3900 50  0000 C CNN
F 2 "Resistors_ThroughHole:Resistor_Horizontal_RM15mm" V 8830 3900 30  0001 C CNN
F 3 "" H 8900 3900 30  0000 C CNN
	1    8900 3900
	0    1    1    0   
$EndComp
$Comp
L PWR_FLAG #FLG04
U 1 1 56391105
P 2300 2600
F 0 "#FLG04" H 2300 2695 50  0001 C CNN
F 1 "PWR_FLAG" H 2300 2780 50  0000 C CNN
F 2 "" H 2300 2600 60  0000 C CNN
F 3 "" H 2300 2600 60  0000 C CNN
	1    2300 2600
	-1   0    0    -1  
$EndComp
$Comp
L PWR_FLAG #FLG05
U 1 1 56391132
P 2250 2750
F 0 "#FLG05" H 2250 2845 50  0001 C CNN
F 1 "PWR_FLAG" H 2250 2930 50  0000 C CNN
F 2 "" H 2250 2750 60  0000 C CNN
F 3 "" H 2250 2750 60  0000 C CNN
	1    2250 2750
	-1   0    0    -1  
$EndComp
$Comp
L PWR_FLAG #FLG06
U 1 1 56391158
P 2200 2900
F 0 "#FLG06" H 2200 2995 50  0001 C CNN
F 1 "PWR_FLAG" H 2200 3080 50  0000 C CNN
F 2 "" H 2200 2900 60  0000 C CNN
F 3 "" H 2200 2900 60  0000 C CNN
	1    2200 2900
	-1   0    0    -1  
$EndComp
Wire Wire Line
	2200 2900 3500 2900
Wire Wire Line
	3500 2900 3500 4750
Wire Wire Line
	3400 4750 4200 4750
Connection ~ 3500 4750
Wire Wire Line
	2250 2750 5500 2750
Wire Wire Line
	3600 2750 3600 4850
Wire Wire Line
	3400 4850 4200 4850
Connection ~ 3600 4850
Wire Wire Line
	2300 2600 3700 2600
Wire Wire Line
	3700 2600 3700 4950
Wire Wire Line
	3400 4950 4200 4950
Connection ~ 3700 4950
Wire Wire Line
	2500 2450 3800 2450
Wire Wire Line
	3800 2450 3800 5050
Wire Wire Line
	3800 5050 3400 5050
Wire Wire Line
	2500 2300 3900 2300
Wire Wire Line
	3900 2300 3900 5150
Wire Wire Line
	3400 5150 4200 5150
Connection ~ 3900 5150
Wire Wire Line
	2500 2150 4000 2150
Wire Wire Line
	4000 2150 4000 5250
Wire Wire Line
	3400 5250 4200 5250
Connection ~ 4000 5250
Wire Wire Line
	6300 4100 6300 4600
Wire Wire Line
	6300 4600 4100 4600
Wire Wire Line
	4100 4600 4100 5050
Wire Wire Line
	4100 5050 4200 5050
Wire Wire Line
	3500 3500 4900 3500
Connection ~ 3500 3500
Wire Wire Line
	3800 3200 4900 3200
Connection ~ 3800 3200
Wire Wire Line
	4000 3700 4900 3700
Connection ~ 4000 3700
Wire Wire Line
	4900 3800 3700 3800
Connection ~ 3700 3800
Wire Wire Line
	4900 3400 3900 3400
Connection ~ 3900 3400
Wire Wire Line
	6300 3200 6300 2750
Wire Wire Line
	6300 2750 7200 2750
Wire Wire Line
	6300 3300 6400 3300
Wire Wire Line
	6400 3300 6400 2850
Wire Wire Line
	6400 2850 7200 2850
Wire Wire Line
	6300 3400 6500 3400
Wire Wire Line
	6500 3400 6500 2950
Wire Wire Line
	6500 2950 7200 2950
Wire Wire Line
	6300 3500 6600 3500
Wire Wire Line
	6600 3500 6600 3050
Wire Wire Line
	6600 3050 7200 3050
Wire Wire Line
	6300 3900 6400 3900
Wire Wire Line
	6400 3900 6400 4600
Wire Wire Line
	6400 4600 7200 4600
Wire Wire Line
	6300 3800 6500 3800
Wire Wire Line
	6500 3800 6500 4500
Wire Wire Line
	6500 4500 7200 4500
Wire Wire Line
	6300 3700 6600 3700
Wire Wire Line
	6600 3700 6600 4400
Wire Wire Line
	6600 4400 7200 4400
Wire Wire Line
	6300 3600 6700 3600
Wire Wire Line
	6700 3600 6700 4300
Wire Wire Line
	6700 4300 7200 4300
Wire Wire Line
	5500 2750 5500 2200
Connection ~ 3600 2750
Wire Wire Line
	8400 2450 9300 2450
Wire Wire Line
	8400 2550 9300 2550
Wire Wire Line
	8400 2650 9300 2650
Wire Wire Line
	8400 2750 9300 2750
Wire Wire Line
	8400 2850 9300 2850
Wire Wire Line
	8400 2950 9300 2950
Wire Wire Line
	8400 3050 9300 3050
Wire Wire Line
	8400 3150 9300 3150
Wire Wire Line
	8400 3250 9300 3250
Wire Wire Line
	8400 3350 9300 3350
Wire Wire Line
	8400 4000 9300 4000
Wire Wire Line
	8400 4100 9300 4100
Wire Wire Line
	8400 4200 9300 4200
Wire Wire Line
	8400 4300 9300 4300
Wire Wire Line
	8400 4400 9300 4400
Wire Wire Line
	8400 4500 9300 4500
Wire Wire Line
	8400 4600 9300 4600
Wire Wire Line
	8400 4700 9300 4700
Wire Wire Line
	8400 4800 9300 4800
Wire Wire Line
	8400 4900 9300 4900
Wire Wire Line
	3100 2750 3100 3200
Connection ~ 3100 2750
Wire Wire Line
	3300 2900 3300 3200
Connection ~ 3300 2900
Wire Wire Line
	2900 2600 2900 3200
Connection ~ 2900 2600
Wire Wire Line
	5500 2200 8650 2200
Wire Wire Line
	8650 2200 8650 3900
Wire Wire Line
	8650 3900 8750 3900
Wire Wire Line
	8650 2350 8750 2350
Connection ~ 8650 2350
Wire Wire Line
	9050 2350 9300 2350
Wire Wire Line
	9050 3900 9300 3900
$EndSCHEMATC
